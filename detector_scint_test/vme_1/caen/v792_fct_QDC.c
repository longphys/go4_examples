/*************************************************************************/
/* v792_fct.c  functions for CAEN V792 QDC                               */
/*                                                                       */
/* HS 14-03-07                                                           */
/*************************************************************************/

void V792_SoftReset (int card)
{
  v785_ptr[card]->geo_addr = card;
  v792_ptr[card]->bit_set_1 = 0x80;    // set and clear bit 7
  v792_ptr[card]->bit_clear_1 = 0x80;
}


void V792_StandardSetup (int card)
{
  //  Initialize the V792 QDC for standard list mode operation
  //   and clear data & pointers...

  v792_ptr[card]->bit_set_2 = 0x4;     /* set and clear bit 2 */
  v792_ptr[card]->bit_clear_2 = 0x4;

  // clear the event counter:
  v792_ptr[card]->event_counter_reset = 1;

  // turn OFF the following non-reserved bits:
  // (see v792 manual for details!)
  // (bit 13,12,6,5,4,3,1,0)

  v792_ptr[card]->bit_clear_2 = 0x307b;   /* 0011 0000 0111 1011 */ 

  // ----- turn on relevant bits of BIT SET 2 register
  // (see v792 manual for details!)
  // (bit 14,11,8,7)

  v792_ptr[card]->bit_set_2 = 0x4980;     /* 0100 1001 1000 0000 */
  
  return ;
}


void V792_StepThresholdOn (int card)
{
  //  this function turns "step threshold" ON
  //  => chn suppressed if ADC value < threshold * 2
  //--------------------------------------------

  v792_ptr[card]->bit_set_2 = 0x100;  /* set Bit 8 (wrong in manual!) */

  return ;
}

void V792_StepThresholdOff (int card)
{
  //  this function turns "step threshold" OFF
  //  => chn suppressed if ADC value < threshold * 16
  //--------------------------------------------

  v792_ptr[card]->bit_clear_2 = 0x100;  /* clear Bit 8 (wrong in manual!) */

  return ;
}
 

void V792_ZeroSuppressionOn (int card)
{
  //  this function turns zero suppression ON
  //--------------------------------------------

  v792_ptr[card]->bit_clear_2 = 0x10;  /* clear Bit 4 */

  return ;
}


void V792_ZeroSuppressionOff (int card)
{
  //  this function turns zero suppression OFF
  //--------------------------------------------

  v792_ptr[card]->bit_set_2 = 0x10;    /* set Bit 4 */

  return ;
}

 
void V792_EnableAllChannels (int card)
{
  // ----- enable all channels
  //--------------------------------------------

  int i;

  for (i=0; i<32; i++)
    v792_ptr[card]->thresholds[i] = 
             v792_ptr[card]->thresholds[i] & 0xfeff;   /* clear kill bit(8) */

  return ;
}


void V792_DisableChannels (int card, unsigned long mask)
{
  // ----- disable chosen channels
  //--------------------------------------------

  int i;
  unsigned long ch_bit=1;

  for (i=0; i<32; i++)
  {
    if (ch_bit & mask)
    {
      v792_ptr[card]->thresholds[i] =
             v792_ptr[card]->thresholds[i] | 0x0100;   /* set kill bit(8) */
    }
    ch_bit=2*ch_bit;
  }

  return ;
}


void V792_SetThreshold (int card, int n, int val)
{
  // Set the threshold value [val] for the
  // n_th channel
  //   !!! be careful not to overwrite the "kill" bit (8)!
  //--------------------------------------

  short l_val;

  if (n>= 0 && n < 32 && val <= 255) 
  {
    l_val = ((v792_ptr[card]->thresholds[n] >> 8) << 8) + val;
    v792_ptr[card]->thresholds[n] = l_val;
  }

  return ;
}

void V792_ResetThresholds (int card)
{
  //  Reset/Initialize the V792 thresholds
  //--------------------------------------------

  int i;

  for(i=0 ; i < 32 ; i++)
    V792_SetThreshold(card, i, 0) ;

  return;
}


