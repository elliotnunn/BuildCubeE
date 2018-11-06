/*———————————————————————————————————————————————————————————————————————————————————*/
/*											
	©Apple Computer, Inc.  2/21/91 			
	      All Rights Reserved.				

*/

#ifndef __AEOBJECTS__
#define __AEOBJECTS__

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

#ifndef __APPLEEVENTS__
#include <AppleEvents.h>
#endif



/* Logical operators: look for them in descriptors of type typeLogicalDescriptor
  with keyword keyAELogicalOperator */
#define kAEAND						'AND '
#define kAEOR						'OR  '
#define kAENOT						'NOT '

/* Absolute ordinals: look for them in descriptors of type typeAbsoluteOrdinal.
  Possible use is as keyAEKeyData in an object specifier whose keyAEKeyForm
  field is formAbsolutePosition. */
#define kAEFirst					'firs'
#define kAELast						'last'
#define kAEMiddle					'midd'
#define kAEAny						'any '
#define kAEAll						'all '

/*  Relative ordinals: look for them in descriptors of type formRelativePosition. */
#define kAENext						'next'
#define kAEPrevious					'prev'

/********** Keywords for getting fields out of object specifier records **********/
#define keyAEDesiredClass			'want'
#define keyAEContainer				'from'
#define keyAEKeyForm				'form'
#define keyAEKeyData	 		 	'seld'


/********** Keywords for getting fields out of Range specifier records **********/
#define keyAERangeStart				'star'		/* These are the only two fields in the range desc */
#define keyAERangeStop				'stop'
	
/********** Possible values for the keyAEKeyForm field of an object specifier **********/
/* Remember that this set is an open-ended one.  The OSL makes assumptions about some of them,
  but nothing in the grammar says you can't define your own */
#define formAbsolutePosition 		'indx'	 	/* e.g., 1st, -2nd ( 2nd from end) */
#define formRelativePosition		'rele' 		/* next, previous */
#define formTest					'test' 		/* A logical or a comparison */
#define formRange					'rang' 		/* Two arbitrary objects and everything in between */
#define formPropertyID				'prop' 		/* Key data is a 4-char property name */
#define formName					'name' 		/* Key data may be of type 'TEXT' */

/************** Various relevant types ****************/
/* Some of these tend to be paired with certain of the forms above.  Where this
  is the case comments indicating the form(s) follow. */
#define typeObjectSpecifier 	 	'obj '		/* keyAEContainer will often be one of these */
#define typeObjectBeingExamined 	'exmn'		/* Another possible value for keyAEContainer */
#define typeCurrentContainer		'ccnt'		/* Another possible value for keyAEContainer */
#define typeToken					'toke'		/* Substituted for 'ccnt' before accessor called */

#define typeRelativeDescriptor 		'rel '		/* formRelativePosition */
#define typeAbsoluteOrdinal 		'abso'		/* formAbsolutePosition */
#define typeIndexDescriptor			'inde'		/* formAbsolutePosition */
#define typeRangeDescriptor 	 	'rang'		/* formRange */
#define typeLogicalDescriptor	 	'logi'		/* formTest is this or typeCompDescriptor */
#define typeCompDescriptor			'cmpd'		/* formTest is this or typeLogicalDescriptor */
	
/************** various relevant keywords ****************/
#define keyAECompOperator			'relo'		/* Relates two terms: '', '<', etc. */
#define keyAELogicalTerms			'term'		/* An AEList of terms to be related by 'logc' below */
#define keyAELogicalOperator		'logc'		/* kAEAND,  kAEOR or kAENOT */
#define keyAEObject1				'obj1'		/* One of two objects in a term must be object specifier */
#define keyAEObject2				'obj2'		/* The other object may be a simple descriptor or obj. spec. */


/************ Special Handler selectors for OSL Callbacks ***************/
/* You don't need to use these unless you are not using AESetObjectCallbacks. */
#define keyDisposeTokenProc			'xtok'
#define keyAECompareProc 		 	'cmpr'
#define keyAECountProc 			 	'cont'
#define keyAEMarkTokenProc 		 	'mkid'
#define keyAEMarkProc 			 	'mark'
#define keyAEAdjustMarksProc 	 	'adjm'
#define keyAEGetErrDescProc 	 	'indc'

/************ Error codes ***************/
/* OSL error codes: AEM proper uses up to -1719*/
#define errAEImpossibleRange		-1720 		/* A range like 3rd to 2nd, or 1st to all. */
#define errAEWrongNumberArgs		-1721 		/* Logical op kAENOT used with other than 1 term */

#define errAEAccessorNotFound 		-1723 		/* Accessor proc matching wantClass and containerType
												...or wildcards not found */
#define errAENoSuchLogical			-1725 	 	/* Something other than AND, OR, or NOT */
#define errAEBadTestKey				-1726 		/* Test is neither typeLogicalDescriptor
												...nor typeCompDescriptor */
#define errAENotAnObjSpec			-1727 	 	/* Param to AEResolve not of type 'obj ' */
#define errAENoSuchObject			-1728  		/* e.g.,: specifier asked for the 3rd, but there are only 2.
												...Basically, this indicates a run-time resolution error. */
#define errAENegativeCount			-1729 		/* CountProc returned negative value */
#define errAEEmptyListContainer		-1730 		/* Attempt to pass empty list as container to accessor */
	
/* Possible values for flags parameter to AEResolve.  They're additive */
#define kAEIDoMinimum				0x0000 
#define kAEIDoWhose					0x0001 
#define kAEIDoMarking				0x0004 


/* You only care about the constants that follow if you're doing your own whose
  clause resolution */
