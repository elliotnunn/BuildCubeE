/*
	AutoQuit.c

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

#include <types.h>
#include <limits.h>
#include <stddef.h>
#include <SegLoad.h>
#include <Script.h>
#include <Files.h>
#include <Devices.h>
#include <Windows.h>
#include <TextEdit.h>
#include <Dialogs.h>
#include <ShutDown.h>
#include <Traps.h>
#include <Scrap.h>

typedef unsigned long ui5b;
typedef unsigned short ui4b;
typedef unsigned char ui3b;

typedef long si5b;
typedef short si4b;
typedef char si3b;

#define NULL ((void *)0)

#define kdCtlPosition 16

#define kDSK_Block_Base 0x00F40000
#define kDSK_QuitOnEject 3

#define SonyVarsPtr 0x0134

#define kcom_checkval 0x841339E2
#define kcom_callcheck 0x5B17

#define kDiskDriverExtension 0x4C9219E6

struct MyDriverDat_R {
	ui5b zeroes[4];
	ui5b checkval;
	ui5b pokeaddr;
};
typedef struct MyDriverDat_R MyDriverDat_R;

#define DSKDat_checkval 0
#define DSKDat_extension 2
#define DSKDat_commnd 4
#define DSKDat_result 6
#define DSKDat_params 8
#define DSKDat_TotSize 32

#define kCmndFindExtnFind 1
#define kCmndFindExtnId2Code 2
#define kCmndFindExtnCount 3

#define kCmndDiskNDrives 1
#define kCmndDiskRead 2
#define kCmndDiskWrite 3
#define kCmndDiskEject 4
#define kCmndDiskGetSize 5
#define kCmndDiskGetCallBack 6
#define kCmndDiskSetCallBack 7
#define kCmndDiskQuitOnEject 8

#define kParamVersion 8

#define kParamFindExtnTheExtn 8
#define kParamFindExtnTheId 12

#define ROMBase 0x02AE

#define UTableBase 0x011C
#define UnitTableEntryCount 0x01D2
#define VCBQHead 0x358


#define get_long(x) (*((ui5b *)(x)))
#define get_word(x) (*((ui4b *)(x)))
#define get_byte(x) (*((ui3b *)(x)))
#define put_long(x, v) (*((ui5b *)(x))) = (v)
#define put_word(x, v) (*((ui4b *)(x))) = (v)
#define put_byte(x, v) (*((ui3b *)(x))) = (v)

QDGlobals qd;

static TrapType GetTrapType(short theTrap)
{
	if ((theTrap & 0x0800) != 0) {
		return ToolTrap;
	} else {
		return OSTrap;
	}
}

static short NumToolboxTraps(void)
{
	if (NGetTrapAddress(_InitGraf, ToolTrap)
		== NGetTrapAddress(0xAA6E, ToolTrap))
	{
		return 0x200;
	} else {
		return 0x400;
	}
}

static Boolean TrapAvailable(short trap_num)
{
	TrapType type;

	type = GetTrapType(trap_num);
	if (type == ToolTrap) {
		trap_num &= 0x07ff;
	}
	if (trap_num > NumToolboxTraps()) {
		return false;
	} else {
		return NGetTrapAddress(trap_num, type)
			!= NGetTrapAddress(_Unimplemented, ToolTrap);
	}

}

#define MKC_Shift 0x38

/*
	Don't have 'main', and instead have a bit of assembly
	language call 'MyStart', to avoid the glue code of
	a development environment that doesn't really support
	Macintosh 128K
*/

void MyStart(void);

