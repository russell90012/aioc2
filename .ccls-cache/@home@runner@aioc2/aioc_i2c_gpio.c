// MERCURY HEADER GOES HERE
// TBD

/**
 * @file:    aioc_i2c_gpio.h
 * @author:  Russell Shahenian
 * @since:   4/18/23
 * @brief:   This file contains the public AIOC I2C GPIO specifications.
 */

#include "aioc_defs.h"
#include "aioc_gpio.h"
#include "aioc_i2c_gpio.h"
#include "aioc_util.h"

#include <string.h>
#include <stdlib.h>



//==========================
// Private specifications.
//==========================

// The table below is based on the confugration table in the specification
// file (the header).
typedef struct
{
  uint32_t device_adrs;
  uint32_t device;
  uint32_t bank;
  uint32_t pin;
  uint32_t configuration;
  uint32_t polarity;
  uint32_t initial_value;
}
i2c_gpio_pin_conf_t;
    
static const i2c_gpio_pin_conf_t i2c_gpio_pin_configuration_table[] =
{
  {0X20, 0, 0, 0, 0, 0, 0},   // A5V_SW_BANK1_A0,
  {0X20, 0, 0, 1, 0, 0, 0},   // A5V_SW_BANK2_A0,
  {0X20, 0, 0, 2, 0, 0, 0},   // A5V_SW_BANK1_A1,
  {0X20, 0, 0, 3, 0, 0, 0},   // A5V_SW_BANK2_A1,
  {0X20, 0, 0, 4, 0, 0, 1},   // A5V_SW_BANK1_EN,
  {0X20, 0, 0, 5, 0, 0, 1},   // A5V_SW_BANK2_EN,
  {0X20, 0, 0, 6, 0, 0, 1},   // A5V_3V3_ADC_RESET_N,
  {0X20, 0, 0, 7, 1, 0, 0},   // A5V_3V3_ADC_BUSY,

  {0X20, 0, 1, 0, 0, 0, 0},   // A7V_SW_BANK1_A0,
  {0X20, 0, 1, 1, 0, 0, 0},   // A7V_SW_BANK2_A0,
  {0X20, 0, 1, 2, 0, 0, 0},   // A7V_SW_BANK1_A1,
  {0X20, 0, 1, 3, 0, 0, 0},   // A7V_SW_BANK2_A1,
  {0X20, 0, 1, 4, 0, 0, 1},   // A7V_SW_BANK1_EN,
  {0X20, 0, 1, 5, 0, 0, 1},   // A7V_SW_BANK2_EN,
  {0X20, 0, 1, 6, 0, 0, 1},   // A7V_3V3_ADC_RESET_N,
  {0X20, 0, 1, 7, 1, 0, 0},   // A7V_3V3_ADC_BUSY,


  {0X21, 1, 0, 0, 0, 0, 0},   // A95mV_SW_BANK1_A0,
  {0X21, 1, 0, 1, 0, 0, 0},   // A95mV_SW_BANK2_A0,
  {0X21, 1, 0, 2, 0, 0, 0},   // A95mV_SW_BANK1_A1,
  {0X21, 1, 0, 3, 0, 0, 0},   // A95mV_SW_BANK2_A1,
  {0X21, 1, 0, 4, 0, 0, 1},   // A95mV_SW_BANK1_EN,
  {0X21, 1, 0, 5, 0, 0, 1},   // A95mV_SW_BANK2_EN,
  {0X21, 1, 0, 6, 0, 0, 1},   // A95mV_3V3_ADC_RESET_N,
  {0X21, 1, 0, 7, 1, 0, 0},   // A95mV_3V3_ADC_BUSY,

  {0X21, 1, 1, 0, 0, 0, 0},   // ARTD_SW_A0,
  {0X21, 1, 1, 1, 0, 0, 0},   // ARTD_SW_A1,
  {0X21, 1, 1, 2, 0, 0, 1},   // ARTD_SW_EN,
  {0X21, 1, 1, 3, 0, 0, 1},   // ARTD_3V3_ADC_RESET_N,
  {0X21, 1, 1, 4, 1, 0, 0},   // ARTD_3V3_ADC_BUSY,
  {0X21, 1, 1, 5, 0, 0, 1},   // EP10V_3V3_ADC_RESET_N,
  {0X21, 1, 1, 6, 1, 0, 0},   // EP10V_3V3_ADC_BUSY,
  {0X21, 1, 1, 7, 1, 0, 0},   // NC_0, 


  {0X22, 2, 0, 0, 0, 0, 0},   // A10V_SW_A0,
  {0X22, 2, 0, 1, 0, 0, 0},   // A10V_SW_A1,
  {0X22, 2, 0, 2, 0, 0, 1},   // A10V_SW_EN,
  {0X22, 2, 0, 3, 1, 0, 0},   // A5V_ADC_PG,
  {0X22, 2, 0, 4, 1, 0, 0},   // A7V_ADC_PG,
  {0X22, 2, 0, 5, 1, 0, 0},   // A95mV_ADC_PG,
  {0X22, 2, 0, 6, 1, 0, 0},   // ARTD_ADC_PG,
  {0X22, 2, 0, 7, 1, 0, 0},   // EP10V_ADC_PG,

  {0X22, 2, 1, 0, 0, 0, 0},   // AZ_EL_SW_A0,
  {0X22, 2, 1, 1, 0, 0, 0},   // AZ_EL_SW_A1,
  {0X22, 2, 1, 2, 0, 0, 1},   // AZ_EL_SW_EN,
  {0X22, 2, 1, 3, 0, 0, 1},   // RTD_EXC_00_OFF_ON_N,
  {0X22, 2, 1, 4, 0, 0, 1},   // RTD_EXC_01_OFF_ON_N,
  {0X22, 2, 1, 5, 0, 0, 1},   // RTD_EXC_02_OFF_ON_N,
  {0X22, 2, 1, 6, 0, 0, 1},   // RTD_EXC_03_OFF_ON_N,
  {0X22, 2, 1, 7, 0, 0, 1},   // RTD_EXC_04_OFF_ON_N,



  {0x23, 3, 0, 0, 0, 0, 0},   // EP10V_00_EN,
  {0x23, 3, 0, 1, 0, 0, 0},   // EP10V_01_EN,
  {0x23, 3, 0, 2, 0, 0, 0},   // EP10V_02_EN,
  {0x23, 3, 0, 3, 0, 0, 0},   // EP10V_03_EN,
  {0x23, 3, 0, 4, 0, 0, 0},   // EP10V_04_EN,
  {0x23, 3, 0, 5, 0, 0, 0},   // EP10V_05_EN,
  {0x23, 3, 0, 6, 0, 0, 0},   // EP10V_06_EN,
  {0x23, 3, 0, 7, 0, 0, 0},   // EP10V_07_EN,
                           // 
  {0x23, 3, 1, 0, 0, 0, 0},   // EP10V_08_EN,
  {0x23, 3, 1, 1, 0, 0, 0},   // EP10V_09_EN,
  {0x23, 3, 1, 2, 0, 0, 0},   // EP10V_10_EN,
  {0x23, 3, 1, 3, 0, 0, 0},   // EP10V_11_EN,
  {0x23, 3, 1, 4, 0, 0, 0},   // P10V_POWER_EN,  
  {0x23, 3, 1, 5, 1, 0, 0},   // NC_1,      
  {0x23, 3, 1, 6, 1, 0, 0},   // NC_2,      
  {0x23, 3, 1, 7, 1, 0, 0},   // NC_3,      


  {0X24, 4, 0, 0, 1, 0, 0},   // EP10V_00_PG_N,
  {0X24, 4, 0, 1, 1, 0, 0},   // EP10V_01_PG_N,
  {0X24, 4, 0, 2, 1, 0, 0},   // EP10V_02_PG_N,
  {0X24, 4, 0, 3, 1, 0, 0},   // EP10V_03_PG_N,
  {0X24, 4, 0, 4, 1, 0, 0},   // EP10V_04_PG_N,
  {0X24, 4, 0, 5, 1, 0, 0},   // EP10V_05_PG_N,
  {0X24, 4, 0, 6, 1, 0, 0},   // EP10V_06_PG_N,
  {0X24, 4, 0, 7, 1, 0, 0},   // EP10V_07_PG_N,
                           // 
  {0X24, 4, 1, 0, 1, 0, 0},   // EP10V_08_PG_N,
  {0X24, 4, 1, 1, 1, 0, 0},   // EP10V_09_PG_N,
  {0X24, 4, 1, 2, 1, 0, 0},   // EP10V_10_PG_N,
  {0X24, 4, 1, 3, 1, 0, 0},   // EP10V_11_PG_N,
  {0X24, 4, 1, 4, 1, 0, 0},   // P10V_PG_0,     
  {0X24, 4, 1, 5, 1, 0, 0},   // P10V_PG_1,     
  {0X24, 4, 1, 6, 1, 0, 0},   // NC_4,         
  {0X24, 4, 1, 7, 1, 0, 0},   // NC_5,         


  {0X25, 5, 0, 0, 1, 0, 0},   // EP10V_00_FLG_N,
  {0X25, 5, 0, 1, 1, 0, 0},   // EP10V_01_FLG_N,
  {0X25, 5, 0, 2, 1, 0, 0},   // EP10V_02_FLG_N,
  {0X25, 5, 0, 3, 1, 0, 0},   // EP10V_03_FLG_N,
  {0X25, 5, 0, 4, 1, 0, 0},   // EP10V_04_FLG_N,
  {0X25, 5, 0, 5, 1, 0, 0},   // EP10V_05_FLG_N,
  {0X25, 5, 0, 6, 1, 0, 0},   // EP10V_06_FLG_N,
  {0X25, 5, 0, 7, 1, 0, 0},   // EP10V_07_FLG_N,

  {0X25, 5, 1, 0, 1, 0, 0},   // EP10V_08_FLG_N,
  {0X25, 5, 1, 1, 1, 0, 0},   // EP10V_09_FLG_N,
  {0X25, 5, 1, 2, 1, 0, 0},   // EP10V_10_FLG_N,
  {0X25, 5, 1, 3, 1, 0, 0},   // EP10V_11_FLG_N,
  {0X25, 5, 1, 4, 1, 0, 0},   // NC_6,       
  {0X25, 5, 1, 5, 1, 0, 0},   // NC_7,       
  {0X25, 5, 1, 6, 1, 0, 0},   // NC_8,       
  {0X25, 5, 1, 7, 1, 0, 0},   // NC_9,       
};

