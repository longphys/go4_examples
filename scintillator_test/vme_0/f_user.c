//************************************************************************
// N.Kurz 25-Mar-1998                                                    
//                                                                       
// HS 02-09-10  mbs for caen readout with rio2/rio3/rio4                           
//    29-10-10  add mesytec madc32 readout (use caen vme mapping)
// AG 06-09-17  add mesytec mqdc32 and mtdc32 readout (use caen vme mapping)                                                                 
//************************************************************************

#include "stdio.h"
#include "s_veshe.h"
#include <smem.h>
#include <signal.h>
#include <error_mac.h>
#include <err_mask_def.h>
#include <errnum_def.h>
#include <math.h>

#include "/usr/include/ces/vmelib.h"   /* for find_controller() */
/*** also add '/lib/ces/libvme.a' in MAKEFILE line 'LIBS = ...' !!! ***/

//-----------------------------------------------------------------------------------------------------------
// GSI trigger card base: 		0x02000000  // TRIVA address is fixed in MBS
// GSI vulom card base:   		0x03000000  // if address bits 31 to 28 = 0 (rotary switch VN2 = 0), 
//						    // programm of the module can be changed through VME bus 
// other cards base adresses: 	0x04000000 and higher
//-----------------------------------------------------------------------------------------------------------

//#define DEBUG
#define CAEN         // use CAEN ADC,TDC
#define MESYTEC    //use MESYTEC MADC, MQDC, MTDC
#define CAMAC
#define NUMBER_OF_CARDS 24      // number of CAEN and MESYTEC modules in VME crate
#define CARDS_OFF 0x10000    // offset between two VME cards 

#define NO_ANNUAL 1  // Remove Sectors, Rings
/*****************************************************************************/
#ifdef RIO3
	#define CAEN_VME_NAME "CAEN_SEG"
	#define CAEN_VME_BASE      0x50000000
	#define VME_LEN  0x500000 //used only for RIO3 addressing 
#endif

#ifdef RIO4
	#define CAEN_VME_BASE      0xF0000000   // for direct mapping
#endif

#ifdef CAEN
	#include "./caen/caen_vme.h"
#endif

#ifdef MESYTEC
	#include "./mesytec/mesytec.h"
#endif

#ifdef CAMAC
	#include "./camac/camac.c"
#endif

#define round(x)  ((int) floor((double) (x)+0.5))

/*****************************************************************************/
// for CAMAC

#define CNAFLOC(c,n,a,f,offset) (long*)(0x0*c + 0x800*n + 0x40*f + 0x4*a + (long)offset)

/*****************************************************************************/

/*
   This macro performs 32bits alignment of subevent's length.
   All Motorola 68k based computers are big endians.
*/

#define align32() \
switch ((((unsigned char *) ps_veshe) - memory.p8) & 3L) \
{ \
  case 1: \
    *memory.p8++ = 0x65; \
  case 2: \
    *memory.p16++ = 0x4321; \
    break; \
  case 3: \
    *memory.p8++ = 0x21; \
}

/*****************************************************************************/

/* 
 * all pointer which are used for read/write operations in the functions
 * f_user_init and f_user_readout must be defined here as static variables
 */

static char     c_line[256];
static char     c_modnam[] = "f_user.c";
static long     l_pr_mask = MASK__PRTT;


static long volatile *pl_trig_vme_fct, 
                     *pl_trig_vme_cvt;
static long volatile *pGTBC;
static long volatile *pINHIBIT;
			 

/*****************************************************************************/

	#include "./caen/vtimer.h" //computer time
	static s_vt p_vt;

#if defined(CAEN) || defined(MESYTEC)
	static volatile long *caen_base;
	static volatile long *output_buffer[NUMBER_OF_CARDS];
 #endif

#ifdef CAEN
	static struct v7x5_reg *v785_ptr[NUMBER_OF_CARDS];   // ADC V785
	static struct v7x5_reg *v775_ptr[NUMBER_OF_CARDS];   // TDC V775
	static struct v560_reg *v560_ptr[NUMBER_OF_CARDS];   // Scaler V560

	#include "./caen/v785_fct_ADC.c"
	#include "./caen/v775_fct_TDC.c"
	#include "./caen/v560_fct.c"
