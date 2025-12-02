/* -*- mode:c++ c-file-style:"linux" -*- */
//===================================================================
//== TNeEvent.h:
//== Version: 
//===================================================================

#ifndef TNeEVENT_H
#define TNeEVENT_H

#include "TGo4EventElement.h"

class TNeEvent : public TGo4EventElement 
{
public:
	TNeEvent();
	TNeEvent(const char* name);
	virtual ~TNeEvent();

	/** Method called by the framework to clear the event element. */
	void Clear(Option_t *t="");

//-----Si-----
	/*unsigned short Xa[32];
	unsigned short Xt[32];
	unsigned short Xs[32];

	unsigned short Ya[32];
	unsigned short Yt[32];
	unsigned short Ys[32];

	unsigned short Sa[16];
	unsigned short St[16];

	unsigned short Ra[16];
	unsigned short Rt[16];

	unsigned short Rva[16];
	unsigned short Rvt[16];*/

	unsigned short Va[16];
	unsigned short Vt[16];
	double Vc[16];

	unsigned short ampDSSD_L_X[16];
	unsigned short timeDSSD_L_X[16];
	double depDSSD_L_X[16];
	unsigned short multDSSD_L_X;
	unsigned short num_L_X[16];//![multDSSD_L_X]
	double dep_L_X[16];//![multDSSD_L_X]
	
	unsigned short ampDSSD_L_Y[16];
	unsigned short timeDSSD_L_Y[16];
	double depDSSD_L_Y[16];
	unsigned short multDSSD_L_Y;
	unsigned short num_L_Y[16];//![multDSSD_L_Y]
	double dep_L_Y[16];//![multDSSD_L_Y]

	unsigned short aCsI[16];
	unsigned short tCsI[16];

	unsigned short Rxa[16];
	unsigned short Rxt[16];
	unsigned short Rxs[16];

	unsigned short Rya[16];
	unsigned short Ryt[16];
	unsigned short Rys[16];

//-----20mu-----
	unsigned short R20a[16];
	unsigned short R20t[16];

//-----LYSO-----
/*	unsigned short La[16];
	unsigned short Lt[16];*/

//-----TOF & MWPC-----
	unsigned short F3[4];
	unsigned short tF3[4];
	unsigned short F5[4];
	unsigned short tF5[4];
	unsigned short F6[4];
	unsigned short tF6[4];
 	unsigned short tMWPC[4];
	unsigned int scaler[16];

//-----calibrated-----
	
	double af3;
	double af5;
	double ToF;
	
	double xbt, ybt;
	double xbd, ybd;

	/*double Xc[32];
	double Yc[32];
	double Lc[16];

	double Sc[16];
	double Rc[16];
	
	*/
	double Rxc[16];
	double Ryc[16];
	double R20c[16];

/*	unsigned short ADC[32];
	unsigned short TDC[32];
	unsigned short mQDC[32];
	unsigned short mTDC[32];
*/

//-----WIRES-----
	unsigned short nx1, ny1, nx2, ny2; // wires
	unsigned short x1[32],y1[32],x2[32],y2[32]; // wires
	unsigned int rx1, rx2, ry1, ry2;

	int nevent;
	int trigger;
	int subevents;
	int evsize;
	unsigned int mtime;
	unsigned int utime;
	unsigned int utime_old;
	
// Plastic ND demonstrator
	unsigned short digi_1w[16];
	unsigned short digi_2w[16];


	unsigned short neutAmp[48];
	unsigned short neutTAC[48];
	unsigned short neutTDC[48];

	unsigned short NneutAmp[48];
	unsigned short NneutTAC[48];
	unsigned short NneutTDC[48];


ClassDef(TNeEvent,1)
};
#endif //TEVENT_H



