/*****************************************************************

 Created: Monday, September 16, 1991 at 2:22 PM
 AppleEvents.h
 C Interface to the Macintosh Libraries

 Copyright Apple Computer, Inc. 1989-1992
 All rights reserved
 
 Modified for AppleEvents manager version 1.0.1 Nov 13th, 1992

*****************************************************************/


#ifndef __APPLEEVENTS__
#define __APPLEEVENTS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef __OSUTILS__
#include <OSUtils.h>
#endif

#ifndef __EVENTS__
#include <Events.h>
#endif

#ifndef __EPPC__
#include <EPPC.h>
#endif

#ifndef __NOTIFICATION__
#include <Notification.h>
#endif

/*--------------------------------------------------------------
		Apple event descriptor types
--------------------------------------------------------------*/

enum {														/* compiler limits us to 20 items within an enum */
	typeBoolean = 'bool',									/* enum's are used to avoid conflicts with other header files */
	typeChar = 'TEXT',
	typeSMInt = 'shor',
	typeInteger = 'long',
	typeSMFloat = 'sing',
	typeFloat = 'doub',
	typeLongInteger = 'long',
	typeShortInteger = 'shor',
	typeLongFloat = 'doub',
	typeShortFloat = 'sing',
	typeExtended = 'exte',
	typeComp = 'comp',
	typeMagnitude = 'magn',
	typeAEList = 'list',
	typeAERecord = 'reco',
	typeAppleEvent = 'aevt',
	typeTrue = 'true',
	typeFalse = 'fals',
	typeAlias = 'alis',
	typeEnumerated = 'enum'
};

enum {
	typeType = 'type',
	typeAppParameters = 'appa',
	typeProperty = 'prop',
	typeFSS = 'fss ',
	typeKeyword = 'keyw',
	typeSectionH = 'sect',
	typeWildCard = '****',
	typeApplSignature = 'sign',
	typeSessionID = 'ssid',
	typeTargetID = 'targ',
	typeProcessSerialNumber = 'psn ',
	typeNull = 'null'										/* null or nonexistent data */
};

/*--------------------------------------------------------------
		Keywords for Apple event parameters
--------------------------------------------------------------*/

enum {
	keyDirectObject = '----',
	keyErrorNumber = 'errn',
	keyErrorString = 'errs',
	keyProcessSerialNumber = 'psn '
};

/*--------------------------------------------------------------
		Keywords for Apple event attributes
--------------------------------------------------------------*/

enum {
	keyTransactionIDAttr = 'tran',
	keyReturnIDAttr = 'rtid',
	keyEventClassAttr = 'evcl',
	keyEventIDAttr = 'evid',
	keyAddressAttr = 'addr',
	keyOptionalKeywordAttr = 'optk',
	keyTimeoutAttr = 'timo',
	keyInteractLevelAttr = 'inte',							/* this attribute is read only - will be set in AESend */
	keyEventSourceAttr = 'esrc',							/* this attribute is read only */
	keyMissedKeywordAttr = 'miss',							/* this attribute is read only */
	keyOriginalAddressAttr = 'from'							/* new in 1.0.1 */
};

/*--------------------------------------------------------------
		Keywords for special handlers
--------------------------------------------------------------*/

enum {
	keyPreDispatch = 'phac',								/* preHandler accessor call */
	keySelectProc = 'selh',									/* more selector call */

/*--------------------------------------------------------------
		Keyword for recording
--------------------------------------------------------------*/

	keyAERecorderCount = 'recr',							/* available only in vers 1.0.1 and greater */

/*--------------------------------------------------------------
		Keyword for version information
--------------------------------------------------------------*/

	keyAEVersion = 'vers',									/* available only in vers 1.0.1 and greater */

/*--------------------------------------------------------------
		Event Class
--------------------------------------------------------------*/

	kCoreEventClass = 'aevt'
};															/* end of enum */

/*--------------------------------------------------------------
		Event ID's
--------------------------------------------------------------*/

enum {
	kAEOpenApplication = 'oapp',
	kAEOpenDocuments = 'odoc',
	kAEPrintDocuments = 'pdoc',
	kAEQuitApplication = 'quit',
	kAEAnswer = 'ansr',
	kAEApplicationDied = 'obit'
};

