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
//	Si
	/*memset(Xa, 0, sizeof(Xa));
	memset(Xt, 0, sizeof(Xt));
	memset(Xc, 0, sizeof(Xc));
	memset(Xs, 0, sizeof(Xs));

	memset(Ya, 0, sizeof(Ya));
	memset(Yt, 0, sizeof(Yt));
	memset(Yc, 0, sizeof(Yc));
	memset(Ys, 0, sizeof(Ys));

	memset(La, 0, sizeof(La));
	memset(Lt, 0, sizeof(Lt));
	memset(Lc, 0, sizeof(Lc));

	memset(Sa, 0, sizeof(Sa));
	memset(St, 0, sizeof(St));
	memset(Sc, 0, sizeof(Sc));

	memset(Ra, 0, sizeof(Ra));
	memset(Rt, 0, sizeof(Rt));
	memset(Rc, 0, sizeof(Rc));
*/
	memset(Va, 0, sizeof(Va));
	memset(Vt, 0, sizeof(Vt));
	memset(Vc, 0, sizeof(Vc));

	memset(R20a, 0, sizeof(R20a));
	memset(R20t, 0, sizeof(R20t));
	memset(R20c, 0, sizeof(R20c));

	memset(ampDSSD_L_Y, 0, sizeof(ampDSSD_L_Y));
	memset(timeDSSD_L_Y, 0, sizeof(timeDSSD_L_Y));
	memset(ampDSSD_L_X, 0, sizeof(ampDSSD_L_X));
	memset(timeDSSD_L_X, 0, sizeof(timeDSSD_L_X));
	
	memset(aCsI, 0, sizeof(aCsI));
	memset(tCsI, 0, sizeof(tCsI));

	memset(Rxa, 0, sizeof(Rxa));
	memset(Rxt, 0, sizeof(Rxt));
	memset(Rxc, 0, sizeof(Rxc));
	memset(Rxs, 0, sizeof(Rxs));

	memset(Rya, 0, sizeof(Rya));
	memset(Ryt, 0, sizeof(Ryt));
	memset(Ryc, 0, sizeof(Ryc));
	memset(Rys, 0, sizeof(Rys));

/*	std::fill_n(Rcsa,16,0);
	std::fill_n(Rcst,16,0);
	std::fill_n(Lcsa,16,0);
	std::fill_n(Lcst,16,0);
*/

// ToF
	memset(F3, 0, sizeof(F3));
	memset(tF3, 0, sizeof(tF3));
	memset(F5, 0, sizeof(F5));
	memset(tF5, 0, sizeof(tF5));

// MWPC
	memset(tMWPC, 0, sizeof(tMWPC));

	af3 = 0;
	af5 = 0;
	ToF = 0;
	xbt = -10;
	ybt = -10;

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
