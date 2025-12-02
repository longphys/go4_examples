//===================================================================
//== TNeMParms.h:	exp1210
//== Version: 			2010-11-1226
//===================================================================

#ifndef TNeMPARMS_H
#define TNeMPARMS_H

#include "TGo4Parameter.h"

class TNeMParms : public TGo4Parameter 
{
public:
	TNeMParms(const char* name = 0);
	virtual ~TNeMParms();
	virtual Bool_t   UpdateFrom(TGo4Parameter *);


	    Bool_t   fill;
   int mtracksx,mtracksy;
   
	
	ClassDef(TNeMParms,1)
};

#endif 