void MyStart(void)
{
	ui3b theKeys[16];
	MyDriverDat_R *SonyVars;

	InitGraf((Ptr)&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(NULL);

	GetKeys(*(KeyMap *)theKeys);
	if ((theKeys[MKC_Shift / 8] & (1 << (MKC_Shift & 7))) == 0) {
		/* shift key not pressed */

		SonyVars = (MyDriverDat_R *)get_long(SonyVarsPtr);

		if ((SonyVars != NULL)
			&& ((1 & (ui5b)SonyVars) == 0)
				/* for emulators like sheepshaver */
			&& (SonyVars->zeroes[0] == 0)
			&& (SonyVars->zeroes[1] == 0)
			&& (SonyVars->zeroes[2] == 0)
			/* && (SonyVars->zeroes[3] == 0) */
			)
		{
			ui5b pokeaddr = SonyVars->pokeaddr;

			if ((SonyVars->checkval == kcom_checkval)
				&& (pokeaddr != 0))
			{
				/* have new Mini vMac extension mechanism */

				ui3b DskDatV[DSKDat_TotSize];
				ui4b DistExtnId;

				put_word(DskDatV + DSKDat_checkval, kcom_callcheck);
				put_word(DskDatV + DSKDat_extension, 0);
				put_word(DskDatV + DSKDat_commnd, kCmndFindExtnFind);
				put_long(DskDatV + kParamFindExtnTheExtn,
					kDiskDriverExtension);
				put_long(pokeaddr, (ui5b)&DskDatV);
				if (get_word(DskDatV + DSKDat_checkval) == 0) {
					DistExtnId =
						get_word(DskDatV + kParamFindExtnTheId);

					put_word(DskDatV + DSKDat_checkval, kcom_callcheck);
					put_word(DskDatV + DSKDat_extension, DistExtnId);
					put_word(DskDatV + DSKDat_commnd,
						kCmndDiskQuitOnEject);
					put_long(pokeaddr, (ui5b)&DskDatV);
				}
			} else {
				/* see if this is old Mini vMac */
				Ptr StartAddr = *(Ptr *)ROMBase;
				if (StartAddr == (Ptr)0x00400000) {
					ui5b CheckSum = get_long(StartAddr);
					if ((CheckSum == 0x4D1EEEE1)
						|| (CheckSum == 0x4D1EEAE1)
						|| (CheckSum == 0x4D1F8172))
					{
						/* this is a Mac Plus, now check for patches */
						if ((get_word(StartAddr + 3450) == 0x6022)
							&& (get_word(StartAddr + 3752) == 0x4E71)
							&& (get_word(StartAddr + 3728) == 0x4E71))
						{
							/* yes, this is old Mini vMac */
							((short *)kDSK_Block_Base)[kDSK_QuitOnEject]
								= 1;
						}
					}
				}
			}
		}
	}


	if (TrapAvailable(_ShutDown)) {
		ShutDwnPower();
	} else {
		/*
			manual shutdown, following description of Shutdown
			manager in Inside Mac Vol V.
		*/

		int i;
		ParamBlockRec r;
		ui5b *UTable = (ui5b *)get_long(UTableBase);
		ui4b UCount = get_word(UnitTableEntryCount);
		VCBPtr vcbp;
		VCBPtr nextvcbp;

		for (i = 0; i < UCount; ++i) {
			DCtlHandle h = (DCtlHandle)UTable[i];
			if (h != NULL) {
				if (((*h)->dCtlFlags & (1 << dNeedGoodBye)) != 0) {
					r.cntrlParam.ioCompletion = NULL;
					r.cntrlParam.ioVRefNum = 0;
					r.cntrlParam.ioCRefNum = (*h)->dCtlRefNum;
					r.cntrlParam.csCode = -1;
					PBControlSync(&r);
				}
			}
		}

		(void) UnloadScrap();

		vcbp = (VCBPtr)get_long(VCBQHead);

		while (vcbp != NULL) {
			nextvcbp = (VCBPtr)vcbp->qLink;
			r.ioParam.ioCompletion = NULL;
			r.ioParam.ioNamePtr = NULL;
			r.ioParam.ioVRefNum = vcbp->vcbVRefNum;
			(void) PBEject(&r);
			(void) PBUnmountVol(&r);
			vcbp = nextvcbp;
		}
		/*
			in case haven't actually quit by now.
			documentation mentions something about
			async component of PBEject.
		*/
		while (1) {
			EventRecord theEvent;
			(void)GetNextEvent(everyEvent, &theEvent);
		}
	}
}
