//===================================================================
//== TNe1HParms.cpp: exp1210
//== Version: 			2010-11-26
//===================================================================
using namespace std;
#include "TNeMParms.h"

#include <stdio.h>
#include "Riostream.h"

//const int mchan = 32;
//const int m     = 3;

//***********************************************************
TNeMParms::TNeMParms(const char* name)
	:TGo4Parameter(name),
	fill(kTRUE)
{

} //----------------------------------------------------------------

TNeMParms::~TNeMParms()
{
} //-----------------------------------------------------------------

Bool_t TNeMParms::UpdateFrom(TGo4Parameter *source)
{
	cout << "**** TNeHParm " << GetName() 
		<< " updated from auto save file" << endl;

	TNeMParms * from = dynamic_cast<TNeMParms *>(source);

	if(from==0) 
	{
		cout << "Wrong parameter class: " 
			<< source->ClassName() << endl;
		return kFALSE;
	}

     fill  = from->fill;
	mtracksx  = from->mtracksx;
	mtracksy  = from->mtracksy;
	
  return kTRUE;
} //-----------------------------------------------------------------

