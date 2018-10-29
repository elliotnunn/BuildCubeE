#!/usr/bin/env python3

from machfs import Volume, Folder, File
from resourcefork import parse_file, make_rez_code
import os.path as path
import os

with open('MacStoopid.dmg', 'rb') as f:
	v = Volume()
	v.read(f.read())

knownpaths = {}
try:
	for line in v['List of Synced Files'].data.decode('mac_roman').split('\r'):
		if line and not line.startswith('#'):
			t = int(line[:8], 16)
			p = tuple(line[9:].split(':'))
			knownpaths[p] = t
except KeyError:
	pass

written = []
for p, obj in v.iter_paths():
	if p[0] != 'BuildResults': continue

	if isinstance(obj, Folder):
		os.makedirs(path.join(*p), exist_ok=True)
	elif isinstance(obj, File) and obj.mddat != knownpaths.get(p, None):
		data = obj.data
		if obj.type == b'TEXT':
			data = data.decode('mac_roman').replace('\r', os.linesep).encode('utf8')
		if data:
			written.append(path.join(*p))
			with open(written[-1], 'wb') as f:
				f.write(data)

		rsrc = obj.rsrc
		if rsrc:
			rsrc = make_rez_code(parse_file(rsrc), ascii_clean=True)
			written.append(path.join(*p[:-1], p[-1]+'.rdump'))
			with open(written[-1], 'wb') as f:
				f.write(rsrc)

		written.append(path.join(*p[:-1], p[-1]+'.idump'))
		with open(written[-1], 'wb') as f:
			f.write(obj.type)
			f.write(obj.creator)

if written:
	t = path.getmtime(written[-1])
	for f in written:
		os.utime(f, (t, t))
