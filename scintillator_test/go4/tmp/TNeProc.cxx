/* -*- mode:c++ c-file-style:"linux" -*- */
/* -*- mode:c++ c-file-style:"linux" -*- */
//===================================================================
//==   EXPERIMENT A-2
//==   VERSION:   30.10.2018
//===================================================================
using namespace std;

#include "TNeProc.h"

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Riostream.h"

#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TCutG.h"
#include "TGo4WinCond.h"
#include "TGo4PolyCond.h"
#include "TGo4CondArray.h"
#include "TGo4Picture.h"
#include "TGo4MbsEvent.h"
#include "snprintf.h"

#include "TNeEvent.h"
#include "TNeDet16.h"
#include "TNeAnalysis.h"
#include "TRandom.h"
#include "TNeMParms.h"

//#include "TNeSel.h"

long TNeProc::bit[32] =
  {0x00000001, 0x00000002, 0x00000004, 0x00000008
   ,0x00000010, 0x00000020, 0x00000040, 0x00000080
   ,0x00000100, 0x00000200, 0x00000400, 0x00000800
   ,0x00001000, 0x00002000, 0x00004000, 0x00008000
   ,0x00010000, 0x00020000, 0x00040000, 0x00080000
   ,0x00100000, 0x00200000, 0x00400000, 0x00800000
   ,0x01000000, 0x02000000, 0x04000000, 0x08000000
   ,0x10000000, 0x20000000, 0x40000000, 0x80000000};

bool TNeProc::mapLYSO(int nl,int nx,int ny)
{
	const int yl= nl/3;
	const int xl= nl%3;
	bool cnd=true;
	switch(yl){
	case 0:
		cnd=cnd&&(ny<11);
		break;
	case 1:
		cnd=cnd&&(ny>10)&&(ny<21);
		break;
	case 2:
		cnd=cnd&&(ny>20);
		break;
	default:
		cnd=false;
		break;
	}
	if (cnd) {
		switch(xl){
		case 0:
			cnd=cnd&&(nx<11);
			break;
		case 1:
			cnd=cnd&&(nx>10)&&(nx<21);
			break;
		case 2:
			cnd=cnd&&(nx>20);
			break;
		default:
			cnd=false;
			break;
		}
	}
	return cnd;
}

void TNeProc::MakeHistND()
{
	//-----neutrons-----
	for (int i = 0; i < 48; ++i) {
		//d1neutAmp[i]   = MakeTH1('I', Form("Neutrons/Amp/Amp_%2.2d",i)
		//		, Form("Neutrons Amp CH %2.2d",i), 4096, 0., 4095.);
		d1neutAmp[i] = MakeTH1('I', Form("Neutrons/Amp/Amp_%2.2d",i),
					 Form("Neutrons Amp CH %2.2d",i),
					 8192, 0., 8191.);
		d1neutTAC[i] = MakeTH1('I', Form("Neutrons/TAC/TAC_%2.2d",i),
					 Form("Neutrons TAC CH %2.2d",i),
					 4096, 0., 4095.);
		d1neutTDC[i] = MakeTH1('I', Form("Neutrons/time/time_%2.2d",i),
				       Form("Neutrons time CH %2.2d",i),
				       4999, 0., 5000.);
		d2Ngamma[i]   = MakeTH2('I', Form("Neutrons/Ng/Ng_%2.2d",i)
					, Form("N gamma %2.2d",i), 400, 0., 4095., 400, 0., 4095.,"Amp","TAC");
	}
//------Digitizer----
	for ( int i = 0; i < 16; ++i) {
		d1digi_1w[i] = MakeTH1('I',Form("Digitizer/long/l_digi_%2.2d",i),
				       Form("Long window CH %2.2d",i), 4096, 0.,4095.);
		d1digi_2w[i] = MakeTH1('I', Form("Digitizer/short/s_digi_%2.2d",i)
				       , Form("Short window CH %2.2d",i), 4096, 0., 4095.);
//		digi_g_n[i]   =  MakeTH2('D', Form("Digitizer/gn/gn_digi_%2.2d",i)
//				, Form("PSD %2.2d",i), 400, 0., 4095., 400, -100., 100.,"amp","psd");
		digi_g_n[i]   =  MakeTH2('D', Form("Digitizer/gn/gn_digi_%2.2d",i)
					 , Form("PSD %2.2d",i), 400, 0., 4095., 400, -1.,1.,"amp","psd");
	}

	d2digiADC = MakeTH2('I', "2D", "Correlation",
			    400, 0., 4095., 400, 0., 4095.,"digi","ADC");
}
void TNeProc::UnpackND(TGo4MbsSubEvent* se,TNeEvent* ev)
{
	uint32_t* idata;
	int header,typ,adc,module_id,chnl;
	idata = (uint32_t*) se->GetDataField();
	int n=-1;
	bool m_bool;
	while(++n < se->GetIntLen())  {
		header = idata[n]  >> 24;
		if (header==0x40){
			m_bool=true;
		} else if ((idata[n]==0xaffeaffe) || (idata[n]== 0x06000000) ||
			   (idata[n]== 0x05000000)){
			m_bool=false;
		}
			
			
		//if (dooutput) 	printf("Raw data = %x\n", idata[n]);
		if (m_bool){ //in case of MESYTEC data
			typ=idata[n]  >> 30;
			switch(typ) {
			case 1: //MESYTEC header
				module_id = (idata[n] >> 16) & 0xff;
				//if (dooutput) printf("Mesytec Module ID %d\n", module_id);
				//TGo4Log::Info("ND module_id  %d", module_id);
				break;
			case 0: //MESYTEC data
				if(idata[n]  >> 24!=0x04){
					break;
				}
				switch (module_id) {
				case 8:	// even - neutAmp, odd - neutTAC
					chnl= (idata[n] >> 16)&0x1f;
					//adc = idata[n] & 0xfff; //only 12 bits
					adc = idata[n] & 0x1fff; //only 13 bits
				
					if(chnl%2 == 0) {
						ev->neutAmp[chnl/2] = adc;
					} else {
						ev->neutTAC[chnl/2] = adc;
					}
					break;
				case 9:	// mADC: SQ1_x && SQ1_y
					chnl= (idata[n] >> 16)&0x3f;
					adc = idata[n] & 0xfff; //only 12 bits
					ev->neutTDC[chnl] = adc;
					break;
				}
				break;
			case 3: //-----MESYTEC footer-----
				m_bool=false;
				break;
			default:
				printf("ERROR !!!!!! Unknown MESYTEC typ %d\n", typ); 
				printf("Data = %x\n", idata[n]);
				break;
			}
		}
	}
}

