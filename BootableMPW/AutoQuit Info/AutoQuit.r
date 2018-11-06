/*
	AutoQuit.r

	Copyright (C) 2004 Paul Pratt

	You can redistribute this file and/or modify it under the terms
	of version 2 of the GNU General Public License as published by
	the Free Software Foundation.  You should have received a copy
	of the license along with this file; see the file COPYING.

	This file is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	license for more details.
*/

#include "Types.r"
#include "Icons.r"

#define kStrVersion "1.1.1"
#define kMajorVersion 1
#define kMinorVersion 1
#define kMinorSubVersion 1

#define kStrCopyrightYear "2012"

resource 'vers' (1) {
	kMajorVersion,
	kMinorVersion * 16 + kMinorSubVersion,
	release,
	0x0,
	0,
	kStrVersion,
	kStrVersion ", © " kStrCopyrightYear " Paul C. Pratt."
};

/*
	for SIZE flags, just pretend it's a normal
	application. i.e. it would act normally, if
	it didn't quit immediately after launch.
*/

resource 'SIZE' (-1) {
	reserved,
	acceptSuspendResumeEvents,
	reserved,
	canBackground,
	multiFinderAware,
	backgroundAndForeground,
	dontGetFrontClicks,
	ignoreChildDiedEvents,
	is32BitCompatible,
	isHighLevelEventAware,
	localAndRemoteHLEvents,
	isStationeryAware,
	useTextEditServices,
	reserved,
	reserved,
	reserved,
	65536,
	65536
};