/*--------------------------------------------------------------
		Constants for use in AESend mode
--------------------------------------------------------------*/

enum {
	kAENoReply = 0x00000001,								/* sender doesn't want a reply to event */
	kAEQueueReply = 0x00000002,								/* sender wants a reply but won't wait */
	kAEWaitReply = 0x00000003,								/* sender wants a reply and will wait */
	kAENeverInteract = 0x00000010,							/* server should not interact with user */
	kAECanInteract = 0x00000020,							/* server may try to interact with user */
	kAEAlwaysInteract = 0x00000030,							/* server should always interact with user where appropriate */
	kAECanSwitchLayer = 0x00000040,							/* interaction may switch layer */
	kAEDontReconnect = 0x00000080,							/* don't reconnect if there is a sessClosedErr from PPCToolbox */
	kAEWantReceipt = nReturnReceipt,						/* sender wants a receipt of message */
	kAEDontRecord = 0x00001000,								/* don't record this event - available only in vers 1.0.1 and greater */
	kAEDontExecute = 0x00002000,							/* don't send the event for recording - available only in vers 1.0.1 and greater */

/*--------------------------------------------------------------
		Constants for the send priority in AESend
--------------------------------------------------------------*/

	kAENormalPriority = 0x00000000,							/* post message at the end of the event queue */
	kAEHighPriority = nAttnMsg								/* post message at the front of the event queue */
};															/* end of enum */

/*--------------------------------------------------------------
		Constants for recording
--------------------------------------------------------------*/

enum {
	kAEStartRecording = 'reca',								/* available only in vers 1.0.1 and greater */
	kAEStopRecording = 'recc',								/* available only in vers 1.0.1 and greater */
	kAENotifyStartRecording = 'rec1',						/* available only in vers 1.0.1 and greater */
	kAENotifyStopRecording = 'rec0',						/* available only in vers 1.0.1 and greater */
	kAENotifyRecording = 'recr'								/* available only in vers 1.0.1 and greater */
};

/*--------------------------------------------------------------
		Constant for the returnID param of AECreateAppleEvent
--------------------------------------------------------------*/

enum {
 	kAutoGenerateReturnID = -1,								/* AECreateAppleEvent will generate a session-unique ID */

/*--------------------------------------------------------------
		Constant for transaction ID's
--------------------------------------------------------------*/

	kAnyTransactionID = 0,									/* no transaction is in use */

/*--------------------------------------------------------------
		Constants for timeout durations
--------------------------------------------------------------*/

 	kAEDefaultTimeout = -1,									/* timeout value determined by AEM */
 	kNoTimeOut = -2											/* wait until reply comes back, however long it takes */
};															/* end of enum */

/*--------------------------------------------------------------
		Constants for AEResumeTheCurrentEvent
--------------------------------------------------------------*/

enum {
	kAENoDispatch=  0,										/* dispatch parameter to AEResumeTheCurrentEvent takes a pointer to a dispatch */
	kAEUseStandardDispatch = -1								/* table, or one of these two constants */

};															/* end of enum */

/*--------------------------------------------------------------
		Apple event manager data types
--------------------------------------------------------------*/

typedef unsigned long AEEventClass;
typedef unsigned long AEEventID;
typedef unsigned long AEKeyword;
typedef ResType DescType;

struct AEDesc {
 	DescType descriptorType;
 	Handle dataHandle;
};
typedef struct AEDesc AEDesc;

struct AEKeyDesc {
	AEKeyword descKey;
	AEDesc descContent;
};
typedef struct AEKeyDesc AEKeyDesc;

typedef AEDesc AEAddressDesc;								/* an AEDesc which contains address data */
typedef AEDesc AEDescList;									/* a list of AEDesc's is a special kind of AEDesc */
typedef AEDescList AERecord;								/* AERecord is a list of keyworded AEDesc's */
typedef AERecord AppleEvent;								/* an AERecord that contains an AppleEvent */

typedef long AESendMode;									/* parameter to AESend */
typedef short AESendPriority;								/* priority param of AESend */

enum { kAEInteractWithSelf, kAEInteractWithLocal, kAEInteractWithAll };
typedef unsigned char AEInteractAllowed;

