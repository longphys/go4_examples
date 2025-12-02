//=============================================================================
//==      	SYSTEM TIME
//=============================================================================
#define VTIMER_H
#include <time.h>

struct timeval vt_t0,vt_tx;

typedef struct 
{
	long header,bottom;
	long td;
	unsigned short geo_address;
} s_vt;
