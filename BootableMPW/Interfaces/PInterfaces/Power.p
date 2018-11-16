{
Created: Sunday, January 6, 1991 at 10:54 PM
    Power.p
    Pascal Interface to the Macintosh Libraries

        Copyright Apple Computer, Inc.    1989-1990
        All rights reserved
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT Power;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingPower}
{$SETC UsingPower := 1}

{$I+}
{$SETC PowerIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingTypes}
{$I $$Shell(PInterfaces)Types.p}
{$ENDC}
{$SETC UsingIncludes := PowerIncludes}

CONST

{ Bit positions for ModemByte }
modemOnBit = 0;
ringWakeUpBit = 2;
modemInstalledBit = 3;
ringDetectBit = 4;
modemOnHookBit = 5;

{ masks for ModemByte }
modemOnMask = $1;
ringWakeUpMask = $4;
modemInstalledMask = $8;
ringDetectMask = $10;
modemOnHookMask = $20;

{ bit positions for BatteryByte }
chargerConnBit = 0;
hiChargeBit = 1;
chargeOverFlowBit = 2;
batteryDeadBit = 3;
batteryLowBit = 4;
connChangedBit = 5;

{ masks for BatteryByte }
chargerConnMask = $1;
hiChargeMask = $2;
chargeOverFlowMask = $4;
batteryDeadMask = $8;
batteryLowMask = $10;
connChangedMask = $20;

{ commands to SleepQRec sleepQProc }
sleepRequest = 1;
sleepDemand = 2;
sleepWakeUp = 3;
sleepRevoke = 4;

{ SleepQRec.sleepQFlags }
noCalls = 1;
noRequest = 2;

slpQType = 16;
sleepQType = 16;

TYPE
ModemByte = Byte; 
BatteryByte = Byte; 

PMResultCode = LONGINT;

SleepQRecPtr = ^SleepQRec;
SleepQRec = RECORD
    sleepQLink: SleepQRecPtr;
    sleepQType: INTEGER;    {type = 16}
    sleepQProc: ProcPtr;    {Pointer to sleep routine}
    sleepQFlags: INTEGER;
    END;


FUNCTION DisableWUTime: OSErr;
FUNCTION GetWUTime(VAR WUTime: LONGINT;VAR WUFlag: Byte): OSErr;
FUNCTION SetWUTime(WUTime: LONGINT): OSErr;
FUNCTION BatteryStatus(VAR Status: Byte;VAR Power: Byte): OSErr;
FUNCTION ModemStatus(VAR Status: Byte): OSErr;
FUNCTION IdleUpdate: LONGINT;
    INLINE $A285,$2E80;
FUNCTION GetCPUSpeed: LONGINT;
    INLINE $70FF,$A485,$2E80;
PROCEDURE EnableIdle;
    INLINE $7000,$A485;
PROCEDURE DisableIdle;
    INLINE $7001,$A485;
PROCEDURE SleepQInstall(qRecPtr: SleepQRecPtr);
    INLINE $205F,$A28A;
PROCEDURE SleepQRemove(qRecPtr: SleepQRecPtr);
    INLINE $205F,$A48A;
PROCEDURE AOn;
    INLINE $7004,$A685;
PROCEDURE AOnIgnoreModem;
    INLINE $7005,$A685;
PROCEDURE BOn;
    INLINE $7000,$A685;
PROCEDURE AOff;
    INLINE $7084,$A685;
PROCEDURE BOff;
    INLINE $7080,$A685;


{$ENDC}    { UsingPower }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

