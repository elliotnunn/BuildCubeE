{
	File:		ActionAtomIntf.p

	Contains:	Pascal declarations for things the Installer wants to tell 
				action atoms about.

	Written by:	Bobby Carp

	Copyright:	© 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 11/5/91	RRK		Added Function prototype comment
		 <2>	 11/7/90	BAC		Adding the AAPBRec that defines the parameters an action atom
									receives.
		 <1>	 10/8/90	BAC		first checked in

	To Do:
}

UNIT ActionAtomIntf;

INTERFACE

TYPE
	{ A parameter passed to the action atom tells whether it is being executed before installation }
	{ takes place, after it has taken place, or we're being called after the user hit cancel or stop. }

	InstallationStage = (before, after, cleanUpCancel);
	
	{ The action atom param block record contains all of the parameters that action atoms }
	{ receive.  The first (and only) parameter to action atoms is a ptr to this block (AAPBRecPtr) }
	
	AAPBRecPtr = ^AAPBRec;
	AAPBRec = RECORD
		targetVRefNum:		INTEGER;
		blessedDirID:		LONGINT;
		aaRefCon:			LONGINT;
		doingInstall:		BOOLEAN; 
		whichStage:			InstallationStage; 
		didLiveUpdate:		BOOLEAN; 
		installerTempDirID:	LONGINT;
	END;
	
	{ The function prototype for the format 0 Action Atom code is as follows  }
	
	{ FUNCTION	MyActionAtom(myAAPBPtr : AAPBRecPtr) : Boolean;				}
	

	{ The function prototype for the format 1 Action Atom code is as follows  }
	
	{ FUNCTION	MyActionAtom(myAAPBPtr : AAPBRecPtr) : LongInt;				}
	


END.
