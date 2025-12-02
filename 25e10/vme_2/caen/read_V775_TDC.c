/***************************************************************************/
/* read_V775_TDC.c                                                         */
/* HS                                                                      */
/* 02-09-05 check busy bit in status register before reading the buffer    */
/* AG check BUFFER EMPTY after readout									   */
/***************************************************************************/

{
  // Read the Output Buffer of CAEN TDC V775

  long i,temp,
       lwtype,
       ncV775;

  /*-------------------*/

  if(!(v775_ptr[card]->status_reg_1 & 0x04)) // NEW 02-09-05: module not busy
  {
    // read the first longword:
    temp = *(output_buffer[card]);

    // extract longword "type" (2=header,6=invalid data):
    lwtype = (temp >> V7X5__HEADER_TYPE_SHIFT) & V7X5__HEADER_TYPE_MASK;

    if (lwtype == 2)
    {
      // extract number of data longwords:
      ncV775 = (temp >> V7X5__HEADER_CNT_SHIFT) & V7X5__HEADER_CNT_MASK;

#ifdef OLD_FORMAT
      // pass on the header long word after reformatting it a bit:
      //  push the "number of converted chns" to the lowest 6 bits...
      *(memory.p32++) = (temp & 0xffff0000) + ncV775;
#endif
      *(memory.p32++) = temp;

      // read and pass on the data in "original" format (long words):
      for(i=0 ; i < ncV775; i++)
        *(memory.p32++) = *(output_buffer[card]);

      // read the EOB longword (GEO and "event counter" info):
      *(memory.p32++) = *(output_buffer[card]);
    }
    else  // most likely no valid data (lwtype was 6)
    {
#ifdef OLD
      // IF "no valid data" we need to reformat the header info a bit:
      //  we pass on the GEO address + the "not valid datum" identifier
      //  and also return "number of channels" as zero

      *(memory.p32++) = (temp & 0x07000000) + 
                       ((v775_ptr[card]->geo_addr & 0x1F) << 27);
#endif
      *(memory.p32++) = temp;
    }
  }  
  else  // module busy
    *(memory.p32++) = 0x05000000;  // NEW return value 5: module busy 
                                   // 2: valid data, 6: empty buffer

								   
								   

// check bit1 (BUFFER EMPTY) in status reg2 of CAEN TDC V775

	if((v775_ptr[card]->status_reg_2 & 0x2) == 0x0)
	{
		printf("Buffer not empty after readout!  card = %i\n",card);

		for(j=0;j<32;j++)
		{
		  if((v775_ptr[card]->status_reg_2 & 0x2) == 0x0)
			{v775_ptr[card]->inc_event = 0x0;

		  //printf("             j=  %d\n",j);
			}	
		  else
			j=32;
		}
	}									   
	   
}

/* EOF */

