//===========================================================
//==
//== mqdc32_fct_ADC.c  functions for Mesytec MQDC32 QDC                    
//==                                                                       
//===========================================================

void MQDC32_ResetThresholds (int card) {
	//===========================================================
  //==  Reset/Initialize the MQDC32 thresholds
	//===========================================================

  int i;

  for(i=0; i<32; i++)
    *mqdc32_thresh[i][card] = 0;

  return;
}


void MQDC32_DisplayStoredThresholds (int card) {
	//===========================================================
  //== Display thresholds stored in MQDC32 
	//===========================================================

  int i;
  char dummy[10];

  F_ERROR(ERR__MSG_INFO,0,"Channel/Threshold ->",l_pr_mask);
  sprintf(c_line," ");
  for(i=0;i<32;i++){
    sprintf(dummy," %02d/%02d ",i,*mqdc32_thresh[i][card] & 0x1FFF);
    strcat(c_line,dummy);
    if (strlen(c_line) >= 55){
      F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
      sprintf(c_line," ");
    }
  }

  strcat(c_line,".");
  F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

  return ;
}


void MQDC32_SetThreshold (int card, int ch, int val) {
	//===========================================================  
	// Set the threshold value [val] for the
  // channel ch
	//===========================================================

  short l_val; //?????

  if (ch>=0 && ch<32){
    *mqdc32_thresh[ch][card] = val & 0x1FFF;   // 13 bit
  }

  return ;
}


void MQDC32_SetFileThresholds (int card) {
  //===========================================================
  //== Read file "thresh_mqdc32_%d.dat"
  //== and Set the threshold value [val] for the
  //== n_th channel
	//===========================================================

  FILE *fp;
  int  i,ival;
  char txt[100],
       txt2[30];

  //== Open the thresholds file 

  sprintf(txt,"./mesytec/vme_0/thresh_mqdc32_%d.dat",card);

//  strcpy(txt,HOME_PATH);                           // NEW 08-08-12
//  sprintf(txt2,"/mqdc32/thresh_mqdc32_%d.dat",card);
//  strcat(txt,txt2);

  if ((fp=fopen(txt,"r")) != NULL) {
//    printf("\nFound file %s -> Read/Set ........", txt) ;

    sprintf(c_line,"Found file %s -> Read/Set ...", txt);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);

    // ----- Get/Set the values -----
    while(fgets(txt,100,fp) != NULL) {
      if (strchr("!@#$%*",txt[0]) != NULL || strlen(txt) < 2) continue ;
      sscanf(txt, "%d %d ", &i, &ival) ;
      MQDC32_SetThreshold(card, i, ival) ;
    }

    fclose(fp) ;
//    printf("....Ok! done\n") ;
  } 
  else {
//    printf("\n*** file %s NOT-Found --> No-Action ***\n", txt) ;

    sprintf(c_line,"file %s NOT found --> No Action!", txt);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
  }

  return ;
}


void MQDC32_SetSlidScale (int card, char mode) {
  if (!mode)                       // OFF
    mqdc32_ptr[card]->slc_off=1;
  else
    mqdc32_ptr[card]->slc_off=0;
}
//===========================================================
//== EOF
