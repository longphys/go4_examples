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
#define V1725_CH_OFF 0x1020   //offset valid for DPP-PSD firmware
#define V1725_OFF 0x8000
#define V1725_EF_OFF 0xEF00
#define V1725_CH_DIFF 0x0100 


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

/****************************************************************************/
/* registers of CAEN V1725 DIGITIZER                                        */
/* v1725_ch_reg, v1725_reg, v1725_EF_reg -                                  */
/* - structures for digirizers with DPP-PSD Firmware                        */
/****************************************************************************/


struct v1725_ch_reg { //one per channel
	volatile long record_length;                              //0x1n20 broadcast->0x8020 R/W
  volatile long dummy;                                      //0x1n24
	volatile long input_dynamic_range;                        //0x1n28 broadcast->0x8028 R/W
	volatile long dummy1[2];                                  //0x1n2C && 0x1n30                     
  volatile long number_of_events_per_aggregate;             //0x1n34 broadcast->0x8034 R/W
  volatile long pre_trigger;                                //0x1n38 broadcast->0x8038 R/W
  volatile long CFD_settings;                               //0x1n3C broadcast->0x803C R/W
  volatile long forced_data_flush;                          //0x1n40 broadcast->0x8040 W
  volatile long charge_zero_suppression_threshold;          //0x1n44 broadcast->0x8044 R/W
	volatile long dummy2[3];                                  //0x1n48 - 0x1n50     
  volatile long short_gate_width;                           //0x1n54 broadcast->0x8054 R/W
  volatile long long_gate_width;                            //0x1n58 broadcast->0x8058 R/W
  volatile long gate_offset;                                //0x1n5C broadcast->0x805C R/W
  volatile long trigger_threshold;                          //0x1n60 broadcast->0x8060 R/W
  volatile long fixed_baseline;                             //0x1n64 broadcast->0x8064 R/W
  volatile long dummy3;                                     //0x1n68
  volatile long trigger_latency;                            //0x1n6C broadcast->0x806C R/W
  volatile long shaped_trigger_width;                       //0x1n70 broadcast->0x8070 R/W
  volatile long trigger_holdoff_width;                      //0x1n74 broadcast->0x8074 R/W
  volatile long threshold_for_the_PSD_cut;                  //0x1n78 broadcast->0x8078 R/W
  volatile long PUR_GAP_threshold;                          //0x1n7C broadcast->0x807C R/W
  volatile long DPP_algorithm_control;                      //0x1n80 broadcast->0x8080 R/W
  volatile long DPP_algorithm_control_2;                    //0x1n84 broadcast->0x8084 R/W
	volatile long channel_status;                             //0x1n88 R
	volatile long AMC_firmware_revision;                      //0x1n8C R
	volatile long dummy4[2];                                  //0x1n90 && 0x1n94
	volatile long DC_offset;                                  //0x1n98 broadcast->0x8098 R/W
	volatile long dummy5[3];                                  //0x1n9C - 0x1nA4
	volatile long channel_ADC_temperature;                    //0x1nA8 R
	volatile long dummy6[5];                                  //0x1nAC - 0x1nBC
	volatile long individual_software_trigger;                //0x1nC0 broadcast->0x80C0 W
  volatile long dummy7[4];                                  //0x1nC4 - 0x1nD0
	volatile long veto_width;                                 //0x1nD4 broadcast->0x8084!! R/W
  volatile long early_baseline_freeze;                      //0x1nD8 broadcast->0x80D8 R/W
};

