/************************************************************

Created: Wednesday, October 21, 1992 at 2:55 PM
 Components.h
 C Interface to the Macintosh Libraries


 Copyright Apple Computer, Inc. 1991, 1992
 All rights reserved

************************************************************/

#ifndef __COMPONENTS__
#define __COMPONENTS__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifndef __MEMORY__
#include <Memory.h>
#endif

#ifndef kSmallestArray
	#define kSmallestArray 1
#endif

#define gestaltComponentMgr 'cpnt'

#define	kAnyComponentType			0
#define	kAnyComponentSubType		0
#define	kAnyComponentManufacturer	0
#define	kAnyComponentFlagsMask		0

#define cmpWantsRegisterMessage 1L<<31

typedef struct
	{
	OSType componentType;					/* A unique 4-byte code indentifying the command set */
	OSType componentSubType;				/* Particular flavor of this instance */
	OSType componentManufacturer;			/* Vendor indentification */
	unsigned long componentFlags;			/* 8 each for Component,Type,SubType,Manuf/revision */
	unsigned long componentFlagsMask;		/* Mask for specifying which flags to consider in search, zero during registration */
	} ComponentDescription;


typedef struct
	{
	OSType resType;							/* 4-byte code 	*/
	short resID;							/*  			*/
	} ResourceSpec;


struct ComponentResource {
	ComponentDescription cd;				/* Registration parameters */
	ResourceSpec component;					/* resource where Component code is found */
	ResourceSpec componentName;				/* name string resource */
	ResourceSpec componentInfo;				/* info string resource */
	ResourceSpec componentIcon;				/* icon resource */
};
typedef struct ComponentResource ComponentResource;
typedef ComponentResource *ComponentResourcePtr, **ComponentResourceHandle;


#ifndef _PrivateThingManager_
	typedef struct privateComponentRecord *Component;
	typedef struct privateComponentInstanceRecord *ComponentInstance;
#endif _PrivateThingManager_


/*  Structure received by Component:		*/

typedef struct
	{
	unsigned char flags;				/* call modifiers: sync/async, deferred, immed, etc */
	unsigned char paramSize;			/* size in bytes of actual parameters passed to this call */
	short what;							/* routine selector, negative for Component management calls */
	long params[kSmallestArray];		/* actual parameters for the indicated routine */
	} ComponentParameters;


typedef long ComponentResult;

typedef pascal ComponentResult (*ComponentRoutine)
		(ComponentParameters *cp, Handle componentStorage );

typedef pascal ComponentResult (*ComponentFunction)();



#define ComponentCallNow(callNumber, paramSize) {0x2f3c,paramSize,callNumber,0x7000,0xA82A}

/********************************************************
* Required Component routines
********************************************************/

#define kComponentOpenSelect	 -1			/* ComponentInstance for this open */
#define kComponentCloseSelect	 -2			/* ComponentInstance for this close */
#define kComponentCanDoSelect	 -3			/* selector # being queried */
#define kComponentVersionSelect	 -4			/* no params */
#define kComponentRegisterSelect -5			/* no params */
#define kComponentTargetSelect 	 -6			/* ComponentInstance for top of call chain */

enum {				/* Set Default Component flags */
	defaultComponentIdentical		= 0,
	defaultComponentAnyFlags		= 1,
	defaultComponentAnyManufacturer	= 2,
	defaultComponentAnySubType		= 4
	};
	
#define defaultComponentAnyFlagsAnyManufacturer defaultComponentAnyFlags+defaultComponentAnyManufacturer
#define defaultComponentAnyFlagsAnyManufacturerAnySubType  defaultComponentAnyFlags+defaultComponentAnyManufacturer+defaultComponentAnySubType

enum {					/* errors from component manager & components  */
	invalidComponentID = -3000,
	validInstancesExist = -3001,
	componentNotCaptured = -3002,
	componentDontRegister = -3003
};

#define badComponentInstance	0x80008001
#define badComponentSelector	0x80008002

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

/********************************************************
*														*
*  				APPLICATION LEVEL CALLS					*
*														*
********************************************************/

/********************************************************
* Component Database Add, Delete, and Query Routines 
********************************************************/

