{	int i, j, k, ch;

	for(i=20;i<24;i++)
	{
		printf("Cycle", i);
		mwpc_ptr[i]->crate = 1;
		mwpc_ptr[i]->geo   = i;
		mwpc_ptr[i]->ndata = 0;
/*		for(j = 0; j < 16; ++j) mwpc_ptr[i]->k_read[j] = 0;
		
		mwpc_ptr[i]->offset = pl_rem_cam[1];
		
		for(ch = 0; ch < 2; ++ch)
		{
			mwpc_ptr[i]->data[ch] = CNAFLOC(1,i,0,2,pl_rem_cam[1]);
			mwpc_ptr[i]->data[ch] = CNAFLOC(1,i,1,2,pl_rem_cam[1]);
			mwpc_ptr[i]->k_read[ch] = 1;
		}
		
		
		//====================================================================
		//== Set top and bottom		
		//====================================================================

  
		if(mwpc_ptr[i]->k_read[15] == 0)
		{
			mwpc_ptr[i]->k_read[15] = 1;
			mwpc_ptr[i]->data[15] = CNAFLOC(0,i,15,2,pl_rem_cam[1]);
		}

		mwpc_ptr[i]->top = (mwpc_ptr[i]->geo << 27) & 0xf8000000;
		mwpc_ptr[i]->top += (1 << 25);
		mwpc_ptr[i]->top += (mwpc_ptr[i]->crate << 16);
		mwpc_ptr[i]->top += (mwpc_ptr[i]->ndata << 8);

		mwpc_ptr[i]->bot = (mwpc_ptr[i]->geo << 27) &0xf8000000;
		mwpc_ptr[i]->bot += (1 << 26);

		mwpc_ptr[i]->ndata = 0;
		for(k = 0; k < 16; ++k)
		{
			mwpc_ptr[i]->adr[k] =  (mwpc_ptr[i]->geo << 27) & 0xf8000000;
			mwpc_ptr[i]->adr[k] += (k << 16);
			if(mwpc_ptr[i]->k_read[k]) mwpc_ptr[i]->ndata++;
	    }*/
	}
}