static const uint32_t i2c_gpio_pin_configuration_table_length  =
  sizeof(i2c_gpio_pin_configuration_table)/
  sizeof(*i2c_gpio_pin_configuration_table);


// The i2c GPIO register map (along with addresses).
/**********
Control Register and Command Byte

CONTROL REGISTER BITS   COMMAND
B2  B1  B0              BYTE    REGISTER        PROTOCOL          POWER-UP
0   0   0               0x00    Input Bank 0    Read byte         xxxx xxxx
0   0   1               0x01    Input Bank 1    Read byte         xxxx xxxx
0   1   0               0x02    Output Bank 0   Read-write byte   1111 1111
0   1   1               0x03    Output Bank 1   Read-write byte   1111 1111
1   0   0               0x04    Polarity 
                                Inversion 
                                Bank 0          Read-write byte   0000 0000
1   0   1               0x05    Polarity
                                Inversion 
                                Bank 1          Read-write byte   0000 0000
1   1   0               0x06    Configuration 
                                Bank 0          Read-write byte   1111 1111
1   1   1               0x07    Configuration
                                Bank 1          Read-write byte   1111 1111
**********/
#define NUM_BANKS         2
#define NUM_DEVICES       6
#define DEVICE_ADRS_BASE  0x20


// Commands used to write to registers (basically addresses).
enum
{
  COMMAND_BYTE_OUTPUT_0 = 2,
  COMMAND_BYTE_OUTPUT_1,
  COMMAND_BYTE_POLARITY_0,
  COMMAND_BYTE_POLARITY_1,
  COMMAND_BYTE_CONFIG_0,
  COMMAND_BYTE_CONFIG_1
};