pascal Component RegisterComponent(ComponentDescription *cd, ComponentRoutine componentEntryPoint, short global, Handle componentName, Handle componentInfo, Handle componentIcon)
		= {0x7001,0xA82A};
pascal Component RegisterComponentResource(ComponentResourceHandle cr, short global)
		= {0x7012,0xA82A};
pascal OSErr UnregisterComponent(Component aComponent)
		= {0x7002,0xA82A};

pascal Component FindNextComponent(Component aComponent, ComponentDescription *looking)
		= {0x7004,0xA82A};
pascal long CountComponents(ComponentDescription *looking)
		= {0x7003,0xA82A};

pascal OSErr GetComponentInfo(Component aComponent, ComponentDescription *cd, Handle componentName, Handle componentInfo, Handle componentIcon)
		= {0x7005,0xA82A};
pascal long GetComponentListModSeed( void )
		= {0x7006,0xA82A};

/********************************************************
* Component Instance Allocation and dispatch routines 
********************************************************/

pascal ComponentInstance OpenComponent(Component aComponent)
		= {0x7007,0xA82A};
pascal OSErr CloseComponent(ComponentInstance aComponentInstance)
		= {0x7008,0xA82A};

pascal OSErr GetComponentInstanceError(ComponentInstance aComponentInstance)
		= {0x700A,0xA82A};

/* direct calls to the Components */

pascal long ComponentFunctionImplemented(ComponentInstance ci, short ftnNumber) = {0x2F3C,0x2,0xFFFD,0x7000,0xA82A};
pascal long GetComponentVersion(ComponentInstance ci) = {0x2F3C,0,0xFFFC,0x7000,0xA82A};
pascal long ComponentSetTarget(ComponentInstance ci, ComponentInstance target) = {0x2F3C,0x4,0xFFFA,0x7000,0xA82A};


/********************************************************
*														*
*  					CALLS MADE BY ComponentS		  		*
*														*
********************************************************/

/********************************************************
* Component Management routines
********************************************************/

pascal void SetComponentInstanceError(ComponentInstance aComponentInstance, OSErr theError)
		= {0x700B,0xA82A};

pascal long GetComponentRefcon(Component aComponent)
		= {0x7010,0xA82A};
pascal void SetComponentRefcon(Component aComponent, long theRefcon)
		= {0x7011,0xA82A};

pascal short OpenComponentResFile(Component aComponent)
		= {0x7015,0xA82A};
pascal OSErr CloseComponentResFile(short refnum)
		= {0x7018,0xA82A};

/********************************************************
* Component Instance Management routines
********************************************************/

pascal Handle GetComponentInstanceStorage(ComponentInstance aComponentInstance)
		= {0x700C,0xA82A};
pascal void SetComponentInstanceStorage(ComponentInstance aComponentInstance, Handle theStorage)
		= {0x700D,0xA82A};

pascal long GetComponentInstanceA5(ComponentInstance aComponentInstance)
		= {0x700E,0xA82A};
pascal void SetComponentInstanceA5(ComponentInstance aComponentInstance, long theA5)
		= {0x700F,0xA82A};

pascal long CountComponentInstances(Component aComponent)
		= {0x7013,0xA82A};

/* useful helper routines for convenient method dispatching */

pascal long CallComponentFunction(ComponentParameters *params, ComponentFunction func ) = {0x70FF,0xA82A};
pascal long CallComponentFunctionWithStorage(Handle storage, ComponentParameters *params, ComponentFunction func ) = {0x70FF,0xA82A};

pascal long DelegateComponentCall( ComponentParameters *originalParams, ComponentInstance ci ) = {0x7024,0xA82A};

pascal OSErr SetDefaultComponent( Component aComponent, short flags )
		= {0x701E,0xA82A};
pascal ComponentInstance OpenDefaultComponent( OSType componentType, OSType componentSubType )
		= {0x7021,0xA82A};

pascal Component CaptureComponent( Component capturedComponent, Component capturingComponent )
		= {0x701C,0xA82A};
pascal OSErr UncaptureComponent( Component aComponent )
		= {0x701D,0xA82A};

pascal long RegisterComponentResourceFile(short resRefNum, short global)
		= {0x7014,0xA82A};


#ifdef __cplusplus
}
#endif __cplusplus

#endif __COMPONENTS__
