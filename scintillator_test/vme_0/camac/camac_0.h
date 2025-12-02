/****************************************************************************/
/* CAMAC								                                    */
/*                                                                          */
/****************************************************************************/


struct mwpc_reg {
   long volatile *data[16];
   short k_read[16];
   long adr[16];
   long crate;
   long geo;
   long top;
   long bot;
   long ndata;
   long offset;
};