#endif

#ifdef MESYTEC
	static volatile short *madc32_thresh[32][NUMBER_OF_CARDS]; // mesytec ADC madc32
	static struct madc32_reg *madc32_ptr[NUMBER_OF_CARDS];
	#include "./mesytec/madc32_fct_ADC.c"	

	static volatile short *mqdc32_thresh[32][NUMBER_OF_CARDS]; // mesytec QDC mqdc32
	static struct mqdc32_reg *mqdc32_ptr[NUMBER_OF_CARDS];
	#include "./mesytec/mqdc32_fct_QDC.c"

	static struct mtdc32_reg *mtdc32_ptr[NUMBER_OF_CARDS]; // mesytec TDC mtdc32
	#include "./mesytec/mtdc32_fct_TDC.c"
#endif


#ifdef CAMAC
	static camac smwx1;
	static camac smwy1;
	static camac smwx2;
	static camac smwy2;
	camac *mwx1;			//== MWPC X1
	camac *mwy1;			//== MWPC Y1
	camac *mwx2;			//== MWPC X2
	camac *mwy2;			//== MWPC Y2
#endif

/*****************************************************************************/

int f_user_get_virt_ptr (long  *pl_loc_hwacc, long  pl_rem_cam[])
{
	int i,j;
	static char sh_mem_flg=0;  

	struct pdparam_master param;  /* for 'find_controller() */

	/*
	 * create virtual pointer to be used in f_user_init and f_user_readout
	 */

	/* vme */
	pl_trig_vme_fct = (long*) ( (long) pl_loc_hwacc + 0x8 );
	pl_trig_vme_cvt = (long*) ( (long) pl_loc_hwacc + 0xc );
	/* camac (crate 1) */
	pGTBC = CNAFLOC(0,28,0,27,pl_rem_cam[1]);
	pINHIBIT = CNAFLOC(0,30,9,24,pl_rem_cam[1]);

	if(!sh_mem_flg)     /* must not be called more than once! */
	{
		sh_mem_flg=1;
		#if defined(CAEN) || defined(MESYTEC)


			#ifdef RIO3
				if((caen_base = (long *) smem_create(CAEN_VME_NAME,
												  (char *) CAEN_VME_BASE,
												  VME_LEN,
												  SM_READ|SM_WRITE)) == NULL)
				{
					printf("Can't create CAEN segment, exiting...\n");
					exit(-1);
				}
			#endif  //rio3

			#ifdef RIO4
				caen_base = (long *) CAEN_VME_BASE;   // NEW: direct mapping 
			#endif

			#ifdef DEBUG
				printf("Addr caen_base: 0x%08x\n",caen_base);
			#endif

			for(i=0;i<NUMBER_OF_CARDS;i++){
				output_buffer[i] = (long *) ((long) caen_base + (long)((i)*CARDS_OFF));
				#ifdef CAEN
					v785_ptr[i] = (struct v7x5_reg *) ((long) caen_base+ (long)((i)*CARDS_OFF) + (long)(V7X5_OFF));
					v775_ptr[i] = (struct v7x5_reg *) ((long) caen_base+ (long)((i)*CARDS_OFF) + (long)(V7X5_OFF));
					v560_ptr[i] = (struct v560_reg *) ((long) caen_base+ (long)((i)*CARDS_OFF));
				#endif

				#ifdef MESYTEC  
				madc32_thresh[0][i] = (short *) ((long) caen_base + (long)((i)*CARDS_OFF) + (long)(MADC32_THRESH_OFF));
				mqdc32_thresh[0][i] = (short *) ((long) caen_base + (long)((i)*CARDS_OFF) + (long)(MQDC32_THRESH_OFF));
				for(j=1;j<32;j++){
					madc32_thresh[j][i]=madc32_thresh[j-1][i]+1;
					mqdc32_thresh[j][i]=mqdc32_thresh[j-1][i]+1;
				}
				madc32_ptr[i] = (struct madc32_reg *) ((long) caen_base + (long)((i)*CARDS_OFF) + (long)(MADC32_REG_OFF));
				mqdc32_ptr[i] = (struct mqdc32_reg *) ((long) caen_base + (long)((i)*CARDS_OFF) + (long)(MQDC32_REG_OFF));
				mtdc32_ptr[i] = (struct mtdc32_reg *) ((long) caen_base + (long)((i)*CARDS_OFF) + (long)(MTDC32_REG_OFF));
				#endif


			}
		#endif  // CAEN or MESYTEC	
		
		#ifdef CAMAC
		   //MWPC	
		   mwx1 = &smwx1;
		   Camac_Reset(mwx1);
		   Camac_SetOneCh(mwx1, 1, 1, 0, pl_rem_cam);
		   Camac_SetOneCh(mwx1, 1, 1, 1, pl_rem_cam);
		   Camac_SetHead(mwx1);

		   mwy1 = &smwy1;
		   Camac_Reset(mwy1);
		   Camac_SetOneCh(mwy1, 1, 2, 0, pl_rem_cam);
		   Camac_SetOneCh(mwy1, 1, 2, 1, pl_rem_cam);
		   Camac_SetHead(mwy1);

		   mwx2 = &smwx2;
		   Camac_Reset(mwx2);
		   Camac_SetOneCh(mwx2, 1, 3, 0, pl_rem_cam);
		   Camac_SetOneCh(mwx2, 1, 3, 1, pl_rem_cam);
		   Camac_SetHead(mwx2);

		   mwy2 = &smwy2;
		   Camac_Reset(mwy2);
		   Camac_SetOneCh(mwy2, 1, 4, 0, pl_rem_cam);
		   Camac_SetOneCh(mwy2, 1, 4, 1, pl_rem_cam);
		   Camac_SetHead(mwy2);	
		   

		   pINHIBIT = CNAFLOC(0,30,9,24,pl_rem_cam[1]);
		   //fflush (stdout);
		#endif
	
	}
}