enum { kAEUnknownSource, kAEDirectCall, kAESameProcess,
	   kAELocalProcess, kAERemoteProcess };
typedef unsigned char AEEventSource;

enum { kAEDataArray, kAEPackedArray, kAEHandleArray, kAEDescArray,
	   kAEKeyDescArray };
typedef unsigned char AEArrayType;

union AEArrayData {
	short AEDataArray[1];
	char AEPackedArray[1];
	Handle AEHandleArray[1];
	AEDesc AEDescArray[1];
	AEKeyDesc AEKeyDescArray[1];
};
typedef union AEArrayData AEArrayData;

typedef AEArrayData *AEArrayDataPointer;

typedef ProcPtr EventHandlerProcPtr;
typedef ProcPtr IdleProcPtr;
typedef ProcPtr EventFilterProcPtr;


/*--------------------------------------------------------------
		Apple event manager error messages
--------------------------------------------------------------*/

enum {
	errAECoercionFail = -1700,								/* bad parameter data or unable to coerce the data supplied */
	errAEDescNotFound = -1701,
	errAECorruptData = -1702,
	errAEWrongDataType = -1703,
	errAENotAEDesc = -1704,
	errAEBadListItem = -1705,								/* the specified list item does not exist */
	errAENewerVersion = -1706,								/* need newer version of the AppleEvent manager */
	errAENotAppleEvent = -1707,								/* the event is not in AppleEvent format */
	errAEEventNotHandled = -1708,							/* the AppleEvent was not handled by any handler */
	errAEReplyNotValid = -1709,								/* AEResetTimer was passed an invalid reply parameter */
	errAEUnknownSendMode = -1710,							/* mode wasn't NoReply, WaitReply, or QueueReply or Interaction level is unknown */
	errAEWaitCanceled = -1711,								/* in AESend, the user cancelled out of wait loop for reply or receipt */
	errAETimeout = -1712,									/* the AppleEvent timed out */
	errAENoUserInteraction = -1713,							/* no user interaction is allowed */
	errAENotASpecialFunction = -1714,						/* there is no special function for/with this keyword */
	errAEParamMissed = -1715,								/* a required parameter was not accessed */
	errAEUnknownAddressType = -1716,						/* the target address type is not known */
	errAEHandlerNotFound = -1717,							/* no handler in the dispatch tables fits the parameters to AEGetEventHandler or AEGetCoercionHandler */
	errAEReplyNotArrived = -1718							/* the contents of the reply you are accessing have not arrived yet */
};

enum {														/* error codes should be continued within this enum */
	errAEIllegalIndex = -1719,								/* index is out of range in a put operation */
	errAEUnknownObjectType = -1731,							/* available only in version 1.0.1 or greater */
	errAERecordingIsAlreadyOn = -1732						/* available only in version 1.0.1 or greater */
};

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
 The following calls apply to any AEDesc. Every 'result' descriptor is
 created for you, so you will be responsible for memory management
 (including disposing) of the descriptors so created. Note: purgeable
 descriptor data is not supported - the AEM does not call LoadResource.  
**************************************************************************/

pascal OSErr
AECreateDesc( DescType typeCode, const void* dataPtr, Size dataSize, AEDesc *result )
	= {0x303C,0x0825,0xA816};
	
pascal OSErr
AECoercePtr( DescType typeCode, const void* dataPtr, Size dataSize, DescType toType,
			 AEDesc *result )
	= {0x303C,0x0A02,0xA816}; 
	
pascal OSErr
AECoerceDesc( const AEDesc *theAEDesc, DescType toType, AEDesc *result )
	= {0x303C,0x0603,0xA816}; 
	
pascal OSErr
AEDisposeDesc( AEDesc *theAEDesc )
	= {0x303C,0x0204,0xA816};
 
pascal OSErr
AEDuplicateDesc( const AEDesc *theAEDesc, AEDesc *result )
	= {0x303C,0x0405,0xA816}; 


/**************************************************************************
  The following calls apply to AEDescList. Since AEDescList is a subtype of
  AEDesc, the calls in the previous section can also be used for AEDescList.
  All list and array indices are 1-based. If the data was greater than
  maximumSize in the routines below, then actualSize will be greater than
  maximumSize, but only maximumSize bytes will actually be retrieved.
**************************************************************************/

