/****************************************************************************/
/* caen_vme.h                                                               */
/* defines and registers for different CAEN VME cards                       */
/* HS 01-01-05 V785 and V775                                                */
/*    26-09-05 add registers of V767 TDC                                    */
/*    05-02-07 add registers of V792 QDC   									*/
/*AG  29-09-17 add registers of V560 Scaler                                 */
/*                                                                          */
/****************************************************************************/

#define V7X5_OFF  0x1000   // offset between output buffer and registers
#define V767_OFF  0x0004
#define V792_OFF  0x1000


#define V775__OUTPUT_BUFFER_GEO_N_WORD_COUNT   8
#define V775__OUTPUT_BUFFER_WORD_COUNT         0x3F

#define V785__OUTPUT_BUFFER_GEO_N_WORD_COUNT   8
#define V785__OUTPUT_BUFFER_WORD_COUNT         0x3F

#define V792__OUTPUT_BUFFER_GEO_N_WORD_COUNT   8
#define V792__OUTPUT_BUFFER_WORD_COUNT         0x3F

#define V7X5__HEADER_TYPE_SHIFT 24
#define V7X5__HEADER_TYPE_MASK 0x7

#define V7X5__HEADER_CNT_SHIFT 8
#define V7X5__HEADER_CNT_MASK  0x3F

#define V767__HEADER_TYPE_SHIFT 20
#define V767__HEADER_TYPE_MASK 0x6

#define V792__HEADER_CNT_SHIFT 8
#define V792__HEADER_CNT_MASK  0x3F

#define BIT00  0x001
#define BIT01  0x002
#define BIT02  0x004
#define BIT03  0x008

#define BIT04  0x010
#define BIT05  0x020
#define BIT06  0x040
#define BIT07  0x080

#define BIT08  0x100
#define BIT09  0x200
#define BIT10  0x400
#define BIT11  0x800

//volatile long *output_buffer[V7X5_CARDS];

/****************************************************************************/
/* registers of CAEN V785 ADC, V775 TDC                                     */
/*                                                                          */
/****************************************************************************/

struct v7x5_reg {
  volatile short firmware_revision;
  volatile short geo_addr;
  volatile short mcst_addr;

  volatile short bit_set_1;
  volatile short bit_clear_1;

  volatile short interrupt_level;
  volatile short interrupt_vector;

  volatile short status_reg_1;
  volatile short control_reg_1;

  volatile short ader_h; //Address Decoder High Register (A31...A24 bits)
  volatile short ader_l; //Address Decoder Low Register (A23...A16 bits)
  volatile short single_shot_reset;

  short dummy0;

  volatile short mcst_ctrl;

  short dummy1[2];

  volatile short event_trig_reg;
  volatile short status_reg_2;

  volatile short event_counter_l;
  volatile short event_counter_h;
  volatile short inc_event;
  volatile short inc_offset;

  volatile short load_test_reg;
  volatile short fclr_window;

  short dummy2;

  volatile short bit_set_2;
  volatile short bit_clear_2;

  volatile short w_mem_test_addr;
  volatile short mem_test_wh;
  volatile short mem_test_wl;

  volatile short crate_select;
  volatile short test_event_write;
  volatile short event_counter_reset;

  short dummy3[15];

  volatile short full_scale_range;   /* TDC only */

  short dummy4;

  volatile short r_test_addr;

  short dummy5;

  volatile short sw_comm;
  volatile short slide_const;

  short dummy6[2];

  volatile short aad;
  volatile short bad; 

  short dummy7[6]; 

  volatile short thresholds[32];
};

/****************************************************************************/
/* registers of CAEN V767 TDC                                               */
/*                                                                          */
/****************************************************************************/

struct v767_reg {
  volatile short geo_addr;
  volatile short bit_set;
  volatile short bit_clear;

  volatile short interrupt_level;
  volatile short interrupt_vector;

  volatile short status_reg_1;
  volatile short control_reg_1;

  volatile short ader_32;
  volatile short ader_24;

  volatile short mcst_addr;
  volatile short single_shot_reset;

  short dummy0[3];

  volatile short mcst_ctrl;

  //------------------------

  short dummy1[19];

  volatile short status_reg_2;
  volatile short control_reg_2;

  volatile short event_counter;
  volatile short event_counter_reset;

  volatile short opc_hs;      // opcode handshake
  volatile short opc_reg;

  volatile short clear;
  volatile short mem_test_wh;
  volatile short mem_test_wl;
  
  volatile short sw_trig;
};

/****************************************************************************/
/* registers of CAEN V792 QDC					                            */
/*                                                                          */
/****************************************************************************/

struct v792_reg {
  volatile short firmware_revision;
  volatile short geo_addr;
  volatile short mcst_addr;

  volatile short bit_set_1;
  volatile short bit_clear_1;

  volatile short interrupt_level;
  volatile short interrupt_vector;

  volatile short status_reg_1;
  volatile short control_reg_1;

  volatile short ader_h;
  volatile short ader_l;
  volatile short single_shot_reset;

  short dummy0;

  volatile short mcst_ctrl;

  short dummy1[2];

  volatile short event_trig_reg;
  volatile short status_reg_2;

  volatile short event_counter_l;
  volatile short event_counter_h;
  volatile short inc_event;
  volatile short inc_offset;

  volatile short load_test_reg;
  volatile short fclr_window;

  short dummy2;

  volatile short bit_set_2;
  volatile short bit_clear_2;

  volatile short w_mem_test_addr;
  volatile short mem_test_wh;
  volatile short mem_test_wl;

  volatile short crate_select;
  volatile short test_event_write;
  volatile short event_counter_reset;

  short dummy3[15];

  volatile short iped;

  short dummy4;

  volatile short r_test_addr;

  short dummy5;

  volatile short sw_comm;
  volatile short slide_const;

  short dummy6[2];

  volatile short aad;
  volatile short bad;

  short dummy7[6];

  volatile short thresholds[32];
};

/****************************************************************************/
/* registers of CAEN V560 Scaler	  						                */
/*                                                                          */
/****************************************************************************/

struct v560_reg {
	volatile short dummy[2];
	
	volatile short interrupt_vector;
	volatile short interrupt_level;
	volatile short ena_vme_interrupt;
	volatile short dis_vme_interrupt;
	volatile short clear_vme_interrupt;
	volatile short request_register;
	
	volatile long counter[16]; //counters #0-15
	
	volatile short scale_clear;
	volatile short vme_veto_set;
	volatile short vme_veto_res;
	volatile short scaler_inc;
	volatile short scaler_st_reg; //Scale Status register read only
	volatile short dummy1;
	
	volatile long dummy2[41];
	
	volatile short fixed_code;
	volatile short manufacturer_type;
	volatile short version;
};

/* EOF */