void TNeProc::FillHistND(TNeEvent* ev)
{
	for (int n=0; n<16; ++n) {
		if(ev->digi_1w[n] > 0) d1digi_1w[n]->Fill(ev->digi_1w[n]);
		if(ev->digi_2w[n] > 0) d1digi_2w[n]->Fill(ev->digi_2w[n]);
		if(ev->digi_1w[n] > 0 && ev->digi_2w[n] > 0) 	{
			double psd = (double)(ev->digi_1w[n]-ev->digi_2w[n])/(double) ev->digi_1w[n];
			double amp = (double) ev->digi_1w[n];
//			slow = ev->digi_2w[n];
			digi_g_n[n]->Fill(amp, psd);
		}
	}

/*	unsigned short Amp = ev->neutAmp[0];
	unsigned short TDC = ev->neutTDC[0];

	ev->neutAmp[0] = ev->nAmp;
	ev->neutTDC[0] = ev->nTDC;

	ev->nAmp = Amp;
	ev->nTDC = TDC;
*/
//-----neutrons-----
	for (int n=0; n<48; ++n) {

//		if(ev->NneutTDC[n] > 0 && ev->digi_1w[n] > 0)
//		if(ev->neutTDC[n] > 0 && ev->digi_1w[n] > 0)
		if(ev->neutTDC[n] > 0) {
			d1neutAmp[n]->Fill(ev->neutAmp[n]);
			d1neutTAC[n]->Fill(ev->neutTAC[n]);
			d1neutTDC[n]->Fill(ev->neutTDC[n]);
			d2Ngamma[n] ->Fill(ev->neutAmp[n],ev->neutTAC[n]);
//			d1neutAmp[n]->Fill(ev->neutAmp[n]);
//			d1neutTAC[n]->Fill(ev->neutTAC[n]);
//			d1neutTDC[n]->Fill(ev->neutTDC[n]);
//			d2Ngamma[n]->Fill(ev->neutAmp[n],ev->neutTAC[n]);
		}
	}
//-----correlations-----
	if(ev->digi_1w[0] > 0 && ev->NneutAmp[0] > 0)
		d2digiADC->Fill(ev->digi_1w[0],ev->NneutAmp[0]);

//		if(ev->digi_1w[0] > 0 && ev->neutAmp[0] > 0)
//			d2digiADC->Fill(ev->digi_1w[0],ev->neutAmp[0]);
/*
printf("nAmp old%x\n",ev-> nAmp);

ev->nAmp = ev->neutAmp[0];
printf("nAmp new%x\n",ev-> nAmp);
*/

}

TNeProc::TNeProc() : TGo4EventProcessor()
{
	int i;
	cout << "**** TNeProc: Create instance " << endl;
	fTrigger = NULL;
	fSubEvents = NULL;
	fEventsSizes = NULL;

	for(i = 0; i < 4; ++i)
	{
		d1F3[i] = NULL;
		d1tF3[i] = NULL;
		d1F5[i] = NULL;
		d1tF5[i] = NULL;

		d1tMWPC[i] = NULL;

	}

	for(i = 0; i < 32; ++i) {
//-----Si in the center----- 
		d1Xa[i] = NULL;
		d1Xt[i] = NULL;
		d1Xc[i] = NULL;

		d1Ya[i] = NULL;
		d1Yt[i] = NULL;
		d1Yc[i] = NULL;
	}

	for(i = 0; i < 16; ++i) {
// #ifndef NO_ANNUAL
//-----Anular Silicon
		d1Sa[i] = NULL;
		d1St[i] = NULL;
		d1Sc[i] = NULL;

		d1Ra[i] = NULL;
		d1Rt[i] = NULL;
		d1Rc[i] = NULL;
// #endif // NO_ANNUAL		
		d1Va[i] = NULL;
		d1Vt[i] = NULL;
		d1Vc[i] = NULL;

		d1R20a[i] = NULL;
		d1R20t[i] = NULL;
		d1R20c[i] = NULL;
		
		d1Rxa[i] = NULL;
		d1Rxt[i] = NULL;
		d1Rxc[i] = NULL;

		d1Rya[i] = NULL;
		d1Ryt[i] = NULL;
		d1Ryc[i] = NULL;
	}

	for(i = 0; i < 16; ++i) {
//-----LYSO in the center----- 
		d1La[i] = NULL;
		d1Lt[i] = NULL;
		d1Lc[i] = NULL;
	}

//
	d1ToF    = NULL;
	d1aF3    = NULL;
	d2ToFaF3 = NULL;
	d1aF5    = NULL;
	d2ToFaF5 = NULL;

	d1X1 = NULL;
	d1Y1 = NULL;
	d1X2 = NULL;
	d1Y2 = NULL;
	d1NX1 = NULL;
	d1NY1 = NULL;
	d1NX2 = NULL;
	d1NY2 = NULL;
	d2XY1 = NULL;
	d2XY2 = NULL;

//	d2XL  = NULL;

	d1CX1 = NULL;
	d1CY1 = NULL;
	d1CX2 = NULL;
	d1CY2 = NULL;
	d2XYbeamOnTar = NULL;

} //-------------------------------------------------------------------

TNeProc::~TNeProc()
{
	cout << "**** TNeProc: Delete instance " << endl;
} //-------------------------------------------------------------------