/*****************************************************************************/

int f_user_init (unsigned char  bh_crate_nr,
                 long           *pl_loc_hwacc,
                 long           *pl_rem_cam,
                 long           *pl_stat)

{
	unsigned long volatile *hardware;
	int card;
	long i,c,
	status,
	l_dat;

	switch (bh_crate_nr)
		{
			case 0:             /* crate 0 */


				#ifdef CAEN
					card=0;
					#include "./caen/init_V560.c"		// scaler
				#endif

				#ifdef MESYTEC

					card=1;
					#include "./mesytec/init_mtdc32.c"		// R20mkm & RVeto _time
					mtdc32_ptr[card]->tdc_resolution=7;			// 7 -> 125 ps
					mtdc32_ptr[card]->bank0_win_start = 16384;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns
//					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=2;
					#include "./mesytec/init_madc32.c"		// R20mkm & RVeto _amp.
  					usleep(10000);
					madc32_ptr[card]->ignore_treshold = 1;		// Keep on. SK
					madc32_ptr[card]->input_range = 1;  		// range [0=4V, 1=10V, 2=8V]

					card=3;
					#include "./mesytec/init_mtdc32.c"		// L1500 _time
					mtdc32_ptr[card]->tdc_resolution=7;			// 7 -> 125 ps
					mtdc32_ptr[card]->bank0_win_start = 16384;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns
//					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=4;
					#include "./mesytec/init_madc32.c"		// L1500 _amp.
  					//usleep(10000);
					//madc32_ptr[card]->ignore_treshold = 1;
					madc32_ptr[card]->input_range = 1;  		// range [0=4V, 1=10V, 2=8V]
/*
					card=5;
					#include "./mesytec/init_mtdc32.c"		// Lx _time
					mtdc32_ptr[card]->tdc_resolution=7;			// 7 -> 125 ps
					mtdc32_ptr[card]->bank0_win_start = 16384;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns
//					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=6;
					#include "./mesytec/init_madc32.c"		// Lx _amp.
//					madc32_ptr[card]->ignore_treshold = 1;
					madc32_ptr[card]->input_range = 1;			// range [0=4V, 1=10V, 2=8V]

					card=7;
					#include "./mesytec/init_mtdc32.c"		// Ly _time 
					mtdc32_ptr[card]->tdc_resolution=7;			// 7 -> 125 ps
					mtdc32_ptr[card]->bank0_win_start = 16384;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns
//					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=8;
					#include "./mesytec/init_madc32.c"		// Ly _amp.
//					madc32_ptr[card]->ignore_treshold = 1;
					madc32_ptr[card]->input_range = 1;			// range [0=4V, 1=10V, 2=8V]

					card=9;
					#include "./mesytec/init_mtdc32.c"		// Cx & Cy _time
					mtdc32_ptr[card]->tdc_resolution=7;			// 7 -> 125 ps
					mtdc32_ptr[card]->bank0_win_start = 16384;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns
//					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=10;
					#include "./mesytec/init_madc32.c"		// Cx & Cy _amp.
					madc32_ptr[card]->ignore_treshold = 1;
					madc32_ptr[card]->input_range = 1;  		// range [0=4V, 1=10V, 2=8V]
*/
					card=11;
					#include "./mesytec/init_mtdc32.c"		// R1000 x & y _time
					mtdc32_ptr[card]->tdc_resolution=7;			// 7 -> 125 ps
					mtdc32_ptr[card]->bank0_win_start = 16384;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns
//					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=12;
					#include "./mesytec/init_madc32.c"		// R1000 x & y _amp.
  					//usleep(10000);
					//madc32_ptr[card]->ignore_treshold = 1;
					madc32_ptr[card]->input_range = 1;			// range [0=4V, 1=10V, 2=8V]
					madc32_ptr[card]->ecl_term = 7;				 

					card=13;								// ToF_time
					#include "./mesytec/init_mtdc32.c"
					mtdc32_ptr[card]->tdc_resolution=5;			// 2-> 1/256 ns ~4ps	4-> 1/64 ns ~ 15 ps		6 -> 1/16 ns = 62.5 ps		8 -> 250ps	
																// 3-> 1/128 ns ~8 ps 	5-> 1/32 ns ~ 31 ps  	7 -> 125ps					9 -> 500ps
//					mtdc32_ptr[card]->bank0_win_start = 15784;	// 16384 -> trigger
					mtdc32_ptr[card]->bank0_win_start = 15984;	// 16384 -> trigger
//					mtdc32_ptr[card]->bank0_win_width = 800;	// in ns
					mtdc32_ptr[card]->bank0_win_width = 450;	// in ns test
					mtdc32_ptr[card]->trig_select = 0;			// trigger from NIM

					card=14;								// ToF_qdc
						#include "./mesytec/init_mqdc32.c"

					gettimeofday(&vt_t0, NULL); // reset of computer time calculation

				#endif

				break;
			case 1:             /* crate 1 */
				
				#ifdef CAMAC
					Camac_Print(mwx1);
					Camac_Print(mwy1);
					Camac_Print(mwx2);
					Camac_Print(mwy2);
					//*pINHIBIT = 1;
				#endif
								
				//printf("Init Crate #1!\n");
				break;
			default:
				printf("Unknown crate!\n");
				break;
		}
		return (1);
}

