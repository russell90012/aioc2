// MERCURY HEADER GOES HERE
// TBD

#include "aioc.h"
#include "aioc_adc.h"
#include "no_os_gpio.h"
#include "no_os_i2c.h"
#include "aioc_tca9555.h"
#include "aioc_i2c.h"
#include "xilinx_gpio.h"
#include "aioc_mux.h"


//==========================
// Private specifications.
//==========================

/**
 * Map the aioc analog input id to an adc device handle and an adc input.
 *
 * @param analog_id is the analog input that gets mapped to the adc handle
 *        and adc input.
 *
 * @param adc_handle is how the handle is returned to the caller.
 *
 * @param adc_input is how the adc input is returned to the caller.
 *
 * @return error handling result code.
 */
static aioc_error_t map_ai_to_adc_handle_and_input(
        aioc_analog_id_t analog_id,
        struct ad469x_dev** dev,
        aioc_adc_input_t* adc_input);
    
static struct ad469x_dev* aioc_adc_dev_5v = 0;
static struct aioc_mux_bank_dev *aioc_mux_bank_desc_5v_1 = 0;
static struct aioc_mux_bank_dev *aioc_mux_bank_desc_5v_2 = 0;

static aioc_error_t aioc_adc_device_create_5v(struct ad469x_dev **dev);
static aioc_error_t aioc_mux_bank_create_5v_1(struct aioc_mux_bank_dev **dev);
static aioc_error_t aioc_mux_bank_create_5v_2(struct aioc_mux_bank_dev **dev);

//==========================
//==========================
//==========================
//==========================


//================================
// Public  definitions.
//================================

//==============================================================================
//==============================================================================
aioc_error_t 
aioc_init(void)
{
  aioc_error_t e = error_none;

 // Create the 5V ADC device.
  e = aioc_adc_device_create_5v(&aioc_adc_dev_5v);
  if (e)  {  return e;  }

  // Create  5V mux bank device and set to external inputs for banks 1 and 2.
  e = aioc_mux_bank_create_5v_1(&aioc_mux_bank_desc_5v_1);
  if (e)  {  return e;  }
  e = aioc_mux_bank_create_5v_2(&aioc_mux_bank_desc_5v_2);
  if (e)  {  return e;  }

  return error_none;
}


//==============================================================================
//==============================================================================
aioc_error_t 
aioc_analog_input_conversion(aioc_analog_id_t analog_id, uint16_t* result)
{
  aioc_error_t e = error_none;

  struct ad469x_dev* dev = 0;
  aioc_adc_input_t adc_input = 0;
  
  e = map_ai_to_adc_handle_and_input(analog_id, &dev, &adc_input);
  if (e)  {  return e;  }      

  e = aioc_adc_convert_single_cycle(dev, adc_input, result);
  if (e)  {  return e;  }     

  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_banks_set_external_5v()
{
  aioc_error_t e;
  
  e = aioc_mux_bank_set_external(aioc_mux_bank_desc_5v_1);
  if (e)  {  return e;  }
    
  e = aioc_mux_bank_set_external(aioc_mux_bank_desc_5v_2);
  if (e)  {  return e;  }
    
  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_banks_set_high_5v()
{
  aioc_error_t e;
  
  e = aioc_mux_bank_set_bit_high(aioc_mux_bank_desc_5v_1);
  if (e)  {  return e;  }
    
  e = aioc_mux_bank_set_bit_high(aioc_mux_bank_desc_5v_2);
  if (e)  {  return e;  }
    
  return error_none;
}

///==============================================================================
//==============================================================================
aioc_error_t aioc_mux_banks_set_low_5v()
{
  aioc_error_t e;
  
  e = aioc_mux_bank_set_bit_low(aioc_mux_bank_desc_5v_1);
  if (e)  {  return e;  }
    
  e = aioc_mux_bank_set_bit_low(aioc_mux_bank_desc_5v_2);
  if (e)  {  return e;  }
    
  return error_none;
}

///================================
// Private definitions.
//================================
// TBD
const int tbd = 0;

//==============================================================================
//==============================================================================
static aioc_error_t aioc_adc_device_create_5v(struct ad469x_dev **dev)
{  
  aioc_error_t e;
    
  
  // convst_line
  struct no_os_i2c_init_param  aioc_i2c_convst_line = 
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
 };

	struct no_os_gpio_init_param ad469x_convst =
  {
		.port = tbd,
    .number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_convst_line
	};

	
  // A5V_3V3_ADC_RESET_N,
  struct no_os_i2c_init_param  aioc_i2c_reset_n_line =
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param ad469x_resetn =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_reset_n_line
	};
  
  // A5V_3V3_ADC_busy,
  struct no_os_i2c_init_param  aioc_i2c_busy_line =
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
  };

  struct no_os_gpio_init_param ad469x_busy =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_busy_line
	};

  
  struct no_os_spi_init_param spi_init =
  {
  	.chip_select = 0,
    .device_id = 0
  };
  
  
  struct ad469x_init_param ad469x_init_param =
  {
  	.spi_init = &spi_init,
  	.gpio_resetn = &ad469x_resetn,
    .gpio_convst = &ad469x_convst,
    .gpio_busy = &ad469x_busy
  };
  
  e = aioc_adc_init(dev, &ad469x_init_param);
  if (e)  {  return e;  }

  return error_none;
}

