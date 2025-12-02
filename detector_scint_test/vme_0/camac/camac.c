typedef struct
{  
   long volatile *data[16];
   short k_read[16];
   long adr[16];
   long crate;
   long geo;
   long top;
   long bot;
   long ndata;
   long offset;
} camac;

#define CNAFLOC(c,n,a,f,offset)                                    \
   (long*)(0x0*c + 0x800*n + 0x40*f + 0x4*a + (long)offset)

void Camac_Print(camac *pCamac);
void Camac_Reset(camac *pCamac);
void Camac_SetHead(camac *pCamac);
int Camac_SetOneCh(camac *pCamac, short crate, short geo, short ch, long *offset);
void Camac_SetAllCh(camac *pCamac, short crate, short geo, long *offset); 

static int ntmp; 

void Camac_Print(camac *pCamac)
{
	//===============================================================
	//== Print geo address
	//===============================================================

	long x0;
	x0 = pCamac->top;
//	printf("GEO: %5d %5d %5d\n" ,pCamac->geo, (x0>>27)&0x1f,(x0>>24)&0x7);
	printf("GEO: %5d %5d\n" ,pCamac->geo, pCamac->crate);
}

int Camac_GetOutputPointer1(camac *pCamac, long **pl_dat)
{
   //====================================================================
   //== Read camac one 32 bit word
   //====================================================================

   *((*pl_dat)++) = pCamac->top;
   *((*pl_dat)++) = (*pCamac->data[0] & 0xffff);
   *((*pl_dat)++) = (*pCamac->data[1] & 0xffff); 
   *((*pl_dat)++) = pCamac->bot;

   return 16;
} //---------------------------------------------------------------------


void Camac_Reset(camac *pCamac)
{
   //====================================================================
   //== Reset crate and geo numbers
   //====================================================================
   
   int i;
   pCamac->crate = 0;
   pCamac->geo   = 0;
   pCamac->ndata = 0;

   for(i = 0; i < 16; ++i)
   {
      pCamac->k_read[i] = 0;
   }
} //----------------------------------------------------------------------

void Camac_SetHead(camac *pCamac)
{
   //====================================================================
   //== Set top and bottom
   //====================================================================

   int i;
   if(pCamac->k_read[15] == 0)
   {
      pCamac->k_read[15] = 1;
      pCamac->data[15] = CNAFLOC(0,pCamac->geo,15,2,pCamac->offset);
   }

   pCamac->top = (pCamac->geo << 27) & 0xf8000000;
   pCamac->top += (1 << 25);
   pCamac->top += (pCamac->crate << 16);
   pCamac->top += (pCamac->ndata << 8);

   pCamac->bot = (pCamac->geo << 27) &0xf8000000;
   pCamac->bot += (1 << 26);

   pCamac->ndata = 0;
   for(i = 0; i < 16; ++i)
   {
      pCamac->adr[i] =  (pCamac->geo << 27) & 0xf8000000;
      pCamac->adr[i] += (i << 16);
      if(pCamac->k_read[i]) pCamac->ndata++;
   }


} //----------------------------------------------------------------------

int Camac_SetOneCh(camac *pCamac, short crate, short geo, short ch, long *offset)
{
	//======================================================================
	//== Set address of one channel
	//======================================================================

	if(!pCamac->crate) pCamac->crate = crate;
	if(!pCamac->geo)   pCamac->geo   = geo;
   pCamac->offset = offset[crate];
   pCamac->data[ch] = CNAFLOC(crate,geo,ch,2,offset[crate]);
   pCamac->k_read[ch] = 1;
   return 0;
} //----------------------------------------------------------------------



