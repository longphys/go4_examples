//***********************************************************************
// read_madc32.c
//
// HS 29-10-10
//***********************************************************************
{
  long i,
       ndata;

  // read data ready bit

  if (madc32_ptr[card]->data_ready)
  {
    // read event length

    ndata = madc32_ptr[card]->buffer_data_len;

    // read data (+header/trailer) from buffer

    if (ndata) 
    {
      // test header format???

      for(i=0;i<ndata;i++)
        *memory.p32++ = *output_buffer[card];

      // test trailer format???
    }
		else
		{
			//=== write no data header (the same as caen)
			*memory.p32++ = 0x06000000; 
		}
 
  }  
  else
    *memory.p32++ = 0xaffeaffe; 


  // readout reset (allows new trigger in single event mode)

  madc32_ptr[card]->readout_reset=1;

}

// EOF

