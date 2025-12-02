//===================================================================
//== TNeSel.h:	exp0211
//== Version: 2011-03-01
//===================================================================

#ifndef TNeSEL_H
#define TNeSEL_H

#include "TGo4Parameter.h"

class TNeSel : public TGo4Parameter 
{
public:
	TNeSel(const char* name = 0);
	virtual ~TNeSel();
	virtual Bool_t   UpdateFrom(TGo4Parameter *);
	int CheckValue(double val);

	double lval;
	double uval;
	
	ClassDef(TNeSel,1)
};

#endif 