pascal OSErr
AECreateList( const void* factoringPtr, Size factoredSize, Boolean isRecord,
              AEDescList *resultList )
	= {0x303C,0x0706,0xA816}; 
	
	
pascal OSErr
AECountItems( const AEDescList *theAEDescList, long *theCount )
	= {0x303C,0x0407,0xA816}; 
	
pascal OSErr
AEPutPtr( const AEDescList *theAEDescList, long index, DescType typeCode,
          const void* dataPtr, Size dataSize )
	= {0x303C,0x0A08,0xA816};
 
pascal OSErr
AEPutDesc( const AEDescList *theAEDescList, long index,
		   const AEDesc *theAEDesc )
	= {0x303C,0x0609,0xA816}; 
	
pascal OSErr
AEGetNthPtr( const AEDescList *theAEDescList, long index, DescType desiredType,
             AEKeyword *theAEKeyword, DescType *typeCode, void* dataPtr,
             Size maximumSize, Size *actualSize )
	= {0x303C,0x100A,0xA816}; 
	
pascal OSErr
AEGetNthDesc( const AEDescList *theAEDescList, long index, DescType desiredType,
               AEKeyword *theAEKeyword, AEDesc *result )
	= {0x303C,0x0A0B,0xA816}; 
	
pascal OSErr
AESizeOfNthItem( const AEDescList *theAEDescList, long index,
				 DescType *typeCode, Size *dataSize )
	= {0x303C,0x082A,0xA816};

pascal OSErr
AEGetArray( const AEDescList *theAEDescList, AEArrayType arrayType,
            AEArrayDataPointer arrayPtr, Size maximumSize, DescType *itemType,
            Size *itemSize, long *itemCount )
	= {0x303C,0x0D0C,0xA816}; 
	
pascal OSErr
AEPutArray( const AEDescList *theAEDescList, AEArrayType arrayType,
            const AEArrayData *arrayPtr, DescType itemType,
			Size itemSize, long itemCount )
	= {0x303C,0x0B0D,0xA816};

pascal OSErr
AEDeleteItem( const AEDescList *theAEDescList, long index )
	= {0x303C,0x040E,0xA816}; 


/**************************************************************************
 The following calls apply to AERecord. Since AERecord is a subtype of
 AEDescList, the calls in the previous sections can also be used for
 AERecord an AERecord can be created by using AECreateList with isRecord
 set to true. 
**************************************************************************/

pascal OSErr
AEPutKeyPtr( const AERecord *theAERecord, AEKeyword theAEKeyword,
			 DescType typeCode, const void* dataPtr, Size dataSize )
	= {0x303C,0x0A0F,0xA816};
	
pascal OSErr
AEPutKeyDesc( const AERecord *theAERecord, AEKeyword theAEKeyword,
              const AEDesc *theAEDesc )
	= {0x303C,0x0610,0xA816};

pascal OSErr
AEGetKeyPtr( const AERecord *theAERecord, AEKeyword theAEKeyword,
             DescType desiredType, DescType *typeCode, void* dataPtr,
             Size maximumSize, Size *actualSize )
	= {0x303C,0x0E11,0xA816};
	
pascal OSErr
AEGetKeyDesc( const AERecord *theAERecord, AEKeyword theAEKeyword,
              DescType desiredType, AEDesc *result )
	= {0x303C,0x0812,0xA816};
	
pascal OSErr
AESizeOfKeyDesc( const AERecord *theAERecord, AEKeyword theAEKeyword,
                 DescType *typeCode, Size *dataSize )
	= {0x303C,0x0829,0xA816};
	
pascal OSErr
AEDeleteKeyDesc( const AERecord *theAERecord, AEKeyword theAEKeyword )
	= {0x303C,0x0413,0xA816}; 


/**************************************************************************
  The following calls are used to pack and unpack parameters from records
  of type AppleEvent. Since AppleEvent is a subtype of AERecord, the calls
  in the previous sections can also be used for variables of type
  AppleEvent. The next six calls are in fact identical to the six calls
  for AERecord.
**************************************************************************/

pascal OSErr
AEPutParamPtr( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
               DescType typeCode, const void* dataPtr, Size dataSize )
	= {0x303C,0x0A0F,0xA816};
	
