//===================================================================
//== TNeAnalysis.cxx:	exp0211
//== Version:	2011-02-01
//===================================================================

using namespace std;

#include "TNeAnalysis.h"

#include <stdlib.h>
#include "Riostream.h"

#include "Go4EventServer.h"
#include "TGo4StepFactory.h"
#include "TGo4AnalysisStep.h"
#include "TNeDet16.h"
//#include "TNeH1Parms.h"
//#include "TNeH2Parms.h"
#include "TNeMParms.h"
#include "TNeSel.h"

#include "TGo4Version.h"
#include "TGo4MbsEventServer.h"

//***********************************************************
TNeAnalysis::TNeAnalysis()
:fMbsEvent(0)
	,fEvents(0)
	,fLastEvent(0)
{
}
//***********************************************************

// this constructor is called by go4analysis executable
TNeAnalysis::TNeAnalysis(int argc, char** argv)
   :TGo4Analysis(argc, argv)
	,fMbsEvent(0)
	,fEvents(0)
	,fLastEvent(0)
{
   cout << "**** Create TNeAnalysis name: " << argv[0] << endl;

   if (!TGo4Version::CheckVersion(__GO4BUILDVERSION__)) {
      cout << "****  Go4 version mismatch" << endl;
      exit(-1);
   }

   TGo4StepFactory* factory = new TGo4StepFactory("Factory");
   factory->DefEventProcessor("NeProc","TNeProc");// object name, class name
   factory->DefOutputEvent("NeEvent","TNeEvent"); // object name, class name

//   TGo4EventSourceParameter* sourcepar = new TGo4MbsEventServerParameter("rio3");
   TGo4EventSourceParameter* sourcepar = new TGo4MbsStreamParameter("rio3-2");

    //TGo4EventSourceParameter* sourcepar = new TGo4MbsTransportParameter("rio3");

 //  TGo4EventSourceParameter* sourcepar = 
 //      new TGo4MbsFileParameter("/LynxOS/RIO3_3.1/mbsusr/user1/mbsrun/flnr/wrk3a/aa*.lmd");

   TGo4FileStoreParameter* storepar = new TGo4FileStoreParameter(Form("%sOutput", argv[0]),99,320000,5);
   storepar->SetOverwriteMode(kTRUE);

   TGo4AnalysisStep* step = new TGo4AnalysisStep("Analysis", factory, sourcepar, storepar);

   step->SetSourceEnabled(kTRUE);
   //step->SetStoreEnabled(kTRUE);
   step->SetProcessEnabled(kTRUE);
   step->SetErrorStopEnabled(kTRUE);

    // Now the first analysis step is set up.
   // Other steps could be created here
   AddAnalysisStep(step);

   // uncomment following line to define custom passwords for analysis server
   // DefineServerPasswords("Neadmin", "Nectrl", "Neview");
   DefineServerPasswords("Acu0La0", "Acu0La0",  "go4view");

   //////////////// Parameter //////////////////////////
   // At this point, autosave file has not yet been read!
   // Therefore parameter values set here will be overwritten
   // if an autosave file is there.

//   pMTracks = new TNeMParms("MTRACKS");
//   AddParameter(pMTracks);

}

//***********************************************************
TNeAnalysis::~TNeAnalysis()
{
   cout << "**** TNeAnalysis: Delete instance" << endl;
}

//-----------------------------------------------------------
Int_t TNeAnalysis::UserPreLoop()
{
   // all this is optional:
   cout << "**** TNeAnalysis: PreLoop" << endl;
   // get pointer to input event (used in postloop and event function):
   fMbsEvent = dynamic_cast<TGo4MbsEvent*> (GetInputEvent("Analysis"));   // of step "Analysis"
   if(fMbsEvent) {
      // fileheader structure (lmd file only):
      s_filhe* fileheader=fMbsEvent->GetMbsSourceHeader();
      if(fileheader)
      {
         cout <<"\nInput file: "<<fileheader->filhe_file << endl;
         cout <<"Tapelabel:\t" << fileheader->filhe_label<<endl;
         cout <<"UserName:\t" << fileheader->filhe_user<<endl;
         cout <<"RunID:\t" << fileheader->filhe_run<<endl;
         cout <<"Explanation: "<<fileheader->filhe_exp <<endl;
         cout <<"Comments: "<<endl;
         Int_t numlines=fileheader->filhe_lines;
         for(Int_t i=0; i<numlines;++i)
         {
            cout<<"\t"<<fileheader->s_strings[i].string << endl;
         }
      }
   }
   fEvents=0; // event counter
   fLastEvent=0; // number of last event processed

   return 0;
}
//-----------------------------------------------------------
Int_t TNeAnalysis::UserPostLoop()
{
   // all this is optional:
   cout << "**** TNeAnalysis: PostLoop" << endl;
   cout << "Last event  #: " << fLastEvent << " Total events: " << fEvents << endl;
   fMbsEvent = 0; // reset to avoid invalid pointer if analysis is changed in between
   fEvents=0;
   return 0;
}

//-----------------------------------------------------------
Int_t TNeAnalysis::UserEventFunc()
{
   // all this is optional:
   // This function is called once for each event after all steps.
   if(fMbsEvent) {
      fEvents++;
      fLastEvent=fMbsEvent->GetCount();
   }
   if(fEvents == 1 || IsNewInputFile()) {
      cout << "First event #: " << fLastEvent  << endl;
      SetNewInputFile(kFALSE); // we have to reset the newfile flag
   }
   return 0;
}
