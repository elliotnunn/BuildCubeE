#!/usr/bin/env python3

import argparse
import os
import os.path as path
import re
from machfs import Volume, Folder, File
import resourcefork

########################################################################
# Logs

curstage = 0
NSTAGES = 5

def nextstage(name):
	global curstage
	curstage += 1
	print('[CubeE build %d/%d] %s' % (curstage, NSTAGES, name))

########################################################################
# Argparse

args = argparse.ArgumentParser()
args.add_argument('-v --verbose', action='store_true', help='List every file rather than summaries')
args = args.parse_args()
args.maker = 'RISC'

########################################################################

nextstage('Walking source tree')

def includefilter(n):
	if n.endswith('.rdump'): return True
	if n.endswith('.idump'): return True
	if n.startswith('.'): return False
	if n.upper().endswith('.DMG'): return False
	return True

def mkbasename(n):
	if n.endswith('.rdump'): return n[:-6]
	if n.endswith('.idump'): return n[:-6]
	return n

g_volume = Volume()
g_volume.name = 'MacStoopid'
tmptree = {'.': g_volume}

for dirpath, dirnames, filenames in os.walk('.'):
	dirnames[:] = list(filter(includefilter, dirnames))
	filenames[:] = list(filter(includefilter, filenames))

	for dn in dirnames:
		newdir = Folder()
		tmptree[dirpath][dn] = newdir
		tmptree[path.join(dirpath, dn)] = newdir

	for fn in filenames:
		basename = mkbasename(fn)
		fullbase = path.join(dirpath, basename)
		fullpath = path.join(dirpath, fn)

		thefile = tmptree.get(fullbase, File())

		try:
			thefile.monkeypatch_mtime
		except AttributeError:
			thefile.monkeypatch_mtime = 0

		if fn.endswith('.idump'):
			with open(fullpath, 'rb') as f:
				thefile.type = f.read(4)
				thefile.creator = f.read(4)
		elif fn.endswith('rdump'):
			rez = open(fullpath, 'rb').read()
			resources = resourcefork.iter_from_rezfile(rez)
			resfork = resourcefork.rsrcfork_from_iter(resources)
			thefile.rsrc = resfork
		else:
			thefile.data = open(fullpath, 'rb').read()

		thefile.monkeypatch_mtime = max(thefile.monkeypatch_mtime, path.getmtime(fullpath))

		tmptree[dirpath][basename] = thefile
		tmptree[fullbase] = thefile

for pathtpl, obj in g_volume.iter_paths():
	try:
		if obj.type == b'TEXT':
			obj.data = obj.data.decode('utf8').replace('\n', '\r').encode('mac_roman')
	except AttributeError:
		pass

########################################################################

nextstage('Dating files')

times = set()
for pathtpl, obj in g_volume.iter_paths():
	if isinstance(obj, File):
		times.add(obj.monkeypatch_mtime)

ts2idx = {ts: idx for (idx, ts) in enumerate(sorted(set(times)))}

for pathtpl, obj in g_volume.iter_paths():
	if isinstance(obj, File):
		obj.crdat = obj.mddat = 0x90000000 + 60 * ts2idx[obj.monkeypatch_mtime]

########################################################################

nextstage('Creating BuildResults')

folder_levels = [
	['BuildResults'],
	['RISC', 'ROM', 'LC930', 'dbLite'],
	['Image', 'Lib', 'Obj', 'Rsrc', 'Text'],
]

every_folder = [()]
for level in folder_levels:
	for i in reversed(range(len(every_folder))):
		every_folder[i:i+1] = (every_folder[i] + (memb,) for memb in level)

for folder_path in every_folder:
	base = g_volume
	for element in folder_path:
		nextbase = base.get(element, Folder())
		base[element] = nextbase
		base = nextbase

########################################################################

nextstage('Splicing amphibian DNA into makefiles')

OVERDIR = 'Amphibian'

try:
	overs = g_volume[OVERDIR]
except KeyError:
	pass
else:
	overs_re = '|'.join(re.escape(x) for x in overs)
	overs_re = rb'^[^#\s]*\b(Thing.lib)"?\s*\xC4\s*'.replace(b'Thing.lib', overs_re.encode('ascii'))
	overs_re = re.compile(overs_re, re.IGNORECASE)

	failed = list(overs)

	for pathtpl, obj in g_volume.iter_paths():
		if not isinstance(obj, File): continue
		if not pathtpl[-1].upper().endswith('.MAKE'): continue

		havechanged = False
		mfile = obj.data.split(b'\r')
		newmfile = []

		idx = -1
		while idx + 1 < len(mfile):
			idx += 1
			m = overs_re.match(mfile[idx])
			if m:
				thefile = m.group(1)
				havechanged = True
				newmfile.append(b'# Rule replaced at build time by ' + path.basename(__file__).encode('ascii'))
				failed = [x for x in failed if x.upper() != thefile.decode('ascii').upper()]

				srcfile = b'{Sources}%s:%s' % (OVERDIR.encode('ascii'), thefile)
				newmfile.append(m.group(0) + srcfile)
				newmfile.append(b'\tDuplicate -y {Deps} {Targ}')

				lastidx = idx # how many "old" lines should be commented out?
				if mfile[idx].endswith(b'\xB6'):
					while lastidx + 1 < len(mfile) and mfile[lastidx + 1].endswith(b'\xB6'):
						lastidx += 1 # capture continuations of first line
				while lastidx + 1 < len(mfile) and mfile[lastidx + 1].startswith(b'\t'):
					lastidx += 1 # capture build lines starting with tab

				while idx <= lastidx:
					newmfile.append(b'#\t' + mfile[idx])
					idx += 1
			else:
				newmfile.append(mfile[idx])

		if havechanged:
			obj.data = b'\r'.join(newmfile)

	if failed: # try to find where these override files with *no build rule* should go
		found_locations = {k: [] for k in failed}

		overs_re = '|'.join(re.escape(x) for x in failed)
		overs_re = rb'^[^#]*"({\w+}(?:\w+:)*)(Thing.lib)"'.replace(b'Thing.lib', overs_re.encode('ascii'))
		overs_re = re.compile(overs_re, re.IGNORECASE)

		for pathtpl, obj in g_volume.iter_paths():
			if not isinstance(obj, File): continue
			if not pathtpl[-1].upper().endswith('.MAKE'): continue

			for line in obj.data.split(b'\r'):
				m = overs_re.match(line)
				if m:
					orig_name = next(x for x in failed if x.upper() == m.group(2).decode('ascii').upper())
					found_loc = m.group(1)+m.group(2)
					if found_loc.upper() not in (x.upper() for x in found_locations[orig_name]):
						found_locations[orig_name].append(found_loc)

		obj = g_volume['Make']['RISC.make']
		obj.data = bytearray(obj.data)
		obj.data.extend(b'\r# Rules created at build time by %s\r' % path.basename(__file__).encode('ascii'))
		for orig_name, found_locs in found_locations.items():
			if len(found_locs) == 1:
				failed = [x for x in failed if x != orig_name]
				obj.data.extend(found_locs[0])
				obj.data.extend(b' \xC4 {Sources}%s:%s\r' % (OVERDIR.encode('ascii'), orig_name.encode('ascii')))
				obj.data.extend(b'\tDuplicate -y {Deps} {Targ}\r')

	print('Successfully edited: %d. Failed: %s.' % (len(overs) - len(failed), ' '.join(failed) or 'none'))

########################################################################

nextstage('Spitting image')

open('%s.dmg' % g_volume.name, 'wb').write(g_volume.write(90*1024*1024))