//================================
// Private  definitions.
//================================

//==============================================================================
//==============================================================================
static aioc_error_t
aioc_i2c_gpio_register_read(
  void* instance,
  uint32_t device_address,
  uint32_t command_byte,
  uint8_t* reg_val)
{
  aioc_error_t  e = 0;

  e = aioc_util_i2c_read(instance, device_address, command_byte, reg_val, 1);
  if (e)  {  return e;  }
  
  return error_none;
}


static aioc_error_t
aioc_i2c_gpio_register_write(
  void* instance,
  uint32_t device_address,
  uint32_t command_byte,
  uint8_t reg_val)
{
  aioc_error_t  e = 0;

  e = aioc_util_i2c_write(instance, device_address, command_byte, &reg_val, 1);
  if (e)  {  return e;  }
  
  return error_none;
}


//==============================================================================
//==============================================================================
/**
 * @brief Prepare the GPIO decriptor.
 * @param desc - The GPIO descriptor.
 * @param param - The structure that contains the GPIO parameters.
 * @return 0 in case of success, -1 otherwise.
 */
static int32_t _gpio_init(
  struct no_os_gpio_desc *desc,
	const struct no_os_gpio_init_param *param)
{
	int32_t				ret;
	struct aioc_i2c_gpio_desc		    *xdesc;
	struct aioc_i2c_gpio_init_param	*xinit;

	xdesc = desc->extra;
	xinit = param->extra;

	desc->number = param->number;

  aioc_util_i2c_init(&xdesc->instance);
  
	return 0;
}




