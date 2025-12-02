/****************************************************************************/
/* read_v785_ADC.c                                                         	*/
/* HS                                                                      	*/
/* 02-09-05 check busy bit in status register before reading the buffer   	*/
/* AG check BUFFER EMPTY after readout									    */
/****************************************************************************/

{
  // Read the Output Buffer of CAEN ADC V785 and check BUFFER EMPTY

  long i,temp,temp1,
       lwtype,
       ncV785;

  /*-------------------*/

  if(!(v785_ptr[card]->status_reg_1 & 0x04)) // NEW 02-09-05: module not busy
  {
    // read the first longword:
    temp = *(output_buffer[card]);
//		printf("first lw 0x%08x\n",temp);

    // extract longword "type" (2=header,6=invalid data):
    lwtype = (temp >> V7X5__HEADER_TYPE_SHIFT) & V7X5__HEADER_TYPE_MASK;

    if (lwtype == 2)
    {
      // extract number of data longwords:
      ncV785 = (temp >> V7X5__HEADER_CNT_SHIFT) & V7X5__HEADER_CNT_MASK;
      *(memory.p32++) = temp;

      // read and pass on the data in "original" format (long words):
      for(i=0 ; i < ncV785; i++)
        *(memory.p32++) = *(output_buffer[card]);

      // read the EOB longword (GEO and "event counter" info):
      temp1 = *(output_buffer[card]);
//		printf("EOB lw 0x%08x\n",temp1);
      *(memory.p32++) = temp1;
      
    }
    else  // most likely no valid data (lwtype was 6)
    {
      *(memory.p32++) = temp;
    }
  }
  else  // module busy
    *(memory.p32++) = 0x05000000;  // NEW return value 5: module busy
                                   // 2: valid data, 6: empty buffer

								   
								   
								   
// check bit1 (BUFFER EMPTY) in status reg2 of V785 CAEN ADC cards

	if((v785_ptr[card]->status_reg_2 & 0x2) == 0x0)
	{
		printf("Buffer not empty after readout!  card = %i\n",card);

		for(j=0;j<32;j++)
		{
		  if((v785_ptr[card]->status_reg_2 & 0x2) == 0x0)
			{v785_ptr[card]->inc_event = 0x0;

		  //printf("             j=  %d\n",j);
			}	
		  else
			j=32;
		}
	}							   
								   
}

/* EOF */

