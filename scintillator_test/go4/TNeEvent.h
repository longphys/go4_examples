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