//================================
// Public  definitions.
//================================

/**
 * @brief Obtain the GPIO decriptor.
 * @param desc - The GPIO descriptor.
 * @param param - GPIO initialization parameters
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_get(struct no_os_gpio_desc **desc,
		     const struct no_os_gpio_init_param *param)
{
	struct no_os_gpio_desc	*descriptor;
	struct aioc_i2c_gpio_desc	*extra;
	int32_t			ret;

	descriptor = (struct no_os_gpio_desc *)malloc(sizeof(*descriptor));
	extra = (struct aioc_i2c_gpio_desc*)malloc(sizeof(*extra));

	if (!descriptor || !extra)
		return -1;

	descriptor->extra = extra;
	ret = _gpio_init(descriptor, param);

	if(ret != 0)
		goto error;

	*desc = descriptor;

	return 0;
  
error:
	free(extra);
	free(descriptor);

	return -1;
}

/**
 * @brief Get the value of an optional GPIO.
 * @param desc - The GPIO descriptor.
 * @param param - GPIO Initialization parameters.
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_get_optional(struct no_os_gpio_desc **desc,
			      const struct no_os_gpio_init_param *param)
{
	if(param == NULL) {
		*desc = NULL;
		return 0;
	}

	return aioc_i2c_gpio_get(desc, param);
}

/**
 * @brief Free the resources allocated by no_os_gpio_get().
 * @param desc - The GPIO descriptor.
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_remove(struct no_os_gpio_desc *desc)
{
	if (desc != NULL) {
	  struct aioc_i2c_gpio_desc* xdesc = desc->extra;
	  free(xdesc->instance);
		free(desc->extra);
		free(desc);
	}

	return 0;
}

/**
 * @brief Enable the input direction of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_direction_input(struct no_os_gpio_desc *desc)
{
  aioc_error_t e;
	struct aioc_i2c_gpio_desc	*extra = desc->extra;
  const i2c_gpio_pin_conf_t*  pin_conf = &i2c_gpio_pin_configuration_table[desc->number];
  uint32_t              device_adrs = pin_conf->device_adrs;
  uint32_t              bank = pin_conf->bank;
  uint32_t              pin = pin_conf->pin;
	uint8_t               reg_val;
  
  // Get the configuration register value for this pin configuration.
  e = aioc_i2c_gpio_register_read(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_CONFIG_0 + bank,
        &reg_val);

  // Set the direction as output for this pin.
	reg_val |= (1 << pin);

  // Set the configuration register value for this pin configuration.
  e = aioc_i2c_gpio_register_write(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_CONFIG_0 + bank,
        reg_val);

	return 0;
}


/**
 * @brief Enable the output direction of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param value - The value.
 *                Example: NO_OS_GPIO_HIGH
 *                         NO_OS_GPIO_LOW
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_direction_output(struct no_os_gpio_desc *desc,
				  uint8_t value)
{
  aioc_error_t e;
	struct aioc_i2c_gpio_desc	*extra = desc->extra;
  const i2c_gpio_pin_conf_t*  pin_conf = &i2c_gpio_pin_configuration_table[desc->number];
  uint32_t              device_adrs = pin_conf->device_adrs;
  uint32_t              bank = pin_conf->bank;
  uint32_t              pin = pin_conf->pin;
	uint8_t               reg_val;
  
  // Get the configuration register value for this pin configuration.
  e = aioc_i2c_gpio_register_read(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_CONFIG_0 + bank,
        &reg_val);

  // Set the direction as output for this pin.
	reg_val &= ~(1 << pin);

  // Set the configuration register value for this pin configuration.
  e = aioc_i2c_gpio_register_write(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_CONFIG_0 + bank,
        reg_val);

  // Get the output register value for this pin configuration.
  e = aioc_i2c_gpio_register_read(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_OUTPUT_0 + bank,
        &reg_val);

  // Set the value  as given for this pin.
	if (value)
		reg_val |= (1 << pin);
  else
    reg_val &= ~(1 << pin);
  
  // Set the output register value for this pin configuration.
  e = aioc_i2c_gpio_register_write(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_OUTPUT_0 + bank,
        reg_val);

	return 0;
}


/**
 * @brief Get the direction of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param direction - The direction.
 *                    Example: NO_OS_GPIO_OUT
 *                             NO_OS_GPIO_IN
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_get_direction(struct no_os_gpio_desc *desc,
			       uint8_t *direction)
{
  return 0;
}

/**
 * @brief Set the value of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param value - The value.
 *                Example: NO_OS_GPIO_HIGH
 *                         NO_OS_GPIO_LOW
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_set_value(struct no_os_gpio_desc *desc,
			   uint8_t value)
{
  aioc_error_t e;
	struct aioc_i2c_gpio_desc	*extra = desc->extra;
  const i2c_gpio_pin_conf_t*  pin_conf = &i2c_gpio_pin_configuration_table[desc->number];
  uint32_t              device_adrs = pin_conf->device_adrs;
  uint32_t              bank = pin_conf->bank;
  uint32_t              pin = pin_conf->pin;
	uint8_t               reg_val;
  
   // Get the output register value for this pin configuration.
  e = aioc_i2c_gpio_register_read(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_OUTPUT_0 + bank,
        &reg_val);

  // Set the value  as given for this pin.
	if (value)
		reg_val |= (1 << pin);
  else
    reg_val &= ~(1 << pin);
  
  // Set the output register value for this pin configuration.
  e = aioc_i2c_gpio_register_write(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_OUTPUT_0 + bank,
        reg_val);

	return 0;
}


/**
 * @brief Get the value of the specified GPIO.
 * @param desc - The GPIO descriptor.
 * @param value - The value.
 *                Example: NO_OS_GPIO_HIGH
 *                         NO_OS_GPIO_LOW
 * @return 0 in case of success, -1 otherwise.
 */