TNeProc::TNeProc(const char* name) : TGo4EventProcessor(name)
{
	TGo4Log::Info("**** TNeProc: Create instance %s", name);
	fTrigger = MakeTH1('I', "Trigger","Values of trigger",16, 0., 15.);
	futime    = MakeTH1('I', "utime",    "mashine time (usec)",   65535, 0, 65534);
	fSubEvents  = MakeTH1('I', "SubEvents",  "Number of subevents", 16, 0, 15);
	fEventsSizes = MakeTH1('I', "EventSizes", "Size of each event", 1024, 0, 1023);
	int i;

	for (i = 0; i < 32; ++i) {
//-----SQ telescope raw-----
		d1Xa[i]   = MakeTH1('I', Form("Xa/Xas_%2.2d",i)			//указывать не повторяющуюся структуру папок и уникальные имена
				, Form("X amp CH %2.2d",i), 8192, 0., 8192.);
		d1Xt[i]   = MakeTH1('I', Form("Xt/Xts_%2.2d",i)
				, Form("X time CH %2.2d",i), 4096, 1., 4096);
		d1Xc[i]   = MakeTH1('D', Form("Xc/Xcs_%2.2d",i)
				, Form("X energy MeV %2.2d",i), 4000, -2., 98.);
//
		d1Ya[i]   = MakeTH1('I', Form("Ya/Yas_%2.2d",i)			//указывать не повторяющуюся структуру папок и уникальные имена
				, Form("Y amp CH %2.2d",i), 8192, 0., 8192.);
		d1Yt[i]   = MakeTH1('I', Form("Yt/Yts_%2.2d",i)
				, Form("Y time CH %2.2d",i), 4096, 1, 4096);
		d1Yc[i]   = MakeTH1('D', Form("Yc/Ycs_%2.2d",i)
				, Form("Y energy MeV %2.2d",i), 4000, -2., 98.);
		}

  for (int i = 0; i < 16; ++i) {
// #ifndef NO_ANNUAL
//-----Anular Silicon
		d1Sa[i]   = MakeTH1('I', Form("Sa/Sas_%2.2d",i)		
				, Form("Sect amp CH %2.2d",i), 8192, 0., 8192.);
		d1St[i]   = MakeTH1('I', Form("St/Sts_%2.2d",i)
				, Form("Sect time CH %2.2d",i), 4096, 1, 4096);
		d1Sc[i]   = MakeTH1('D', Form("Sc/Scs_%2.2d",i)
				, Form("Sect energy MeV %2.2d",i), 4000, -2., 98.);
//
		d1Ra[i]   = MakeTH1('I', Form("Ra/Ras_%2.2d",i)		
				, Form("Ring amp CH %2.2d",i), 8192, 0., 8192.);
		d1Rt[i]   = MakeTH1('I', Form("Rt/Rts_%2.2d",i)
				, Form("Ring time CH %2.2d",i), 4096, 1, 4096);
		d1Rc[i]   = MakeTH1('D', Form("Rc/Rcs_%2.2d",i)
				, Form("Ring energy MeV %2.2d",i), 4000, -2., 98.);
// #endif // NO_ANNUAL
		d1Va[i]   = MakeTH1('I', Form("Va/Vas_%2.2d",i)		
				, Form("Veto amp CH %2.2d",i), 8192, 0., 8192.);
		d1Vt[i]   = MakeTH1('I', Form("Vt/Vts_%2.2d",i)
				, Form("Veto time CH %2.2d",i), 4096, 1, 4096);
		d1Vc[i]   = MakeTH1('D', Form("Vc/Vcs_%2.2d",i)
				, Form("Veto energy MeV %2.2d",i), 4000, -2., 98.);

		d1Rxa[i]   = MakeTH1('I', Form("Rxa/Rxas_%2.2d",i)			
				, Form("R x amp CH %2.2d",i), 8192, 0., 8192.);
		d1Rxt[i]   = MakeTH1('I', Form("Rxt/Rxts_%2.2d",i)
				, Form("R x time CH %2.2d",i), 4096, 1., 4096);
		d1Rxc[i]   = MakeTH1('D', Form("Rxc/Rxcs_%2.2d",i)
				, Form("R x energy MeV %2.2d",i), 4000, -2., 98.);

		d1Rya[i]   = MakeTH1('I', Form("Rya/Ryas_%2.2d",i)			
				, Form("R y amp CH %2.2d",i), 8192, 0., 8192.);
		d1Ryt[i]   = MakeTH1('I', Form("Ryt/Ryts_%2.2d",i)
				, Form("R y time CH %2.2d",i), 4096, 1, 4096);
		d1Ryc[i]   = MakeTH1('D', Form("Ryc/Rycs_%2.2d",i)
				, Form("R y energy MeV %2.2d",i), 4000, -2., 98.);

		d1R20a[i]   = MakeTH1('I', Form("R20a/R20as_%2.2d",i)			
				, Form("R 20 amp CH %2.2d",i), 8192, 0., 8192.);
		d1R20t[i]   = MakeTH1('I', Form("R20t/R20ts_%2.2d",i)
				, Form("R 20 time CH %2.2d",i), 4096, 1, 4096);
		d1R20c[i]   = MakeTH1('D', Form("R20c/R20cs_%2.2d",i)
				, Form("R 20 energy MeV %2.2d",i), 4000, -2., 98.);
	}

	for (int i = 0; i < 16; ++i) {
		d1La[i] = MakeTH1('I', Form("La/Las_%02d",i),
				  Form("LYSO amp CH %02d",i), 8192, 0., 8192);
		d1Lt[i] = MakeTH1('I', Form("Lt/Lts_%02d",i)
				, Form("LYSO time CH %02d",i), 4096, 1., 4095);
		d1Lc[i] = MakeTH1('D', Form("Lc/Lcs_%02d",i),
				  Form("LYSO energy MeV %2.2d",i), 4000, 0.,  8192.);
		}

	for (int i = 0; i < 9; ++i) {
		d2XL[i]  = MakeTH2('D', Form("2D/XL_%02d",i),
				  Form("Y vs LYSO %2.2d",i), 200,0.,8000.,400,0.,120.);
	}
	
	d2edeR20  = MakeTH2('D', "ede R20", "ede R20", 200,0.,80.,400,0.,120.,"eR1mm","deR20");
	d2edeLYSO = MakeTH2('D', "ede LYSO", "ede LYSO", 200,0.,80.,400,0.,120.,"e","de");
	d2xy  = MakeTH2('D', "xy MeV", "xy MeV", 200,0.,80.,200,0.,80.,"x","y");
	d2Si  = MakeTH2('D', "XY mapping", "XY mapping", 32,0.,32.,32,0.,32.,"SiX","SiY");

//
	d1F3[0]   = MakeTH1('I',"F3/QDC/F3_QDC_L","F3 QDC  left", 4096, 0., 4095.);
	d1F3[1]   = MakeTH1('I',"F3/QDC/F3_QDC_R","F3 QDC right", 4096, 0., 4095.);
	d1F3[2]   = MakeTH1('I',"F3/QDC/F3_QDC_U","F3 QDC    up", 4096, 0., 4095.);
	d1F3[3]   = MakeTH1('I',"F3/QDC/F3_QDC_D","F3 QDC  down", 4096, 0., 4095.);
	d1tF3[0]  = MakeTH1('I',"F3/TDC/tF3_TDC_L","F3 TDC  left", 15000, 0, 14999);
	d1tF3[1]  = MakeTH1('I',"F3/TDC/tF3_TDC_R","F3 TDC right", 15000, 0, 14999);
	d1tF3[2]  = MakeTH1('I',"F3/TDC/tF3_TDC_U","F3 TDC    up", 15000, 0, 14999);
	d1tF3[3]  = MakeTH1('I',"F3/TDC/tF3_TDC_D","F3 TDC  down", 15000, 0, 14999);
//
	d1F5[0]   = MakeTH1('I',"F5/QDC/F5_QDC_L","F5 QDC  left", 4096, 0., 4095.);
	d1F5[1]   = MakeTH1('I',"F5/QDC/F5_QDC_R","F5 QDC right", 4096, 0., 4095.);
	d1F5[2]   = MakeTH1('I',"F5/QDC/F5_QDC_U","F5 QDC    up", 4096, 0., 4095.);
	d1F5[3]   = MakeTH1('I',"F5/QDC/F5_QDC_D","F5 QDC  down", 4096, 0., 4095.);
	d1tF5[0]  = MakeTH1('I',"F5/TDC/tF5_TDC_L","F5 TDC  left", 15000, 0, 14999);
	d1tF5[1]  = MakeTH1('I',"F5/TDC/tF5_TDC_R","F5 TDC right", 15000, 0, 14999);
	d1tF5[2]  = MakeTH1('I',"F5/TDC/tF5_TDC_U","F5 TDC    up", 15000, 0, 14999);
	d1tF5[3]  = MakeTH1('I',"F5/TDC/tF5_TDC_D","F5 TDC  down", 15000, 0, 14999);
//

//-----ToF-----
	d1ToF = MakeTH1('D', "ToF/ToF", "time of flight", 14000,-100.,600.,"ToF(ns)");

	d1aF3 = MakeTH1('D', "ToF/aF3", "amplitude of plastic F3", 4000,0.,4000.,"amp F3");
	d2ToFaF3 = MakeTH2('D', "ToF/ToFaF3", "ToF vs aF3", 550,50.,600.,400,0.,4000.,"ToF","aF3");

	d1aF5 = MakeTH1('D', "ToF/aF5", "amplitude of plastic F5", 4000,0.,4000.,"amp F5");
	d2ToFaF5 = MakeTH2('D', "ToF/ToFaF5", "ToF vs aF5", 550,50.,600.,400,0.,4000.,"ToF","aF5");


//-----MWPC-----
	d2XY1 = MakeTH2('I', "MWPC/XY1", "WIRES 1 Y1 vs X1", 32,0.,32.,32,0.,32.,"X1","Y1");
	d2XY2 = MakeTH2('I', "MWPC/XY2", "WIRES 2 Y2 vs X2", 32,0.,32.,32,0.,32.,"X2","Y2");
	d2XYbeamOnTar = MakeTH2('f', "MWPC/XY_beamOnTar", "beam at target trig L+R", 200,-50.0,50.0,200,-50,50,"X(Z=0.0mm)","Y(Z=0.0mm)");
	d2XYbeamOnTarTrg1 = MakeTH2('f', "MWPC/XY_beamOnTarTrg1", "beam at target beam trig", 200,-50.0,50.0,200,-50,50,"X(Z=0.0mm)","Y(Z=0.0mm)");
	d2XYbeamOnDia = MakeTH2('f', "MWPC/XY_beamOnDia", "beam at diaphragm", 200,-50.0,50.0,200,-50,50,"X(Z=-110.0mm)","Y(Z=-110.0mm)");
	
	d1X1 = MakeTH1('I', "MWPC/X1","WIRES X1",32,0.,32.);
	d1Y1 = MakeTH1('I', "MWPC/Y1","WIRES Y1",32,0.,32.);
	d1X2 = MakeTH1('I', "MWPC/X2","WIRES X2",32,0.,32.);
	d1Y2 = MakeTH1('I', "MWPC/Y2","WIRES Y2",32,0.,32.);

	d1tMWPC[0]  = MakeTH1('I',"MWPC/tX1","MWPC TDC  X1", 15000, 0, 14999);
	d1tMWPC[1]  = MakeTH1('I',"MWPC/tY1","MWPC TDC  Y1", 15000, 0, 14999);
	d1tMWPC[2]  = MakeTH1('I',"MWPC/tX2","MWPC TDC  X2", 15000, 0, 14999);
	d1tMWPC[3]  = MakeTH1('I',"MWPC/tY2","MWPC TDC  Y2", 15000, 0, 14999);

	d1NX1 = MakeTH1('I', "MWPC/NX1","WIRES X1",32,0.,32.);
	d1NY1 = MakeTH1('I', "MWPC/NY1","WIRES Y1",32,0.,32.);
	d1NX2 = MakeTH1('I', "MWPC/NX2","WIRES X2",32,0.,32.);
	d1NY2 = MakeTH1('I', "MWPC/NY2","WIRES Y2",32,0.,32.);

	d1CX1 = MakeTH1('I', "MWPC/CX1","clusters X1",32,0.,32.);
	d1CY1 = MakeTH1('I', "MWPC/CY1","clusters Y1",32,0.,32.);
	d1CX2 = MakeTH1('I', "MWPC/CX2","clusters X2",32,0.,32.);
	d1CY2 = MakeTH1('I', "MWPC/CY2","clusters Y2",32,0.,32.);

	// ND demonstrator
	MakeHistND();

//------------------------------------------------------------
}//------------------------------------------------------------

