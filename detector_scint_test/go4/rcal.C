void rcall(const char* name)
{
	TNeDet1 *pDet 
	= (TNeDet1*)(TGo4Analysis::Instance())->GetParameter(name);
	if(!pDet)
	{
		printf("OBJECT: %s WAS NOT FOUND \n",name);
		return;
	}
	TString fname(name);
	fname.ToLower();
	fname += ".cal";
	pDet->Read(fname.Data());
}
