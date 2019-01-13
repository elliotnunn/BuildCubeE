/************************************************************

Created: Thursday, September 7, 1989 at 9:13 PM
	ErrMgr.h
	C Interface to the Macintosh Libraries


	<<< Error File Manager Routines Interface File >>>
	
	Copyright Apple Computer, Inc.	1987-1990
	All rights reserved
	
	This file contains:
	
	InitErrMgr(toolname, sysename, Nbrs)  - ErrMgr initialization
	CloseErrMgr()						  - Close ErrMgr message files
	GetSysErrText(Nbr, Msg) 			  - Get a system error message for a number
	GetToolErrText(Nbr, Insert, Msg)	  - Get a tool error message for a number
	AddErrInsert(insert, msgString) 	  - Add an insert to a message
	addInserts(msgString, insert,...)	  - Add a number of inserts to a message
	

************************************************************/


#ifndef __ERRMGR__
#define __ERRMGR__

#ifndef __TYPES__
#include <Types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern void InitErrMgr(char *toolErrFilename,char *sysErrFilename,Boolean showToolErrNbrs);
/*
	ErrMgr initialization.This must be done before using any other ErrMgr
	routine.  Set showToolErrNbrs to true if you want all tool messages to contain
	the error number following the message text enclosed in parentheses (e.g.,
	"<msg txt> ([OS] Error <n>)"; system error messages always contain the error
	number).  The toolErrFileName parameter is used to specify the name of a
	tool-specific error file, and should be the NULL or a null string if not used
	(or if the tool's data fork is to be used as the error file, see
	GetToolErrText for futher details). The sysErrFileName parameter is used to
	specify the name of a system error file, and should normally be the NULL or a
	null string, which causes the ErrMgr to look in the MPW Shell directory for
	"SysErrs.Err" (see GetSysErrText).
	
	If InitErrMgr is NOT called prior to calling GetSysErrText or GetToolErrText,
	then those routines, the first time they are called, will call InitErrMgr as
	InitErrMgr(NULL, NULL, true).
	
	The following global may be set to true to allow a C caller to process all
	strings as Pascal strings:*/
	
	extern Boolean pascalStrings;	/* set to true for Pascal strings*//*
	
	This should be set PRIOR to calling InitErrMgr.  Once set, ALL strings, both
	those passed to the ErrMgr as filenames and error message inserts, as well as
	the messages returned by the ErrMgr will be Pascal strings.  There is NO
	guarantee a '\0' byte is at the end of the string.	Results are unpredictable
	if pascalStringsis set false after it has been set true!
	
*/

extern void CloseErrMgr(void);
/*
	Ideally a CloseErrMgr should be done at the end of execution to make sure all
	files opened by the ErrMgr are closed.	You can let normal program termination
	do the closing.  But if you are a purist...
*/

extern char *GetSysErrText(short msgNbr,char *errMsg);
/*
	Get the error message text corresponding to system error number errNbr from
	the system error message file (whose name was specified in the InitErrMgr
	call).	The text of the message is returned in errMsg and the function returns
	a pointer to errMsg.  The maximum length of the message is limited to 254
	characters.
	
	Note, if a system message filename was not specified to InitErrMgr, then the
	ErrMgr assumes the message file contained in the file "SysErrs.Err".  This
	file is first accessed as "{ShellDirectory}SysErrs.Err" on the assumption that
	SysErrs.Err is kept in the same directory as the MPW Shell.  If the file
	cannot be opened, then an open is attempted on "SysErrs.Err" in the System
	Folder.
*/

extern char *GetToolErrText(short msgNbr,char *errInsert,char *errMsg); 
/*
	Get the error message text corresponding to tool error number errNbr from
	the tool error message file (whose name was specified in the InitErrMgr
	call).	The text of the message is returned in errMsg and the function returns
	a pointer to errMsg.  The maximum length of the message is limited to 254
	characters.  If the message is to have an insert, then ErrInsert should be a
	pointer to it.	Otherwise it should be either be a null string or a NULL
	pointer.
	
	Inserts are indicated in error messages by specifying a '^' to indicate where
	the insert is to be placed.
	
	Note, if a tool message filename was not specified to InitErrMgr, then the
	ErrMgr assumes the message file contained in the data fork of the tool calling
	the ErrMgr.  This name is contained in the Shell variable {Command} and the
	value of that variable is used to open the error message file.
*/

extern void AddErrInsert(unsigned char *insert,unsigned char *msgString);
/*
	Add another insert to an error message string.This call is used when more
	than one insert is to be added to a message (because it contains more than
	one '^' character).
*/

extern unsigned char *addInserts(unsigned char *msgString,unsigned char *insert,
	... );
/*
	Add a set of inserts to an error message string.  AddErrInsert is called for
	each insert parameter specified.
*/
#ifdef __cplusplus
}
#endif

#endif
