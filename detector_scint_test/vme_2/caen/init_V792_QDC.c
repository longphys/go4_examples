/******************************************************************/
/* init_V792_QDC.c                                                */
/******************************************************************/

{
//    printf("\n");
//    printf("Init CAEN V792 QDC #%d\n",card);

    sprintf(c_line,"initialize CAEN V792 QDC, card #%d",card);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

/*
    printf("Address '        output_buffer0: 0x%x\n",output_buffer[0]);
    printf("Address '        output_buffer%d: 0x%x\n",card,output_buffer[card]);
    printf("Address 'firmware_revision Reg.: 0x%x\n",&(v792_ptr[card]->firmware_revision));
    printf("Address '        bit_set_1 Reg.: 0x%x\n",&(v792_ptr[card]->bit_set_1));
    printf("Address '        mcst_ctrl Reg.: 0x%x\n",&(v792_ptr[card]->mcst_ctrl));
    printf("Address '       event_trig Reg.: 0x%x\n",&(v792_ptr[card]->event_trig_reg));
    printf("Address '        bit_set_2 Reg.: 0x%x\n",&(v792_ptr[card]->bit_set_2));
    printf("Address '      bit_clear_2 Reg.: 0x%x\n",&(v792_ptr[card]->bit_clear_2));
    printf("Address '      r_test_addr Reg.: 0x%x\n",&(v792_ptr[card]->r_test_addr));
    printf("Address '    thresholds[0] Reg.: 0x%x\n",&(v792_ptr[card]->thresholds[0]));
*/

    V792_SoftReset(card);
    V792_StandardSetup(card);         /* includes ZeroSuppr ON */

//    V792_StepThresholdOff(card);      /* thresh times 16 */
    V792_StepThresholdOn(card);       /* thresh times 2 */

//    V792_Set_FClrWin(card,7.0);    // NEW 30-03-07

//    V792_ZeroSuppressionOff(card);
    V792_ZeroSuppressionOn(card);

//    V792_OverflowSuppressionOff(card);
    V792_OverflowSuppressionOn(card);

    V792_EnableAllChannels(card);
//    V792_DisableChannels(card,0xFFFF0000);  // disable upper 16 channels

//    V792_SetFileThresholds(card) ;
    V792_ResetThresholds(card) ;
    V792_DisplayStoredThresholds(card); 
}

/* EOF */
