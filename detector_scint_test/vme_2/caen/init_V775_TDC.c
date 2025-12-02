/******************************************************************/
/* init_V775_TDC.c                                                */
/******************************************************************/

{
//    printf("\n");
//    printf("Init CAEN V775 TDC #%d\n",card);

    sprintf(c_line,"initialize CAEN V775 TDC, card #%d",card);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

/*
    printf("Address '        output_buffer0: 0x%x\n",output_buffer[0]);
    printf("Address '        output_buffer%d: 0x%x\n",card,output_buffer[card]);
    printf("Address 'firmware_revision Reg.: 0x%x\n",&(v775_ptr[card]->firmware_revision));
    printf("Address '        bit_set_1 Reg.: 0x%x\n",&(v775_ptr[card]->bit_set_1));
    printf("Address '        mcst_ctrl Reg.: 0x%x\n",&(v775_ptr[card]->mcst_ctrl));
    printf("Address '       event_trig Reg.: 0x%x\n",&(v775_ptr[card]->event_trig_reg));
    printf("Address '        bit_set_2 Reg.: 0x%x\n",&(v775_ptr[card]->bit_set_2));
    printf("Address '      bit_clear_2 Reg.: 0x%x\n",&(v775_ptr[card]->bit_clear_2));
    printf("Address '      r_test_addr Reg.: 0x%x\n",&(v775_ptr[card]->r_test_addr));
    printf("Address '    thresholds[0] Reg.: 0x%x\n",&(v775_ptr[card]->thresholds[0]));
*/

    V775_SoftReset(card);
    V775_StandardSetup(card);         /* ZeroSuppr ON, SlidScale ON */

//    V775_SlidScaleOff(card,2);        /* SS const=2, -> manual 4.36 */

    V775_StepThresholdOff(card);      /* thresh times 16 */
//    V775_StepThresholdOn(card);       /* thresh times 2 */

    V775_Set_Com_Start(card);
//    V775_Set_Com_Stop(card);

//    V775_OV_SuppressionOff(card);
    V775_OV_SuppressionOn(card);

//    V775_ZeroSuppressionOff(card);
    V775_ZeroSuppressionOn(card);

//    V775_Nvalid_SuppressionOff(card);
    V775_Nvalid_SuppressionOn(card);

    V775_SetFullScale(card,30);       // 30: full range=1200ns
    V775_EnableAllChannels(card);

//    V775_SetFileThresholds(card) ;
    V775_ResetThresholds(card) ;
    V775_DisplayStoredThresholds(card); 
}

/* EOF */