Bool_t TNeProc::BuildEvent(TGo4EventElement* target)
{
// called by framework from TNeEvent to fill it

	TGo4Analysis *go4 = TGo4Analysis::Instance();

	TNeEvent* NeEvent = (TNeEvent*) target;
	target->Clear();
	TGo4MbsSubEvent* psubevt;

	TGo4MbsEvent* fInput = (TGo4MbsEvent* ) GetInputEvent();
	if(fInput == 0) 
	{
		TGo4Log::Error( "TNeProc::BuildEvent: no input event !");
		return false;
	}
	bool dooutput = false;
	double value1, value2;
	double eXa = 0, eYa = 0, eLa = 0 , eSa = 0, eRa = 0, eVa = 0;
	double eR20a = 0, eRxa = 0, eRya = 0;
	int mXa = 0, mYa = 0, mLa = 0, mSa = 0, mRa = 0, mVa = 0;
	int mR20a = 0, mRxa = 0, mRya = 0;
	int nXa = -1, nYa = -1, nLa = -1, nSa = -1, nRa = -1, nVa = -1;
	int nR20a = -1, nRxa = -1, nRya = -1;
//
	int num = 0, sz = 0;
	int i, n, geo, typ, header,caen_header, module_id=0, crate=-1, cnt, chnl, evnt /*,gch*/;

	bool m_bool= false, c_bool = false;
	uint16_t MSB, LSB;
	uint32_t MSBLSB, adc;
	uint32_t *idata;

	double tf3=0., tf5=0.;

	fInput->ResetIterator();
	while ((psubevt = fInput->NextSubEvent()) != 0) {
		num++;
		sz += psubevt->GetIntLen();
		idata = (uint32_t*) psubevt->GetDataField();

		n = -1;		
		while (++n < psubevt->GetIntLen()) {
			header = idata[n]  >> 24;
			caen_header = header & 0x7;
			if (dooutput)
				printf("Raw data = %x\n", idata[n]);

			switch (psubevt->GetProcid()) {
			case 100: //VME_0, see setup.usf
			  if (header==0x40) {
			    m_bool=true; /*MESYTEC header flag*/
			  } else if (caen_header == 2) {
			    c_bool=true;  //CAEN  header flag
			  } else if ((idata[n]==0xaffeaffe) || (idata[n]== 0x06000000) || (idata[n]== 0x05000000)) {
			    c_bool=false;
			    m_bool=false;
			  }

			  if (m_bool) {//in case of MESYTEC data
						typ=idata[n]  >> 30;

						switch(typ) {
						case 1: //MESYTEC header
							module_id = (idata[n] >> 16) & 0xff;
							if (dooutput)
								printf("Mesytec Module ID %d\n", module_id);
							break;

						case 0: //MESYTEC data
							if(idata[n]  >> 24!=0x04) break;
							switch (module_id) 
							{
							case  1:	// mTDC: time An S  & R
								chnl= (idata[n] >> 16)&0x3f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<16) {
									NeEvent->R20t[chnl] = adc;
//									NeEvent->St[chnl] = adc;
								} else if(chnl<32) {
									NeEvent->Rt[chnl-16] = adc;
								}
								break;

							case  2:	// mADC: amp An S  & R
								chnl= (idata[n] >> 16)&0x1f;
								adc = idata[n] & 0x1fff; //only 12 bits
								if(chnl<16) {
									NeEvent->R20a[chnl] = adc;
//									NeEvent->Sa[chnl] = adc;
								} else {
									NeEvent->Ra[chnl-16] = adc;
								}
								break;

							case  3:	// mTDC: AnV
								chnl= (idata[n] >> 16)&0x3f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<16) {
									NeEvent->Vt[chnl] = adc;
								} 
								else if(chnl<32) {
									NeEvent->R20t[chnl-16] = adc;
								} 
								break;

							case  4:	// mADC: AnV
								chnl= (idata[n] >> 16)&0x1f;
								adc = idata[n] & 0x1fff; //only 12 bits
								if(chnl<16) {
									NeEvent->Va[chnl] = adc;
									}
								else if(chnl<32) {
									NeEvent->R20a[chnl-16] = adc;
								} 
								break;
							case  5:	// mTDC: time Cx (Lx?)
								chnl= (idata[n] >> 16)&0x3f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<32) {
									NeEvent->Xt[chnl] = adc;
								}
								break;

							case  6:	// mADC: amp Cx
								chnl= (idata[n] >> 16)&0x1f;
								adc = idata[n] & 0x1fff; //only 12 bits
								if(chnl<32) {
									NeEvent->Xa[chnl] = adc;
									NeEvent->Xs[chnl] = chnl;
									nXa = chnl;
								}
								break;
							case 7:	// mTDC: time Cy (Ly?)
								chnl= (idata[n] >> 16)&0x3f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<32) {
									NeEvent->Yt[chnl] = adc;
								}
								break;

							case 8:	// mADC: amp Cy 
								chnl= (idata[n] >> 16)&0x1f;
								adc = idata[n] & 0x1fff; //only 12 bits
								if(chnl<32){
									NeEvent->Ya[chnl] = adc;
									NeEvent->Ys[chnl] = chnl;
									nYa = chnl;
								}
								break;
							case  9:	// mTDC: time LYSO
								chnl= (idata[n] >> 16)&0x3f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<16) {
									;
								} else {
									NeEvent->Lt[chnl-16] = adc;
								}								
								break;

							case 10:	// mADC: amp LYSO
								chnl= (idata[n] >> 16)&0x1f;
								adc = idata[n] & 0x1fff; //only 12 bits
								if(chnl<16) {
									;
								} else {
									NeEvent->La[chnl-16] = adc;
								}
								break;
							case 11:	// mTDC: time Rx & Ry
								chnl= (idata[n] >> 16)&0x3f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<16) {
									NeEvent->Rxt[chnl] = adc;
								} else if(chnl<32) {
									NeEvent->Ryt[chnl-16] = adc;
								}
								break;

							case 12:	// mADC: amp Rx & Ry
								chnl= (idata[n] >> 16)&0x1f;
								adc = idata[n] & 0x1fff; //only 12 bits
								if(chnl<16) {
									NeEvent->Rxa[chnl] = adc;
									NeEvent->Rxs[chnl] = chnl;
									nRxa = chnl;
								} else {
									NeEvent->Rya[chnl-16] = adc;
									NeEvent->Rys[chnl] = chnl;
									nRya = chnl;
								}
								break;
							case 13:	//mTDC: ToF
								if ((idata[n] >> 16) & 0x20) break; //T bit analysis
								chnl= (idata[n] >> 16) & 0x1f;
								adc = idata[n] & 0xffff; //only 16 bits
								if(chnl<4) NeEvent->tF3[chnl] = adc;
								else if(chnl<8) NeEvent->tF5[chnl-4] = adc;
								else if(chnl<12);
								else if(chnl<16) NeEvent->tMWPC[chnl-12] = adc;
								break;

							case 14:	//mQDC:
								chnl= (idata[n] >> 16) & 0x1f;
								adc = idata[n] & 0xfff; //only 12 bits
								if(chnl<4) NeEvent->F3[chnl] = adc;
								else if(chnl<8) NeEvent->F5[chnl-4] = adc;

								break;



							}
							break;

							case 3: //-----MESYTEC footer-----
								m_bool=false;
								break;

							default:
								printf("ERROR !!!!!! Unknown MESYTEC typ %d\n", typ);
								printf("Data = %x\n", idata[n]);
							break;
						}
					}
					else if (c_bool) //in case of CAEN data
					{
						typ   = (idata[n] >> 24) & 0x7;
						geo   = idata[n]  >> 27;
						if (dooutput)
							printf("CAEN geo %d\n", geo);

						switch(typ)
						{
							case 2: //CAEN header
								crate = (idata[n] >> 16) & 0xff;
								cnt = (idata[n] >> 8) & 0x1f;
								if (geo==30)
									{
									  NeEvent->mtime=idata[++n];//machine time
									  NeEvent->utime=(idata[++n] & 0xffff);//machine time in usec
									}
								if (dooutput)
									printf("Header: geo:%d crate:%d cnt = %d\n", geo, crate, cnt);
								break;

							case 0: //CAEN data
								adc = idata[n] & 0xfff;
								chnl = (idata[n] >> 16) & 0x1f;
								//printf("DATA: geo:%d Channel = %d\n", geo, chnl);
								switch(geo)
								{
									case 6: //scaler v560
										for(i = 0; i < 16; ++i)
											NeEvent->scaler[i]=idata[n++] & 0x07ffffff;
									break;
								}
								//                printf("  Data: geo:%d chnl:%d adc:%d\n", geo, chnl, adc);
								break;

							case 4: //CAEN footer
								c_bool = false;
								evnt = idata[n] & 0xffffff;
								if (dooutput)
								   printf("  Event: geo:%d number:%d\n", geo, evnt);
								break;

							case 6: //CAEN no valid data
								c_bool = false;
								if (dooutput)
									printf("!!!No valid data from CAEN!!!");
								break;

							default:
								printf("ERROR !!!!!! Uncknown CAEN typ %d\n", typ);
								printf("Data = %x\n", idata[n]);

							break;
						}
					}
					break; //end of VME_0

				case 101: // CAMAC through VME_0, see setup.usf
					    geo   = idata[n]  >> 27;

					    switch(geo)
					    {

						case 1:
						     NeEvent->nx1 = 0;
						     adc = idata[++n];
						     LSB=adc;
						     //printf("First word from MWPC X1= %x\n", adc);
						     for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->x1[NeEvent->nx1++] = i;
						     adc = idata[++n];
						     MSB = adc;
						     MSBLSB = (MSB << 16) | LSB;
						     //printf("Second word from MWPC X1= %x\n", adc);
						     for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->x1[NeEvent->nx1++] = i+16;
						     adc = idata[++n];//pass throug footer
						     //printf("Third word from MWPC X1= %x\n", adc);
						     NeEvent->rx1=MSBLSB;
						     break;

						case 2:
						      NeEvent->ny1 = 0;
						      adc = idata[++n];
						      LSB=adc;
						      //printf("First word from MWPC Y1 = %x\n", adc);
						      for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->y1[NeEvent->ny1++] = i;
						      adc = idata[++n];
						      MSB = adc;
						      MSBLSB= (MSB << 16) | LSB;
						      //printf("Second word from MWPC Y1 = %x\n", adc);
						      for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->y1[NeEvent->ny1++] = i+16;
						      adc = idata[++n];//pass through footer
						      //printf("Third word from MWPC Y1 = %x\n", adc);
						      NeEvent->ry1=MSBLSB;
						      break;
						case 3:
						      NeEvent->nx2 = 0;
						      adc = idata[++n];
						      LSB=adc;
						      //printf("First word from MWPC X2 = %x\n", adc);
						      for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->x2[NeEvent->nx2++] = i;
						      adc = idata[++n];
						      MSB = adc;
						      MSBLSB= (MSB << 16) | LSB;
						      //printf("Second word from MWPC X2 = %x\n", adc);
						      for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->x2[NeEvent->nx2++] = i+16;
						      adc = idata[++n];//pass through footer
						      //printf("Third word from MWPC X2 = %x\n", adc);
						      NeEvent->rx2=MSBLSB;
						      break;
						case 4:
						      NeEvent->ny2 = 0;
						      adc = idata[++n];
						      LSB=adc;
						      //printf("First word from MWPC Y2 = %x\n", adc);
						      for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->y2[NeEvent->ny2++] = i;
						      adc = idata[++n];
						      MSB = adc;
						      MSBLSB= (MSB << 16) | LSB;
						      //printf("Second word from MWPC Y2 = %x\n", adc);
						      for(i = 0; i < 16; ++i)
							if((adc & bit[i]) > 0) NeEvent->y2[NeEvent->ny2++] = i+16;
						      adc = idata[++n];//pass throug footer
						      //printf("Third word from MWPC Y2 = %x\n", adc);
						      NeEvent->ry2=MSBLSB;
						      break;
						 }

					break; // end of CAMAC

					case 200: //VME_1, see setup.usf


					if (header==0x40)
						m_bool=true; //MESYTEC header flag
					else if (caen_header == 2)
						c_bool=true;  //CAEN  header flag
					else if ((idata[n]==0xaffeaffe) || (idata[n]== 0x06000000) || (idata[n]== 0x05000000))
					{
						c_bool=false;
						m_bool=false;
					}


					if (m_bool) //in case of MESYTEC data
					{
						typ=idata[n]  >> 30;

						switch(typ)
						{
							case 1: //MESYTEC header
								module_id = (idata[n] >> 16) & 0xff;
								if (dooutput)
									printf("Mesytec Module ID %d\n", module_id);
								break;


							case 0: //MESYTEC data
								if(idata[n]  >> 24!=0x04) break;
								switch (module_id)
								{
									case 3:	// mTDC: time sect & rings p1
										chnl= (idata[n] >> 16)&0x3f;
										adc = idata[n] & 0xfff; //only 12 bits
										if(chnl<16) {
											NeEvent->Rvt[chnl] = adc;
										}
										break;

									case 4:	// mADC: amp sect & rings p1
										chnl= (idata[n] >> 16)&0x1f;
										adc = idata[n] & 0xfff; //only 12 bits
										if(chnl<16) {
											NeEvent->Rva[chnl] = adc;
										}
										break;
								}
								break;

							case 3: //-----MESYTEC footer-----
								m_bool=false;
								break;

							default:
								printf("ERROR !!!!!! Unknown MESYTEC typ %d\n", typ);
								printf("Data = %x\n", idata[n]);
							break;
						}
					}
					break; //end of VME_1
		
			} //end of GetProcID
		} //end of GetIntLen
	} //end of NextSubEvent
	// read and fill ND part 
	{
		psubevt = fInput->GetSubEvent(300);
		if(psubevt){
			UnpackND(psubevt,NeEvent);
			FillHistND(NeEvent);
		} else {
			TGo4Log::Error( "TNeProc::BuildEvent: no subevent with procID 300 !");
		}
	}
	NeEvent->nevent		= fInput->GetCount();
	NeEvent->trigger	= fInput->GetTrigger();
	NeEvent->subevents	= num;
	NeEvent->evsize		= sz;


	fTrigger->Fill(NeEvent->trigger);

	unsigned short Dtime = NeEvent->utime - NeEvent->utime_old;
	futime->Fill(Dtime);

	fSubEvents->Fill(num);
	fEventsSizes->Fill(sz);

    NeEvent->utime_old = NeEvent->utime;
 
	for (n=0; n<4; ++n)
