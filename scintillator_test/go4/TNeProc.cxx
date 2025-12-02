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

void TNeProc::MakeHistND()
{
	//-----neutrons-----
	for (int i = 0; i < 48; ++i) {
		d1neutAmp[i] = MakeTH1('I', Form("scint/Amp/Amp_%2.2d",i),
					 Form("Amp CH %2.2d",i),
					 8192, 0., 8191.);
		d1neutTAC[i] = MakeTH1('I', Form("scint/TAC/TAC_%2.2d",i),
					 Form("TAC CH %2.2d",i),
					 4096, 0., 4095.);
		d1neutTDC[i] = MakeTH1('I', Form("scint/Time/Time_%2.2d",i),
				       Form("Time CH %2.2d",i),
				       5000, 0., 4999.);
		d2Ngamma[i]   = MakeTH2('I', Form("scint/Ng/Ng_%2.2d",i)
					, Form("N gamma %2.2d",i), 400, 0., 4095., 400, 0., 4095.,"Amp","TAC");
	}
//------Digitizer----
	// for ( int i = 0; i < 16; ++i) {
	// 	d1digi_1w[i] = MakeTH1('I',Form("Digitizer/long/l_digi_%2.2d",i),
	// 			       Form("Long window CH %2.2d",i), 4096, 0.,4095.);
	// 	d1digi_2w[i] = MakeTH1('I', Form("Digitizer/short/s_digi_%2.2d",i)
	// 			       , Form("Short window CH %2.2d",i), 4096, 0., 4095.);
	// 	digi_g_n[i]   =  MakeTH2('D', Form("Digitizer/gn/gn_digi_%2.2d",i)
	// 				 , Form("PSD %2.2d",i), 400, 0., 4095., 400, -1.,1.,"amp","psd");
	// }

	// d2digiADC = MakeTH2('I', "2D", "Correlation",
	// 		    400, 0., 4095., 400, 0., 4095.,"digi","ADC");
	
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
				case 9:	// Time
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
	/* Digitizer
	for (int n=0; n<4; ++n) {
		if(ev->digi_1w[n] > 0) d1digi_1w[n]->Fill(ev->digi_1w[n]);
		if(ev->digi_2w[n] > 0) d1digi_2w[n]->Fill(ev->digi_2w[n]);
		if(ev->digi_1w[n] > 0 && ev->digi_2w[n] > 0) 	{
			double psd = (double)(ev->digi_1w[n]-ev->digi_2w[n])/(double) ev->digi_1w[n];
			double amp = (double) ev->digi_1w[n];
			digi_g_n[n]->Fill(amp, psd);
		}
	}
	*/

//-----neutrons-----
	for (int n=0; n<4; ++n) {

		if(ev->neutTDC[n] > 0) {
			d1neutAmp[n]->Fill(ev->neutAmp[n]);
			d1neutTAC[n]->Fill(ev->neutTAC[n]);
			d1neutTDC[n]->Fill(ev->neutTDC[n]);
			d2Ngamma[n] ->Fill(ev->neutAmp[n],ev->neutTAC[n]);
		}
	}
//-----correlations-----
	// if(ev->digi_1w[0] > 0 && ev->NneutAmp[0] > 0)
	// 	d2digiADC->Fill(ev->digi_1w[0],ev->NneutAmp[0]);

}

TNeProc::TNeProc() : TGo4EventProcessor()
{
	int i;
	cout << "**** TNeProc: Create instance " << endl;
	fTrigger = NULL;
	fSubEvents = NULL;
	fEventsSizes = NULL;

} //-------------------------------------------------------------------

TNeProc::~TNeProc()
{
	cout << "**** TNeProc: Delete instance " << endl;
} //-------------------------------------------------------------------

TNeProc::TNeProc(const char* name) : TGo4EventProcessor(name)
{
	TGo4Log::Info("**** TNeProc: Create instance %s", name);
	fTrigger = MakeTH1('I', "Trigger","Values of trigger",16, 0., 15.);
	futime    = MakeTH1('I', "utime",    "mashine time (usec)",   65536, 0, 65535);
	fSubEvents  = MakeTH1('I', "SubEvents",  "Number of subevents", 16, 0, 15);
	fEventsSizes = MakeTH1('I', "EventSizes", "Size of each event", 1024, 0, 1023);

	// ND demonstrator
	MakeHistND();

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
//
	int num = 0, sz = 0;
	int i, n, geo, typ, header,caen_header, module_id=0, crate=-1, cnt, chnl, evnt /*,gch*/;

	bool m_bool= false, c_bool = false;
	uint16_t MSB, LSB;
	uint32_t MSBLSB, adc;
	uint32_t *idata;

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
							switch (module_id) {
							case  1:	
								break;

							case  2:
								break;

							case  3:
								break;

							case  4:
								break;
							case  5:
								break;

							case  6:
								break;
							case  7:
								break;

							case  8:
								break;
							case  9:							
								break;
							case 10:
								break;
							case 11:
								break;
							case 12:
								break;
							case 13:
								break;
							case 14:
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
									case 0:
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
						     break;

						case 2:
						      break;
						case 3:
						      break;
						case 4:
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
									case 3:
										break;

									case 4:
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

	NeEvent->SetValid(kTRUE); // to store
	return kTRUE;
} //-------------------------------------------------------------------
