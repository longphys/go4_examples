/*************************************************************************/
/* v1725_fct.c  functions for CAEN V1725 Digitizer                       */
/*                                                                       */
/*************************************************************************/

#define CHANNEL_0 0x1000
#define CHANNEL_1 0x1100
#define CHANNEL_2 0x1200
#define CHANNEL_3 0x1300
#define CHANNEL_4 0x1400
#define CHANNEL_5 0x1500
#define CHANNEL_6 0x1600
#define CHANNEL_7 0x1700
#define CHANNEL_8 0x1800
#define CHANNEL_9 0x1900
#define CHANNEL_A 0x1A00
#define CHANNEL_B 0x1B00
#define CHANNEL_C 0x1C00
#define CHANNEL_D 0x1D00
#define CHANNEL_E 0x1E00
#define CHANNEL_F 0x1F00

#define RECORD_LENGTH 0x20                     // R/W
#define INPUT_DYNAMIC_RANGE 0x28               // R/W
#define NUMBER_OF_EVENTS_PER_AGGREGATE 0x34    // R/W
#define PRE_TRIGGER 0x38                       // R/W
#define CFD_SETTINGS 0x3C                      // R/W
#define FORCED_DATA_FLUSH 0x40                 // W
#define CHARGE_ZERO_SUPPRESSION_THRESHOLD 0x44 // R/W
#define SHORT_GATE_WIDTH 0x54                  // R/W
#define LONG_GATE_WIDTH 0x58                   // R/W
#define GATE_OFFSET 0x5C                       // R/W
#define TRIGGER_THRESHOLD 0x60                 // R/W
#define FIXED_BASELINE 0x64                    // R/W
#define TRIGGER_LATENCY 0x6C                   // R/W
#define SHAPED_TRIGGER_WIDTH 0x70              // R/W
#define TRIGGER_HOLDOFF_WIDTH 0x74             // R/W
#define THRESHOLD_FOR_THE_PSD_CUT 0x78         // R/W
#define PUR_GAP_THRESHOLD 0x7C                 // R/W
#define DPP_ALGORITHM_CONTROL 0x80             // R/W
#define DPP_ALGORITHM_CONTROL_2 0x84           // R/W
#define CHANNEL_STATUS 0x88                    // R
#define AMC_FIRMWARE_REVISION 0x8C             // R
#define DC_OFFSET 0x98                         // R/W
#define CHANNEL_ADC_TEMPERATURE 0xA8           // R
#define INDIVIDUAL_SOFTWARE_TRIGGER 0xC0       // W
#define VETO_WIDTH 0xD4                        // R/W
#define EARLY_BASELINE_FREEZE 0xD8             // R/W

