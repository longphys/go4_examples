//**************************************************************************
// Mesytec MADC-32 ADC
//**************************************************************************

//#define MADC32_CARDS 15
#define MADC32_THRESH_OFF 0x4000   // offset of madc32 threshold registers
#define MADC32_REG_OFF    0x6000   // offset of madc32 registers

struct madc32_reg {
  volatile short address_source;     // 0x6000
  volatile short address_reg;
  volatile short module_id;
  volatile short dummy;          
  volatile short soft_reset;         // 0x6008
  volatile short dummy2[2];
  volatile short firmware_rev;
  volatile short irq_level;          // 0x6010
  volatile short irq_vector;
  volatile short irq_test;
  volatile short irq_reset;
  volatile short irq_threshold;
  volatile short max_transfer_data;  // 0x601A
  volatile short withdraw_irq;       // 0x601C
  volatile short dummy3;
  volatile short cblt_mcst_ctrl;     // 0x6020
  volatile short cblt_address;
  volatile short mcst_address;
  volatile short dummy4[5];
  volatile short buffer_data_len;    // 0x6030, FIFO handling
  volatile short data_len_format;
  volatile short readout_reset;
  volatile short multievent;
  volatile short marking_type;
  volatile short start_acq;
  volatile short fifo_reset;
  volatile short data_ready;
  volatile short bank_op;            // 0x6040, operation mode
  volatile short adc_resolution;
  volatile short output_format;
  volatile short adc_override;
  volatile short slc_off;
  volatile short skip_oorange;
  volatile short ignore_treshold;
  volatile short dummy5;
  volatile short hold_del0;          // 0x6050, gate generator
  volatile short hold_del1;
  volatile short hold_width0;
  volatile short hold_width1;
  volatile short use_gg;
  volatile short dummy6[3];
  volatile short input_range;        // 0x6060, inputs, outputs
  volatile short ecl_term;
  volatile short ecl_gate1_osc;
  volatile short ecl_fc_res;
  volatile short ecl_busy;
  volatile short nim_gate1_osc;
  volatile short nim_fc_res;
  volatile short nim_busy;
  volatile short pulser_status;      // 0x6070
  volatile short dummy7[7];
  volatile short rc_busno;           // 0x6080, MRC
  volatile short rc_modnum;
  volatile short rc_opcode;
  volatile short rc_adr;
  volatile short rc_dat;
  volatile short rc_ret_status;
  volatile short dummy8[2];
  volatile short reset_ctr_ab;       // 0x6090, CTRA
  volatile short evctr_lo;
  volatile short evctr_hi;
  volatile short ts_sources;
  volatile short ts_divisor;
  volatile short dummy9;
  volatile short ts_count_lo;
  volatile short ts_count_hi;
  volatile short adc_busy_time_lo;   // 0x60A0, CTRB
  volatile short adc_busy_time_hi;
  volatile short gate_1_time_lo;
  volatile short gate_1_time_hi;
  volatile short time0;
  volatile short time1;
  volatile short time2;
  volatile short stop_ctr;
};

//=====================================================================
// Mesytec MQDC-32 QDC
//=====================================================================


#define MQDC32_THRESH_OFF 0x4000   // offset of mqdc32 threshold registers
#define MQDC32_REG_OFF    0x6000   // offset of mqdc32 registers

