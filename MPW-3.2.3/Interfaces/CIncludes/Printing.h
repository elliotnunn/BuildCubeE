/************************************************************

Created: Sunday, January 6, 1991 at 9:40 PM
    Printing.h
    C Interface to the Macintosh Libraries


        Copyright Apple Computer, Inc.    1985-1989
        All rights reserved

************************************************************/


#ifndef __PRINTING__
#define __PRINTING__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

#ifndef __DIALOGS__
#include <Dialogs.h>
#endif


enum {

    iPFMaxPgs = 128,
    iPrPgFract = 120,               /*Page scale factor. ptPgSize (below) is in units of 1/iPrPgFract*/
    iPrPgFst = 1,                   /*Page range constants*/
    iPrPgMax = 9999,
    iPrRelease = 3,                 /*Current version number of the code.*/
    iPrSavPFil = -1,
    iPrAbort = 0x0080,
    iPrDevCtl = 7,                  /*The PrDevCtl Proc's ctl number*/
    lPrReset = 0x00010000,          /*The PrDevCtl Proc's CParam for reset*/
    lPrLineFeed = 0x00030000,
    lPrLFStd = 0x0003FFFF,          /*The PrDevCtl Proc's CParam for std paper advance*/
    lPrLFSixth = 0x0003FFFF,
    lPrPageEnd = 0x00020000,        /*The PrDevCtl Proc's CParam for end page*/
    lPrDocOpen = 0x00010000,
    lPrPageOpen = 0x00040000,
    lPrPageClose = 0x00020000,
    lPrDocClose = 0x00050000,
    iFMgrCtl = 8,                   /*The FMgr's Tail-hook Proc's ctl number*/
    iMemFullErr = -108,
    iIOAbort = -27
};
enum {
    pPrGlobals = 0x00000944,        /*The PrVars lo mem area:*/
    bDraftLoop = 0,
    bSpoolLoop = 1,
    bUser1Loop = 2,
    bUser2Loop = 3,
    iPrBitsCtl = 4,
    lScreenBits = 0,
    lPaintBits = 1,
    lHiScreenBits = 0x00000002,     /*The Bitmap Print Proc's Screen Bitmap param*/
    lHiPaintBits = 0x00000003,      /*The Bitmap Print Proc's Paint [sq pix] param*/
    iPrIOCtl = 5,
    iPrEvtCtl = 6,                  /*The PrEvent Proc's ctl number*/
    lPrEvtAll = 0x0002FFFD,         /*The PrEvent Proc's CParam for the entire screen*/
    lPrEvtTop = 0x0001FFFD,         /*The PrEvent Proc's CParam for the top folder*/

#define sPrDrvr ".Print"

    iPrDrvrRef = -3,
    getRslDataOp = 4,
    setRslOp = 5,
    draftBitsOp = 6,
    noDraftBitsOp = 7,
    getRotnOp = 8
};
enum {
    NoSuchRsl = 1,
    RgType1 = 1
};

enum {feedCut,feedFanfold,feedMechCut,feedOther};
typedef unsigned char TFeed;

enum {scanTB,scanBT,scanLR,scanRL};
typedef unsigned char TScan;


typedef Rect *TPRect;
typedef pascal void (*PrIdleProcPtr)(void);
typedef pascal void (*PItemProcPtr)(DialogPtr theDialog, short item);

struct TPrPort {
    GrafPort gPort;                 /*The Printer's graf port.*/
    QDProcs gProcs;                 /*..and its procs*/
    long lGParam1;                  /*16 bytes for private parameter storage.*/
    long lGParam2;
    long lGParam3;
    long lGParam4;
    Boolean fOurPtr;                /*Whether the PrPort allocation was done by us.*/
    Boolean fOurBits;               /*Whether the BitMap allocation was done by us.*/
};

typedef struct TPrPort TPrPort;
typedef TPrPort *TPPrPort;

/* Printing Graf Port. All printer imaging, whether spooling, banding, etc, happens "thru" a GrafPort.
  This is the "PrPeek" record. */
