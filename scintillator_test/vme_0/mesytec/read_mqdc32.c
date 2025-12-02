//=====================================================================
//=== read_mqdc32.c
//===  02-07-15
//=====================================================================
{
  long i, ndata;

	mqdc32_ptr[card]->start_acq=0; // stop gate accepting
    //=== read event length
    ndata = mqdc32_ptr[card]->buffer_data_len;
    // read data (+header/trailer) from buffer 

    if (ndata) {
      
      for(i=0;i<ndata;i++)
	*memory.p32++ = *output_buffer[card];

    }
		else
		{
			//=== write no data header (the same as caen)
			*memory.p32++ = 0x06000000; 
		}


	if ((mqdc32_ptr[card]->buffer_data_len) > 0){
	 	 sprintf(c_line,"MQDC32 (card=#%d) buffer not empty after readout. If you can see this line, not about it in the experimental log book",card);
		 F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
	}
	
  //=== readout reset (allows new trigger in single event mode)
  mqdc32_ptr[card]->readout_reset=1;
  mqdc32_ptr[card]->start_acq=1; // start gate accepting
}

//===EOF