struct v1725_reg { //one per board
	volatile long board_configuration;                        //0x8000 R/W
	volatile long board_configuration_bitSet;                 //0x8004 R/W
	volatile long board_configuration_bitClear;               //0x8008 R/W
	volatile long aggregate_organization;                     //0x800C R/W
	volatile long dummy[4];                                   //0x8010 - 0x801C
	volatile long record_length_broadcast;                    //0x8020 R/W
  volatile long dummy1;                                     //0x8024
	volatile long input_dynamic_range_broadcast;              //0x8028 R/W
	volatile long dummy2[2];                                  //0x802C && 0x8030
	volatile long number_of_events_per_aggregate_broadcast;   //0x8034 R/W
	volatile long pre_trigger_broadcast;                      //0x8038 R/W
	volatile long CFD_settings_broadcast;                     //0x803C R/W
	volatile long forced_data_flush_broadcast;                //0x8040 W
	volatile long charge_zero_suppression_threshold_broadcast;//0x8044 R/W
  volatile long dummy3[3];                                  //0x8048 - 0x8050
	volatile long short_gate_width_broadcast;                 //0x8054 R/W
	volatile long long_gate_width_broadcast;                  //0x8058 R/W
	volatile long gate_offset_broadcast;                      //0x805C R/W
	volatile long trigger_threshold_broadcast;                //0x8060 R/W
	volatile long fixed_baseline_broadcast;                   //0x8064 R/W
  volatile long dummy4;                                     //0x8068
	volatile long trigger_latency_broadcast;                  //0x806C R/W
	volatile long shaped_trigger_width_broadcast;             //0x8070 R/W
	volatile long trigger_holdoff_width_broadcast;            //0x8074 R/W
	volatile long threshold_for_the_PSD_cut_broadcast;        //0x8078 R/W
	volatile long PUR_GAP_threshold_broadcast;                //0x807C R/W
  volatile long DPP_algorithm_control_broadcast;            //0x8080 R/W
  volatile long DPP_algorithm_control_2_broadcast;          //0x8084 R/W
  volatile long dummy5[4];                                  //0x8088 - 0x8094
  volatile long DC_offset_broadcast;                        //0x8098 R/W
  volatile long channel_ADC_calibration;                    //0x809C W
  volatile long dummy6[7];                                  //0x80A0 - 0x80B8
  volatile long channels_shutdown;                          //0x80BC W
  volatile long individual_software_trigger_broadcast;      //0x80C0 W
  volatile long dummy7[5];                                  //0x80C4 - 0x80D4
  volatile long early_baseline_freeze_broadcast;            //0x80D8 R/W
  volatile long dummy8[9];                                  //0x80DC - 0x80FC
  volatile long acquisition_control;                        //0x8100 R/W
  volatile long acquisition_status;                         //0x8104 R
  volatile long software_trigger;                           //0x8108 W
  volatile long global_mask_trigger;                        //0x810C R/W
  volatile long front_panel_TRGOUT_GPO_enable_mask;         //0x8110 R/W
  volatile long dummy9;                                     //0x8114
  volatile long LVDS_IO_data;                               //0x8118 R/W
	volatile long front_panel_io_control;                     //0x811C R/W
	volatile long channel_enable_mask;                        //0x8120 R/W
	volatile long roc_fpga_firmware_revision;                 //0x8124 R
	volatile long dummy10[4];                                 //0x8128 - 0x8134
	volatile long voltage_level_mode_configuration;           //0x8138 R/W
	volatile long software_clock_sync;                        //0x813C W
	volatile long board_info;                                 //0x8140 R
	volatile long analog_monitor_mode;                        //0x8144 R/W
  volatile long dummy11;                                    //0x8148
	volatile long event_size;                                 //0x814C R
	volatile long dummy12[2];                                 //0x8150 && 0x8154
  volatile long time_bomb_downcounter;                      //0x8158 R
  volatile long dummy13[3];                                 //0x815C - 0x8164
	volatile long fan_speed_control;                          //0x8168 R/W
	volatile long dummy14;                                    //0x816C
	volatile long run_start_stop_delay;                       //0x8170 R/W
	volatile long dummy15;                                    //0x8174
	volatile long board_failure_status;                       //0x8178 R
	volatile long disable_external_trigger;                   //0x817C R/W
  volatile long trigger_validation_mask_couple_0;           //0x8180 R/W
  volatile long trigger_validation_mask_couple_1;           //0x8184 R/W
  volatile long trigger_validation_mask_couple_2;           //0x8188 R/W
  volatile long trigger_validation_mask_couple_3;           //0x818C R/W
  volatile long trigger_validation_mask_couple_4;           //0x8190 R/W
  volatile long trigger_validation_mask_couple_5;           //0x8194 R/W
  volatile long trigger_validation_mask_couple_6;           //0x8198 R/W
  volatile long trigger_validation_mask_couple_7;           //0x819C R/W
	volatile long front_panel_lvds_io_new_features;           //0x81A0 R/W
	volatile long dummy16[4];                                 //0x81A4 - 0x81B0
	volatile long buffer_occupancy_gain;                      //0x81B4 R/W
	volatile long dummy17[3];                                 //0x81B8 - 0x81C0
	volatile long extended_veto_delay;                        //0x81C4 R/W
};

struct v1725_EF_reg { //one per board
	volatile long readout_control;                            //0xEF00 R/W
	volatile long readout_status;                             //0xEF04 R
	volatile long board_ID;                                   //0xEF08 R/W
	volatile long MCST_base_address_and_control;              //0xEF0C R/W
	volatile long relocation_address;                         //0xEF10 R/W
	volatile long intrrupt_statusID;                          //0xEF14 R/W
	volatile long interrupt_event_number;                     //0xEF18 R/W
	volatile long aggregate_number_per_BLT;                   //0xEF1C R/W
	volatile long scratch;                                    //0xEF20 R/W
	volatile long software_reset;                             //0xEF24 W
	volatile long software_clear;                             //0xEF28 W
	volatile long dummy[2];                                   //0xEF2C && 0xEF30
	volatile long configuration_reload;                       //0xEF34 W
};

/* EOF */