#define BOARD_CONFIGURATION 0x8000                         // R/W
#define BOARD_CONFIGURATION_BITSET 0x8004                  // R/W
#define BOARD_CONFIGURATION_BITCLEAR 0x8008                // R/W
#define AGGREGATE_ORGANIZATION 0x800C                      // R/W
#define RECORD_LENGTH_BROADCAST 0x8020                     // R/W
#define INPUT_DYNAMIC_RANGE_BROADCAST 0x8028               // R/W
#define NUMBER_OF_EVENTS_PER_AGGREGATE_BROADCAST 0x8034    // R/W
#define PRE_TRIGGER_BROADCAST 0x8038                       // R/W
#define CFD_SETTINGS_BROADCAST 0x803C                      // R/W
#define FORCED_DATA_FLUSH_BROADCAST 0x8040                 // W
#define CHARGE_ZERO_SUPPRESSION_THRESHOLD_BROADCAST 0x8044 // R/W
#define SHORT_GATE_WIDTH_BROADCAST 0x8054                  // R/W
#define LONG_GATE_WIDTH_BROADCAST 0x8058                   // R/W
#define GATE_OFFSET_BROADCAST 0x805C                       // R/W
#define TRIGGER_THRESHOLD_BROADCAST 0x8060                 // R/W
#define FIXED_BASELINE_BROADCAST 0x8064                    // R/W
#define TRIGGER_LATENCY_BROADCAST 0x806C                   // R/W
#define SHAPED_TRIGGER_WIDTH_BROADCAST 0x8070              // R/W
#define TRIGGER_HOLDOFF_WIDTH_BROADCAST 0x8074             // R/W
#define THRESHOLD_FOR_THE_PSD_CUT_BROADCAST 0x8078         // R/W
#define PUR_GAP_THRESHOLD_BROADCAST 0x807C                 // R/W
#define DPP_ALGORITHM_CONTROL_BROADCAST 0x8080             // R/W
#define DPP_ALGORITHM_CONTROL_2_BROADCAST 0x8084           // R/W
#define DC_OFFSET_BROADCAST 0x8098                         // R/W
#define CHANNEL_ADC_CALIBRATION 0x809C                     // W
#define CHANNELS_SHUTDOWN 0x80BC                           // W
#define INDIVIDUAL_SOFTWARE_TRIGGER_BROADCAST 0x80C0       // W
#define EARLY_BASELINE_FREEZE_BROADCAST 0x80D8             // R/W
#define ACQUISITION_CONTROL 0x8100                         // R/W
#define ACQUISITION_STATUS 0x8104                          // R
#define SOFTWARE_TRIGGER 0x8108                            // W
#define GLOBAL_MASK_TRIGGER 0x810C                         // R/W
#define FRONT_PANEL_TRGOUT_GPO_ENABLE_MASK 0x8110          // R/W
#define LVDS_IO_DATA 0x8118                                // R/W
#define FRONT_PANEL_IO_CONTROL 0x811C                      // R/W
#define CHANNEL_ENABLE_MASK 0x8120                         // R/W
#define ROC_FPGA_FIRMWARE_REVISION 0x8124                  // R
#define VOLTAGE_LEVEL_MODE_CONFIGURATION 0x8138            // R/W
#define SOFTWARE_CLOCK_SYNC 0x813C                         // W
#define BOARD_INFO 0x8140                                  // R
#define ANALOG_MONITOR_MODE 0x8144                         // R/W
#define EVENT_SIZE 0x814C                                  // R
#define TIME_BOMB_DOWNCOUNTER 0x8158                       // R
#define FAN_SPEED_CONTROL 0x8168                           // R/W
#define RUN_START_STOP_DELAY 0x8170                        // R/W
#define BOARD_FAILURE_STATUS 0x8178                        // R
#define DISABLE_EXTERNAL_TRIGGER 0x817C                    // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_0 0x8180            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_1 0x8184            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_2 0x8188            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_3 0x818C            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_4 0x8190            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_5 0x8194            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_6 0x8198            // R/W
#define TRIGGER_VALIDATION_MASK_COUPLE_7 0x819C            // R/W
#define FRONT_PANEL_LVDS_IO_NEW_FEATURES 0x81A0            // R/W
#define BUFFER_OCCUPANCY_GAIN 0x81B4                       // R/W
#define EXTENDED_VETO_DELAY 0x81C4                         // R/W

#define READOUT_CONTROL 0xEF00               // R/W
#define READOUT_STATUS 0xEF04                // R
#define BOARD_ID 0xEF08                      // R/W
#define MCST_BASE_ADDRESS_AND_CONTROL 0xEF0C // R/W
#define RELOCATION_ADDRESS 0xEF10            // R/W
#define INTRRUPT_STATUSID 0xEF14             // R/W
#define INTERRUPT_EVENT_NUMBER 0xEF18        // R/W
#define AGGREGATE_NUMBER_PER_BLT 0xEF1C      // R/W
#define SCRATCH 0xEF20                       // R/W
#define SOFTWARE_RESET 0xEF24                // W
#define SOFTWARE_CLEAR 0xEF28                // W
#define CONFIGURATION_RELOAD 0xEF34          // W

#define CHANNEL_MASK 0x1F00
#define CHANNEL_REGISTER_MASK 0x000000FF
#define INVALID_CHANNEL_VALUE -1
#define INVALID_CHANNEL_REGISTER_VALUE 0xFF
#define REGISTER_MASK 0x0000FFFF
#define INVALID_REGISTER_VALUE 0xFFFF

void v1725_loadConfiguration(int card);
int v1725_findChannel(uint32_t reg);
uint32_t v1725_findRegistersForChannel(uint32_t reg, int card, int channel);
uint32_t v1725_findRegister(uint32_t reg, int card);
void v1725_saveConfiguration(int card);

void V1725_read_reg(int card, long reg)
{
    long *v1725_ptr_tmp = (long *)((long)caen_base + (long)(card * CARDS_OFF) + reg);
    sprintf(c_line, "v1725 card %d register 0x%04x: 0x%08x		0x%08x\n", card, reg, v1725_ptr_tmp, *v1725_ptr_tmp);
    F_ERROR(ERR__MSG_INFO,0,c_line,l_pr_mask);
}

void V1725_write_reg(int card, long reg, long value)
{
    long *v1725_ptr_tmp = (long *)((long)caen_base + (long)(card * CARDS_OFF) + reg);
    *v1725_ptr_tmp = value;
    sprintf(c_line, "v1725 card %d register 0x%04x value: 0x%08x		0x%08x    0x%08x\n", card, reg, value, v1725_ptr_tmp, *v1725_ptr_tmp);
    F_ERROR(ERR__MSG_INFO, 0, c_line, l_pr_mask);
}

