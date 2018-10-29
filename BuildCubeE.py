#!/usr/bin/env python3

import argparse
import os
import os.path as path
import re
from machfs import Volume, Folder, File
import macresources

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
			resources = macresources.parse_rez_code(rez)
			resfork = macresources.make_file(resources)
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

linelist = []

for pathtpl, obj in g_volume.iter_paths():
	if isinstance(obj, File):
		mactime = 0x90000000 + 60 * ts2idx[obj.monkeypatch_mtime]
		obj.crdat = obj.mddat = mactime
		line = '%08X %s\r' % (mactime, ':'.join(pathtpl))
		linelist.append(line.encode('mac_roman'))

if linelist:
	linelist.sort()
	sync_list = File()
	sync_list.type, sync_list.creator = b'TEXT', b'MPS '
	sync_list.data = b''.join(linelist)
	g_volume['List of Synced Files'] = sync_list

########################################################################

nextstage('Creating BuildResults')

folder_levels = [
	['BuildResults'],
	['RISC', 'ROM', 'LC930', 'dbLite'],
	['Image', 'Lib', 'Obj:Interface', 'Rsrc', 'Text'],
]

every_folder = [()]
for level in folder_levels:
	for i in reversed(range(len(every_folder))):
		every_folder[i:i+1] = (every_folder[i] + (memb,) for memb in level)

for folder_path in every_folder:
	base = g_volume
	for element in folder_path:
		for subelement in element.split(':'):
			nextbase = base.get(subelement, Folder())
			base[subelement] = nextbase
			base = nextbase

########################################################################

nextstage('Disseminating amphibian DNA through disk')

OVERDIR = 'Amphibian'

try:
	for name, obj in g_volume[OVERDIR].items():
		*subdirs, file = name.split('-')
		folder = g_volume
		for s in subdirs:
			folder = folder[s]
		folder[file] = obj
	del g_volume[OVERDIR]
except KeyError:
	pass

########################################################################

nextstage('Spitting image')

open('%s.dmg' % g_volume.name, 'wb').write(g_volume.write(90*1024*1024))