struct mqdc32_reg {
// Address registers
	volatile short address_source;     // 0x6000
  volatile short address_reg;
  volatile short module_id;
  volatile short dummy;          
  volatile short soft_reset;         // 0x6008
  volatile short dummy2[2];
  volatile short firmware_rev;

// IRQ (ROACK)	
  volatile short irq_level;          // 0x6010
  volatile short irq_vector;
  volatile short irq_test;
  volatile short irq_reset;
  volatile short irq_threshold;
  volatile short max_transfer_data;  // 0x601A
  volatile short withdraw_irq;       // 0x601C
  volatile short dummy3;

// MCST CBLT
  volatile short cblt_mcst_ctrl;     // 0x6020
  volatile short cblt_address;
  volatile short mcst_address;
  volatile short dummy4[5];

// FIFO handling
  volatile short buffer_data_len;    // 0x6030
  volatile short data_len_format;
  volatile short readout_reset;
  volatile short multievent;
  volatile short marking_type;
  volatile short start_acq;
  volatile short fifo_reset;
  volatile short data_ready;

// operation mode
  volatile short bank_op;            // 0x6040, 
  volatile short adc_resolution;
  volatile short offset_bank0;
  volatile short offset_bank1;
  volatile short slc_off;
  volatile short skip_oorange;
  volatile short ignore_treshold;
  volatile short dummy5;

//gate limit/trigger
  volatile short limit_bank0;         // 0x6050
  volatile short limit_bank1;
  volatile short exp_trig_delay0;
  volatile short exp_trig_delay1;
  volatile short dummy6[4];

// inputs, outputs
  volatile short input_coupling;      // 0x6060
  volatile short ecl_term;
  volatile short ecl_gate1_osc;
  volatile short ecl_fc_res;
  volatile short gate_select;
  volatile short nim_gate1_osc;
  volatile short nim_fc_res;
  volatile short nim_busy;

// testpulser
  volatile short pulser_status;      // 0x6070
	volatile short pulser_dac;
  volatile short dummy7[6];

//MRC
  volatile short rc_busno;           // 0x6080
  volatile short rc_modnum;
  volatile short rc_opcode;
  volatile short rc_adr;
  volatile short rc_dat;
  volatile short rc_ret_status;
  volatile short dummy8[2];

//CTRA
  volatile short reset_ctr_ab;       // 0x6090, CTRA
  volatile short evctr_lo;
  volatile short evctr_hi;
  volatile short ts_sources;
  volatile short ts_divisor;
  volatile short dummy9;
  volatile short ts_count_lo;
  volatile short ts_count_hi;

//CTRB
  volatile short adc_busy_time_lo;   // 0x60A0, CTRB
  volatile short adc_busy_time_hi;
  volatile short gate_1_time_lo;
  volatile short gate_1_time_hi;
  volatile short time0;
  volatile short time1;
  volatile short time2;
  volatile short stop_ctr;

//MULT
	volatile short hi_limit0;
	volatile short lo_limit0;
	volatile short hi_limit1;
	volatile short lo_limit1;
};

//=====================================================================
// Mesytec MTDC-32 TDC
//=====================================================================

#define MTDC32_REG_OFF 0x6000 //offset of mtdc32 registers

struct mtdc32_reg {
// Address registers
  volatile short address_source;     // 0x6000
  volatile short address_reg;
  volatile short module_id;
  volatile short dummy;
  volatile short soft_reset;         // 0x6008
  volatile short dummy2[2];
  volatile short firmware_rev;

// IRQ (ROACK)	
  volatile short irq_level;          // 0x6010
  volatile short irq_vector;
  volatile short irq_test;
  volatile short irq_reset;
  volatile short irq_data_threshold;
  volatile short max_transfer_data;  // 0x601A
  volatile short irq_source;       // 0x601C
  volatile short irq_event_threshold;

// MCST CBLT
  volatile short cblt_mcst_ctrl;     // 0x6020
  volatile short cblt_address;
  volatile short mcst_address;
  volatile short dummy4[5];

// FIFO handling
  volatile short buffer_data_len;    // 0x6030
  volatile short data_len_format;
  volatile short readout_reset;
  volatile short multievent;
  volatile short marking_type;
  volatile short start_acq;	    //0x603A
  volatile short fifo_reset;
  volatile short data_ready;

// operation mode
  volatile short bank_op;            // 0x6040, 
  volatile short tdc_resolution;
  volatile short output_format;
  volatile short dummy5[5];

// trigger
  volatile short bank0_win_start;  //0x6050
  volatile short bank1_win_start;
  volatile short bank0_win_width;
  volatile short bank1_win_width;
  volatile short bank0_trig_source;
  volatile short bank1_trig_source;
  volatile short first_hit;
  volatile short dummy6[1];

// inputs, outputs
  volatile short negative_edge;      // 0x6060
  volatile short ecl_term;
  volatile short ecl_trig1_osc;
  volatile short ecl_out_config;
  volatile short trig_select;
  volatile short nim_trig1_osc;
  volatile short nim_fc_res; //dummy
  volatile short nim_busy;

// testpulser
  volatile short pulser_status;      // 0x6070
  volatile short pulser_dac[3]; //dummy
  volatile short bank0_input_thr;
  volatile short bank1_input_thr;
  volatile short dummy7[2];

//MRC
  volatile short rc_busno;           // 0x6080
  volatile short rc_modnum;
  volatile short rc_opcode;
  volatile short rc_adr;
  volatile short rc_dat;
  volatile short rc_ret_status;
  volatile short dummy8[2];

//CTRA
  volatile short reset_ctr_ab;       // 0x6090, CTRA
  volatile short evctr_lo;
  volatile short evctr_hi;
  volatile short ts_sources;
  volatile short ts_divisor;
  volatile short dummy9;
  volatile short ts_count_lo;
  volatile short ts_count_hi;

//CTRB
  volatile short dummy10[4];
  volatile short time0; 					//0x60A0 CTRB
  volatile short time1;
  volatile short time2;
  volatile short stop_ctr;

//MULT
  volatile short hi_limit0;				//0x60B0 MULT
  volatile short lo_limit0;
  volatile short hi_limit1;
  volatile short lo_limit1;
};

// EOF
