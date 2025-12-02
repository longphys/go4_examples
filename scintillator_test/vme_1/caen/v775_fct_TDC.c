
/*************************************************************************/
/* v775_fct.c  functions for CAEN V775 TDC (outputs with F_ERROR)        */
/* HS                                                                    */
/* 30-08-05 add functions for overflow suppression                       */
/* 06-02-07 add function V775_DisableChannels                            */
/* 08-03-07 add function 'V775_SlidScaleOff()'                           */
/*                                                                       */
/*************************************************************************/

void V775_SoftReset (int card)
{
  v785_ptr[card]->geo_addr = card;
  v775_ptr[card]->bit_set_1 = 0x80;  // set and clear bit 7
  v775_ptr[card]->bit_clear_1 = 0x80;
}


void V775_StandardSetup (int card)
{
  //  Initialize the V775 TDC for standard list mode operation
  //   and clear data & pointers...
  //--------------------------------------------

  v775_ptr[card]->bit_set_2 = 0x4;     /* set and clear bit 2 */
  v775_ptr[card]->bit_clear_2 = 0x4;

  // clear the event counter:
  v775_ptr[card]->event_counter_reset = 1;

  // turn OFF the following non-reserved bits:
  // (see v775 manual for details!)
  // (bit 13,12,10,6,5,4,3,1,0)

  v775_ptr[card]->bit_clear_2 = 0x347b;   /* 0011 0100 0111 1011 */ 

  // ----- turn on relevant bits of BIT SET 2 register
  // (see v775 manual for details!)
  // (bit 14,11,8,7)

  v775_ptr[card]->bit_set_2 = 0x4980;     /* 0100 1001 1000 0000 */
  
  return ;
}


void V775_StepThresholdOn (int card)
{
  //  this function turns "step threshold" ON
  //   => chn suppressed if ADC value < threshold * 2
  //--------------------------------------------

  v775_ptr[card]->bit_set_2 = 0x100;  /* set Bit 8 (wrong in manual!) */

  return ;
}


void V775_StepThresholdOff (int card)
{
  //  this function turns "step threshold" OFF
  //   => chn suppressed if ADC value < threshold * 16
  //--------------------------------------------

  v775_ptr[card]->bit_clear_2 = 0x100;  /* clear Bit 8 (wrong in manual!) */

  return ;
}
 

void V775_ZeroSuppressionOn (int card)
{
  //  this function turns zero suppression ON
  //--------------------------------------------

  v775_ptr[card]->bit_clear_2 = 0x10;  /* clear Bit 4 */

  return ;
}


void V775_ZeroSuppressionOff (int card)
{
  //  this function turns zero suppression OFF
  //--------------------------------------------

  v775_ptr[card]->bit_set_2 = 0x10;    /* set Bit 4 */

  return ;
}

 
void V775_EnableAllChannels (int card)
{
  // ----- enable all channels

  int i;

  for (i=0; i<32; i++)
    v775_ptr[card]->thresholds[i] = 
             v775_ptr[card]->thresholds[i] & 0xfeff;   /* clear kill bit(8) */

  return ;
}


void V775_DisableChannels (int card, unsigned long mask)
{
  // ----- disable channels with 'mask'
  //--------------------------------------------

  int i;
  unsigned long ch_bit=1;

  for (i=0; i<32; i++)
  {
    if (ch_bit & mask)  // disable channel
    {
      v775_ptr[card]->thresholds[i] =
             v775_ptr[card]->thresholds[i] | 0x0100;   /* set kill bit(8) */
    }
    ch_bit=2*ch_bit;
  }

  return ;
}


void V775_SetThreshold (int card, int n, int val)
{
  // Set the threshold value [val] for the
  // n_th channel
  //   !!! be careful not to overwrite the "kill" bit (8)!
  //--------------------------------------------

  short l_val;

  if (n>= 0 && n < 32 && val <= 255) 
  {
    l_val = ((v775_ptr[card]->thresholds[n] >> 8) << 8) + val;
    v775_ptr[card]->thresholds[n] = l_val;
  }

  return ;
}

void V775_ResetThresholds (int card)
{
  //  Reset/Initialize the V775 thresholds
  //--------------------------------------------

  int i;

  for(i=0 ; i < 32 ; i++)
    V775_SetThreshold(card, i, 0) ;

  return;
}


void V775_DisplayStoredThresholds (int card)
{

  // Display thresholds stored in V775
  //-------------------------------------

  int i;
  char dummy[10];

/*
  printf("\n Channel/Threshold/Kill-bit -> \n") ;
  for(i=0 ; i < 32; i++)
  printf(" %d/%d/%d ",i,v775_ptr[card]->thresholds[i] & 0xff,
                      (v775_ptr[card]->thresholds[i] & 0x100)>>8) ;

  printf("\n");
  fflush(stdout);
*/

  F_ERROR(ERR__MSG_INFO,0,"Channel/Threshold/Kill-bit ->",l_pr_mask);
  sprintf(c_line," ");
  for(i=0;i<32;i++)
  {
    sprintf(dummy," %02d/%02d/%d ",i,v775_ptr[card]->thresholds[i] & 0xff,
                      (v775_ptr[card]->thresholds[i] & 0x100)>>8) ;
    strcat(c_line,dummy);
    if (strlen(c_line) >= 55)
    {
      F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
      sprintf(c_line," ");
    }
  }

  strcat(c_line,".");
  F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

  return ;
}


