{
Created: Friday, October 20, 1989 at 3:26 PM
	Strings.p
	Pascal Interface to the Macintosh Libraries

	Copyright Apple Computer, Inc.	1985-1989
	All rights reserved
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
	UNIT Strings;
	INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingStrings}
{$SETC UsingStrings := 1}

{$I+}
{$SETC StringsIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := StringsIncludes}


FUNCTION C2PStr(cString: UNIV Ptr): StringPtr;
PROCEDURE C2PStrProc(cString: UNIV Ptr);
FUNCTION P2CStr(pString: StringPtr): Ptr;
PROCEDURE P2CStrProc(pString: StringPtr);

{$ENDC}    { UsingStrings }

{$IFC NOT UsingIncludes}
	END.
{$ENDC}

