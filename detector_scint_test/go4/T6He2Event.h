/* -*- mode:c++ c-file-style:"linux" -*- */
//===================================================================
//== T6He2Event.h:
//== Version: 
//===================================================================

#ifndef T6HE2EVENT_H
#define T6HE2EVENT_H

#include "TGo4EventElement.h"

class T6He2Event : public TGo4EventElement 
{
public:
	T6He2Event();
	T6He2Event(const char* name);
	virtual ~T6He2Event();

	void Clear(Option_t *t="");

	double beam_beta;
	double beam_gamma;
	
	ClassDef(T6He2Event,1)
};
#endif // T6HE2EVENT_H



