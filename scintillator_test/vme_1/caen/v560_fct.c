/************************************************************************/
/* v560_fct.c  functions for CAEN V560 Scaler                    		*/
/* AG	29-09-17									                    */
/*   																	*/
/************************************************************************/

void V560_Reset (int card)
{
  v560_ptr[card]->scale_clear = 0x1;
  v560_ptr[card]->vme_veto_res = 0x1;
}

void V560_Clear (int card)
{
  v560_ptr[card]->scale_clear = 0x1;
}

/* EOF */