void V1725_boardAddress(int card)
{
    fprintf(CAEN_logfile, "v1725 board address: 0x%x\n", v1725_ptr[card]);
}

void V1725_boardInfo(int card)
{
    fprintf(CAEN_logfile, "v1725 board info: 0x%x	0x%04x\n", &(v1725_ptr[card]->board_info), v1725_ptr[card]->board_info);
}

void V1725_boardConfiguration(int card)
{
    fprintf(CAEN_logfile, "v1725 board configuration: 0x%x	0x%04x\n", &(v1725_ptr[card]->board_configuration), v1725_ptr[card]->board_configuration);
}

void V1725_acquisitionStatus(int card)
{
    fprintf(CAEN_logfile, "v1725 acquisition status: 0x%x	0x%04x\n", &(v1725_ptr[card]->acquisition_status), v1725_ptr[card]->acquisition_status);
}

void V1725_ROCFpgaFirmwareRevision(int card)
{
    fprintf(CAEN_logfile, "v1725 roc_fpga_firmware_revision: 0x%x	0x%04x\n", &(v1725_ptr[card]->roc_fpga_firmware_revision), v1725_ptr[card]->roc_fpga_firmware_revision);
}

void V1725_startAC(int card)
{
    v1725_ptr[card]->acquisition_control |= 4;
    fprintf(CAEN_logfile, "v1725 start ac2: 0x%x		0x%04x\n", &(v1725_ptr[card]->acquisition_control), v1725_ptr[card]->acquisition_control);
    sprintf(c_line, "v1725 start ac2: 0x%x		0x%04x\n", &(v1725_ptr[card]->acquisition_control), v1725_ptr[card]->acquisition_control);
    F_ERROR(ERR__MSG_INFO, 0, c_line, l_pr_mask);
}

void V1725_stopAC(int card)
{
    v1725_ptr[card]->acquisition_control &= ~4;
    fprintf(CAEN_logfile, "v1725 stop ac2: 0x%x		0x%04x\n", &(v1725_ptr[card]->acquisition_control), v1725_ptr[card]->acquisition_control);
    sprintf(c_line, "v1725 stop ac2: 0x%x		0x%04x\n", &(v1725_ptr[card]->acquisition_control), v1725_ptr[card]->acquisition_control);
    F_ERROR(ERR__MSG_INFO, 0, c_line, l_pr_mask);
}

void V1725_channel_enable_mask(int card, long val)
{
    v1725_ptr[card]->channel_enable_mask &= ~val;
    v1725_ptr[card]->channel_enable_mask |= val;
    fprintf(CAEN_logfile, "v1725 channel enable mask: 0x%x		0x%04x\n", &(v1725_ptr[card]->channel_enable_mask), v1725_ptr[card]->channel_enable_mask);
}

void V1725_AMC_firmware_revision(int card, int channel)
{
    if (card == 6)
    {
        fprintf(CAEN_logfile, "v1725 card 6 channel %d AMC firmware rev.: 0x%x		0x%04x\n", channel, &(v1725_ch_ptr_6[channel]->AMC_firmware_revision), v1725_ch_ptr_6[channel]->AMC_firmware_revision);
    }
}

void V1725_boardID(int card)
{
    v1725_EF_ptr[card]->board_ID = card;
    fprintf(CAEN_logfile, "v1725 board ID: 0x%x		0x%04x\n", &(v1725_EF_ptr[card]->board_ID), v1725_EF_ptr[card]->board_ID);
}

void V1725_softwareReset(int card)
{
    v1725_EF_ptr[card]->software_reset = 1;
    sprintf(c_line, "v1725 software reset card: %d\n", card);
    F_ERROR(ERR__MSG_INFO, 0, c_line, l_pr_mask);
    fprintf(CAEN_logfile, "v1725 software reset; card: %d\n", card);
}

void V1725_openFile()
{
    CAENfile = fopen(file_name, "w");
    if(!CAENfile)
    {
        printf("Error caen file!!\n");
    }
    CAEN_logfile = fopen(log_file_name, "w");
     if(!CAEN_logfile)
    {
        printf("Error CAEN logfile!!\n");
    }
}

void V1725_closeFile()
{
    fclose(CAENfile);
    fclose(CAEN_logfile);
}