struct TPrInfo {
    short iDev;                     /*Font mgr/QuickDraw device code*/
    short iVRes;                    /*Resolution of device, in device coordinates*/
    short iHRes;                    /*..note: V before H => compatable with Point.*/
    Rect rPage;                     /*The page (printable) rectangle in device coordinates.*/
};

typedef struct TPrInfo TPrInfo;
typedef TPrInfo *TPPrInfo;

/* Print Info Record: The parameters needed for page composition. */
struct TPrStl {
    short wDev;
    short iPageV;
    short iPageH;
    char bPort;
    TFeed feed;
};

typedef struct TPrStl TPrStl;
typedef TPrStl *TPPrStl;

struct TPrXInfo {
    short iRowBytes;
    short iBandV;
    short iBandH;
    short iDevBytes;
    short iBands;
    char bPatScale;
    char bUlThick;
    char bUlOffset;
    char bUlShadow;
    TScan scan;
    char bXInfoX;
};

typedef struct TPrXInfo TPrXInfo;
typedef TPrXInfo *TPPrXInfo;

struct TPrJob {
    short iFstPage;                 /*Page Range.*/
    short iLstPage;
    short iCopies;                  /*No. copies.*/
    char bJDocLoop;                 /*The Doc style: Draft, Spool, .., and ..*/
    Boolean fFromUsr;               /*Printing from an User's App (not PrApp) flag*/
    PrIdleProcPtr pIdleProc;        /*The Proc called while waiting on IO etc.*/
    StringPtr pFileName;            /*Spool File Name: NIL for default.*/
    short iFileVol;                 /*Spool File vol, set to 0 initially*/
    char bFileVers;                 /*Spool File version, set to 0 initially*/
    char bJobX;                     /*An eXtra byte.*/
};

typedef struct TPrJob TPrJob;
typedef TPrJob *TPPrJob;

/* Print Job: Print "form" for a single print request. */
struct TPrint {
    short iPrVersion;               /*(2) Printing software version*/
    TPrInfo prInfo;                 /*(14) the PrInfo data associated with the current style.*/
    Rect rPaper;                    /*(8) The paper rectangle [offset from rPage]*/
    TPrStl prStl;                   /*(8)  This print request's style.*/
    TPrInfo prInfoPT;               /*(14)  Print Time Imaging metrics*/
    TPrXInfo prXInfo;               /*(16)  Print-time (expanded) Print info record.*/
    TPrJob prJob;                   /*(20) The Print Job request (82)  Total of the above; 120-82 = 38 bytes needed to fill 120*/
    short printX[19];               /*Spare to fill to 120 bytes!*/
};

typedef struct TPrint TPrint;
typedef TPrint *TPPrint, **THPrint;

/* The universal 120 byte printing record */
struct TPrStatus {
    short iTotPages;                /*Total pages in Print File.*/
    short iCurPage;                 /*Current page number*/
    short iTotCopies;               /*Total copies requested*/
    short iCurCopy;                 /*Current copy number*/
    short iTotBands;                /*Total bands per page.*/
    short iCurBand;                 /*Current band number*/
    Boolean fPgDirty;               /*True if current page has been written to.*/
    Boolean fImaging;               /*Set while in band's DrawPic call.*/
    THPrint hPrint;                 /*Handle to the active Printer record*/
    TPPrPort pPrPort;               /*Ptr to the active PrPort*/
    PicHandle hPic;                 /*Handle to the active Picture*/
};

typedef struct TPrStatus TPrStatus;
typedef TPrStatus *TPPrStatus;

/* Print Status: Print information during printing. */
struct TPfPgDir {
    short iPages;
    long iPgPos[129];               /*ARRAY [0..iPfMaxPgs] OF LONGINT*/
};

typedef struct TPfPgDir TPfPgDir;
typedef TPfPgDir *TPPfPgDir, **THPfPgDir;

