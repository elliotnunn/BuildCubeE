#!/usr/bin/env python3

import argparse
import os
import os.path as path
import tempfile
import datetime as dt
import time
import subprocess as sp
import shutil
import re

########################################################################
# Logs

curstage = 0
NSTAGES = 7

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
	if n.startswith('.'): return False
	if n.upper().endswith('.DMG'): return False
	return True

g_filetree = []
g_reztree = []
for dirpath, dirnames, filenames in os.walk('.'):
	dirnames[:] = list(filter(includefilter, dirnames))
	filenames[:] = list(filter(includefilter, filenames))
	for f in filenames:
		p = path.join(dirpath, f).lstrip('./')
		if p.endswith('.RezDump'):
			g_reztree.append(p)
			p = p.rpartition('.')[0]
		g_filetree.append(p)
g_filetree = sorted(set(g_filetree))

print('Got %d files' % len(g_filetree))

########################################################################

nextstage('Classifying files')

g_fileclass = {}
for f in g_filetree:
	ext = os.path.splitext(f)[1].lower()
	if ext in ['.o', '.lib']:
		inf = 'MPS OBJ '
	elif ext in ['.txt', '.a', '.c']:
		inf = 'MPS TEXT'
	elif f.startswith('Tools/'):
		inf = 'MPS MPST'
	else:
		inf = 'MPS TEXT'
	g_fileclass[f] = inf

########################################################################

nextstage('Dating files')

def trytime(p):
	t = []
	try:
		t.append(path.getmtime(p))
	except FileNotFoundError:
		pass
	try:
		t.append(path.getmtime(p + '.RezDump'))
	except FileNotFoundError:
		pass
	return max(t)

def datefiles(files):
	tsbase = time.mktime(dt.date(1993, 12, 20).timetuple())

	f2ts = {f: trytime(f) for f in files}
	idx2ts = enumerate(sorted(set(f2ts.values())))
	ts2idx = {ts: idx for (idx, ts) in idx2ts}
	return {f: tsbase + 60*ts2idx[ts] for (f, ts) in f2ts.items()}

g_filetime = datefiles(g_filetree)

########################################################################

nextstage('Copying to the build tree')

g_tmp = tempfile.TemporaryDirectory()
g_tmp.name = '/tmp/elmo'; os.system('rm -rf /tmp/elmo'); os.system('mkdir /tmp/elmo')

for f in g_reztree:
	d = path.dirname(f)
	if d: os.makedirs(path.join(g_tmp.name, d), exist_ok=True)

	newf = f.rpartition('.')[0]
	sp.run(['Rez', '-o', path.join(g_tmp.name, newf), f])

setfile_batch = {}
for f in g_filetree:
	d = path.dirname(f)
	if d: os.makedirs(path.join(g_tmp.name, d), exist_ok=True)

	fclass = g_fileclass[f]
	ftime = g_filetime[f]

	try:
		with open(f, 'rb') as fd:
			data = fd.read()
	except FileNotFoundError:
		pass
	else:
		if 'TEXT' in fclass:
			data = data.replace(b'\n', b'\r')

		opath = path.join(g_tmp.name, f)
		with open(opath, 'wb') as fd:
			fd.write(data)

	os.utime(opath, (ftime, ftime))
	
	if fclass not in setfile_batch: setfile_batch[fclass] = []
	setfile_batch[fclass].append(f)

for fclass, flist in setfile_batch.items():
	sp.run(['SetFile', '-c', fclass[:4], '-t', fclass[4:], *flist], cwd=g_tmp.name)

########################################################################

nextstage('Creating BuildResults')

for dname in ['Image', 'Lib', 'Obj', 'Rsrc', 'Text']:
	os.makedirs(path.join(g_tmp.name, 'BuildResults', args.maker, dname), exist_ok=True)

########################################################################

nextstage('Splicing amphibian DNA into makefiles')

OVERDIR = 'Amphibian'

try:
	overs = os.listdir(path.join(g_tmp.name, OVERDIR))
	if not overs: raise FileNotFoundError
except FileNotFoundError:
	pass
else:
	overs_re = '|'.join(re.escape(x) for x in overs)
	overs_re = rb'^[^#\s]*\b(Thing.lib)"?\s*\xC4\s*'.replace(b'Thing.lib', overs_re.encode('ascii'))
	overs_re = re.compile(overs_re, re.IGNORECASE)

	failed = list(overs)

	for f in g_filetree:
		if not f.upper().endswith('.MAKE'): continue
		with open(path.join(g_tmp.name, f), 'rb') as fd:
			mfile = fd.read().split(b'\r')

		havechanged = False
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
			with open(path.join(g_tmp.name, f), 'wb') as fd:
				fd.write(b'\r'.join(newmfile))

	if failed: # try to find where these override files with *no build rule* should go
		found_locations = {k: [] for k in failed}

		overs_re = '|'.join(re.escape(x) for x in failed)
		overs_re = rb'^[^#]*"({\w+}(?:\w+:)*)(Thing.lib)"'.replace(b'Thing.lib', overs_re.encode('ascii'))
		overs_re = re.compile(overs_re, re.IGNORECASE)

		for f in g_filetree:
			if not f.upper().endswith('.MAKE'): continue
			with open(path.join(g_tmp.name, f), 'rb') as fd:
				mfile = fd.read().split(b'\r')

			for line in mfile:
				m = overs_re.match(line)
				if m:
					orig_name = next(x for x in failed if x.upper() == m.group(2).decode('ascii').upper())
					found_loc = m.group(1)+m.group(2)
					if found_loc.upper() not in (x.upper() for x in found_locations[orig_name]):
						found_locations[orig_name].append(found_loc)

		with open(path.join(g_tmp.name, 'Make', 'RISC.make'), 'ab') as fd:
			fd.write(b'\r# Rules created at build time by %s\r' % path.basename(__file__).encode('ascii'))
			for orig_name, found_locs in found_locations.items():
				if len(found_locs) == 1:
					failed = [x for x in failed if x != orig_name]
					fd.write(found_locs[0])
					fd.write(b' \xC4 {Sources}%s:%s\r' % (OVERDIR.encode('ascii'), orig_name.encode('ascii')))
					fd.write(b'\tDuplicate -y {Deps} {Targ}\r')

	print('Successfully edited: %d; Failed: %s' % (len(overs) - len(failed), ' '.join(failed) or 'none'))

########################################################################

nextstage('Running Make')

sp.run(['mpw', 'Make', '-f', ':Make:RISC.make', '-d', 'Sources=:'], cwd=g_tmp.name)