int32_t aioc_i2c_gpio_get_value(struct no_os_gpio_desc *desc,
			   uint8_t *value)
{
  aioc_error_t e;
	struct aioc_i2c_gpio_desc	*extra = desc->extra;
  const i2c_gpio_pin_conf_t*  pin_conf = &i2c_gpio_pin_configuration_table[desc->number];
  uint32_t              device_adrs = pin_conf->device_adrs;
  uint32_t              bank = pin_conf->bank;
  uint32_t              pin = pin_conf->pin;
	uint8_t               reg_val;
  
   // Get the output register value for this pin configuration.
  e = aioc_i2c_gpio_register_read(
        extra->instance,
        device_adrs,
        COMMAND_BYTE_OUTPUT_0 + bank,
        &reg_val);

  // Get the value as given for this pin.
	*value = (reg_val >> pin) & 0x01;
  
	return 0;
}




/**
 * @brief AIOC platform specific GPIO platform ops structure
 */
const struct no_os_gpio_platform_ops aioc_i2c_gpio_ops = {
	.gpio_ops_get = &aioc_i2c_gpio_get,
	.gpio_ops_get_optional = &aioc_i2c_gpio_get_optional,
	.gpio_ops_remove = &aioc_i2c_gpio_remove,
	.gpio_ops_direction_input = &aioc_i2c_gpio_direction_input,
	.gpio_ops_direction_output = &aioc_i2c_gpio_direction_output,
	.gpio_ops_get_direction = &aioc_i2c_gpio_get_direction,
	.gpio_ops_set_value = &aioc_i2c_gpio_set_value,
	.gpio_ops_get_value = &aioc_i2c_gpio_get_value,
};