void v1725_loadConfiguration(int card)
{
    FILE *lcfile;
    uint32_t readRegister, readValue;
    uint32_t channelRegister = INVALID_CHANNEL_REGISTER_VALUE;
    uint32_t reg = INVALID_REGISTER_VALUE;
    int channel = INVALID_CHANNEL_VALUE;

    lcfile = fopen("register_map.txt", "r");
    if (lcfile)
    {
        while (fscanf(lcfile, "%i %i", &readRegister, &readValue) != EOF)
        {
            channel = v1725_findChannel(readRegister);
            if (channel >= 0 && channel <= 15)
            {
                channelRegister = v1725_findRegistersForChannel(readRegister, card, channel);
                if (channelRegister != INVALID_CHANNEL_REGISTER_VALUE)
                {
                    fprintf(CAEN_logfile, "READ: 0x%08x		0x%08x\n", readRegister, readValue);
                    if (card == 6)
                    {
                        *(uint32_t*)channelRegister = readValue;
                        fprintf(CAEN_logfile, "addr/val 6: 0x%08x		0x%08x\n", channelRegister, readValue);
                    }
                    if (card == 7)
                    {
                        *(uint32_t*)channelRegister = readValue;
                        fprintf(CAEN_logfile, "addr/val 7: 0x%08x		0x%08x\n", channelRegister, readValue);
                    }
                }
            }
            reg = v1725_findRegister(readRegister, card);
            if (reg != INVALID_REGISTER_VALUE)
            {
                fprintf(CAEN_logfile, "READ reg: 0x%08x		0x%08x\n", readRegister, readValue);
                if (reg < V1725_EF_OFF)
                {
                    *(uint32_t*)reg = readValue;
                    fprintf(CAEN_logfile, "addr/val reg: 0x%08x		0x%08x\n", reg, readValue);
                }
                else
                {
                    *(uint32_t*)reg = readValue;
                    fprintf(CAEN_logfile, "addr/val EF_OFF: 0x%08x		0x%08x\n", reg, readValue);                  
                }
            }
            if (channelRegister == INVALID_CHANNEL_REGISTER_VALUE && reg == INVALID_REGISTER_VALUE)
                fprintf(CAEN_logfile, "Error %08x\n", readRegister);
        }
        fclose(lcfile);
    }
    else
    {
        fprintf(CAEN_logfile, "File 404 error...\n");
        sprintf(c_line, "File 404 error...\n");
        F_ERROR(ERR__MSG_INFO, 0, c_line, l_pr_mask);
    }
}

int v1725_findChannel(uint32_t reg)
{
    int channel = INVALID_CHANNEL_VALUE;
    switch (reg & CHANNEL_MASK)
    {
    case CHANNEL_0:
        channel = 0;
        break;
    case CHANNEL_1:
        channel = 1;
        break;
    case CHANNEL_2:
        channel = 2;
        break;
    case CHANNEL_3:
        channel = 3;
        break;
    case CHANNEL_4:
        channel = 4;
        break;
    case CHANNEL_5:
        channel = 5;
        break;
    case CHANNEL_6:
        channel = 6;
        break;
    case CHANNEL_7:
        channel = 7;
        break;
    case CHANNEL_8:
        channel = 8;
        break;
    case CHANNEL_9:
        channel = 9;
        break;
    case CHANNEL_A:
        channel = 10;
        break;
    case CHANNEL_B:
        channel = 11;
        break;
    case CHANNEL_C:
        channel = 12;
        break;
    case CHANNEL_D:
        channel = 13;
        break;
    case CHANNEL_E:
        channel = 14;
        break;
    case CHANNEL_F:
        channel = 15;
        break;
    default:
        channel = INVALID_CHANNEL_VALUE;
    }
    return channel;
}

