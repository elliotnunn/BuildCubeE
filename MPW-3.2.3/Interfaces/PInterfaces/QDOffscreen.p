{
Created: Sunday, January 6, 1991 at 10:59 PM
    QDOffscreen.p
    Pascal Interface to the Macintosh Libraries

        Copyright Apple Computer, Inc.    1985-1990
        All rights reserved
}


{$IFC UNDEFINED UsingIncludes}
{$SETC UsingIncludes := 0}
{$ENDC}

{$IFC NOT UsingIncludes}
    UNIT QDOffscreen;
    INTERFACE
{$ENDC}

{$IFC UNDEFINED UsingQDOffscreen}
{$SETC UsingQDOffscreen := 1}

{$I+}
{$SETC QDOffscreenIncludes := UsingIncludes}
{$SETC UsingIncludes := 1}
{$IFC UNDEFINED UsingQuickdraw}
{$I $$Shell(PInterfaces)Quickdraw.p}
{$ENDC}
{$SETC UsingIncludes := QDOffscreenIncludes}

CONST

{ New error codes }
cDepthErr = -157;   {invalid pixel depth}
pixPurgeBit = 0;
noNewDeviceBit = 1;
useTempMemBit = 2;
keepLocalBit = 3;
pixelsPurgeableBit = 6;
pixelsLockedBit = 7;
mapPixBit = 16;
newDepthBit = 17;
alignPixBit = 18;
newRowBytesBit = 19;
reallocPixBit = 20;
clipPixBit = 28;
stretchPixBit = 29;
ditherPixBit = 30;
gwFlagErrBit = 31;

TYPE
GWorldFlags = SET OF (pixPurge,noNewDevice,useTempMem,keepLocal,GWorldFlags4,
    GWorldFlags5,pixelsPurgeable,pixelsLocked,GWorldFlags8,GWorldFlags9,GWorldFlags10,
    GWorldFlags11,GWorldFlags12,GWorldFlags13,GWorldFlags14,GWorldFlags15,
    mapPix,newDepth,alignPix,newRowBytes,reallocPix,GWorldFlags21,GWorldFlags22,
    GWorldFlags23,GWorldFlags24,GWorldFlags25,GWorldFlags26,GWorldFlags27,
    clipPix,stretchPix,ditherPix,gwFlagErr);


GWorldPtr = CGrafPtr;


FUNCTION NewGWorld(VAR offscreenGWorld: GWorldPtr;PixelDepth: INTEGER;boundsRect: Rect;
    cTable: CTabHandle;aGDevice: GDHandle;flags: GWorldFlags): QDErr;
    INLINE $203C, $0016, $0000,$AB1D;
FUNCTION LockPixels(pm: PixMapHandle): BOOLEAN;
    INLINE $203C, $0004, $0001, $AB1D;
PROCEDURE UnlockPixels(pm: PixMapHandle);
    INLINE $203C, $0004, $0002, $AB1D;
FUNCTION UpdateGWorld(VAR offscreenGWorld: GWorldPtr;pixelDepth: INTEGER;
    boundsRect: Rect;cTable: CTabHandle;aGDevice: GDHandle;flags: GWorldFlags): GWorldFlags;
    INLINE $203C, $0016, $0003, $AB1D;
PROCEDURE DisposeGWorld(offscreenGWorld: GWorldPtr);
    INLINE $203C, $0004, $0004, $AB1D;
PROCEDURE GetGWorld(VAR port: CGrafPtr;VAR gdh: GDHandle);
    INLINE $203C, $0008, $0005, $AB1D;
PROCEDURE SetGWorld(port: CGrafPtr;gdh: GDHandle);
    INLINE $203C, $0008, $0006, $AB1D;
PROCEDURE CTabChanged(ctab: CTabHandle);
    INLINE $203C, $0004, $0007, $AB1D;
PROCEDURE PixPatChanged(ppat: PixPatHandle);
    INLINE $203C, $0004, $0008, $AB1D;
PROCEDURE PortChanged(port: GrafPtr);
    INLINE $203C, $0004, $0009, $AB1D;
PROCEDURE GDeviceChanged(gdh: GDHandle);
    INLINE $203C, $0004, $000A, $AB1D;
PROCEDURE AllowPurgePixels(pm: PixMapHandle);
    INLINE $203C, $0004, $000B, $AB1D;
PROCEDURE NoPurgePixels(pm: PixMapHandle);
    INLINE $203C, $0004, $000C, $AB1D;
FUNCTION GetPixelsState(pm: PixMapHandle): GWorldFlags;
    INLINE $203C, $0004, $000D, $AB1D;
PROCEDURE SetPixelsState(pm: PixMapHandle;state: GWorldFlags);
    INLINE $203C, $0008, $000E, $AB1D;
FUNCTION GetPixBaseAddr(pm: PixMapHandle): Ptr;
    INLINE $203C, $0004, $000F, $AB1D;
FUNCTION NewScreenBuffer(globalRect: Rect;purgeable: BOOLEAN;VAR gdh: GDHandle;
    VAR offscreenPixMap: PixMapHandle): QDErr;
    INLINE $203C, $000E, $0010, $AB1D;
PROCEDURE DisposeScreenBuffer(offscreenPixMap: PixMapHandle);
    INLINE $203C, $0004, $0011, $AB1D;
FUNCTION GetGWorldDevice(offscreenGWorld: GWorldPtr): GDHandle;
    INLINE $203C, $0004, $0012, $AB1D;
FUNCTION QDDone(port: GrafPtr): BOOLEAN;
    INLINE $203C, $0004, $0013, $AB1D;
FUNCTION OffscreenVersion: LONGINT;
    INLINE $7014, $AB1D;
FUNCTION NewTempScreenBuffer(globalRect: Rect;purgeable: BOOLEAN;VAR gdh: GDHandle;
    VAR offscreenPixMap: PixMapHandle): QDErr;
    INLINE $203C, $000E, $0015, $AB1D;
FUNCTION PixMap32Bit(pmHandle: PixMapHandle): BOOLEAN;
    INLINE $203C, $0004, $0016, $AB1D;
FUNCTION GetGWorldPixMap(offscreenGWorld: GWorldPtr): PixMapHandle;
    INLINE $203C, $0004, $0017, $AB1D;


{$ENDC}    { UsingQDOffscreen }

{$IFC NOT UsingIncludes}
    END.
{$ENDC}

