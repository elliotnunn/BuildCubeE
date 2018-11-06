/*
	LEGALESE:	© 1988-1990 Apple Computer, Inc.  All Rights Reserved
	
	PROJECT:	Installer 3.3
	
	PROGRAM:	Installer
	
	AUTHORS:	Bruce Jones, Cindy Frost, Bobby Carp
	
	PURPOSE:	This file contains all the resource templates necessary to
				create installer scripts.

	CHANGE HISTORY (most recent first):

		<28>	 6/16/91	KBA		Add defines for resource attributes.  Removed 2nd version of
		<27>	 5/14/91	KBA		Added flag to Format1 for stopping cursors during action atom.
									Created 2nd version inra with split resource info.
		<26>	 4/18/91	KBA		Moved to new project InstallerTypes. Added 'inff' template for
									installing split font resources.
		<25>	 1/15/91	BAC		Changing project to Installer 3.2.
		<24>	 1/10/91	BAC		Adding the type definition for the 'invs' required Installer
									application version resource.
		<22>	 12/6/90	BAC		Changing 'alwaysCopy' (opposite of updateOnly) to something that
									doesn't semantically conflict with keepExisting.
		<21>	 12/5/90	BKJ		Clean up capitalization as per Jon Zap's request.
		<20>	11/27/90	BKJ		Let scriptwriters have control of when an installation requires
									a restart. This means adding the dontForceRestart/forceRestart
									flag to packages.
		<19>	 11/2/90	BAC		We need to define REGION for people who are using pre-7.0
									interfaces.
		<18>	 11/2/90	BKJ		Fix typos
		<17>	  9/3/90	BAC		Added the LONGINT refCon field to the 'inaa' and
									checkUserFunction definitions.
		<15>	  8/1/90	BKJ		Fixing bug in indo resource template
		<14>	 7/28/90	BKJ		Add AlwaysTrue key resource type
				 7/13/90	BKJ		Fixing Format for the Facist Nazi Header stuff
				 4/27/90	BKJ		Cleaned up for Developer's Conference release.  Removed all old
									Default Maps stuff.
				  4/5/90	BKJ		Added 3 new clause types - reportError, addAuditRecord, checkAuditRecord
				 2/14/90	BKJ		Added 'indo' template for ordering disks.  (Happy Valentine's Day)
				 12/2/89	BKJ		Changed format1 default maps to rules & default maps
									groups to rule frameworks
				 9/12/89	BKJ		Made major changes for support of format1 default maps
				 9/12/89	BKJ		Changed 'indg' to support a list of IDs rather than a range
				 9/12/89	CIF		Added types for Installer action atoms
				 9/11/89	BKJ		Added types for default map groups
				 9/11/89	BKJ		Forked off of 6.0.4 final
				 7/25/89	BKJ		Added support for international keyboards
				 2/17/89			ALPHA 7 Release
				 1/12/89			ALPHA 6 Release
				12/19/88			ALPHA 5
				 5/26/88	CIF		Created
				 9/14/88			ALPHA 2 Release
*/


#include "SysTypes.r"									/* For region codes */

/* For those using pre-7.0 "SysTypes.r" we need to define region.  It used */
/* to be country, but became region in 7.0 */

#ifndef region
#define region country
#endif


/*----------------------------Installer 3.0 Scripts-----------------------------------*/

#define evenPaddedString																						\
	pstring;																									\
	align word


#define OSType																									\
	literal longint
	
	
#define rsrcType																								\
	OSType												/* type of a rsrc which must exist in system */			\
		patchrsrcType = 'PTCH',																					\
		userFunctionType = 'infn',																				\
		auditrsrcType = 'audt'


#define rsrcID																									\
	integer												/* ID of a rsrc which must exist in system */			\
		macPlusPatch = 117,																						\
		macSEPatch = 630,																						\
		macIIPatch = 376,																						\
		portablePatch = 890,																					\
		macIIciPatch = 1660,																					\
		oldAuroraPatch = 1657


#define RsrcName																								\
	evenPaddedString

