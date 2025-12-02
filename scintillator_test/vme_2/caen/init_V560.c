/******************************************************************/
/* init_V7560.c                                                   */
/* AG 29-09-17                                                    */
/******************************************************************/

{
#ifdef DEBUG
    printf("Address '        counter0: 0x%x\n",&(v560_ptr[card]->counter[0]));
    printf("Address '        counter1: 0x%x\n",&(v560_ptr[card]->counter[1]));
    printf("Address 'scale_clear: 0x%x\n",&(v560_ptr[card]->scale_clear));
#endif

    sprintf(c_line,"initialize CAEN V560 Scaler, card #%d",card);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

    V560_Reset(card); 
}

/* EOF */