//	if(NeEvent->trigger == 2)
	{
	if(NeEvent->F3[n] > 0 ) d1F3[n]->Fill(NeEvent->F3[n]);
	if(NeEvent->F5[n] > 0) d1F5[n]->Fill(NeEvent->F5[n]);

	if(NeEvent->tF3[n] > 0) d1tF3[n]->Fill(NeEvent->tF3[n]);
	if(NeEvent->tF5[n] > 0) d1tF5[n]->Fill(NeEvent->tF5[n]);

	if(NeEvent->tMWPC[n] > 0) d1tMWPC[n]->Fill(NeEvent->tMWPC[n]);
	}
//
	if(NeEvent->F3[0]>0&&NeEvent->F3[1]>0&&NeEvent->F3[2]>0&&NeEvent->F3[3]>0)
	  af3 = (NeEvent->F3[0]+NeEvent->F3[1]+NeEvent->F3[2]+NeEvent->F3[3])/4. + gRandom->Uniform();
	if(NeEvent->F5[0]>0&&NeEvent->F5[1]>0&&NeEvent->F5[2]>0&&NeEvent->F5[3]>0)
	  af5 = (NeEvent->F5[0]+NeEvent->F5[1]+NeEvent->F5[2]+NeEvent->F5[3])/4. + gRandom->Uniform();

	if(NeEvent->tF3[0]>0&&NeEvent->tF3[1]>0&&NeEvent->tF3[2]>0&&NeEvent->tF3[3]>0)
	  tf3 = (NeEvent->tF3[0]+NeEvent->tF3[1]+NeEvent->tF3[2]+NeEvent->tF3[3])/4. + gRandom->Uniform();
	if(NeEvent->tF5[0]>0&&NeEvent->tF5[1]>0&&NeEvent->tF5[2]>0&&NeEvent->tF5[3]>0)
	  tf5 = (NeEvent->tF5[0]+NeEvent->tF5[1]+NeEvent->tF5[2]+NeEvent->tF5[3])/4. + gRandom->Uniform();