/*
§ --------------------------------- Packages ---------------------------------*/
#define	packageFlags 																							\
		boolean		doesntShowOnCustom, showsOnCustom;		/* should show up on Custom screen	 */				\
		boolean		notRemovable, removable;				/* this package can be removed	 */					\
		boolean		forceRestart, dontForceRestart;			/* should installing this package for a restart? */	\
		fill bit[13]										/* Reserved */ 
#define	notShowsOnCustom	doesntShowOnCustom				/* Old wording */

#define	partSpec																								\
		rsrcType;											/* Part Type: inpk, infa, inra… */ 				\
		rsrcID												/* Part ID */


type 'inpk' {
		switch {
			case format0:
				key integer = 0;							/* Package Format version */
				packageFlags;								/* Package Flags */
				unsigned integer;							/* icmt ID */
				unsigned longint;							/* Package Size */
				evenPaddedString;							/* Package Name */
				unsigned integer = $$CountOf(partsList);	/* Parts List */
				wide array partsList {
					partSpec;								/* Parts Spec */
				};
	
		};
};


type 'icmt' {												/* Installer comment */
		unsigned hex longint;								/* Creation Date  */
		unsigned hex longint;								/* Version */
		rsrcID;												/* Icon ID */
		evenPaddedString;									/* Comment Text */
};

/*
§ --------------------------------- File Specs ---------------------------------*/
#define fileSpecID																								\
		rsrcID


#define	fileSpecFlags																							\
		boolean		noSearchForFile, SearchForFile;			/* Search (tgt only) if not found in given path*/	\
		boolean		TypeCrNeedNotMatch, TypeCrMustMatch;	/* Type and creator must match	*/					\
		fill bit[14]										/* currently unused	*/
#define	noTypeCrMustMatch	TypeCrNeedNotMatch

type	'infs' {														
		literal longint;									/* File Type	*/
		literal longint;									/* File Creator	*/
		unsigned hex longint;								/* Creation Date*/ 
		fileSpecFlags;										/* File Spec Flags */
		evenPaddedString;									/* Full Path */
};

/*
§ --------------------------------- File Atoms ---------------------------------*/
#define	opcodeFlags 																							\
		boolean		dontDeleteWhenRemoving, deleteWhenRemoving;			/* Remove file or rsrc if remove clicked */	\
		boolean		dontDeleteWhenInstalling, deleteWhenInstalling;		/* Delete target before copy	*/			\
		boolean		dontCopy, copy;							/* Copy file or rsrc to destination */				\
		fill bit[3]											/* Reserved */
#define	delRemove		deleteWhenRemoving
#define	noDelRemove		dontDeleteWhenRemoving
#define	delInstall		deleteWhenInstalling
#define	noDelInstall	dontDeleteWhenInstalling
#define	noCopy			dontCopy


#define	fileAtomFlags																							\
		opcodeFlags;																							\
		fill bit[5]; 																							\
		boolean		updateEvenIfNewer, leaveAloneIfNewer; 	/* OK for a newer version of this file to exist */	\
		boolean		updateExisting, keepExisting;			/* Keep tgt file if it already exists */			\
		boolean		copyIfNewOrUpdate, copyIfUpdate;		/* Only update if target exists	*/					\
		boolean		noRsrcFork, rsrcFork;					/* Apply operation to rsrc fork */					\
		boolean		noDataFork, dataFork					/* Apply operation to data fork	*/
#define	noLeaveAloneIfNewer	updateEvenIfNewer
#define	noKeepExisting		updateExisting
#define	noUpdateOnly		copyIfNewOrUpdate
#define updateOnly			copyIfUpdate


type 'infa' {
		switch {
			case format0:
				key integer = 0;							/* File Atom Format version */
				fileAtomFlags;								/* File Atom Flags		  */
				rsrcID;										/* tgt file spec ID */
				rsrcID;										/* src file spec ID */
				unsigned longInt;							/* File Size     */
				evenPaddedString;							/* Atom Description     */
		};
};