uint32_t v1725_findRegistersForChannel(uint32_t reg, int card, int channel)
{
    uint32_t tmpReg = reg & CHANNEL_REGISTER_MASK;
    uint32_t retVal = INVALID_CHANNEL_REGISTER_VALUE;
    switch (tmpReg)
    {
    case RECORD_LENGTH:
        if(card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->record_length));
        // else if(card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->record_length));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case INPUT_DYNAMIC_RANGE:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->input_dynamic_range));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->input_dynamic_range));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case NUMBER_OF_EVENTS_PER_AGGREGATE:
    if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->number_of_events_per_aggregate));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->number_of_events_per_aggregate));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case PRE_TRIGGER:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->pre_trigger));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->pre_trigger));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case CFD_SETTINGS:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->CFD_settings));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->CFD_settings));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case FORCED_DATA_FLUSH: //write only, do not use during initial setup
        retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case CHARGE_ZERO_SUPPRESSION_THRESHOLD:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->charge_zero_suppression_threshold));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->charge_zero_suppression_threshold));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case SHORT_GATE_WIDTH:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->short_gate_width));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->short_gate_width));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case LONG_GATE_WIDTH:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->long_gate_width));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->long_gate_width));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case GATE_OFFSET:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->gate_offset));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->gate_offset));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case TRIGGER_THRESHOLD:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->trigger_threshold));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->trigger_threshold));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case FIXED_BASELINE:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->fixed_baseline));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->fixed_baseline));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case TRIGGER_LATENCY:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->trigger_latency));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->trigger_latency));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case SHAPED_TRIGGER_WIDTH:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->shaped_trigger_width));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->shaped_trigger_width));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case TRIGGER_HOLDOFF_WIDTH:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->trigger_holdoff_width));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->trigger_holdoff_width));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case THRESHOLD_FOR_THE_PSD_CUT:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->threshold_for_the_PSD_cut));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->threshold_for_the_PSD_cut));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case PUR_GAP_THRESHOLD:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->PUR_GAP_threshold));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->PUR_GAP_threshold));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;;
        break;
    case DPP_ALGORITHM_CONTROL:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->DPP_algorithm_control));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->DPP_algorithm_control));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case DPP_ALGORITHM_CONTROL_2:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->DPP_algorithm_control_2));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->DPP_algorithm_control_2));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case CHANNEL_STATUS: //read only
        retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case AMC_FIRMWARE_REVISION: //read only
        retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case DC_OFFSET:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->DC_offset));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->DC_offset));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case CHANNEL_ADC_TEMPERATURE: //read only
        retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case INDIVIDUAL_SOFTWARE_TRIGGER:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->individual_software_trigger));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->individual_software_trigger));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    case VETO_WIDTH:  //first enabled through 1n84(8084) DPP_ALGORITHM_CONTROL_2
        retVal = INVALID_CHANNEL_REGISTER_VALUE; //recommend for manually set
        break;
    case EARLY_BASELINE_FREEZE:
        if (card == 6)
            retVal = (uint32_t)(&(v1725_ch_ptr_6[channel]->early_baseline_freeze));
        // else if (card == 7)
        //     retVal = (uint32_t)(&(v1725_ch_ptr_7[channel]->early_baseline_freeze));
        else
            retVal = INVALID_CHANNEL_REGISTER_VALUE;
        break;
    default:
        retVal = INVALID_CHANNEL_REGISTER_VALUE;
    }
    return retVal;
}

