/****************************************************************************/
/* read_v560.c                                                         		*/
/* AG 29-09-17                                                             	*/
/*																		    */
/****************************************************************************/

{
  // Read the CAEN V560 Scaler
    int ncV560;
    long temp;
    ncV560=16; //number of scalers for reading
	
    temp = (long)0x2000000L + (long)(card << 27); // CAEN header 
    *(memory.p32++) = temp;
	/*-------------------*/
    // read and pass on the data in "original" format (long words):
    for(i=0 ; i < ncV560; i++)
		*(memory.p32++) = v560_ptr[card]->counter[i] + (long)(card << 27);
	
	temp = (long)0x4000000L + (long)(card << 27); // CAEN footer
	*(memory.p32++)=temp;
}

/* EOF */