/*
§ -------------------------------- Resource Atoms ---------------------------------*/
#define	resourceAtomFlags																						\
		opcodeFlags;																							\
		fill bit[3];										/* Reserved	*/										\
		boolean		noTgtRequired, tgtRequired;				/* target req or can be created by another inra */	\
		boolean		updateExisting, keepExisting;			/* Keep tgt rsrc if it already exists */			\
		boolean		copyIfNewOrUpdate, copyIfUpdate;		/* Only update if target exists	*/					\
		boolean		dontIgnoreProtection, ignoreProtection;	/* Do it even if rsrc protected */					\
		boolean		srcNeedExist, srcNeedNotExist;			/* Rsrc need not exist on source */					\
		boolean		byName, byID;							/* Use name or id to find rsrc	*/					\
		boolean		nameNeedNotMatch, nameMustMatch			/* name must match*/
#define	evenIf				ignoreProtection
#define	noEvenIf			dontIgnoreProtection
#define	noByID				byName
#define	notNameMustMatch	nameNeedNotMatch

type 'inra' {
		switch {
			case format0:
				key integer = 0;							/* Resource Atom Format version */
				resourceAtomFlags;							/* Resource Atom Flags */
				rsrcID;										/* tgt file spec ID */
				rsrcID;										/* src file spec ID */
				rsrcType;									/* Resource Type */
				integer;									/* Source ID */
				integer;									/* Target ID */
				unsigned longInt;							/* Resource Size */
				evenPaddedString;							/* Atom Description */
				evenPaddedString;							/* Resource Name */
		};
};
/*
§ --------------------------------- Boot Block Atoms ---------------------------------*/
#define	bootBlockAtomFlags																						\
		fill bit[14];																							\
		boolean		dontChangeOnInstall, changeOnInstall;	/* change parameter if we're installing */			\
		boolean		dontChangeOnRemove, changeOnRemove		/* change parameter if we're removing */ 
#define	notChangeOnInstall	dontChangeOnInstall
#define	notChangeOnRemove	dontChangeOnRemove

#define	BootBlockUpdateFlags																					\
		fill bit[7];																							\
		boolean		replaceBBSysName, 																			\
					saveBBSysName; 																				\
		boolean		replaceBBShellName, 																		\
					saveBBShellName;																			\
		boolean		replaceBBDbg1Name, 																			\
					saveBBDbg1Name; 																			\
		boolean		replaceBBDbg2Name, 																			\
					saveBBDbg2Name; 																			\
		boolean		replaceBBScreenName, 																		\
					saveBBScreenName; 																			\
		boolean		replaceBBHelloName, 																		\
					saveBBHelloName; 																			\
		boolean		replaceBBScrapName,																			\
					saveBBScrapName; 																			\
		boolean		replaceBBCntFCBs, 																			\
					maxBBCntFCBs; 																				\
		boolean		replaceBBCntEvts, 																			\
					maxBBCntEvts


type 'inbb' {
		switch {
			case format0:
				key integer = 0;							/* Boot Block Format version */
				bootBlockAtomFlags;							/* Boot Block Atom Flags	  */
						
						/* now case off the type for the boot block value */
				switch {
					case bbUpdate:
						key integer = -1;
						rsrcID;								/* The file spec ID for the source of the 'boot' resource */
						bootBlockUpdateFlags;
						
					case bbID:
						key integer = 1;
						decimal integer;
					
					case bbEntry:
						key integer = 2;
						decimal longint;
						
					case bbVersion:
						key integer = 3;
						decimal integer;
						
					case bbPageFlags:
						key integer = 4;
						decimal integer;
						
					case bbSysName:
						key integer = 5;
						evenPaddedString;
						
					case bbShellName:
						key integer = 6;
						evenPaddedString;
						
					case bbDbg1Name:
						key integer = 7;
						evenPaddedString;
						
					case bbDbg2Name:
						key integer = 8;
						evenPaddedString;
						
					case bbScreenName:
						key integer = 9;
						evenPaddedString;
						
					case bbHelloName:
						key integer = 10;
						evenPaddedString;
						
					case bbScrapName:
						key integer = 11;
						evenPaddedString;
						
					case bbCntFCBs:
						key integer = 12;
						decimal integer;
						
					case bbCntEvts:
						key integer = 13;
						decimal integer;
						
					case bb128KSHeap:
						key integer = 14;
						decimal longint;
						
					case bb256KSHeap:
						key integer = 15;
						decimal longint;
						
					case bb512KSHeap:
						key integer = 16;
						decimal longint;
						
					case bbSysHeapSize:						/* Note - same as 512 */
						key integer = 16;
						decimal longint;
						
					case bbSysHeapExtra:
						key integer = 18;
						decimal longint;
						
					case bbSysHeapFract:
						key integer = 19;
						decimal longint;
				};
				evenPaddedString;								/* Boot Block Atom Description */
		};
};


