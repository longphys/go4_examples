//***********************************************************************
// init_madc32.c
//
// HS 29-10-10
//    16-11-10 new threshold functions
//    08-08-12 print info of ADC resolution and range
//
//***********************************************************************
{
  long i,
       res,
       range;
  char *str1[]={"2K","4K","4Khires","8K","8Khires"};
  char *str2[]={"4V","10V","8V"};

 
 //----------------------------------------------------------

  sprintf(c_line,"initialize MESYTEC MADC32, card #%d",card);
  F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

  //------------------------------------------


#ifdef DEBUG
  printf("Debug section for MESYTEC MADC32, card #%d\n", card);	
  printf("Addr  thresh[ 0]: 0x%08x\n",madc32_thresh[0][card]);
  printf("Addr  thresh[31]: 0x%08x\n",madc32_thresh[31][card]);  

  printf("Addr soft_reset: 0x%08x\n",&madc32_ptr[card]->soft_reset);
  printf("Addr  start_acq: 0x%08x\n",&madc32_ptr[card]->start_acq);
  printf("Addr multievent: 0x%08x\n",&madc32_ptr[card]->multievent);
  printf("Addr pulser_status: 0x%08x\n",&madc32_ptr[card]->pulser_status);
  printf("Addr      time2: 0x%08x\n",&madc32_ptr[card]->time2);
  printf("Addr buffer_data_len: 0x%08x\n",&madc32_ptr[card]->buffer_data_len);
  printf("Addr data_ready: 0x%08x\n",&madc32_ptr[card]->data_ready);
  printf("Firmware revision: 0x%04x\n",mtdc32_ptr[card]->firmware_rev);
#endif


  usleep(10000);
  madc32_ptr[card]->soft_reset=1;

//  printf("Slid Scale: 0x%08x\n",madc32_ptr[card]->slc_off);
  usleep(10000);
  madc32_ptr[card]->start_acq=0;
  usleep(10000);
  madc32_ptr[card]->multievent=0;
  usleep(10000);
  madc32_ptr[card]->fifo_reset=1;
  usleep(10000);
  //*** set module ID
  madc32_ptr[card]->module_id = card;     // 
  usleep(10000);
  //*** set 0x6038, trailer contains trigger counter or timestamp

  madc32_ptr[card]->marking_type=0;   // 0: event counter
//  madc32_ptr[card]->marking_type=1;  // 1: timestamp

  //*** set 0x6042, ADC resolution (2,4,8k)
  usleep(10000);
  res=3;                     // [0=2K,1=4K,2=4Khires,3=8K,4=8Khires]   
  madc32_ptr[card]->adc_resolution=res;  
  
  printm("MADC32: ADC resolution: %s\n",str1[res]);

  // set 0x6060, ADC input range (4,10,8V) 
  usleep(10000);
  range=1;                                 // [0=4V, 1=10V, 2=8V]
  madc32_ptr[card]->input_range = range;  

  printm("MADC32: input range: %s\n",str2[range]);

  //*** set sliding scale (default ON)

//  MADC32_SetSlidScale(card,OFF);

//  printf("Slid Scale: 0x%08x\n",madc32_ptr[card]->slc_off);

  //*** set output 'NIM busy' mode 
  // 0: nim_busy, 1: gate0 out, 2: gate1 out
  // 3: RCbus, 4: buffer full, 5: 
  usleep(10000);
  madc32_ptr[card]->nim_busy=0;  // nim busy (default)

  //*** set thresholds
  usleep(10000);
  madc32_ptr[card]->ignore_treshold = 0;
  usleep(10000);
  MADC32_ResetThresholds(card);
  usleep(10000);
  MADC32_SetFileThresholds(card);
  usleep(10000);
  MADC32_DisplayStoredThresholds(card);

  //--------------------

//  madc32_ptr[card]->fifo_reset=1;   // ???? 
  usleep(10000);
  madc32_ptr[card]->start_acq=1;
  usleep(10000);
  madc32_ptr[card]->readout_reset=1;
}

// EOF