pascal OSErr
AEPutParamDesc( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                const AEDesc *theAEDesc )
	= {0x303C,0x0610,0xA816};
	
pascal OSErr
AEGetParamPtr( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
               DescType desiredType, DescType *typeCode, void* dataPtr,
               Size maximumSize, Size *actualSize )
	= {0x303C,0x0E11,0xA816};
	
pascal OSErr
AEGetParamDesc( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                DescType desiredType, AEDesc *result )
	= {0x303C,0x0812,0xA816};
	
pascal OSErr
AESizeOfParam( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
               DescType *typeCode, Size *dataSize )
	= {0x303C,0x0829,0xA816};
	
pascal OSErr
AEDeleteParam( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword )
	= {0x303C,0x0413,0xA816}; 


/**************************************************************************
 The following calls also apply to type AppleEvent. Message attributes are
 far more restricted, and can only be accessed through the following 5
 calls. The various list and record routines cannot be used to access the
 attributes of an event. 
**************************************************************************/

pascal OSErr
AEGetAttributePtr( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                   DescType desiredType, DescType *typeCode, void* dataPtr,
                   Size maximumSize, Size *actualSize )
	= {0x303C,0x0E15,0xA816};
	
pascal OSErr
AEGetAttributeDesc( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                    DescType desiredType, AEDesc *result )
	= {0x303C,0x0826,0xA816};
	
pascal OSErr
AESizeOfAttribute( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                   DescType *typeCode, Size *dataSize )
	= {0x303C,0x0828,0xA816};
	
pascal OSErr
AEPutAttributePtr( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                   DescType typeCode, const void* dataPtr, Size dataSize )
	= {0x303C,0x0A16,0xA816};
	
pascal OSErr
AEPutAttributeDesc( const AppleEvent *theAppleEvent, AEKeyword theAEKeyword,
                    const AEDesc *theAEDesc )
	= {0x303C,0x0627,0xA816}; 


/**************************************************************************
  The next couple of calls are basic routines used to create, send,
  and process AppleEvents. 
**************************************************************************/

pascal OSErr
AECreateAppleEvent( AEEventClass theAEEventClass, AEEventID theAEEventID,
                    const AEAddressDesc *target, short returnID,
                    long transactionID, AppleEvent *result )
	= {0x303C,0x0B14,0xA816};
	
pascal OSErr
AESend( const AppleEvent *theAppleEvent, AppleEvent *reply,
		AESendMode sendMode, AESendPriority sendPriority, long timeOutInTicks,
        IdleProcPtr idleProc, EventFilterProcPtr filterProc )
	= {0x303C,0x0D17,0xA816};
	
pascal OSErr
AEProcessAppleEvent( const EventRecord *theEventRecord )
	= {0x303C,0x021B,0xA816}; 

/* 
 Note: during event processing, an event handler may realize that it is likely
 to exceed the client's timeout limit. Passing the reply to this
 routine causes a wait event to be generated that asks the client
 for more time. 
*/

pascal OSErr
AEResetTimer( const AppleEvent *reply )
	= {0x303C,0x0219,0xA816}; 


/**************************************************************************
 The following four calls are available for applications which need more
 sophisticated control over when and how events are processed. Applications
 which implement multi-session servers or which implement their own
 internal event queueing will probably be the major clients of these
 routines. They can be called from within a handler to prevent the AEM from
 disposing of the AppleEvent when the handler returns. They can be used to
 asynchronously process the event (as MacApp does).
**************************************************************************/

pascal OSErr
AESuspendTheCurrentEvent( const AppleEvent *theAppleEvent )
	= {0x303C,0x022B,0xA816}; 

/* 
 Note: The following routine tells the AppleEvent manager that processing
 is either about to resume or has been completed on a previously suspended
 event. The procPtr passed in as the dispatcher parameter will be called to
 attempt to redispatch the event. Several constants for the dispatcher
 parameter allow special behavior. They are:
  	- kAEUseStandardDispatch means redispatch as if the event was just
	  received, using the standard AppleEvent dispatch mechanism.
  	- kAENoDispatch means ignore the parameter.
   	  Use this in the case where the event has been handled and no
	  redispatch is needed.
  	- non nil means call the routine which the dispatcher points to.
*/