uint32_t v1725_findRegister(uint32_t reg, int card)
{
    uint32_t tmpReg = reg & REGISTER_MASK;
    uint32_t retVal = INVALID_REGISTER_VALUE;
    switch (tmpReg)
    {
    case BOARD_CONFIGURATION:
        retVal = (uint32_t)(&(v1725_ptr[card]->board_configuration));
        break;
    case BOARD_CONFIGURATION_BITSET:
        retVal = (uint32_t)(&(v1725_ptr[card]->board_configuration_bitSet));
        break;
    case BOARD_CONFIGURATION_BITCLEAR:
        retVal = (uint32_t)(&(v1725_ptr[card]->board_configuration_bitClear));
        break;
    case AGGREGATE_ORGANIZATION:
        retVal = (uint32_t)(&(v1725_ptr[card]->aggregate_organization));
        break;
    case RECORD_LENGTH_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->record_length_broadcast));
        break;
    case INPUT_DYNAMIC_RANGE_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->input_dynamic_range_broadcast));
        break;
    case NUMBER_OF_EVENTS_PER_AGGREGATE_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->number_of_events_per_aggregate_broadcast));
        break;
    case PRE_TRIGGER_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->pre_trigger_broadcast));
        break;
    case CFD_SETTINGS_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->CFD_settings_broadcast));
        break;
    case FORCED_DATA_FLUSH_BROADCAST: //write only, do not use during initial setup
        retVal = INVALID_REGISTER_VALUE;
        break;
    case CHARGE_ZERO_SUPPRESSION_THRESHOLD_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->charge_zero_suppression_threshold_broadcast));
        break;
    case SHORT_GATE_WIDTH_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->short_gate_width_broadcast));
        break;
    case LONG_GATE_WIDTH_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->long_gate_width_broadcast));
        break;
    case GATE_OFFSET_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->gate_offset_broadcast));
        break;
    case TRIGGER_THRESHOLD_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_threshold_broadcast));
        break;
    case FIXED_BASELINE_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->fixed_baseline_broadcast));
        break;
    case TRIGGER_LATENCY_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_latency_broadcast));
        break;
    case SHAPED_TRIGGER_WIDTH_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->shaped_trigger_width_broadcast));
        break;
    case TRIGGER_HOLDOFF_WIDTH_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_holdoff_width_broadcast));
        break;
    case THRESHOLD_FOR_THE_PSD_CUT_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->threshold_for_the_PSD_cut_broadcast));
        break;
    case PUR_GAP_THRESHOLD_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->PUR_GAP_threshold_broadcast));
        break;
    case DPP_ALGORITHM_CONTROL_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->DPP_algorithm_control_broadcast));
        break;
    case DPP_ALGORITHM_CONTROL_2_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->DPP_algorithm_control_2_broadcast));
        break;
    case DC_OFFSET_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->DC_offset_broadcast));
        break;
    case CHANNEL_ADC_CALIBRATION:
        retVal = (uint32_t)(&(v1725_ptr[card]->channel_ADC_calibration));
        break;
    case CHANNELS_SHUTDOWN:
        retVal = (uint32_t)(&(v1725_ptr[card]->channels_shutdown));
        break;
    case INDIVIDUAL_SOFTWARE_TRIGGER_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->individual_software_trigger_broadcast));
        break;
    case EARLY_BASELINE_FREEZE_BROADCAST:
        retVal = (uint32_t)(&(v1725_ptr[card]->early_baseline_freeze_broadcast));
        break;
    case ACQUISITION_CONTROL:
        retVal = (uint32_t)(&(v1725_ptr[card]->acquisition_control));
        break;
    case ACQUISITION_STATUS: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case SOFTWARE_TRIGGER: //write only, do not use during initial setup
        retVal = INVALID_REGISTER_VALUE;
        break;
    case GLOBAL_MASK_TRIGGER:
        retVal = (uint32_t)(&(v1725_ptr[card]->global_mask_trigger));
        break;
    case FRONT_PANEL_TRGOUT_GPO_ENABLE_MASK:
        retVal = (uint32_t)(&(v1725_ptr[card]->front_panel_TRGOUT_GPO_enable_mask));
        break;
    case LVDS_IO_DATA:
        retVal = (uint32_t)(&(v1725_ptr[card]->LVDS_IO_data));
        break;
    case FRONT_PANEL_IO_CONTROL:
        retVal = (uint32_t)(&(v1725_ptr[card]->front_panel_io_control));
        break;
    case CHANNEL_ENABLE_MASK:
        retVal = (uint32_t)(&(v1725_ptr[card]->channel_enable_mask));
        break;
    case ROC_FPGA_FIRMWARE_REVISION: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case VOLTAGE_LEVEL_MODE_CONFIGURATION:
        retVal = (uint32_t)(&(v1725_ptr[card]->voltage_level_mode_configuration));
        break;
    case SOFTWARE_CLOCK_SYNC:
        retVal = (uint32_t)(&(v1725_ptr[card]->software_clock_sync));
        break;
    case BOARD_INFO: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case ANALOG_MONITOR_MODE:
        retVal = (uint32_t)(&(v1725_ptr[card]->analog_monitor_mode));
        break;
    case EVENT_SIZE: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case TIME_BOMB_DOWNCOUNTER: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case FAN_SPEED_CONTROL:
        retVal = (uint32_t)(&(v1725_ptr[card]->fan_speed_control));
        break;
    case RUN_START_STOP_DELAY:
        retVal = (uint32_t)(&(v1725_ptr[card]->run_start_stop_delay));
        break;
    case BOARD_FAILURE_STATUS: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case DISABLE_EXTERNAL_TRIGGER:
        retVal = (uint32_t)(&(v1725_ptr[card]->disable_external_trigger));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_0:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_0));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_1:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_1));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_2:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_2));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_3:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_3));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_4:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_4));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_5:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_5));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_6:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_6));
        break;
    case TRIGGER_VALIDATION_MASK_COUPLE_7:
        retVal = (uint32_t)(&(v1725_ptr[card]->trigger_validation_mask_couple_7));
        break;
    case FRONT_PANEL_LVDS_IO_NEW_FEATURES:
        retVal = (uint32_t)(&(v1725_ptr[card]->front_panel_lvds_io_new_features));
        break;
    case BUFFER_OCCUPANCY_GAIN:
        retVal = (uint32_t)(&(v1725_ptr[card]->buffer_occupancy_gain));
        break;
    case EXTENDED_VETO_DELAY:
        retVal = (uint32_t)(&(v1725_ptr[card]->extended_veto_delay));
        break;
    case READOUT_CONTROL:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->readout_control));
        break;
    case READOUT_STATUS: //read only
        retVal = INVALID_REGISTER_VALUE;
        break;
    case BOARD_ID:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->board_ID));
        break;
    case MCST_BASE_ADDRESS_AND_CONTROL:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->MCST_base_address_and_control));
        break;
    case RELOCATION_ADDRESS:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->relocation_address));
        break;
    case INTRRUPT_STATUSID:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->intrrupt_statusID));
        break;
    case INTERRUPT_EVENT_NUMBER:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->interrupt_event_number));
        break;
    case AGGREGATE_NUMBER_PER_BLT:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->aggregate_number_per_BLT));
        break;
    case SCRATCH:
        retVal = (uint32_t)(&(v1725_EF_ptr[card]->scratch));
        break;
    case SOFTWARE_RESET: //write only, do not use during initial setup
        retVal = INVALID_REGISTER_VALUE;
        break;
    case SOFTWARE_CLEAR: //write only, do not use during initial setup
        retVal = INVALID_REGISTER_VALUE;
        break;
    case CONFIGURATION_RELOAD: //write only, do not use during initial setup
        retVal = INVALID_REGISTER_VALUE;
        break;
    default:
        retVal = INVALID_REGISTER_VALUE;
    }
    return retVal;
}