/*
§ --------------------------------- Action Atoms ---------------------------------*/

#define	whenToActAAFlags																					\
		boolean		actAfter,				/* Call this proc after all installations */					\
					actBefore;				/* Call this proc before all installations */					\
		boolean		dontActOnRemove, 																		\
					actOnRemove;			/* Call this proc when doing a remove */						\
		boolean		dontActOnInstall, 																		\
					actOnInstall			/* Call this proc when doing an Install */


#define	actionAtomFlagsFormat0																				\
		fill bit[13];																						\
		whenToActAAFlags

#define	actionAtomFlagsFormat1																				\
		fill bit[12]; 																						\
		boolean		continueBusyCursors,	/* Allow Installer busy cursor during call (3.3+ Only) */		\
					suspendBusyCursors;		/* Stop Installer busy cursor before call (3.3+ Only) */		\
		whenToActAAFlags

type 'inaa' {
		switch {
			case format0:
				key integer = 0;			/* Action Atom Format version */
				actionAtomFlagsFormat0;		/* Action Atom Flags for Format 0 */
				partSpec;					/* Resource type & id for executable resource */
				longint;					/* RefCon that's passed to the executable resource */
				evenPaddedString;			/* Atom Description     */
				
			case format1:
				key integer = 1;			/* Action Atom Format version.  Use with Installer 3.3 and newer */
				actionAtomFlagsFormat1;		/* Action Atom Flags for Format 1 */
				partSpec;					/* Resource type & id for executable resource */
				longint;					/* RefCon that's passed to the executable resource */
				evenPaddedString;			/* Atom Description     */
		};
};

/*
§ --------------------------------- Audit Trail Atoms ---------------------------------*/
type 'inat' {
		switch {
			case format0:
				key integer = 0;							/* Version */
				fileSpecID;									/* Target File Spec */
				OSType;										/* Selector */
				literal longint;							/* Value */
			};
};

/*
§ --------------------------------- Installer Rules ---------------------------------*/

#define Version																									\
	hex byte;												/* System file Major revision in BCD*/				\
	hex byte;												/* System file Minor revision in BCD*/				\
	hex byte	development = 0x20,							/* System file Release stage		*/				\
				alpha = 0x40, beta = 0x60,																		\
				final = 0x80, release = 0x80;																	\
	hex byte												/* Non Final */
	
	
/* Note that if the minimal & maximal target disk sizes are both 0, any volume will match */
/* If the Minimal is > 0 and the maximal = 0, then only the minimum requirement is used */
#define TargetVolReqs										/* Required Target Volume Description */			\
	decimal longint											/* Minimal Target Disk Size */						\
		floppy = 0,																								\
		hdFloppy = 1400,																						\
		hardDisk = 10000;																						\
	decimal longint											/* Maximal Target Disk Size */						\
		floppy = 900,																							\
		hdFloppy = 1500,																						\
		hardDisk = 0
	
	
#define IntegerList																								\
	unsigned integer = $$CountOf(IntegerArray);																	\
	array IntegerArray {																						\
		integer;																								\
	}


