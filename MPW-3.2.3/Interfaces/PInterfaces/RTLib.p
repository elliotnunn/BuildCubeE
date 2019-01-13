{*----------------------------------------------------------------------*}
{*		RTLib.p 																				*}
{*		Created by Sandy McEntee.  Friday, April 6, 1990.						*}
{*		Copyright © 1990 Apple Computer, Inc.										*}
{*		All Rights Reserved.																*}
{*----------------------------------------------------------------------*}

{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT RTLib;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingRT}
{$SETC UsingRT := 1}

{$I+}
{$SETC RTIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := RTIncludes}


CONST
	{
			Error Codes
	}
	eRTNoErr				= 0;
	eRTBadVersion		= 2;
	eRTInvalidOp		= 4;
	eRTInvalidJTPtr	= 6;

	{
			Action Codes
	}
	kRTSysErr	= 0;
	kRTRetry		= 1;
	kRTContinue	= 2;

	{
			Runtime Operations
	}
	kRTGetVersion			= 10;
	kRTGetVersionA5		= 11;
	kRTGetJTAddress		= 12;
	kRTGetJTAddressA5		= 13;
	kRTSetPreLoad			= 14;
	kRTSetPreLoadA5		= 15;
	kRTSetSegLoadErr		= 16;
	kRTSetSegLoadErrA5	= 17;
	kRTSetPostLoad			= 18;
	kRTSetPostLoadA5		= 19;
	kRTSetPreUnload		= 20;
	kRTSetPreUnloadA5		= 21;
	kRTPreLaunch			= 22;
	kRTPostLaunch			= 23;

	{
			Version Definitions
	}
	kVERSION32BIT			= $FFFF;
	kVERSION16BIT			= $0000;
	

TYPE
	{
			RTState Definition
	}
	RTState = RECORD 
		fVersion:	INTEGER;						{ run-time version }
		fSP:			Ptr;								{ SP: &-of user return address }
		fJTAddr:		Ptr;								{ PC: &-of called jump table entry }
		fRegisters: Array[0..14] of LONGINT;	{ registers D0-D7 and A0-A6 when }
															{		_LoadSeg was called }
		fSegNo:		INTEGER;							{	segment number }
		fSegType:	ResType;							{	segment type (normally 'CODE') }
		fSegSize:	LONGINT;							{	segment size }
		fSegInCore:	BOOLEAN;							{	true if segment is in memory }
		fReserved1:	BOOLEAN;							{ (reserved for future use) }
		fOSErr:		OSErr;							{	error number }
		fReserved2:	LONGINT;							{ (reserved for future use) }
	END;
	
	RTStatePtr = ^RTState;	
	
	{
			Runtime Parameter Block
	}
	
	RTParam = (RTGetVersionParam, RTGetJTAddrParam, RTSetSegLoadParam);
	
	RTPB = RECORD 
		fOperation:		INTEGER;						{ operation }
		fA5:				Ptr;							{ A5-world }
		CASE RTParam OF
			RTGetVersionParam:
				(fVersion:	INTEGER);				{ run-time version (returned) }

			RTGetJTAddrParam:
				(fJTAddr:	Ptr;						{ ptr to jt entry }
				fCodeAddr:	Ptr);						{ code address w/i jt entry (returned) }
				
			RTSetSegLoadParam:
				(fUserHdlr:		Ptr;					{ ptr to user handler }
				fOldUserHdlr:	Ptr);					{ ptr to old user handler (returned) }
		END;
	
	RTPBPtr = ^RTPB;


FUNCTION Runtime (runtime_parms: RTPBPtr): OSErr;


{$ENDC}    { UsingRT }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

