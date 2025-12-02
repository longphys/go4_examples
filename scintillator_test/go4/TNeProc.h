/* -*- mode:c++ c-file-style:"linux" -*- */
#ifndef TUNPACKPROCESSOR_H
#define TUNPACKPROCESSOR_H
#include <TLine.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TGo4EventProcessor.h"

#define NO_ANNUAL 0  // Remove Sectors, Rings

//-----class TNeParam-----;
extern int otl;
class TNeEvent;
class TGo4MbsSubEvent;

class TNeProc : public TGo4EventProcessor
{
public:
	TNeProc() ;
	TNeProc(const char* name);
	virtual ~TNeProc() ;
	//! event processing function
	Bool_t BuildEvent(TGo4EventElement* target);
	static long bit[32];

private:
	TH1		*fTrigger;
	TH1		*futime;
	TH1		*fSubEvents;
	TH1		*fEventsSizes;

// Plastic ND demonstrator
	// TH1* d1digi_1w[16];
	// TH1* d1digi_2w[16];
	// TH2* digi_g_n[16];

//-----neutrons-----
	TH1* d1neutAmp[4];
	TH1* d1neutTAC[4];
	TH1* d1neutTDC[4];
	TH2* d2Ngamma[4];

//------digi - ADC correlations

	// TH2* d2digiADC;

	void MakeHistND();
	void UnpackND(TGo4MbsSubEvent* se,TNeEvent* ev);
	void FillHistND(TNeEvent* ev);


	ClassDef(TNeProc,1)
};

#endif //TUNPACKPROCESSOR_H
