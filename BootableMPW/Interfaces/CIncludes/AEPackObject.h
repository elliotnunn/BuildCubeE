/************************************************************************************
											
	©Apple Computer, Inc.  1991 			
	      All Rights Reserved.				

************************************************************************************/

#ifndef __AEOBJECTPACKING__
#define __AEOBJECTPACKING__

#ifndef __APPLEEVENTS__
#include <AppleEvents.h>
#endif


/* These are the object packing routines.  */

pascal OSErr CreateOffsetDescriptor(	long theOffset,
										AEDesc *theDescriptor ) ;

pascal OSErr CreateCompDescriptor(		DescType comparisonOperator,
										AEDesc* operand1,
										AEDesc* operand2,
										Boolean disposeInputs,
										AEDesc* theDescriptor ) ;
								
pascal OSErr CreateLogicalDescriptor(	AEDescList *theLogicalTerms, 		/* a list of comb and logi terms */
										DescType theLogicOperator, 			/* the operator, e.g. AND */
										Boolean disposeInputs,
										AEDesc *theDescriptor ) ; 


pascal OSErr CreateObjSpecifier(		DescType desiredClass,
										AEDesc *theContainer, 
										DescType keyForm,
										AEDesc *keyData, 
										Boolean disposeInputs,
										AEDesc *objSpecifier ) ;
							
pascal OSErr CreateRangeDescriptor(		AEDesc *rangeStart,	
										AEDesc *rangeStop,
										Boolean disposeInputs,
										AEDesc *theDescriptor ) ;


#endif
