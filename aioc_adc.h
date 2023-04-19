#ifndef  AIOC_ADC_H
#define AIOC_ADC_H

// MERCURY HEADER GOES HERE
// TBD

/**
 * @file:    aioc_adc.h
 * @author:  Russell Shahenian
 * @since:   4/4/23
 * @brief:   This file contains the public AIOC adc module specifications.
 */

#include "aioc_defs.h"
#include "aioc_i2c_gpio.h"
#include "aioc_util.h"


//================================
// Public specifications.
//================================

typedef enum
{
  AIOC_ADC_ID_5V,
  AIOC_ADC_ID_7V,
  AIOC_ADC_ID_95mV,
  AIOC_ADC_ID_RTD,
  AIOC_ADC_ID_EP10,
  
  NUMBER_OF_AIOC_ADC_IDS
}
aioc_adc_id_t;

typedef enum
{
  // AI Analog 0-5 VDC
  A5V_00_MON = 0,
  A5V_01_MON,
  A5V_02_MON,
  A5V_03_MON,
  A5V_04_MON,
  A5V_05_MON,
  A5V_06_MON,
  A5V_07_MON,
  A5V_08_MON,
  A5V_09_MON,
  A5V_10_MON,
  A5V_11_MON,
  A5V_12_MON
}
aioc_adc_input_t;

typedef void* aioc_adc_handle_t;

typedef enum
{
  AIOC_ADC_STATE_RESET = 0,
  AIOC_ADC_STATE_REGISTER_MODE = 1,
  AIOC_ADC_STATE_CONVERSION_MODE
}
aioc_adc_state_t;



/**
 * @struct ad469x_init_param
 * @brief  Structure containing the init parameters needed by the ad469x device
 */
struct ad469x_init_param {
	/* SPI */
	struct no_os_spi_init_param		*spi_init;
	/** RESET GPIO initialization structure. */
	struct no_os_gpio_init_param	*gpio_resetn;
	/** CONVST GPIO initialization parameters */
	struct no_os_gpio_init_param *gpio_convst;
	/** BUSY GPIO initialization parameters */
	struct no_os_gpio_init_param *gpio_busy;
	};

/**
 * @struct ad469x_dev
 * @brief  Structure representing an ad469x device
 */
struct ad469x_dev {
	/* SPI descriptor */
	struct no_os_spi_desc		*spi_desc;
	/** RESET GPIO handler. */
	struct no_os_gpio_desc	*gpio_resetn;
	/** CONVST GPIO descriptor */
	struct no_os_gpio_desc *gpio_convst;
	/** BUSY GPIO descriptor */
	struct no_os_gpio_desc *gpio_busy;
};



/**
 * Perform ADC self-check, configuration, and start conversion mode for
 * this ADC.  And return handle to this ADC.
 *
 * @param dev is the ADC device descriptor that is intialized passed back to
 *        the caller.
 *
 * @param adc_parm_init is the ADC parameter structure that helps
 *         to initialize the ADC device.
 *
 * @return error handling result code.
 */
aioc_error_t aioc_adc_init(
  struct ad469x_dev** device,
  struct ad469x_init_param* adc_parm_init);

/**
 * Perform a single-cycle mode adc conversion for for the specified input
 * on the ADC specified by the handle.
 *
 * @param dev is the ADC device descriptor.
 *
 * @param adc_input is the input on the ADC that's getting converted.
 *
 * @return error handling result code.
 */
aioc_error_t aioc_adc_convert_single_cycle(
  struct ad469x_dev* dev, 
  aioc_adc_input_t adc_input,
  uint16_t* result);


#endif  // AIOC_ADC_H
