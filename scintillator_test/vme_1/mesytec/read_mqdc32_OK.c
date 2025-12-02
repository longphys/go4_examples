//=====================================================================
//=== read_mqdc32.c
//===  02-07-15
//=====================================================================
{
  long i, ndata;


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
  //=== readout reset (allows new trigger in single event mode)
  mqdc32_ptr[card]->readout_reset=1;
}

//===EOF