#define LongIntList																								\
	unsigned integer = $$CountOf(LongIntArray);																	\
	array LongIntArray {																						\
		longint;																								\
	}


#define packageList																								\
	IntegerList


#define assertionList																							\
	IntegerList
	
	
#define gestaltList																								\
	LongIntList


#define	alwaysFalseKey							-2
#define	alwaysTrueKey							-1
#define	checkGestaltKey							1
#define checkMinMemoryKey						2
#define	checkFileDataForkExistsKey				3
#define	checkFileRsrcForkExistsKey				4
#define	checkFileContainsRsrcByIDKey			5
#define	checkFileContainsRsrcByNameKey			6
#define	checkFileVersionKey						7
#define	checkFileCountryCodeKey					8
#define	checkTgtVolSizeKey						9
#define	checkUserFunctionKey					10
#define	checkAllAssertionsKey					11
#define	checkAnyAssertionKey					12
#define checkMoreThanOneAssertionKey			13
#define	addUserDescriptionKey					14
#define	addPackagesKey							15
#define	addAssertionKey							16
#define reportVolErrorKey						17
#define reportSysErrorKey						18
#define addAuditRecKey							19
#define checkAuditRecKey						20
#define checkAnyAuditRecKey						21



/* The Easy Install Rules */
type 'inrl' {
	switch {
		case format0:
			key integer = 0;
			hex integer = 0;											/* Rule Flags for future use */
			unsigned integer = $$CountOf(Rules);
			wide array Rules {
				switch {
					case alwaysFalse:
						key integer = alwaysFalseKey;
						
					case alwaysTrue:
						key integer = alwaysTrueKey;
						
					case checkGestalt:
						key integer = checkGestaltKey;
						OSType;											/* Gestalt selector */
						gestaltList;									/* Legal results */
					
					case checkMinMemory:
						key integer = checkMinMemoryKey;
						decimal longint;

					case checkFileDataForkExists:
						key integer = checkFileDataForkExistsKey;
						fileSpecID;
						
					case checkFileRsrcForkExists:
						key integer = checkFileRsrcForkExistsKey;
						fileSpecID;
						
					case checkFileContainsRsrcByID:
						key integer = checkFileContainsRsrcByIDKey;
						fileSpecID;
						rsrcType;
						rsrcID;
						
					case checkFileContainsRsrcByName:
						key integer = checkFileContainsRsrcByNameKey;
						fileSpecID;
						rsrcType;
						rsrcName;
						
					case checkFileVersion:
						key integer = checkFileVersionKey;
						fileSpecID;
						version;
						
					case checkFileCountryCode:
						key integer = checkFileCountryCodeKey;
						fileSpecID;
						integer Region;
						
					case checkTgtVolSize:
						key integer = checkTgtVolSizeKey;
						targetVolReqs;
						                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             						
					case checkUserFunction:
						key integer = checkUserFunctionKey;
						rsrcType;
						rsrcID;
						longint;					/* RefCon that's passed to the executable resource */
						
					case checkAllAssertions:
						key integer = checkAllAssertionsKey;
						assertionList;
						
					case checkAnyAssertion:
						key integer = checkAnyAssertionKey;
						assertionList;
						
					case checkMoreThanOneAssertion:
						key integer = checkMoreThanOneAssertionKey;
						assertionList;
						
					case addUserDescription:
						key integer = addUserDescriptionKey;
						evenPaddedString;
						
					case addPackages:
						key integer = addPackagesKey;
						packageList;
						
					case addAssertion:
						key integer = addAssertionKey;
						assertionList;
						
					case reportVolError:
						key integer = reportVolErrorKey;
						evenPaddedString;
						
					case reportSysError:
						key integer = reportSysErrorKey;
						evenPaddedString;
						
					case addAuditRec:
						key integer = addAuditRecKey;
						fileSpecID;
						OSType;
						literal longint;
						
					case checkAuditRec:
						key integer = checkAuditRecKey;
						fileSpecID;
						OSType;
						literal longint;
						
					case checkAnyAuditRec:
						key integer = checkAnyAuditRecKey;
						fileSpecID;
						OSType;
						longIntList;
						
			};
		};
	};
};