#define typeWhoseDescriptor			'whos'
#define formWhose					'whos'
#define typeWhoseRange				'wrng'
#define keyAEWhoseRangeStart		'wstr'
#define keyAEWhoseRangeStop			'wstp'
#define keyAEIndex					'kidx'
#define keyAETest					'ktst'

struct ccntTokenRecord {		/* used for rewriting tokens in place of 'ccnt' descriptors		*/
		DescType tokenClass ;	/* This record is only of interest to those who, when they...	*/
		AEDesc token ;			/* ...get ranges as key data in their accessor procs, choose	*/
	} ;							/* ...to resolve them manually rather than call AEResolve again.	*/
	
typedef struct ccntTokenRecord ccntTokenRecord, *ccntTokenRecPtr, **ccntTokenRecHandle ;

typedef AEDesc *DescPtr, **DescHandle ;

/* typedefs providing type checking for procedure pointers */

typedef pascal OSErr (*accessorProcPtr) ( DescType desiredClass,
		const AEDesc *container, DescType containerClass, DescType form,
		const AEDesc *selectionData, AEDesc *value, long LongInt ) ;

typedef pascal OSErr (*compareProcPtr)( DescType oper, const AEDesc *obj1,
			const AEDesc *obj2, Boolean *result ) ;
typedef pascal OSErr (*countProcPtr)( DescType desiredType, DescType containerClass,
			const AEDesc *container, long *result ) ;
typedef pascal OSErr (*disposeTokenProcPtr)( AEDesc *unneededToken ) ;

typedef pascal OSErr (*getMarkTokenProcPtr)( const AEDesc *dContainerToken, DescType containerClass,
			AEDesc *result ) ;


typedef pascal OSErr (*getErrDescProcPtr)( DescPtr *appDescPtr ) ;

/* Note: app is supposed to dispose of dToken after marking */
typedef pascal OSErr (*markProcPtr)( const AEDesc *dToken, const AEDesc *markToken, long index ) ;
typedef pascal OSErr (*adjustMarksProcPtr)( long newStart, long newStop, const AEDesc *markToken ) ;



/*——————————————————————————————— PUBLIC PROCEDURES —————————————————————————————————*/


pascal OSErr  AEObjectInit() ;
/* Not done by inline, but by direct linking into code.  It sets up the pack
  such that further calls can be via inline */

pascal OSErr AESetObjectCallbacks(
							compareProcPtr		myCompareProc,
							countProcPtr		myCountProc,
							disposeTokenProcPtr myDisposeTokenProc,	
							getMarkTokenProcPtr myGetMarkTokenProc,			/* called when mark (below) is true (all 3)*/
							markProcPtr			myMarkProc,
							adjustMarksProcPtr	myAdjustMarksProc,
							getErrDescProcPtr	myGetErrDescProcPtr )
= { 0x303C, 0x0E35, 0xA816 } ;




pascal OSErr  AEResolve		(	const AEDesc	*objectSpecifier,
								short			callbackFlags,		/* see above for possible values */
					  			AEDesc			*theToken )
= { 0x303C, 0x0536, 0xA816 } ;


pascal OSErr AEInstallObjectAccessor(
								DescType		desiredClass,
							   	DescType		containerType,
							   	accessorProcPtr theAccessor,
							   	long			accessorRefcon,
							   	Boolean			isSysHandler )
= { 0x303C, 0x0937, 0xA816 } ;

pascal OSErr AERemoveObjectAccessor(
								DescType		desiredClass,
								DescType		containerType,
								accessorProcPtr theAccessor,
								Boolean			isSysHandler )
= { 0x303C, 0x0738, 0xA816 } ;

pascal OSErr AEGetObjectAccessor(
								DescType 		desiredClass,
								DescType		containerType,
								accessorProcPtr	*accessor,
								long			*accessorRefcon,
								Boolean			isSysHandler )
= { 0x303C, 0x0939, 0xA816 } ;

pascal OSErr AEDisposeToken( AEDesc *theToken )
= { 0x303C, 0x023A, 0xA816 } ;

pascal OSErr AECallObjectAccessor(	DescType		desiredClass,
									const AEDesc	*containerToken,
									DescType		containerClass,
									DescType		keyForm,
									const AEDesc	*keyData,
									AEDesc			*token )
= { 0x303C, 0x0C3B, 0xA816 } ;




/*
Here are the interfaces your callback procs must be written to:

pascal OSErr MyCompareProc( DescType comparisonOperator, const AEDesc *theObject,
		const AEDesc *descOrObj, Boolean *result ) ;
pascal OSErr MyCountProc( DescType desiredType, DescType containerClass,
			const AEDesc *container, long *result:  ) ;
pascal OSErr MyGetMarkToken( const AEDesc *containerToken, DescType containerClass,
		AEDesc *result ) ;
pascal OSErr MyMark( const AEDesc *theToken, const AEDesc *markToken, long markCount ) ;
pascal OSErr MyAdjustMarks( long newStart, long newStop, const AEDesc *markToken ) ;
pascal OSErr MyMyDisposeToken( AEDesc *unneededToken ) ;
pascal OSErr MyGetErrDesc( DescPtr *appDescPtr ) ;

pascal OSErr MyObjectAccessor( DescType desiredClass, const AEDesc *containerToken,
		DescType containerClass, DescType keyForm, const AEDesc *keyData,
		AEDesc *theToken, long *theRefcon ) ;

You'll probably want to have a number of these last ones.
A proc that finds a line within a document should be installed with 'line' and 'docu'
as the desiredClass and containerClass fields in the call to AEInstallObjectHandler().
*/

#endif