/*****************************************************************************/

int f_user_readout (unsigned char  bh_trig_typ,
                    unsigned char  bh_crate_nr,
                    register long  *pl_loc_hwacc,
                    register long  *pl_rem_cam,
                    long           *pl_dat,
                    s_veshe        *ps_veshe,
                    long           *l_se_read_len,
                    long           *l_read_stat)
{
    long ev_size;
    int i,j;
    int card;
    unsigned long volatile *hardware;
    register union {
                     unsigned long int *p32;
                     unsigned short int *p16;
                     unsigned char *p8;
    } memory;

    static short int i_type, i_subtype, i_procid;  /* subevent header */
    static char h_subcrate, h_control;

	  *l_se_read_len = 0;

    /* Set initial values for GOOSY VME subevent header (type 10) */

    i_type = ps_veshe->i_type;
    i_subtype = ps_veshe->i_subtype;
    i_procid = ps_veshe->i_procid;
    h_subcrate = ps_veshe->h_subcrate;
    h_control = ps_veshe->h_control;

    memory.p32 = ((unsigned long int *) pl_dat);

    switch (bh_crate_nr)
    {
		case 0:                    /* crate 0 */
			switch (bh_trig_typ)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:

				#ifdef CAEN
					card=0;					
					#include "./caen/read_V560.c"
				#endif

				#ifdef MESYTEC            

					card=1;		// R20mkm & RVeto _time						
					#include "./mesytec/read_mtdc32.c"

					card=2;		// R20mkm & RVeto _amp.						
					#include "./mesytec/read_madc32.c"

					card=3;		// L1500 _time		
					#include "./mesytec/read_mtdc32.c"

					card=4;		// L1500  _amp.						
					#include "./mesytec/read_madc32.c"
/*
					card=5;		// Lx _time						
					#include "./mesytec/read_mtdc32.c"

					card=6;		// Lx _amp.
					#include "./mesytec/read_madc32.c"

					card=7;		// Ly _time
					#include "./mesytec/read_mtdc32.c"

					card=8;		// Ly _amp.
					#include "./mesytec/read_madc32.c"

					card=9;		// Cx & Cy _time						
					#include "./mesytec/read_mtdc32.c"

					card=10;	// Cx & Cy _amp.
					#include "./mesytec/read_madc32.c"
*/
	  				card=11;	// R1000 x & Ry _time						
					#include "./mesytec/read_mtdc32.c"

					card=12;	// R1000 x & Ry_amp.						
					#include "./mesytec/read_madc32.c"

					card=13;	// ToF_time
					#include "./mesytec/read_mtdc32.c"

					card=14;	// ToF_qdc
					#include "./mesytec/read_mqdc32.c"
					
				#endif

				#ifdef CAEN
					// clear CAEN v560 scaler after readout procedure
					card=0;					
					V560_Reset(card);					
				#endif
	
				#include "./caen/read_vtimer.c" //computer time

				break;
			case 14:  /* start acq */
			#ifdef CAEN
				card=0;
				#include "./caen/init_V560.c" //scaler clear
			#endif
				break;   
			case 15: /* stop acq */
			#ifdef CAEN
				card=0;
				#include "./caen/init_V560.c" //scaler clear
			#endif
				break;

			default:
				break;
			}
			break;  // crate 0



		case 1:		/* crate 1 */
			//printf("Read Crate #1!\n");
			switch (bh_trig_typ)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					#ifdef CAMAC
						
						*(memory.p32++) = mwx1->top;
						*(memory.p32++) = (*mwx1->data[0] & 0xffff);
						*(memory.p32++) = (*mwx1->data[1] & 0xffff); 
						*(memory.p32++) = mwx1->bot;

						*(memory.p32++) = mwy1->top;
						*(memory.p32++) = (*mwy1->data[0] & 0xffff);
						*(memory.p32++) = (*mwy1->data[1] & 0xffff); 
						*(memory.p32++) = mwy1->bot;

						*(memory.p32++) = mwx2->top;
						*(memory.p32++) = (*mwx2->data[0] & 0xffff);
						*(memory.p32++) = (*mwx2->data[1] & 0xffff); 
						*(memory.p32++) = mwx2->bot;

						*(memory.p32++) = mwy2->top;
						*(memory.p32++) = (*mwy2->data[0] & 0xffff);
						*(memory.p32++) = (*mwy2->data[1] & 0xffff); 
						*(memory.p32++) = mwy2->bot;						
						
					#endif
					break;
				case 14:  /* start acq */
					break;
				default:
					break;
			}
			break;  // crate 1



		default:
			printf("Unknown crate!\n");
			break;
    }  // end switch (bh_crate_nr)
	
    ev_size = ((unsigned char *) memory.p32) - ((unsigned char *) pl_dat);
    //printf("Ev Size: %d\n",ev_size);

    if (ev_size>100000)
    {
		printf("Ev Size: %d\n",ev_size);
		*l_se_read_len = 0;
    }
    else
		*l_se_read_len = ev_size;    

	return (1);
}

/*** EOF ***/