void V792_DisplayStoredThresholds (int card)
{

  // Display thresholds stored in V785 
  //-------------------------------------

  int i;
  char dummy[10];

/*
  printf("\n Channel/Threshold/Kill-bit -> \n") ;
  for(i=0 ; i < 32; i++)
  printf(" %d/%d/%d ",i,v792_ptr[card]->thresholds[i] & 0xff,
                      (v792_ptr[card]->thresholds[i] & 0x100)>>8) ;

  printf("\n");
  fflush(stdout);
*/

  F_ERROR(ERR__MSG_INFO,0,"Channel/Threshold/Kill-bit ->",l_pr_mask);
  sprintf(c_line," ");
  for(i=0;i<32;i++)
  {
    sprintf(dummy," %02d/%02d/%d ",i,v792_ptr[card]->thresholds[i] & 0xff,
                      (v792_ptr[card]->thresholds[i] & 0x100)>>8) ;
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


int V792_ReadOutputBuffer(int card, long **pl_dat)
{
  // Read the Output Buffer

  long i,temp,
       lwtype,
       ncV792;

  // read the first longword:
  temp = *(output_buffer[card]);

  // extract longword "type" (2=header,6=invalid data):
  lwtype = (temp & 0x7000000) >> 24 ;

  if (lwtype == 2) 
  {
    // extract number of data longwords:
    ncV792 = ( temp >> V792__OUTPUT_BUFFER_GEO_N_WORD_COUNT)
              & V792__OUTPUT_BUFFER_WORD_COUNT ;

    // pass on the header long word after reformatting it a bit:
    //  push the "number of converted chns" to the lowest 6 bits...
    *((*pl_dat)++) = (temp & 0xffff0000) + ncV792;

    // read and pass on the data in "original" format (long words):
    for(i=0 ; i < ncV792; i++)
      *((*pl_dat)++) = *(output_buffer[card]);

    // read the EOB longword (GEO and "event counter" info):
    *((*pl_dat)++) = *(output_buffer[card]); 

    ncV792++ ;    // N_Channel + EventCounter-buffe
  } 
  else  // most likely no valid data (lwtype was 6) 
  {  
    // IF "no valid data" we need to reformat the header info a bit:
    //  we pass on the GEO address + the "not valid datum" identifier
    //  and also return "number of channels" as zero

    ncV792 = 0;
    *((*pl_dat)++) = (temp & 0x7000000) + ((v792_ptr[card]->geo_addr & 0x1F) << 27) ;
  }

  return(1 + ncV792) * 4 ;;
}

void V792_SetFileThresholds (int card)
{
  // Read file "thresh_v792_n.dat"
  // and Set the treshold value [val] for the
  // n_th channel
  //--------------------------------------

  FILE *fp;
  int  i,ival;
  char txt[50];

  // ----- Open the thresholds file -----

//  sprintf(txt,"./caen/thresh_v792_%d.dat",card);
  sprintf(txt,"/frs/usr/rising/mbsrun/july_2008/vme_user_hs/caen/thresh_v792_%d.dat",card);
  if ((fp=fopen(txt,"r")) != NULL) 
  {
//    printf("\nFound file %s -> Read/Set ........", txt) ;

    sprintf(c_line,"Found file %s -> Read/Set ...", txt);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

    // ----- Get/Set the values -----
    while(fgets(txt, 50, fp) != NULL) 
    {
      if (strchr("!@#$%*",txt[0]) != NULL || strlen(txt) < 2) continue ;
      sscanf(txt, "%d %d ", &i, &ival) ;
      V792_SetThreshold(card, i, ival) ;
    }

    fclose(fp) ;
//    printf("....Ok! done\n") ;
  } 
  else
//    printf("\n*** file %s NOT-Found --> No-Action ***\n", txt) ;
  {
    sprintf(c_line,"file %s NOT found --> No Action!", txt);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
  }

  return ;
}


int V792_CheckDreadyStatus (int card)
{
  //  this function checks Status Register 1
  //  to see if the DREADY bit (#0) is set or not
  int dready;

  dready = v792_ptr[card]->status_reg_1 & 0x1;
  return dready ;
}


void V792_QDC_ClearData (int card)
{
  //  this function clears data, read & write pointers,
  //  event counter and QAC sections...
  //  by toggling bit 2 of register 2

  v792_ptr[card]->bit_set_2 = 0x4;
  v792_ptr[card]->bit_clear_2 = 0x4;

  return ;
}


int V792_QDC_CheckBufferStatus (int card)
{
  //  this function checks Status Register 2
  //  to see if the output buffer contains data
  //  return val: 0: buffer empty, 2: buffer full, 1: not empty - not full

  int l_val,
      buffstat;

  l_val = v792_ptr[card]->status_reg_2 ;
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


void V792_OverflowSuppressionOn (int card)
{
  //  this function turns overflow suppression ON
  //----------------------------------------------

  v792_ptr[card]->bit_clear_2 = 0x8;  /* clear Bit 3 */

  return ;
}


void V792_OverflowSuppressionOff (int card)
{
  //  this function turns overflow suppression OFF
  //----------------------------------------------

  v792_ptr[card]->bit_set_2 = 0x8;    /* set Bit 3 */

  return ;


}/* EOF */