//	ToF = (tf5 - tf3)*0.125+89.165;
//	ToF = (tf5 - tf3)*0.0625;
//	ToF = (tf5 - tf3)*0.0625 + 68.55;
//	ToF = (tf5 - tf3)*0.0625 + 68.475;
//	ToF = (tf5 - tf3)*0.015625 + 68.475;
	ToF = (tf5 - tf3)*0.03125 + 68.475;

	NeEvent->af3 = af3;
	NeEvent->af5 = af5;
	NeEvent->ToF = ToF;

	if(af3*af5*tf3*tf5!=0){
//		if(NeEvent->trigger == 1)
		{
			d1ToF->Fill(ToF);
			d1aF3->Fill(af3);
			d2ToFaF3->Fill(ToF,af3);

			d1aF5->Fill(af5);
			d2ToFaF5->Fill(ToF,af5);

		}
	}

	for (int n=0; n<32; ++n) {
//		if(NeEvent->Xt[n]>0)
		{
			d1Xa[n]->Fill(NeEvent->Xa[n]);
			d1Xt[n]->Fill(NeEvent->Xt[n]);
		}
//		if(NeEvent->Yt[n]>0)
		{
			d1Ya[n]->Fill(NeEvent->Ya[n]);
			d1Yt[n]->Fill(NeEvent->Yt[n]);
		}
	}

	for (int n=0; n<16; ++n) {
//		if(NeEvent->Lt[n]>0)
		{
			d1La[n]->Fill(NeEvent->La[n]);
			d1Lt[n]->Fill(NeEvent->Lt[n]);
		}
	}

	for (int n=0; n<16; ++n) {
// #ifndef NO_ANNUAL
//		if(NeEvent->St[n]>0)
		{
			d1Sa[n]->Fill(NeEvent->Sa[n]);
			d1St[n]->Fill(NeEvent->St[n]);
		}
//		if(NeEvent->Rt[n]>0)
		{
			d1Ra[n]->Fill(NeEvent->Ra[n]);
			d1Rt[n]->Fill(NeEvent->Rt[n]);
		}
// #endif // NO_ANNUAL
//		if(NeEvent->Vt[n]>0)
		{
			d1Va[n]->Fill(NeEvent->Va[n]);
			d1Vt[n]->Fill(NeEvent->Vt[n]);
		}

		if(NeEvent->Rxt[n]>0)
		{
			d1Rxa[n]->Fill(NeEvent->Rxa[n]);
			d1Rxt[n]->Fill(NeEvent->Rxt[n]);
		}
		if(NeEvent->Ryt[n]>0)
		{
			d1Rya[n]->Fill(NeEvent->Rya[n]);
			d1Ryt[n]->Fill(NeEvent->Ryt[n]);
		}

		if(NeEvent->R20t[n]>0)
		{
			d1R20a[n]->Fill(NeEvent->R20a[n]);
			d1R20t[n]->Fill(NeEvent->R20t[n]);
		}

	}

