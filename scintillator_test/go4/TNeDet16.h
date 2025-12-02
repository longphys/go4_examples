//===================================================================
//== TNeDet1.h:	exp0211
//== Version: 2011-02-01
//===================================================================

#ifndef TNeDet16_H
#define TNeDet16_H

#include "TGo4Parameter.h"

class TNeDet16 : public TGo4Parameter 
{
public:
	TNeDet16(const char* name = 0);
	virtual ~TNeDet16();
	virtual Bool_t   UpdateFrom(TGo4Parameter *);
	void ReadData();
	double Energy(double value, int chan);


	int kread;
	int n;
	int nchan;
	double a[32][3];  
	
	ClassDef(TNeDet16,1)
};

#endif 
