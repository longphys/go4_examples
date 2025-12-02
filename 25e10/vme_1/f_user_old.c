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



//#define DEBUG
//#define CAEN         // use CAEN ADC,TDC
#define MESYTEC    //use MESYTEC MADC, MQDC, MTDC
#define NUMBER_OF_CARDS 30      // number of CAEN and MESYTEC modules in VME crate

/*****************************************************************************/

//-----------------------------------------------------------------------------------------------------------
// users cards could use 0x00000000 - 0x01ffffff address space
// GSI trigger card base: 		0x02000000  // TRIVA address is fixed in MBS
// GSI vulom card base:   		0x03000000  // if address bits 31 to 28 = 0 (rotary switch VN2 = 0), programm of the module can be changed through VME bus
//-----------------------------------------------------------------------------------------------------------

#define CARDS_OFF 0x10000    // offset between two VME cards 0x10000
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

#define round(x)  ((int) floor((double) (x)+0.5))

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

/*****************************************************************************/

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

	
	#if defined(CAEN) || defined(MESYTEC)
		if(!sh_mem_flg)     /* must not be called more than once! */
		{
		sh_mem_flg=1;

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
	   }
	#endif  // CAEN or MESYTEC	

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
					//card=0;
					//#include "./caen/init_V785_ADC.c"
					//card=1;
					//#include "./caen/init_V785_ADC.c"
					//card=2;
					//#include "./caen/init_V785_ADC.c"

				#endif

				#ifdef MESYTEC
					
					//card=3;
						//#include "./mesytec/init_mtdc32.c"
						//mtdc32_ptr[card]->trig_select = 0;	// trigger from NIM

						//mtdc32_ptr[card]->tdc_resolution=7;			// 9 -> 500ps
													// 8 -> 250ps
													// 7 -> 125ps
													// 6 -> 1/16 ns = 62.5 ps 
													// 5 -> 1/32 ns ~ 31 ps
													// 4 -> 1/64 ns ~ 15 ps
													// 3 -> 1/128 ns ~8 ps
													// 2 -> 1/256 ns ~4ps
																	
						//mtdc32_ptr[card]->bank0_win_start = 15984;	// 16384 -> trigger
						//mtdc32_ptr[card]->bank0_win_width = 500;	// in ns

					//card=4;
						//#include "./mesytec/init_mtdc32.c"
						//mtdc32_ptr[card]->trig_select = 0;	// trigger from NIM
						//mtdc32_ptr[card]->tdc_resolution=7;			// 9 -> 500ps
													// 8 -> 250ps
													// 7 -> 125ps
													// 6 -> 1/16 ns = 62.5 ps 
													// 5 -> 1/32 ns ~ 31 ps
													// 4 -> 1/64 ns ~ 15 ps
													// 3 -> 1/128 ns ~8 ps
													// 2 -> 1/256 ns ~4ps
																	
						//mtdc32_ptr[card]->bank0_win_start = 15984;	// 16384 -> trigger
//						mtdc32_ptr[card]->bank0_win_width = 500;	// in ns
						//mtdc32_ptr[card]->bank0_win_width = 1000;	// in ns

					//card=3;
						//#include "./mesytec/init_mtdc32.c"
						//mtdc32_ptr[card]->bank0_win_start = 15984;	// 16384 -> trigger
						//mtdc32_ptr[card]->bank0_win_width = 500;	// in ns


					card=4;
						#include "./mesytec/init_madc32.c"		
						//madc32_ptr[card]->ignore_treshold = 1;

				#endif

				break;
			case 1:             /* crate 1 */
				printf("Crate #1!\n");
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

				#ifdef CAEN
					card=0;
					#include "./caen/read_V785_ADC.c"
					card=1;
					#include "./caen/read_V785_ADC.c"
					card=2;
					#include "./caen/read_V785_ADC.c"						
				#endif

				#ifdef MESYTEC            
				//card=3;						
				//#include "./mesytec/read_mtdc32.c"
					//card=4;						
					//#include "./mesytec/read_mtdc32.c"
					card=4;						
					#include "./mesytec/read_madc32.c"
				#endif


				break;
			case 14:  /* start acq */

				break;   
			case 15: /* stop acq */

				break;

			default:
				break;
			}
			break;  // crate 0

		case 1:                     /* crate 1 */
			printf("Crate #1!\n");
			switch (bh_trig_typ)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
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
