//=====================================================================
//== init_mtdc32.c
//==  14-10-15
//=====================================================================
{
  long i;  //????
//=====================================================================

//=====================================================================

  sprintf(c_line,"initialize MESYTEC MTDC32, card #%d",card);
  F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

//=====================================================================

#ifdef DEBUG
  printf("Debug section for MESYTEC MTDC32, card #%d\n", card);
  printf("Addr soft_reset: 0x%08x\n",&mtdc32_ptr[card]->soft_reset);
  printf("Addr multievent: 0x%08x\n",&mtdc32_ptr[card]->multievent);
  printf("Addr marking_type: 0x%08x\n",&mtdc32_ptr[card]->marking_type);
  printf("Addr bank_op: 0x%08x\n",&mtdc32_ptr[card]->bank_op);
  printf("Addr output_format: 0x%08x\n",&mtdc32_ptr[card]->output_format);
  printf("Addr data_len_format: 0x%08x\n",&mtdc32_ptr[card]->data_len_format);
  printf("Addr negative_edge: 0x%08x\n",&mtdc32_ptr[card]->negative_edge);
  printf("Addr trig_select: 0x%08x\n",&mtdc32_ptr[card]->trig_select);
  printf("Addr start_acq: 0x%08x\n",&mtdc32_ptr[card]->start_acq);
  printf("Addr tdc_resolution: 0x%08x\n",&mtdc32_ptr[card]->tdc_resolution);
  printf("Addr readout_reset: 0x%08x\n",&mtdc32_ptr[card]->readout_reset);
  printf("Addr fifo_reset: 0x%08x\n",&mtdc32_ptr[card]->fifo_reset);
  printf("Addr pulser_status: 0x%08x\n",&mtdc32_ptr[card]->pulser_status);
  printf("Addr buffer_data_len: 0x%08x\n",&mtdc32_ptr[card]->buffer_data_len);
  printf("Addr data_ready: 0x%08x\n",&mtdc32_ptr[card]->data_ready);
  printf("Addr firmware revision: 0x%04x\n",&mtdc32_ptr[card]->firmware_rev);
  printf("Firmware revision: 0x%04x\n",mtdc32_ptr[card]->firmware_rev);
#endif
  usleep(100000);
  printf("soft_reset\n");
  mtdc32_ptr[card]->soft_reset=1;
  usleep(100000);
//  printf("multievent\n");
//  mtdc32_ptr[card]->multievent=0;
  usleep(100000);
  printf("module_id\n");
  mtdc32_ptr[card]->module_id = card;     // 
  usleep(100000);
//  printf("marking_type\n");
//  mtdc32_ptr[card]->marking_type=0; // [0: event counter 1: timestamp]
//  printf("bank_op\n");
//  mtdc32_ptr[card]->bank_op=0;
//  printf("output_format\n");
//  mtdc32_ptr[card]->output_format=0;
//  printf("data_len_format\n");
//  mtdc32_ptr[card]->data_len_format=2; //32 bit data
//  printf("negative_edge\n"); 
//  mtdc32_ptr[card]->negative_edge=1; //is it right!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  printf("trig_select\n");
//  mtdc32_ptr[card]->trig_select=0;
//  printf("start_acq\n");
//  mtdc32_ptr[card]->start_acq=0;
  printf("tdc_resolution\n");
  mtdc32_ptr[card]->tdc_resolution=7;
// 9 -> 500ps
// 8 -> 250ps
// 7 -> 125ps
// 6 -> 1/16 ns = 62.5 ps 
// 5 -> 1/32 ns ~ 31 ps
// 4 -> 1/64 ns ~ 15 ps
// 3 -> 1/128 ns ~8 ps
// 2 -> 1/256 ns ~4ps
  usleep(100000);
  printf("readout_reset\n");
  mtdc32_ptr[card]->readout_reset=1;
  usleep(100000);
  printf("start_acq\n");
  mtdc32_ptr[card]->start_acq=1;
  usleep(100000);
  printf("fifo_reset\n");
  mtdc32_ptr[card]->fifo_reset=1;
  usleep(100000);

}

// EOF