//______ calibrated spectra __________________________

	for (n=0; n<32; ++n) {

		if(NeEvent->Xt[n]>0){
		  value1 = (double)NeEvent->Xa[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Xa->Energy(value1, n);
			NeEvent->Xc[n] = value2;
			d1Xc[n]->Fill(value2);
			mXa++;
			nXa=n;
			eXa = value2;
		}
		
		if(NeEvent->Yt[n]>0){
		  value1 = (double)NeEvent->Ya[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Ya->Energy(value1, n);
			NeEvent->Yc[n] = value2;
			d1Yc[n]->Fill(value2);
			mYa++;
			nYa=n;
			eYa = value2;
		}
	}

	for (n=0; n<16; ++n) {

		if(NeEvent->Lt[n]>0){
		  value1 = (double)NeEvent->La[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_La->Energy(value1, n);
			NeEvent->Lc[n] = value2;
			d1Lc[n]->Fill(value2);
			mLa++;
			nLa=n;
			eLa = value2;
		}
		
	}

	for (n=0; n<16; ++n) {
// #ifndef NO_ANNUAL
		if(NeEvent->St[n]>0){
		  value1 = (double)NeEvent->Sa[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Sa->Energy(value1, n);
			d1Sc[n]->Fill(value2);
			NeEvent->Sc[n] = value2;
			mSa++;
			eSa = value2;
		}

		if(NeEvent->Rt[n]>0){
		  value1 = (double)NeEvent->Ra[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Ra->Energy(value1, n);
			d1Rc[n]->Fill(value2);
			NeEvent->Rc[n] = value2;
			mRa++;
			eRa = value2;
		}
// #endif // NO_ANNUAL
		if(NeEvent->Vt[n]>0){
		  value1 = (double)NeEvent->Va[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Va->Energy(value1, n);
			d1Vc[n]->Fill(value2);
			NeEvent->Vc[n] = value2;
			mVa++;
			eVa = value2;
		}

		if(NeEvent->R20t[n]>0){
		  	value1 = (double)NeEvent->R20a[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_R20a->Energy(value1, n);
			d1R20c[n]->Fill(value2);
			NeEvent->R20c[n] = value2;
			mR20a++;
			eR20a = value2;
		}
		

		if(NeEvent->Rxt[n]>0){
		  	value1 = (double)NeEvent->Rxa[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Rxa->Energy(value1, n);
			d1Rxc[n]->Fill(value2);
			NeEvent->Rxc[n] = value2;
			mRxa++;
			eRxa = value2;
		}

		if(NeEvent->Ryt[n]>0){
		  value1 = (double)NeEvent->Rya[n] + gRandom->Uniform();
			value2 = ((TNeAnalysis*)go4)->p_Rya->Energy(value1, n);
			d1Ryc[n]->Fill(value2);
			NeEvent->Ryc[n] = value2;
			mRya++;
			eRya = value2;
		}

	}

	if(mXa==1 &&mYa==1 && mLa==1 &&abs(eXa-eYa)<2&&
	   mapLYSO(nLa,nXa,nYa)&&nXa<30){
		
		d2edeLYSO->Fill(eLa,eYa);
	}
	
		if(mR20a==1 && mRxa==1)
		{
			d2edeR20->Fill(eRxa,eR20a);
		}
		
		if(mXa==1 && mYa==1)
		{
			d2xy->Fill(eYa,eXa);
			d2Si->Fill(nYa,nXa);
		}
		

//---------------------start of MWPC----------------------------------------
//	if(NeEvent->trigger == 1 && ToF > 165 && ToF <185)
//	{ 
	
	   for(i = 0; i < NeEvent->nx1; ++i) d1X1->Fill(NeEvent->x1[i]);
	   for(i = 0; i < NeEvent->ny1; ++i) d1Y1->Fill(NeEvent->y1[i]);
	   for(i = 0; i < NeEvent->nx2; ++i) d1X2->Fill(NeEvent->x2[i]);
	   for(i = 0; i < NeEvent->ny2; ++i) d1Y2->Fill(NeEvent->y2[i]);
//	}	

	   if(NeEvent->nx1 > 0) d1NX1->Fill(NeEvent->nx1);

	   if(NeEvent->ny1 > 0) d1NY1->Fill(NeEvent->ny1);

	   if(NeEvent->nx2 > 0) d1NX2->Fill(NeEvent->nx2);

	   if(NeEvent->ny2 > 0) d1NY2->Fill(NeEvent->ny2);

      if(NeEvent->nx1 > 0)
		d1CX1->Fill(GetClasters(NeEvent->nx1, NeEvent->x1));

	   if(NeEvent->ny1 > 0)
		d1CY1->Fill(GetClasters(NeEvent->ny1, NeEvent->y1));

	   if(NeEvent->nx2 > 0)
		d1CX2->Fill(GetClasters(NeEvent->nx2, NeEvent->x2));

	   if(NeEvent->ny2 > 0)
		d1CY2->Fill(GetClasters(NeEvent->ny2, NeEvent->y2));

// Li9
//	if (NeEvent->nx1*NeEvent->ny1*NeEvent->nx2*NeEvent->ny2 == 1 && 162<ToF && ToF<170 && 1000<af3 && af3<1700) 
	
// He6	   
//	if (NeEvent->nx1*NeEvent->ny1*NeEvent->nx2*NeEvent->ny2 == 1 && ToF>158 && ToF<168 && af3>500 && af3<1100)
	   if (NeEvent->nx1*NeEvent->ny1*NeEvent->nx2*NeEvent->ny2 == 1)
		{
				mwz1 = -816;
				mwx1 = (16 - NeEvent->x1[0] + gRandom->Uniform())*1.25;
				mwy1 = (NeEvent->y1[0] - 16 + gRandom->Uniform())*1.25;
			
				mwz2 = -270;
				mwx2 = (16 - NeEvent->x2[0] + gRandom->Uniform())*1.25;
				mwy2 = (NeEvent->y2[0] - 16 + gRandom->Uniform())*1.25;
	
				zbt = 0;
				xbt = mwx2 + (mwx2 - mwx1)*(zbt-mwz2)/(mwz2-mwz1);
				ybt = mwy2 + (mwy2 - mwy1)*(zbt-mwz2)/(mwz2-mwz1);
				
				zbd = -110; // beam on the diaphragm 
				xbd = mwx2 + (mwx2 - mwx1)*(zbd-mwz2)/(mwz2-mwz1);
				ybd = mwy2 + (mwy2 - mwy1)*(zbd-mwz2)/(mwz2-mwz1);
				
				NeEvent->xbt = xbt;
				NeEvent->ybt = ybt;
				NeEvent->xbd = xbd;
				NeEvent->ybd = ybd;
			
				if (af5 > 700 && af5 < 1700)
// 				if (af5 > 2200 && af5 < 3800) // Be
				{
				  if (NeEvent->trigger == 1)
				  {
				    d2XYbeamOnTarTrg1->Fill(xbt, ybt);					
				  }
				  else
				  {
				    d2XYbeamOnTar->Fill(xbt, ybt);
				    d2XYbeamOnDia->Fill(xbd, ybd);
				  }
				}

				/*if (NeEvent->trigger == 2, NeEvent->trigger == 3, NeEvent->trigger == 4, NeEvent->trigger == 5)
				{
					d2XYbeamOnTar_trig2->Fill(xbt, ybt);
				}

				if (NeEvent->tF6[0]*NeEvent->tF6[1]*NeEvent->tF6[2]*NeEvent->tF6[3]>0)
				{
					d2XYbeamOnTar_F6->Fill(xbt, ybt);
				}
*/
		}
		
// 
	   if(NeEvent->nx1 > 0 && NeEvent->ny1 > 0 && (GetClasters(NeEvent->nx1, NeEvent->x1)) == 1 && (GetClasters(NeEvent->ny1, NeEvent->y1)) == 1)
	   {
		d2XY1->Fill(NeEvent->x1[0],NeEvent->y1[0]);
//		if(NeEvent->tF6[2] >100) d2XY1beam->Fill(NeEvent->x1[0],NeEvent->y1[0]);
//		if(NeEvent->trigger == 1) d2XY1beam->Fill(NeEvent->x1[0],NeEvent->y1[0]);
//		else	d2XY1->Fill(NeEvent->x1[0],NeEvent->y1[0]);
	   }
	
	   if(NeEvent->nx2 > 0 && NeEvent->ny2 > 0 && (GetClasters(NeEvent->nx2, NeEvent->x2)) == 1 && (GetClasters(NeEvent->ny2, NeEvent->y2)) == 1)
	   {
		d2XY2->Fill(NeEvent->x2[0],NeEvent->y2[0]);
//		if(NeEvent->tF6[2] >100) d2XY2beam->Fill(NeEvent->x2[0],NeEvent->y2[0]);
//		if(NeEvent->trigger == 1) d2XY2beam->Fill(NeEvent->x2[0],NeEvent->y2[0]);
//		else	d2XY2->Fill(NeEvent->x2[0],NeEvent->y2[0]);
	   }
		
		for (n=0; n<9; ++n){

//			if(NeEvent->Lt[n] > 600 && NeEvent->Lt[n] < 900 && mXa==1 && mYa==1) {
//				d2XL[n]->Fill( (double) NeEvent->La[n],eXa);
			if(NeEvent->Lt[n] > 600 && NeEvent->Lt[n] < 1200 &&
			   abs(eYa-eXa)<3&&
			   mYa==1 && mXa==1&& mapLYSO(n,nXa,nYa) && Dtime > 260) {
				d2XL[n]->Fill( (double) NeEvent->La[n],eYa);
			}
		}

/*
	   if(NeEvent->nx1 == 1 && NeEvent->ny1 == 1 && NeEvent->trigger == 1)
	   {
		d2XY1->Fill(NeEvent->x1[0],NeEvent->y1[0]);
	   }
	
	   if(NeEvent->nx2 == 1 && NeEvent->ny2 == 1 && NeEvent->trigger == 1)
	   {
		d2XY2->Fill(NeEvent->x2[0],NeEvent->y2[0]);
	   }

*/

//---Pictures---
/*
	   if(NeEvent->nx1 == 1 && NeEvent->nx2 == 1)
	   {
		ya1 = -0.5*pya1 + dx1 + (pya1 / 32.)*NeEvent->x1[0];
	        ya2 = -0.5*pya2 + dx2 + (pya2 / 32.)*NeEvent->x2[0];
	        ya3 = ya1 + dtx + (ya2 - ya1) * (pxa3 - pxa1) / (pxa2 - pxa1); 

               if(ya3 > -0.5*pya1 && ya3 < 0.5*pya1)
	       {    
   			if(((TNeAnalysis*)go4)->pMTracks->mtracksx != ntrackx)
			{
				ntrackx = ((TNeAnalysis*)go4)->pMTracks->mtracksx;
				fTracksX->Set(3*ntrackx);
				itrackAX = 0;
				for(i = 0; i < fTracksX->GetN(); ++i)
	   				fTracksX->SetPoint(i,pxb1,0.);
			}
			if(itrackAX == fTracksX->GetN()) itrackAX = 0;
   
			fTracksX->SetPoint(itrackAX++,pxa1,ya1);
			fTracksX->SetPoint(itrackAX++,pxa3,ya3);
			fTracksX->SetPoint(itrackAX++,pxa1,ya1);
	   	}
	   } 
 
	   if(NeEvent->ny1 == 1 && NeEvent->ny2 == 1)
   	   {
	    	yb1 = -0.5*pyb1 + dy1+ (pyb1 / 32.)*NeEvent->y1[0];
	   	yb2 = -0.5*pyb2 + dy2+ (pyb2 / 32.)*NeEvent->y2[0];
	 
	   	yb3 = yb1 + dty + (yb2 - yb1) * (pxb3 - pxb1) / (pxb2 - pxb1); 

   		if(yb3 > -0.5*pyb1 && yb3 < 0.5*pyb1)
   		{    
   			if(((TNeAnalysis*)go4)->pMTracks->mtracksy != ntracky)
			{
				ntracky = ((TNeAnalysis*)go4)->pMTracks->mtracksy;
				fTracksY->Set(3*ntracky);
				itrackBX = 0;
				for(i = 0; i < fTracksY->GetN(); ++i)
   					fTracksY->SetPoint(i,pxb1,0.);
			}
			if(itrackBX == fTracksY->GetN()) itrackBX = 0;
   
			fTracksY->SetPoint(itrackBX++,pxb1,yb1);
			fTracksY->SetPoint(itrackBX++,pxb3,yb3);
			fTracksY->SetPoint(itrackBX++,pxb1,yb1);
   		}
  	 }
	  if(NeEvent->nx1 == 1 && NeEvent->nx2 == 1 && NeEvent->ny1 == 1 && NeEvent->ny2 == 1 )
	   {

			d2Target->Fill(ya3,yb3);
	   }*/

//--------------------end of MWPC----------------------------------------


	NeEvent->SetValid(kTRUE); // to store
	return kTRUE;
} //-------------------------------------------------------------------

double TNeProc::GetClasters(unsigned short n, unsigned short *x)
{
	int i;
	double clasters = 1;

	if(n == 0) clasters = 0.;
	else if(n > 1)
	{
		for(i = 1; i < n; ++i)
		{
			if(abs(x[i] - x[i-1]) > 1) clasters += 1.;
		}
	}
	return clasters;
} //--------------------------------------------------------------------
