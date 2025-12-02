//===================================================================
//== TNeAnalysis.h:	exp1210
//== Version:	2010-11-12
//===================================================================

#ifndef TNeANALYSIS_H
#define TNeANALYSIS_H

#include "TGo4Analysis.h"
#include "TGo4WinCond.h"

class TGo4MbsEvent;
class TNeDet16;
class TNeMParms;
class TNeSel;

class TNeAnalysis : public TGo4Analysis 
{
private:
	TGo4MbsEvent*  fMbsEvent;
	Int_t          fEvents;
	Int_t          fLastEvent;

public:
	TNeAnalysis();
	TNeAnalysis(int argc, char** argv);
	virtual ~TNeAnalysis() ;
	virtual Int_t UserPreLoop();
	virtual Int_t UserEventFunc();
	virtual Int_t UserPostLoop();

//	TNeMParms* pMTracks;	
	ClassDef(TNeAnalysis,1)
};
#endif //TANALYSIS_H