int V775_ReadOutputBuffer(int card, long **pl_dat)
{
  // Read the Output Buffer
  //--------------------------------------------

  long i,temp,
       lwtype,
       ncV775;

  // read the first longword:
  temp = *(output_buffer[card]);

  // extract longword "type" (2=header,6=invalid data):
  lwtype = (temp & 0x7000000) >> 24 ;

  if (lwtype == 2) 
  {
    // extract number of data longwords:
    ncV775 = ( temp >> V775__OUTPUT_BUFFER_GEO_N_WORD_COUNT)
              & V775__OUTPUT_BUFFER_WORD_COUNT ;

    // pass on the header long word after reformatting it a bit:
    //  push the "number of converted chns" to the lowest 6 bits...
    *((*pl_dat)++) = (temp & 0xffff0000) + ncV775;

    // read and pass on the data in "original" format (long words):
    for(i=0 ; i < ncV775; i++)
      *((*pl_dat)++) = *(output_buffer[card]);

    // read the EOB longword (GEO and "event counter" info):
    *((*pl_dat)++) = *(output_buffer[card]); 

    ncV775++ ;    // N_Channel + EventCounter-buffe
  } 
  else  // most likely no valid data (lwtype was 6) 
  {  
    // IF "no valid data" we need to reformat the header info a bit:
    //  we pass on the GEO address + the "not valid datum" identifier
    //  and also return "number of channels" as zero

    ncV775 = 0;
    *((*pl_dat)++) = (temp & 0x7000000) + ((v775_ptr[card]->geo_addr & 0x1F) << 27) ;
  }

  return(1 + ncV775) * 4 ;;
}


void V775_SetFileThresholds (int card)
{
  // Read file "thresholds.v775"
  // and Set the threshold value [val] for the
  // n_th channel
  //--------------------------------------

  FILE *fp;
  int  i,ival;
  char txt[100];

  // ----- Open the thresholds file -----

  sprintf(txt,"./caen/thresh_v775_%d.dat",card);
  if ((fp=fopen(txt,"r")) != NULL) 
  {
//    printf("\nFound file %s -> Read/Set ...", txt) ;
 
    sprintf(c_line,"Found file %s -> Read/Set ...", txt);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

    // ----- Get/Set the values -----
    while(fgets(txt, 50, fp) != NULL) 
    {
      if (strchr("!@#$%*",txt[0]) != NULL || strlen(txt) < 2) continue ;
      sscanf(txt, "%d %d ", &i, &ival) ;
      V775_SetThreshold(card, i, ival) ;
    }

    fclose(fp);
//    printf("....Ok! done\n") ;
  } 
  else
//    printf("\n*** file %s NOT found --> No Action! ***\n", txt) ;
  {
    sprintf(c_line,"file %s NOT found --> No Action!", txt);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
  }

  return ;
}


int V775_CheckDreadyStatus (int card)
{
  //  this function checks Status Register 1
  //  to see if the DREADY bit (#0) is set or not
  //--------------------------------------------

  int dready;

  dready = v775_ptr[card]->status_reg_1 & 0x1;
  return dready ;
}


void V775_ClearData (int card)
{
  //  this function clears data, read & write pointers,
  //  event counter and QAC sections...
  //  by toggling bit 2 of register 2
  //--------------------------------------------

  v775_ptr[card]->bit_set_2 = 0x4;
  v775_ptr[card]->bit_clear_2 = 0x4;

  return ;
}


int V775_CheckBufferStatus (int card)
{
  //  this function checks Status Register 2
  //  to see if the output buffer contains data
  //--------------------------------------------

  int l_val,
      buffstat;

  l_val = v775_ptr[card]->status_reg_2 ;
  if (l_val & 0x2)        /* buffer empty */  
    buffstat=0 ;
  else 
  {
    if (l_val & 0x4)      /* buffer full */
      buffstat=2 ;
    else 
      buffstat=1 ;        /* something between empty and full */
  }
 
  return buffstat ;
}


void V775_SetFullScale (int card, int n)
{
  // set the TDC full scale range
  // n=30: range=1200ns, n=255: range=140ns
  //----------------------------------------

  if ( n>=30 && n<=255 ) {
    v775_ptr[card]->full_scale_range = n;
  }

  return ;
}


void V775_OV_SuppressionOn (int card)
{
  //  this function turns overflow suppression ON
  //---------------------------------------------

  v775_ptr[card]->bit_clear_2 = BIT03;  /* clear Bit 3 */

  return ;
}


void V775_OV_SuppressionOff (int card)
{
  //  this function turns overflow suppression OFF
  //----------------------------------------------

  v775_ptr[card]->bit_set_2 = BIT03;    /* set Bit 3 */

  return ;
}


void V775_Nvalid_SuppressionOn (int card)
{
  //  this function turns nonvalid data suppression ON
  //--------------------------------------------------

  v775_ptr[card]->bit_clear_2 = BIT05;  /* clear Bit 5 */

  return ;
}


void V775_Nvalid_SuppressionOff (int card)
{
  //  this function turns nonvalid data suppression OFF
  //---------------------------------------------------

  v775_ptr[card]->bit_set_2 = BIT05;  /* set Bit 5 */

  return ;
}


void V775_Set_Com_Start (int card)
{
  //  this function sets common start mode
  //----------------------------------------------

  v775_ptr[card]->bit_clear_2 = BIT10;    /* clear Bit 10 */

  return ;
}


void V775_Set_Com_Stop (int card)
{
  //  this function sets common stop mode
  //----------------------------------------------

  v775_ptr[card]->bit_set_2 = BIT10;    /* set Bit 10 */

  return ;
}


void V775_SlidScaleOff (int card, short slide_const)
{
  //  this function turns "sliding scale" OFF
  //  slide_const is set in a register -> manual 4.36
  //-------------------------------------------------

  v775_ptr[card]->slide_const=slide_const;
  v775_ptr[card]->bit_clear_2 = 0x80;    /* clear Bit 7 */

  return ;
}


/* EOF */