/* PicFile = a TPfHeader followed by n QuickDraw Pics (whose PicSize is invalid!) */
struct TPrDlg {
    DialogRecord Dlg;               /*The Dialog window*/
    ModalFilterProcPtr pFltrProc;   /*The Filter Proc.*/
    PItemProcPtr pItemProc;         /*The Item evaluating proc.*/
    THPrint hPrintUsr;              /*The user's print record.*/
    Boolean fDoIt;
    Boolean fDone;
    long lUser1;                    /*Four longs for user's to hang global data.*/
    long lUser2;                    /*...Plus more stuff needed by the particular printing dialog.*/
    long lUser3;
    long lUser4;
};

typedef struct TPrDlg TPrDlg;
typedef TPrDlg *TPPrDlg;


typedef pascal TPPrDlg (*PDlgInitProcPtr)(THPrint hPrint);

/* This is the Printing Dialog Record. Only used by folks appending their own dialogs.
Print Dialog: The Dialog Stream object. */



struct TGnlData {
    short iOpCode;
    short iError;
    long lReserved;                 /*more fields here depending on call*/
};

typedef struct TGnlData TGnlData;

struct TRslRg {
    short iMin;
    short iMax;
};

typedef struct TRslRg TRslRg;

struct TRslRec {
    short iXRsl;
    short iYRsl;
};

typedef struct TRslRec TRslRec;

struct TGetRslBlk {
    short iOpCode;
    short iError;
    long lReserved;
    short iRgType;
    TRslRg xRslRg;
    TRslRg yRslRg;
    short iRslRecCnt;
    TRslRec rgRslRec[27];
};

typedef struct TGetRslBlk TGetRslBlk;

struct TSetRslBlk {
    short iOpCode;
    short iError;
    long lReserved;
    THPrint hPrint;
    short iXRsl;
    short iYRsl;
};

typedef struct TSetRslBlk TSetRslBlk;

struct TDftBitsBlk {
    short iOpCode;
    short iError;
    long lReserved;
    THPrint hPrint;
};

typedef struct TDftBitsBlk TDftBitsBlk;

struct TGetRotnBlk {
    short iOpCode;
    short iError;
    long lReserved;
    THPrint hPrint;
    Boolean fLandscape;
    char bXtra;
};

typedef struct TGetRotnBlk TGetRotnBlk;


#ifdef __cplusplus
extern "C" {
#endif
pascal void PrPurge(void); 
pascal void PrNoPurge(void); 
pascal void PrOpen(void); 
pascal void PrClose(void); 
pascal void PrintDefault(THPrint hPrint); 
pascal Boolean PrValidate(THPrint hPrint); 
pascal Boolean PrStlDialog(THPrint hPrint); 
pascal Boolean PrJobDialog(THPrint hPrint); 
pascal TPPrDlg PrStlInit(THPrint hPrint); 
pascal TPPrDlg PrJobInit(THPrint hPrint); 
pascal void PrJobMerge(THPrint hPrintSrc,THPrint hPrintDst); 
pascal Boolean PrDlgMain(THPrint hPrint,PDlgInitProcPtr pDlgInit); 
pascal TPPrPort PrOpenDoc(THPrint hPrint,TPPrPort pPrPort,Ptr pIOBuf); 
pascal void PrCloseDoc(TPPrPort pPrPort); 
pascal void PrOpenPage(TPPrPort pPrPort,TPRect pPageFrame); 
pascal void PrClosePage(TPPrPort pPrPort); 
pascal void PrPicFile(THPrint hPrint,TPPrPort pPrPort,Ptr pIOBuf,Ptr pDevBuf,
    TPrStatus *prStatus); 
pascal short PrError(void); 
pascal void PrSetError(short iErr); 
pascal void PrGeneral(Ptr pData); 
pascal void PrDrvrOpen(void); 
pascal void PrDrvrClose(void); 
pascal void PrCtlCall(short iWhichCtl,long lParam1,long lParam2,long lParam3); 
pascal Handle PrDrvrDCE(void); 
pascal short PrDrvrVers(void); 
#ifdef __cplusplus
}
#endif

#endif