#define RuleList IntegerList
	
/* The rule framework */
type 'infr' {
	switch {
		case format0:
			key integer = 0;								/* Rule framework version */
			unsigned integer = $$CountOf(RuleArray);
			wide array RuleArray {
				boolean pickFirst, pickAll;					/* which packages to select? */						
				fill bit[15];
				ruleList;									/* List of rules */									
			};
	};
};


/* The list of disks we may need, and the order we want them to appear in */
/* This is optional. */
type 'indo' {
	switch {
		case format0:
			key integer = 0;								/* indo version */
			integer = $$Countof(StringArray);
			array StringArray {
					evenPaddedString;
			};
	};
};


/* This script resource defines the minimum Installer version that is required */
/* to run the script.  If an Installer app is launched that is older than this */
/* required version, the user receives a dialog telling him/her to run a newer Installer */
/* This is optional. */
type 'invs' {
	switch {
		case format0:
			key integer = 0;
			hex byte;												/* Major revision in BCD*/
			hex byte;												/* Minor vevision in BCD*/
			hex byte	development = 0x20,							/* Release stage		*/
						alpha = 0x40,
						beta = 0x60,
						final = 0x80, /* or */ release = 0x80;
			hex byte;												/* Non-final release #	*/
			pstring;												/* Short version number	*/
	};
};



/*
§ -------------------------------- Font Atom & Split Atom Stuff ---------------------------------*/

#define	Style																					\
	fill bit[9];										/* Reserved */							\
	Boolean		noExtendedStyle, extendedStyle;			/* Exteneded style */					\
	Boolean		noCondensedStyle, condensedStyle;		/* Condensed style */					\
	Boolean		noShadowStyle, 	shadowStyle;			/* Shadow style */						\
	Boolean		noOutlineStyle, outlineStyle;			/* Outline style */						\
	Boolean		noUnderlineStyle, underlineStyle;		/* Underline style */					\
	Boolean		noItalicStyle, italicStyle;				/* Italic style */						\
	Boolean		noBoldStyle, boldStyle;					/* Bold style */

#define	RsrcSpec																				\
		fileSpecID;										/* File spec for this resource */		\
		rsrcType;										/* Type of the resource	*/				\
		rsrcID;											/* ID of the resource */				\
		unsigned longInt;								/* Size in bytes of this resource	*/	\
		evenPaddedString								/* Name of the resource */				

#define	SrcPartsList									/* The list of pieces */				\
		integer = $$CountOf (Parts);					/* How many of them? */					\
		wide array Parts {																		\
			RsrcSpec;									/* Description of this piece */			\
		}

#define resSysHeap		64								/* Defines for resource attributes */
#define resPurgeable	32
#define resLocked		16
#define resProtected	8
#define resPreload		4
#define resChanged		2

#define Strike																					\
	integer;											/* Font size */							\
	Style;												/* Which styles? */						\
	RsrcType;											/* Target Font Resource Type */			\
	integer;											/* Target Attributes */					\
	SrcPartsList;										/* All of the pieces */
	
type 'inff' {
	switch {
		case format0:
			key integer = 0;							/*format version 0 */
			resourceAtomFlags;							/* flags */
			fileSpecID;									/* Target File Spec */
			fileSpecID;									/* Source File Spec of the FOND and all pieces, unless overriden by a split definition */
			integer;									/* Target FOND Attributes */
			unsigned longInt;							/* size in bytes of the complete family set */
			rsrcID;										/* source FOND's resource ID */
			switch {
			case entireFamily:
			 	key integer = 1;
			case explicitFamilyMembers:
				key integer = 2;
				unsigned integer = $$CountOf(StrikeEntries);
				wide array StrikeEntries {
					Strike;								/* Source for each of the points */
				};
			};
			evenPaddedString;							/* Atom Description */
			evenPaddedString;							/* the exact family name */
	};
};
			