//==============================================================================
//==============================================================================
static aioc_error_t aioc_mux_bank_create_5v_1(struct aioc_mux_bank_dev **dev)
{  
  aioc_error_t e;
  
  // A5V_SW_BANK1_EN,    
  struct no_os_i2c_init_param  aioc_i2c_en_line =
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param en_line =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_en_line
	};

  // A5V_SW_BANK1_A0,  
  struct no_os_i2c_init_param  aioc_i2c_a0_line =
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param a0_line =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_a0_line
	};
  
 // A5V_SW_BANK1_A1
  struct no_os_i2c_init_param  aioc_i2c_a1_line =
  {
    .slave_address = tbd, 
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param a1_line =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_a1_line
	};

  
  struct aioc_mux_bank_init_param aioc_mux_bank_init_param =
  {
  	.en_line = &en_line,
    .a0_line = &a0_line,
    .a1_line = &a1_line
  };
  
  e = aioc_mux_bank_init(dev, &aioc_mux_bank_init_param);
  if (e)  {  return e;  }

  return error_none;
}

//==============================================================================
//==============================================================================
static aioc_error_t aioc_mux_bank_create_5v_2(struct aioc_mux_bank_dev **dev)
{  
  aioc_error_t e;
    
  // A5V_SW_BANK2_EN,    
  struct no_os_i2c_init_param  aioc_i2c_en_line =
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param en_line =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_en_line
	};

  // A5V_SW_BANK2_A0,  
  struct no_os_i2c_init_param  aioc_i2c_a0_line =
  {
    .slave_address = tbd,
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param a0_line =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_a0_line
	};
  
 // A5V_SW_BANK2_A1
  struct no_os_i2c_init_param  aioc_i2c_a1_line =
  {
    .slave_address = tbd, 
 		.platform_ops = &aioc_i2c_ops,
  };

	struct no_os_gpio_init_param a1_line =
  {
		.port = tbd,
		.number = tbd,
		.platform_ops = &aioc_tca9555_ops,
		.extra = &aioc_i2c_a1_line
	};

  
 struct aioc_mux_bank_init_param aioc_mux_bank_init_param =
  {
  	.en_line = &en_line,
    .a0_line = &a0_line,
    .a1_line = &a1_line
  };
  
  e = aioc_mux_bank_init(dev, &aioc_mux_bank_init_param);
  if (e)  {  return e;  }

  return error_none;
}