pascal OSErr
AEResumeTheCurrentEvent( const AppleEvent *theAppleEvent,
						 const AppleEvent *reply,
						 EventHandlerProcPtr dispatcher, long handlerRefcon )
	= {0x303C,0x0818,0xA816};
	
pascal OSErr
AEGetTheCurrentEvent( AppleEvent *theAppleEvent )
	= {0x303C,0x021A,0xA816};
	
pascal OSErr
AESetTheCurrentEvent( const AppleEvent *theAppleEvent )
	= {0x303C,0x022C,0xA816}; 


/**************************************************************************
  The following three calls are used to allow applications to behave
  courteously when a user interaction such as a dialog box is needed. 
**************************************************************************/

pascal OSErr
AEGetInteractionAllowed( AEInteractAllowed *level )
	= {0x303C,0x021D,0xA816};
	
pascal OSErr
AESetInteractionAllowed( AEInteractAllowed level )
	= {0x303C,0x011E,0xA816};
	
pascal OSErr
AEInteractWithUser( long timeOutInTicks, NMRecPtr nmReqPtr,
					IdleProcPtr idleProc )
	= {0x303C,0x061C,0xA816}; 


/**************************************************************************
  These calls are used to set up and modify the event dispatch table.
**************************************************************************/

pascal OSErr
AEInstallEventHandler( AEEventClass theAEEventClass, AEEventID theAEEventID,
                       EventHandlerProcPtr handler, long handlerRefcon,
                       Boolean isSysHandler )
	= {0x303C,0x091F,0xA816};
	
pascal OSErr
AERemoveEventHandler( AEEventClass theAEEventClass, AEEventID theAEEventID,
                      EventHandlerProcPtr handler, Boolean isSysHandler )
	= {0x303C,0x0720,0xA816};
	
pascal OSErr
AEGetEventHandler( AEEventClass theAEEventClass, AEEventID theAEEventID,
                   EventHandlerProcPtr *handler, long *handlerRefcon,
                   Boolean isSysHandler )
	= {0x303C,0x0921,0xA816}; 


/**************************************************************************
  These calls are used to set up and modify the coercion dispatch table.
**************************************************************************/

pascal OSErr
AEInstallCoercionHandler( DescType fromType, DescType toType, ProcPtr handler,
                          long handlerRefcon, Boolean fromTypeIsDesc,
                          Boolean isSysHandler )
	= {0x303C,0x0A22,0xA816};
	
pascal OSErr
AERemoveCoercionHandler( DescType fromType, DescType toType, ProcPtr handler,
                         Boolean isSysHandler )
	= {0x303C,0x0723,0xA816};
	
pascal OSErr
AEGetCoercionHandler( DescType fromType, DescType toType, ProcPtr *handler,
                      long *handlerRefcon, Boolean *fromTypeIsDesc,
                      Boolean isSysHandler )
	= {0x303C,0x0B24,0xA816}; 


/**************************************************************************
  These calls are used to set up and modify special hooks into the
  AppleEvent manager.
**************************************************************************/

pascal OSErr
AEInstallSpecialHandler( AEKeyword functionClass, ProcPtr handler,
                         Boolean isSysHandler )
	= {0x303C,0x0500,0xA816};
	
pascal OSErr
AERemoveSpecialHandler( AEKeyword functionClass, ProcPtr handler,
                        Boolean isSysHandler )
	= {0x303C,0x0501,0xA816}; 

pascal OSErr
AEGetSpecialHandler( AEKeyword functionClass, ProcPtr *handler,
                     Boolean isSysHandler )
	= {0x303C,0x052D,0xA816}; 


/**************************************************************************
  This call was added in version 1.0.1. If called with the keyword
  keyAERecorderCount ('recr'), the number of recorders that are
  currently active is returned in 'result'.
**************************************************************************/

/* available only in vers 1.0.1 and greater */
pascal OSErr
AEManagerInfo( AEKeyword keyWord, long *result )
	= {0x303C,0x0441,0xA816};


#ifdef __cplusplus
}
#endif

#ifndef __AEREGISTRY__			// for access to constants moved to AERegistry.h
#include <AERegistry.h>			// placed at end because AERegistry.h depends on AppleEvents.h 
#endif

#endif