void v1725_saveConfiguration(int card)
{
    FILE *sfile;
    int i;
    if (card == 6)
        sfile = fopen("log_reg_map_6.txt", "w");//'a' is just for test - should be 'w'
    if (card == 7)
        sfile = fopen("log_reg_map_7.txt", "w");
    if (sfile)
    {
        if (card == 6)
        {
            for (i = 0; i < NUMBER_OF_CHANNELS; i++)
            {
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->record_length), v1725_ch_ptr_6[i]->record_length);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->input_dynamic_range), v1725_ch_ptr_6[i]->input_dynamic_range);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->number_of_events_per_aggregate), v1725_ch_ptr_6[i]->number_of_events_per_aggregate);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->pre_trigger), v1725_ch_ptr_6[i]->pre_trigger);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->CFD_settings), v1725_ch_ptr_6[i]->CFD_settings);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->charge_zero_suppression_threshold), v1725_ch_ptr_6[i]->charge_zero_suppression_threshold);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->short_gate_width), v1725_ch_ptr_6[i]->short_gate_width);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->long_gate_width), v1725_ch_ptr_6[i]->long_gate_width);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->gate_offset), v1725_ch_ptr_6[i]->gate_offset);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->trigger_threshold), v1725_ch_ptr_6[i]->trigger_threshold);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->fixed_baseline), v1725_ch_ptr_6[i]->fixed_baseline);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->trigger_latency), v1725_ch_ptr_6[i]->trigger_latency);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->shaped_trigger_width), v1725_ch_ptr_6[i]->shaped_trigger_width);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->trigger_holdoff_width), v1725_ch_ptr_6[i]->trigger_holdoff_width);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->threshold_for_the_PSD_cut), v1725_ch_ptr_6[i]->threshold_for_the_PSD_cut);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->PUR_GAP_threshold), v1725_ch_ptr_6[i]->PUR_GAP_threshold);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->DPP_algorithm_control), v1725_ch_ptr_6[i]->DPP_algorithm_control);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->DPP_algorithm_control_2), v1725_ch_ptr_6[i]->DPP_algorithm_control_2);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->channel_status), v1725_ch_ptr_6[i]->channel_status);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->AMC_firmware_revision), v1725_ch_ptr_6[i]->AMC_firmware_revision);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->DC_offset), v1725_ch_ptr_6[i]->DC_offset);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->channel_ADC_temperature), v1725_ch_ptr_6[i]->channel_ADC_temperature);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->veto_width), v1725_ch_ptr_6[i]->veto_width);
                fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_6[i]->early_baseline_freeze), v1725_ch_ptr_6[i]->early_baseline_freeze);
            }
        }
        // else if (card == 7)
        //     for (i = 0; i < NUMBER_OF_CHANNELS; i++)
        //     {
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->record_length), v1725_ch_ptr_6[i]->record_length);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->input_dynamic_range), v1725_ch_ptr_6[i]->input_dynamic_range);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->number_of_events_per_aggregate), v1725_ch_ptr_6[i]->number_of_events_per_aggregate);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->pre_trigger), v1725_ch_ptr_6[i]->pre_trigger);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->CFD_settings), v1725_ch_ptr_6[i]->CFD_settings);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->charge_zero_suppression_threshold), v1725_ch_ptr_6[i]->charge_zero_suppression_threshold);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->short_gate_width), v1725_ch_ptr_6[i]->short_gate_width);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->long_gate_width), v1725_ch_ptr_6[i]->long_gate_width);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->gate_offset), v1725_ch_ptr_6[i]->gate_offset);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->trigger_threshold), v1725_ch_ptr_6[i]->trigger_threshold);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->fixed_baseline), v1725_ch_ptr_6[i]->fixed_baseline);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->trigger_latency), v1725_ch_ptr_6[i]->trigger_latency);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->shaped_trigger_width), v1725_ch_ptr_6[i]->shaped_trigger_width);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->trigger_holdoff_width), v1725_ch_ptr_6[i]->trigger_holdoff_width);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->threshold_for_the_PSD_cut), v1725_ch_ptr_6[i]->threshold_for_the_PSD_cut);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->PUR_GAP_threshold), v1725_ch_ptr_6[i]->PUR_GAP_threshold);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->DPP_algorithm_control), v1725_ch_ptr_6[i]->DPP_algorithm_control);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->DPP_algorithm_control_2), v1725_ch_ptr_6[i]->DPP_algorithm_control_2);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->channel_status), v1725_ch_ptr_6[i]->channel_status);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->AMC_firmware_revision), v1725_ch_ptr_6[i]->AMC_firmware_revision);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->DC_offset), v1725_ch_ptr_6[i]->DC_offset);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->channel_ADC_temperature), v1725_ch_ptr_6[i]->channel_ADC_temperature);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->veto_width), v1725_ch_ptr_6[i]->veto_width);
        //         fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ch_ptr_7[i]->early_baseline_freeze), v1725_ch_ptr_6[i]->early_baseline_freeze);
        //     }
        else
        {
            fprintf(CAEN_logfile, "unknown card error...");
        }
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->board_configuration), v1725_ptr[card]->board_configuration);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->aggregate_organization), v1725_ptr[card]->aggregate_organization);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->acquisition_control), v1725_ptr[card]->acquisition_control);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->acquisition_status), v1725_ptr[card]->acquisition_status);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->global_mask_trigger), v1725_ptr[card]->global_mask_trigger);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->front_panel_TRGOUT_GPO_enable_mask), v1725_ptr[card]->front_panel_TRGOUT_GPO_enable_mask);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->LVDS_IO_data), v1725_ptr[card]->LVDS_IO_data);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->front_panel_io_control), v1725_ptr[card]->front_panel_io_control);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->channel_enable_mask), v1725_ptr[card]->channel_enable_mask);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->roc_fpga_firmware_revision), v1725_ptr[card]->roc_fpga_firmware_revision);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->voltage_level_mode_configuration), v1725_ptr[card]->voltage_level_mode_configuration);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->board_info), v1725_ptr[card]->board_info);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->analog_monitor_mode), v1725_ptr[card]->analog_monitor_mode);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->event_size), v1725_ptr[card]->event_size);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->time_bomb_downcounter), v1725_ptr[card]->time_bomb_downcounter);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->fan_speed_control), v1725_ptr[card]->fan_speed_control);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->run_start_stop_delay), v1725_ptr[card]->run_start_stop_delay);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->board_failure_status), v1725_ptr[card]->board_failure_status);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->disable_external_trigger), v1725_ptr[card]->disable_external_trigger);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_0), v1725_ptr[card]->trigger_validation_mask_couple_0);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_1), v1725_ptr[card]->trigger_validation_mask_couple_1);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_2), v1725_ptr[card]->trigger_validation_mask_couple_2);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_3), v1725_ptr[card]->trigger_validation_mask_couple_3);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_4), v1725_ptr[card]->trigger_validation_mask_couple_4);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_5), v1725_ptr[card]->trigger_validation_mask_couple_5);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_6), v1725_ptr[card]->trigger_validation_mask_couple_6);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->trigger_validation_mask_couple_7), v1725_ptr[card]->trigger_validation_mask_couple_7);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->front_panel_lvds_io_new_features), v1725_ptr[card]->front_panel_lvds_io_new_features);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->buffer_occupancy_gain), v1725_ptr[card]->buffer_occupancy_gain);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_ptr[card]->extended_veto_delay), v1725_ptr[card]->extended_veto_delay);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->readout_control), v1725_EF_ptr[card]->readout_control);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->readout_status), v1725_EF_ptr[card]->readout_status);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->board_ID), v1725_EF_ptr[card]->board_ID);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->MCST_base_address_and_control), v1725_EF_ptr[card]->MCST_base_address_and_control);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->relocation_address), v1725_EF_ptr[card]->relocation_address);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->intrrupt_statusID), v1725_EF_ptr[card]->intrrupt_statusID);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->interrupt_event_number), v1725_EF_ptr[card]->interrupt_event_number);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->aggregate_number_per_BLT), v1725_EF_ptr[card]->aggregate_number_per_BLT);
        fprintf(sfile, "%d %04x  %04x\n", card, &(v1725_EF_ptr[card]->scratch), v1725_EF_ptr[card]->scratch);

        fclose(sfile);
    }
    else
    {
        fprintf(CAEN_logfile,"File 504 error...");
        sprintf(c_line, "File closed...\n");
        F_ERROR(ERR__MSG_INFO, 0, c_line, l_pr_mask);
    }
}