//==============================================================================
//==============================================================================
static aioc_error_t
map_ai_to_adc_handle_and_input(
    aioc_analog_id_t analog_id,
    struct ad469x_dev** device,
    aioc_adc_input_t* adc_input)
{
  aioc_error_t e = error_none;
  aioc_adc_input_t input = 0;
  struct ad469x_dev* dev = 0;

  switch(analog_id)
  { 
    // AI Analog 0-5 VDC
    case AIOC_AI_LEFT_FWD_OVER_PRESSURE_SENSOR:
      input = A5V_00_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    case AIOC_AI_LEFT_AFT_OVER_PRESSURE_SENSOR:
      input = A5V_01_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    case AIOC_AI_RIGHT_FWD_OVER_PRESSURE_SENSOR:
      input = A5V_02_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    case AIOC_AI_RIGHT_AFT_OVER_PRESSURE_SENSOR:
      input = A5V_03_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    // NOT DOING THESE FOR NOW
    // OBIGGS_INLET_AIR_TEMP_SENSOR  = A5V_04_MON;
    // OBIGGS_INLET_AIR_PRESSURE_SENSOR  = A5V_05_MON;
    // OBIGGS_NEA_OUTLET_PRESSURE_SENSOR  = A5V_06_MON;

    case AIOC_AI_AFT_RIGHT_FEEDPIPE_PRESSURE_SENSOR:
      input = A5V_07_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    case AIOC_AI_FWD_LEFT_FEEDPIPE_PRESSURE_SENSOR:
      input = A5V_08_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    case AIOC_AI_AFT_LEFT_FEEDPIPE_PRESSURE_SENSOR:
      input = A5V_09_MON;
      dev = aioc_adc_dev_5v;
      break;
    
    case AIOC_AI_FWD_RIGHT_FEEDPIPE_PRESSURE_SENSOR:
      input = A5V_10_MON;
      dev = aioc_adc_dev_5v;
      break;

    // NOT DOING THESE FOR NOW
    //A5V_SPARE_1                         = A5V_11_MON
    //A5V_SPARE_2                       = A5V_12_MON;
    
#if  0
    // AI Analog 0-7 VDC
    case AIOC_AI_PROBE1_RIGHT_FWD_FUEL_QUANTITY:
    
    case AIOC_AI_PROBE1_LEFT_AFT_FUEL_QUANTITY:
    
    case AIOC_AI_PROBE1_RIGHT_AFT_FUEL_QUANTITY:
    
    case AIOC_AI_PROBE2_LEFT_FWD_FUEL_QUANTITY:
    
    case AIOC_AI_PROBE2_RIGHT_FWD_FUEL_QUANTIT:
    
    case AIOC_AI_PROBE2_LEFT_AFT_FUEL_QUANTITY:
    
    case AIOC_AI_PROBE2_RIGHT_AFT_FUEL_QUANTITY:
    
    // AI Analog 95 mVDC
    case AIOC_AI_IGB_OIL_FILTER_DELTA_P:
    
    case AIOC_AI_IGB_MANIFOLD_OIL_PRESSURE:
    
    case AIOC_AI_MGB_OIL_FILTER_DELTA_P:
    
    case AIOC_AI_MGB_MANIFOLD_OIL_PRESSURE:
    
    case AIOC_AI_TGB_OIL_FILTER_DELTA_P:
    
    case AIOC_AI_TGB_MANIFOLD_OIL_PRESSURE:
    
    case AIOC_AI_NGB1_OIL_FILTER_DELTA_P:
    
    case AIOC_AI_NGB1_MANIFOLD_OIL_PRESSURE:
    
    case AIOC_AI_NGB3_MANIFOLD_OIL_FILTER_DELTA_P:
    
    case AIOC_AI_NGB3_MANIFOLD_OIL_PRESSURE:
  
    // AI Analog 350-800Ohms
    case AIOC_AI_IGB_MANIFOLD_OIL_FILTER_TEMPERATURE:
    
    case AIOC_AI_MGB_OIL_FILTER_TEMPERATURE:
    
    case AIOC_AI_TGB_MANIFOLD_OIL_TEMPERATURE:
    
    case AIOC_AI_NGB1_OIL_FILTER_TEMPERATURE:
    
    case AIOC_AI_NGB3_OIL_FILTER_TEMPERATURE:
#endif
    
    default:
      e = error_ai_mapping;
      return e;
    }
  
  *adc_input = input;
  *device = dev;

  return error_none;
}
  



#if 0
//==============================================================================
//==============================================================================
aioc_error_t aioc_ext10_power_disable(void)
{
  // Setup EXT10 Power enable low.
  
  return error_none;
} 
  
//==============================================================================
//==============================================================================
aioc_error_t aioc_ep10_all_disable(void)
{
  // Setup all EP10 enable lines low.
  
  return error_none;
}  




//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_enable_all(void)
{
  // Setup all of the mux enable lines high.
  
  return error_none;
}


//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_select_input_all(void)
{
  // Setup all mux source address lines low.
  
  return error_none;
}
#endif
