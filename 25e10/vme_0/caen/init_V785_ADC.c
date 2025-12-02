/******************************************************************/
/* init_V785_ADC.c                                                */
/* HS 22-02-07                                                    */
/******************************************************************/

{
//    printf("\n");
//    printf("Init CAEN V785 ADC #%d\n",card);

    sprintf(c_line,"initialize CAEN V785 ADC, card #%d",card);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);


#ifdef DEBUG
    printf("Address '        output_buffer0: 0x%x\n",output_buffer[0]);
    printf("Address '        output_buffer%d: 0x%x\n",card,output_buffer[card]);
    printf("Address 'firmware_revision Reg.: 0x%x\n",&(v785_ptr[card]->firmware_revision));
    printf("Address '        bit_set_1 Reg.: 0x%x\n",&(v785_ptr[card]->bit_set_1));
    printf("Address '        mcst_ctrl Reg.: 0x%x\n",&(v785_ptr[card]->mcst_ctrl));
    printf("Address '       event_trig Reg.: 0x%x\n",&(v785_ptr[card]->event_trig_reg));
    printf("Address '        bit_set_2 Reg.: 0x%x\n",&(v785_ptr[card]->bit_set_2));
    printf("Address '      bit_clear_2 Reg.: 0x%x\n",&(v785_ptr[card]->bit_clear_2));
    printf("Address '      r_test_addr Reg.: 0x%x\n",&(v785_ptr[card]->r_test_addr));
    printf("Address '    thresholds[0] Reg.: 0x%x\n",&(v785_ptr[card]->thresholds[0]));
#endif

    V785_SoftReset(card);
    V785_StandardSetup(card);         /* ZeroSuppr ON, SlidScale ON */

//    V785_SlidScaleOff(card,2);        /* SS const=2, -> manual 4.36 */ 

//    V785_StepThresholdOff(card);      /* thresh times 16 */
    V785_StepThresholdOn(card);      /* thresh times 2 */

//    V785_ZeroSuppressionOff(card);
    V785_ZeroSuppressionOn(card);

//    V785_OverflowSuppressionOff(card);
    V785_OverflowSuppressionOn(card);

    V785_EnableAllChannels(card);
//    V785_DisableChannels(card,0xFFFF0000);  // disable upper 16 channels

    V785_SetFileThresholds(card) ;   /* thresholds from file */
//    V785_ResetThresholds(card) ;     /* thresholds = 0 */

    V785_DisplayStoredThresholds(card); 
}

/* EOF */
