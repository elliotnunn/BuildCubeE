/************************************************************

Created: 2:40 PM Thu, 18 Feb 1993
    AERegistry.h
    C Interface to the Apple Event Registry


        Copyright Apple Computer, Inc.    1993
        All rights reserved

************************************************************/


#ifndef __AEREGISTRY__
#define __AEREGISTRY__

#ifndef __TYPES__
#include <Types.h>
#endif
#ifndef __APPLEEVENTS__
#include <AppleEvents.h>
#endif

enum {
	cAEList = 'list',
	cApplication = 'capp',
	cArc = 'carc',
	cBoolean = 'bool',
	cCell = 'ccel',
	cChar = 'cha ',
	cColorTable = 'clrt',
	cColumn = 'ccol',
	cDocument = 'docu',
	cDrawingArea = 'cdrw',
	cEnumeration = 'enum',
	cFile = 'file',
	cFixed = 'fixd',
	cFixedPoint = 'fpnt',
	cFixedRectangle = 'frct',
	cGraphicLine = 'glin',
	cGraphicObject = 'cgob',
	cGraphicShape = 'cgsh',
	cGraphicText = 'cgtx',
	cGroupedGraphic = 'cpic'
};
enum {
	cInsertionLoc = 'insl',
	cInsertionPoint = 'cins',
	cIntlText = 'itxt',
	cIntlWritingCode = 'intl',
	cItem = 'citm',
	cLine = 'clin',
	cLongDateTime = 'ldt ',
	cLongFixed = 'lfxd',
	cLongFixedPoint = 'lfpt',
	cLongFixedRectangle = 'lfrc',
	cLongInteger = 'long',
	cLongPoint = 'lpnt',
	cLongRectangle = 'lrct',
	cMachineLoc = 'mLoc',
	cMenu = 'cmnu',
	cMenuItem = 'cmen',
	cObject = 'cobj',
	cObjectSpecifier = 'obj ',
	cOpenableObject = 'coob',
	cOval = 'covl'
};
enum {
	cParagraph = 'cpar',
	cPICT = 'PICT',
	cPixel = 'cpxl',
	cPixelMap = 'cpix',
	cPolygon = 'cpgn',
	cProperty = 'prop',
	cQDPoint = 'QDpt',
	cQDRectangle = 'qdrt',
	cRectangle = 'crec',
	cRGBColor = 'cRGB',
	cRotation = 'trot',
	cRoundedRectangle = 'crrc',
	cRow = 'crow',
	cSelection = 'csel',
	cShortInteger = 'shor',
	cTable = 'ctbl',
	cText = 'ctxt',
	cTextFlow = 'cflo',
	cTextStyles = 'tsty',
	cType = 'type'
};
enum {
	cVersion = 'vers',
	cWindow = 'cwin',
	cWord = 'cwor',
	enumArrows = 'arro',
	enumJustification = 'just',
	enumKeyForm = 'kfrm',
	enumPosition = 'posi',
	enumProtection = 'prtn',
	enumQuality = 'qual',
	enumSaveOptions = 'savo',
	enumStyle = 'styl',
	enumTransferMode = 'tran',
	errAEBadKeyForm = -10002,
	errAECantHandleClass = -10010,
	errAECantSupplyType = -10009,
	errAECantUndo = -10015,
	errAEEventFailed = -10000,
	errAEIndexTooLarge = -10007,
	errAEInTransaction = -10011,
	errAELocalOnly = -10016
};
enum {
	errAENoSuchTransaction = -10012,
	errAENotAnElement = -10008,
	errAENotASingleObject = -10014,
	errAENotModifiable = -10003,
	errAENoUserSelection = -10013,
	errAEPrivilegeError = -10004,
	errAEReadDenied = -10005,
	errAETypeError = -10001,
	errAEWriteDenied = -10006,
	formUniqueID = 'ID  ',
	kAEAbout = 'abou',
	kAEAfter = 'afte',
	kAEAliasSelection = 'sali',
	kAEAllCaps = 'alcp',
	kAEArrowAtEnd = 'aren',
	kAEArrowAtStart = 'arst',
	kAEArrowBothEnds = 'arbo',
	kAEAsk = 'ask ',
	kAEBefore = 'befo',
	kAEBeginning = 'bgng'
};
enum {
	kAEBeginsWith = 'bgwt',
	kAEBeginTransaction = 'begi',
	kAEBold = 'bold',
	kAECaseSensEquals = 'cseq',
	kAECentered = 'cent',
	kAEChangeView = 'view',
	kAEClone = 'clon',
	kAEClose = 'clos',
	kAECondensed = 'cond',
	kAEContains = 'cont',
	kAECopy = 'copy',
	kAECoreSuite = 'core',
	kAECountElements = 'cnte',
	kAECreateElement = 'crel',
	kAECreatePublisher = 'cpub',
	kAECut = 'cut ',
	kAEDelete = 'delo',
	kAEDoObjectsExist = 'doex',
	kAEDoScript = 'dosc',
	kAEDrag = 'drag'
};
enum {
	kAEDuplicateSelection = 'sdup',
	kAEEditGraphic = 'edit',
	kAEEmptyTrash = 'empt',
	kAEEnd = 'end ',
	kAEEndsWith = 'ends',
	kAEEndTransaction = 'endt',
	kAEEquals = '=   ',
	kAEExpanded = 'pexp',
	kAEFast = 'fast',
	kAEFinderEvents = 'FNDR',
	kAEFormulaProtect = 'fpro',
	kAEFullyJustified = 'full',
	kAEGetClassInfo = 'qobj',
	kAEGetData = 'getd',
	kAEGetDataSize = 'dsiz',
	kAEGetEventInfo = 'gtei',
	kAEGetInfoSelection = 'sinf',
	kAEGetPrivilegeSelection = 'sprv',
	kAEGetSuiteInfo = 'gtsi',
	kAEGreaterThan = '>   '
};
enum {
	kAEGreaterThanEquals = '>=  ',
	kAEGrow = 'grow',
	kAEHidden = 'hidn',
	kAEHiQuality = 'hiqu',
	kAEImageGraphic = 'imgr',
	kAEInfo = 11,
	kAEIsUniform = 'isun',
	kAEItalic = 'ital',
	kAELeftJustified = 'left',
	kAELessThan = '<   ',
	kAELessThanEquals = '<=  ',
	kAELowercase = 'lowc',
	kAEMain = 0,
	kAEMakeObjectsVisible = 'mvis',
	kAEMiscStandards = 'misc',
	kAEModifiable = 'modf',
	kAEMove = 'move',
	kAENo = 'no  ',
	kAENoArrow = 'arno',
	kAENonmodifiable = 'nmod'
};
enum {
	kAEOpen = 'odoc',
	kAEOpenSelection = 'sope',
	kAEOutline = 'outl',
	kAEPageSetup = 'pgsu',
	kAEPaste = 'past',
	kAEPlain = 'plan',
	kAEPrint = 'pdoc',
	kAEPrintSelection = 'spri',
	kAEPrintWindow = 'pwin',
	kAEPutAwaySelection = 'sput',
	kAEQDAddOver = 'addo',
	kAEQDAddPin = 'addp',
	kAEQDAdMax = 'admx',
	kAEQDAdMin = 'admn',
	kAEQDBic = 'bic ',
	kAEQDBlend = 'blnd',
	kAEQDCopy = 'cpy ',
	kAEQDNotBic = 'nbic',
	kAEQDNotCopy = 'ncpy',
	kAEQDNotOr = 'ntor'
};
enum {
	kAEQDNotXor = 'nxor',
	kAEQDOr = 'or  ',
	kAEQDSubOver = 'subo',
	kAEQDSubPin = 'subp',
	kAEQDSupplementalSuite = 'qdsp',
	kAEQDXor = 'xor ',
	kAEQuickdrawSuite = 'qdrw',
	kAERedo = 'redo',
	kAERegular = 'regl',
	kAEReplace = 'rplc',
	kAERequiredSuite = 'reqd',
	kAERestart = 'rest',
	kAERevealSelection = 'srev',
	kAERevert = 'rvrt',
	kAERightJustified = 'rght',
	kAESave = 'save',
	kAESelect = 'slct',
	kAESetData = 'setd',
	kAESetPosition = 'posn',
	kAEShadow = 'shad'
};
enum {
	kAESharing = 13,
	kAEShowClipboard = 'shcl',
	kAEShutDown = 'shut',
	kAESleep = 'slep',
	kAESmallCaps = 'smcp',
	kAESpecialClassProperties = 'c@#!',
	kAEStrikethrough = 'strk',
	kAESubscript = 'sbsc',
	kAESuperscript = 'spsc',
	kAETableSuite = 'tbls',
	kAETextSuite = 'TEXT',
	kAETransactionTerminated = 'ttrm',
	kAEUnderline = 'undl',
	kAEUndo = 'undo',
	kAEWholeWordEquals = 'wweq',
	kAEYes = 'yes ',
	kAEZoom = 'zoom',
	kByCommentView = 6,
	kByDateView = 3,
	kByIconView = 1
};
enum {
	kByKindView = 5,
	kByLabelView = 7,
	kByNameView = 2,
	kBySizeView = 4,
	kBySmallIcon = 0,
	kByVersionView = 8,
	keyAEAngle = 'kang',
	keyAEArcAngle = 'parc',
	keyAEBaseAddr = 'badd',
	keyAEBestType = 'pbst',
	keyAEBgndColor = 'kbcl',
	keyAEBgndPattern = 'kbpt',
	keyAEBounds = 'pbnd',
	keyAECellList = 'kclt',
	keyAEClassID = 'clID',
	keyAEColor = 'colr',
	keyAEColorTable = 'cltb',
	keyAECurveHeight = 'kchd',
	keyAECurveWidth = 'kcwd',
	keyAEDashStyle = 'pdst'
};
enum {
	keyAEData = 'data',
	keyAEDefaultType = 'deft',
	keyAEDefinitionRect = 'pdrt',
	keyAEDescType = 'dstp',
	keyAEDestination = 'dest',
	keyAEDoAntiAlias = 'anta',
	keyAEDoDithered = 'gdit',
	keyAEDoRotate = 'kdrt',
	keyAEDoScale = 'ksca',
	keyAEDoTranslate = 'ktra',
	keyAEEditionFileLoc = 'eloc',
	keyAEElements = 'elms',
	keyAEEndPoint = 'pend',
	keyAEEventClass = 'evcl',
	keyAEEventID = 'evti',
	keyAEFile = 'kfil',
	keyAEFileType = 'fltp',
	keyAEFillColor = 'flcl',
	keyAEFillPattern = 'flpt',
	keyAEFlipHorizontal = 'kfho'
};
enum {
	keyAEFlipVertical = 'kfvt',
	keyAEFont = 'font',
	keyAEFormula = 'pfor',
	keyAEGraphicObjects = 'gobs',
	keyAEID = 'ID  ',
	keyAEImageQuality = 'gqua',
	keyAEInsertHere = 'insh',
	keyAEKeyForms = 'keyf',
	keyAEKeyword = 'kywd',
	keyAELevel = 'levl',
	keyAELineArrow = 'arro',
	keyAEName = 'pnam',
	keyAENewElementLoc = 'pnel',
	keyAEObject = 'kobj',
	keyAEObjectClass = 'kocl',
	keyAEOffStyles = 'ofst',
	keyAEOnStyles = 'onst',
	keyAEParameters = 'prms',
	keyAEParamFlags = 'pmfg',
	keyAEPenColor = 'ppcl'
};
enum {
	keyAEPenPattern = 'pppa',
	keyAEPenWidth = 'ppwd',
	keyAEPixelDepth = 'pdpt',
	keyAEPixMapMinus = 'kpmm',
	keyAEPMTable = 'kpmt',
	keyAEPointList = 'ptlt',
	keyAEPointSize = 'ptsz',
	keyAEPosition = 'kpos',
	keyAEPropData = 'prdt',
	keyAEProperties = 'qpro',
	keyAEProperty = 'kprp',
	keyAEPropFlags = 'prfg',
	keyAEPropID = 'prop',
	keyAEProtection = 'ppro',
	keyAERenderAs = 'kren',
	keyAERequestedType = 'rtyp',
	keyAEResult = '----',
	keyAEResultInfo = 'rsin',
	keyAERotation = 'prot',
	keyAERotPoint = 'krtp'
};
enum {
	keyAERowList = 'krls',
	keyAESaveOptions = 'savo',
	keyAEScale = 'pscl',
	keyAEScriptTag = 'psct',
	keyAEShowWhere = 'show',
	keyAEStartAngle = 'pang',
	keyAEStartPoint = 'pstp',
	keyAEStyles = 'ksty',
	keyAESuiteID = 'suit',
	keyAEText = 'ktxt',
	keyAETextColor = 'ptxc',
	keyAETextFont = 'ptxf',
	keyAETextPointSize = 'ptps',
	keyAETextStyles = 'txst',
	keyAETheText = 'thtx',
	keyAETransferMode = 'pptm',
	keyAETranslation = 'ptrs',
	keyAETryAsStructGraf = 'toog',
	keyAEUniformStyles = 'ustl',
	keyAEUpdateOn = 'pupd'
};
enum {
	keyAEUserTerm = 'utrm',
	keyAEWindow = 'wndw',
	keyAEWritingCode = 'wrcd',
	keyMiscellaneous = 'fmsc',
	keySelection = 'fsel',
	keyWindow = 'kwnd',
	pArcAngle = 'parc',
	pBackgroundColor = 'pbcl',
	pBackgroundPattern = 'pbpt',
	pBestType = 'pbst',
	pBounds = 'pbnd',
	pClass = 'pcls',
	pClipboard = 'pcli',
	pColor = 'colr',
	pColorTable = 'cltb',
	pContents = 'pcnt',
	pCornerCurveHeight = 'pchd',
	pCornerCurveWidth = 'pcwd',
	pDashStyle = 'pdst',
	pDefaultType = 'deft'
};
enum {
	pDefinitionRect = 'pdrt',
	pEnabled = 'enbl',
	pEndPoint = 'pend',
	pFillColor = 'flcl',
	pFillPattern = 'flpt',
	pFont = 'font',
	pFormula = 'pfor',
	pGraphicObjects = 'gobs',
	pHasCloseBox = 'hclb',
	pHasTitleBar = 'ptit',
	pID = 'ID  ',
	pIndex = 'pidx',
	pInsertionLoc = 'pins',
	pIsFloating = 'isfl',
	pIsFrontProcess = 'pisf',
	pIsModal = 'pmod',
	pIsModified = 'imod',
	pIsResizable = 'prsz',
	pIsStationeryPad = 'pspd',
	pIsZoomable = 'iszm'
};
enum {
	pIsZoomed = 'pzum',
	pItemNumber = 'itmn',
	pJustification = 'pjst',
	pLineArrow = 'arro',
	pMenuID = 'mnid',
	pName = 'pnam',
	pNewElementLoc = 'pnel',
	pPenColor = 'ppcl',
	pPenPattern = 'pppa',
	pPenWidth = 'ppwd',
	pPixelDepth = 'pdpt',
	pPointList = 'ptlt',
	pPointSize = 'ptsz',
	pProtection = 'ppro',
	pRotation = 'prot',
	pScale = 'pscl',
	pScript = 'scpt',
	pScriptTag = 'psct',
	pSelected = 'selc',
	pSelection = 'sele'
};
enum {
	pStartAngle = 'pang',
	pStartPoint = 'pstp',
	pTextColor = 'ptxc',
	pTextFont = 'ptxf',
	pTextItemDelimiters = 'txdl',
	pTextPointSize = 'ptps',
	pTextStyles = 'txst',
	pTransferMode = 'pptm',
	pTranslation = 'ptrs',
	pUniformStyles = 'ustl',
	pUpdateOn = 'pupd',
	pUserSelection = 'pusl',
	pVersion = 'vers',
	pVisible = 'pvis',
	typeAEText = 'tTXT',
	typeArc = 'carc',
	typeBest = 'best',
	typeCell = 'ccel',
	typeClassInfo = 'gcli',
	typeColorTable = 'clrt'
};
enum {
	typeColumn = 'ccol',
	typeDashStyle = 'tdas',
	typeData = 'tdta',
	typeDrawingArea = 'cdrw',
	typeElemInfo = 'elin',
	typeEnumeration = 'enum',
	typeEPS = 'EPS ',
	typeEventInfo = 'evin',
	typeFinderWindow = 'fwin',
	typeFixed = 'fixd',
	typeFixedPoint = 'fpnt',
	typeFixedRectangle = 'frct',
	typeGraphicLine = 'glin',
	typeGraphicText = 'cgtx',
	typeGroupedGraphic = 'cpic',
	typeInsertionLoc = 'insl',
	typeIntlText = 'itxt',
	typeIntlWritingCode = 'intl',
	typeLongDateTime = 'ldt ',
	typeLongFixed = 'lfxd'
};
enum {
	typeLongFixedPoint = 'lfpt',
	typeLongFixedRectangle = 'lfrc',
	typeLongPoint = 'lpnt',
	typeLongRectangle = 'lrct',
	typeMachineLoc = 'mLoc',
	typeOval = 'covl',
	typeParamInfo = 'pmin',
	typePict = 'PICT',
	typePixelMap = 'cpix',
	typePixMapMinus = 'tpmm',
	typePolygon = 'cpgn',
	typePropInfo = 'pinf',
	typeQDPoint = 'QDpt',
	typeQDRectangle = 'qdrt',
	typeRectangle = 'crec',
	typeRGB16 = 'tr16',
	typeRGB96 = 'tr96',
	typeRGBColor = 'cRGB',
	typeRotation = 'trot',
	typeRoundedRectangle = 'crrc'
};
enum {
	typeRow = 'crow',
	typeScrapStyles = 'styl',
	typeScript = 'scpt',
	typeStyledText = 'STXT',
	typeSuiteInfo = 'suin',
	typeTable = 'ctbl',
	typeTextStyles = 'tsty',
	typeTIFF = 'TIFF',
	typeVersion = 'vers',
	zoomIn = 7,
	zoomOut = 8
};

struct WritingCode {
	ScriptCode	theScriptCode;
	LangCode	theLangCode;
};

typedef struct WritingCode WritingCode;

struct IntlText {
	ScriptCode	theScriptCode;
	LangCode	theLangCode;
	char		theText[1];
	/* variable length data */
};

typedef struct IntlText IntlText;

#endif