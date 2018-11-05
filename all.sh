#!/bin/sh
./FillGaps -o /tmp/ms && MakeHFS -s 256M -n MacStoopid -i /tmp/ms --mpw-dates /tmp/ms.dmg && ~/empw/M*.app/Contents/MacOS/* /tmp/ms.dmg && DumpHFS /tmp/ms.dmg .
