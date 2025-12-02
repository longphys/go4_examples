//===================================================================
//== TNeSel.cxx: exp0211
//== Version: 2011-03-01
//===================================================================
using namespace std;

#include "TNeSel.h"

#include <stdio.h>
#include "Riostream.h"


//***********************************************************
TNeSel::TNeSel(const char* name)
	:TGo4Parameter(name)
	,lval(0.)
	,uval(4096.)
{
;
} //----------------------------------------------------------------

TNeSel::~TNeSel()
{
} //-----------------------------------------------------------------

Bool_t TNeSel::UpdateFrom(TGo4Parameter *source)
{
	cout << "**** TNeDet1 " << GetName() 
		<< " updated from auto save file" << endl;

	TNeSel * from = dynamic_cast<TNeSel *>(source);

	if(from==0) 
	{
		cout << "Wrong parameter class: " 
			<< source->ClassName() << endl;
		return kFALSE;
	}


	lval = from->lval;
	uval = from->uval;
	return kTRUE;
} //-----------------------------------------------------------------


int TNeSel::CheckValue(double val)
{
	if(val > lval && val < uval) return 1;
	return 0;
} //-----------------------------------------------------------------

