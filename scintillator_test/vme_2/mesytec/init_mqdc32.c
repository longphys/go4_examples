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
  printf("##########################################\n");
  printf("Debug section for MESYTEC MQDC32, card #%d\n", card);
  printf("Addr  thresh[ 0]:     0x%08x\n",mqdc32_thresh[0][card]);
  printf("Addr  thresh[31]:     0x%08x\n",mqdc32_thresh[31][card]);  

  printf("Addr soft_reset:      0x%08x\n",&mqdc32_ptr[card]->soft_reset);
  printf("Addr  start_acq:      0x%08x\n",&mqdc32_ptr[card]->start_acq);
  printf("Addr multievent:      0x%08x\n",&mqdc32_ptr[card]->multievent);
  printf("Addr pulser_status:   0x%08x\n",&mqdc32_ptr[card]->pulser_status);
  printf("Addr      time2:      0x%08x\n",&mqdc32_ptr[card]->time2);
  printf("Addr buffer_data_len: 0x%08x\n",&mqdc32_ptr[card]->buffer_data_len);
  printf("Addr data_ready:      0x%08x\n",&mqdc32_ptr[card]->data_ready);
  printf("Firmware revision:    0x%04x\n", &mqdc32_ptr[card]->firmware_rev);
  //printf("Firmware revision: 0x%04x\n",mtdc32_ptr[card]->firmware_rev);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
#endif

  usleep(100000);
  mqdc32_ptr[card]->soft_reset = 1;
#ifdef DEBUG
  printf("soft_reset is set to %x\n", &mqdc32_ptr[card]->soft_reset);
#endif /*DEBUG*/
  usleep(100000);
  mqdc32_ptr[card]->start_acq = 0;
#ifdef DEBUG
  printf("start_acq is set to %x\n", &mqdc32_ptr[card]->start_acq);
#endif /*DEBUG*/
  usleep(100000);
  mqdc32_ptr[card]->multievent = 1;
#ifdef DEBUG
  printf("multievent is set to %x\n", &mqdc32_ptr[card]->multievent);
#endif /*DEBUG*/
  //usleep(100000);
  //mqdc32_ptr[card]->marking_type = 0; // [0: event counter 1: timestamp]
  usleep(100000);
  mqdc32_ptr[card]->module_id = card;     //
#ifdef DEBUG
  printf("module_id is set to %x\n", &mqdc32_ptr[card]->module_id);
#endif /*DEBUG*/
  usleep(100000);                         
  mqdc32_ptr[card]->adc_resolution = 0; //0 4K, highes resolution, cvt 100ns
#ifdef DEBUG
  printf("adc_resolution is set to %x\n", &mqdc32_ptr[card]->adc_resolution);
#endif /*DEBUG*/
  //usleep(100000);
  //mqdc32_ptr[card]->data_len_format = 2; //32 bit data
//
  mqdc32_ptr[card]->nim_fc_res = 2; // exp trigg on
#ifdef DEBUG
  printf("nim_fc_res is set to %x\n", &mqdc32_ptr[card]->nim_fc_res);
#endif /*DEBUG*/
  mqdc32_ptr[card]->exp_trig_delay0 = 400;  // exp trigger delay in ns
#ifdef DEBUG
  printf("exp_trig_delay0 is set to %x\n", &mqdc32_ptr[card]->exp_trig_delay0);
#endif /*DEBUG*/
//  mqdc32_ptr[card]->exp_trig_delay1 = 200;  
//=====================================================================
//=== set thresholds

#ifdef DEBUG
  printf("Call MQDC32_ResetThresholds(%d)...\n", card);
#endif /*DEBUG*/
  MQDC32_ResetThresholds(card);
#ifdef DEBUG
  printf("MQDC32_ResetThresholds(%d) finished successfully\n", card);
#endif /*DEBUG*/
#ifdef DEBUG
  printf("Call MQDC32_SetFileThresholds(%d)...\n", card);
#endif /*DEBUG*/
  MQDC32_SetFileThresholds(card);
#ifdef DEBUG
  printf("MQDC32_SetFileThresholds(%d) finished successfully\n", card);
#endif /*DEBUG*/
#ifdef DEBUG
  printf("Call MQDC32_DisplayStoredThresholds(%d)...\n", card);
#endif /*DEBUG*/
  MQDC32_DisplayStoredThresholds(card);
#ifdef DEBUG
  printf("MQDC32_DisplayStoredThresholds(%d) finished successfully\n", card);
#endif /*DEBUG*/

//=====================================================================

  usleep(100000);
  mqdc32_ptr[card]->fifo_reset=1;   // ???? 
#ifdef DEBUG
  printf("fifo_reset is set to %x\n", &mqdc32_ptr[card]->fifo_reset);
#endif /*DEBUG*/
  usleep(100000);
  mqdc32_ptr[card]->start_acq=1;
#ifdef DEBUG
  printf("start_acq is set to %x\n", &mqdc32_ptr[card]->start_acq);
#endif /*DEBUG*/
  usleep(100000);
  mqdc32_ptr[card]->readout_reset=1;
#ifdef DEBUG
  printf("readout_reset is set to %x\n", &mqdc32_ptr[card]->readout_reset);
  printf("##########################################\n");
#endif /*DEBUG*/
  usleep(100000);
}

// EOF

