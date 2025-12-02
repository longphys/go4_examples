//=====================================================================
//== init_mqdc32.c
//==  02-07-15
//=====================================================================
{
  long i;  //????
//=====================================================================

//=====================================================================

  sprintf(c_line,"initialize MESYTEC MQDC32, card #%d",card);
  F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

//=====================================================================

#ifdef DEBUG
  printf("Debug section for MESYTEC MQDC32, card #%d\n", card);
  printf("Addr  thresh[ 0]: 0x%08x\n",mqdc32_thresh[0][card]);
  printf("Addr  thresh[31]: 0x%08x\n",mqdc32_thresh[31][card]);  

  printf("Addr soft_reset: 0x%08x\n",&mqdc32_ptr[card]->soft_reset);
  printf("Addr  start_acq: 0x%08x\n",&mqdc32_ptr[card]->start_acq);
  printf("Addr multievent: 0x%08x\n",&mqdc32_ptr[card]->multievent);
  printf("Addr pulser_status: 0x%08x\n",&mqdc32_ptr[card]->pulser_status);
  printf("Addr      time2: 0x%08x\n",&mqdc32_ptr[card]->time2);
  printf("Addr buffer_data_len: 0x%08x\n",&mqdc32_ptr[card]->buffer_data_len);
  printf("Addr data_ready: 0x%08x\n",&mqdc32_ptr[card]->data_ready);
  printf("Firmware revision: 0x%04x\n",mtdc32_ptr[card]->firmware_rev);
#endif


  usleep(100000);
  mqdc32_ptr[card]->soft_reset = 1;
  usleep(100000);
  mqdc32_ptr[card]->start_acq = 0;
 // usleep(100000);
  mqdc32_ptr[card]->multievent = 1;
  //usleep(100000);
  //mqdc32_ptr[card]->marking_type = 0; // [0: event counter 1: timestamp]
  usleep(100000);
  mqdc32_ptr[card]->module_id = card;     // 
  usleep(100000);                         
  mqdc32_ptr[card]->adc_resolution = 0; //0 4K, highes resolution, cvt 100ns  
  //usleep(100000);
  //mqdc32_ptr[card]->data_len_format = 2; //32 bit data
//
  mqdc32_ptr[card]->nim_fc_res = 2; // exp trigg on  
  mqdc32_ptr[card]->exp_trig_delay0 = 400;  // exp trigger delay in ns
//  mqdc32_ptr[card]->exp_trig_delay1 = 200;  
//=====================================================================
//=== set thresholds

  MQDC32_ResetThresholds(card);
  MQDC32_SetFileThresholds(card);
  MQDC32_DisplayStoredThresholds(card);

//=====================================================================

  usleep(100000);
  mqdc32_ptr[card]->fifo_reset=1;   // ???? 
  usleep(100000);
  mqdc32_ptr[card]->start_acq=1;
  usleep(100000);
  mqdc32_ptr[card]->readout_reset=1;
  usleep(100000);
}

// EOF

