//===================================================================
//== TNeDet16.cpp: exp0211
//== Version: 2011-02-01
//===================================================================

using namespace std;

#include "TNeDet16.h"

#include <stdio.h>
#include "Riostream.h"

const int mchan = 16;
const int m     = 3;

//***********************************************************
TNeDet16::TNeDet16(const char* name)
	:TGo4Parameter(name)
	,kread(0)
	,n(2)
	,nchan(mchan)
{
	for(int i = 0; i < mchan; ++i)
	{
		a[i][0] = 0.;
		a[i][1] = 1.;
		a[i][2] = 0.;
	}
} //----------------------------------------------------------------

TNeDet16::~TNeDet16()
{
} //-----------------------------------------------------------------

Bool_t TNeDet16::UpdateFrom(TGo4Parameter *source)
{
	cout << "**** TNeDet1 " << GetName() 
		<< " updated from auto save file" << endl;

	TNeDet16 * from = dynamic_cast<TNeDet16 *>(source);

	if(from==0) 
	{
		cout << "Wrong parameter class: " 
			<< source->ClassName() << endl;
		return kFALSE;
	}

	kread = from->kread;
	switch(kread)
	{
	case 1:
		kread = 0;
		from->kread = 0;
		ReadData();
		from->n = n;
		from->nchan = nchan;
		for(int i = 0; i < mchan; ++i)
		{
			from->a[i][0] = a[i][0];
			from->a[i][1] = a[i][1];
			from->a[i][2] = a[i][2];
		}
		break;
	default:
		n = from->n;
		nchan = from->n;
		for(int i =0; i < mchan; ++i)
		{
			a[i][0] = from->a[i][0];
			a[i][1] = from->a[i][1];
			a[i][2] = from->a[i][2];
		}
	}
  return kTRUE;
} //-----------------------------------------------------------------

void TNeDet16::ReadData()
{
	TString xname = GetName();
	xname.ToLower();
	xname += ".clb";
	xname = "clb/"+xname;
	FILE* F = fopen(xname.Data(),"rt");
	if(!F)
	{
		printf("\n\n!!! FILE: %s WAS NOT FOUND\n\n"
			,xname.Data());
		return;
	}

	fscanf(F,"%d%d",&n,&nchan);
	for(int i=0; i<nchan; i++)
	{
		fscanf(F,"%lf%lf%lf",&a[i][0],&a[i][1],&a[i][2]);
	}
	printf("\n\nREAD DATA FROM FILE: %s\n\n",xname.Data());
	fclose(F);

	return;
} //-----------------------------------------------------------------

double TNeDet16::Energy(double value, int chan)
{
	double res = a[chan][n-1];
	for(int i = n-2; i >= 0 ; --i)
	{
		res = res * value + a[chan][i];
	}
	return res;
} //-----------------------------------------------------------------

