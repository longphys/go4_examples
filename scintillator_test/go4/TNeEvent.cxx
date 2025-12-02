/* -*- mode:c++ c-file-style:"linux" -*- */

//===================================================================
//== TNeEvent.cxx:
//== Version:
//===================================================================
using namespace std;

#include "TNeEvent.h"
#include "Riostream.h"
#include <algorithm>

TNeEvent::TNeEvent()
	:TGo4EventElement()
{
	cout << "**** TNeEvent: Create instance" << endl;
} //-------------------------------------------------------------------

TNeEvent::TNeEvent(const char* name)
	:TGo4EventElement(name)
{
	cout << "**** TNeEvent: Create instance " << name << endl;
} //-------------------------------------------------------------------

TNeEvent::~TNeEvent()
{
	cout << "**** TNeEvent: Delete instance " << endl;
} //-------------------------------------------------------------------

void  TNeEvent::Clear(Option_t *t)
{
	//==================================================================
	//== all members should be cleared.
	//== memset(fRawData,0, sizeof(fRawData));
	//==================================================================

	nevent = 0;
	trigger = 0;
	subevents = 0;
	evsize = 0;
	mtime = 0;
	utime = 0;

	for (int i=0; i<48; ++i) {
	  NneutAmp[i] = neutAmp[i];
	  NneutTAC[i] = neutTAC[i];
	  NneutTDC[i] = neutTDC[i];
	}

	// Plastic ND demonstrator
//	digitizer
	memset(digi_1w, 0, sizeof(digi_1w));
	memset(digi_2w, 0, sizeof(digi_2w));
//	neutrons
	memset(neutAmp, 0, sizeof(neutAmp));
	memset(neutTAC, 0, sizeof(neutTAC));
	memset(neutTDC, 0, sizeof(neutTDC));
} //-------------------------------------------------------------------
