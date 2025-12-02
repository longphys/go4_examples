/* -*- mode:c++ c-file-style:"linux" -*- */
/* -*- mode:c++ c-file-style:"linux" -*- */
//===================================================================
//== TNeEvent.cxx:
//== Version:
//===================================================================
using namespace std;

#include "T6He2Event.h"
#include "Riostream.h"
#include "TGo4Log.h"
#include <algorithm>

T6He2Event::T6He2Event() : TGo4EventElement()
{
	TGo4Log::Info("T6He2Event: Create instance");
}

T6He2Event::T6He2Event(const char* name)
	:TGo4EventElement(name)
{
	TGo4Log::Info("T6He2Event: Create instance %s",
		name);
}

T6He2Event::~T6He2Event()
{
	TGo4Log::Info("T6He2Event: Delete instance");
}

void  T6He2Event::Clear(Option_t *t)
{
	beam_beta=0;
	beam_gamma=0;
} 
