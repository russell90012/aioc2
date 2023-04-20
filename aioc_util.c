//==============================================================================
//==============================================================================
#include "aioc_util.h"

#include "aioc_hw_sim.h"

#include <stdio.h>
#include <stdlib.h>


//==============================================================================
//==============================================================================
aioc_error_t aioc_util_delay_ns(uint32_t delay)
{
#ifdef AIOC_HW_SIM
  aioc_hw_sim_delay_ns(delay);
#endif

  // TBD

  return error_none;
}




//==============================================================================
//==============================================================================
aioc_error_t aioc_util_ultrascale_gpio_pulse_low(
  uint32_t convert_id, 
  uint32_t pulse_duration)
{
  // TBD
#ifdef  AIOC_DEBUG
printf("%s: convert_id [%d], duration [%d]\n", __FUNCTION__,
  convert_id, pulse_duration);
#endif
  
  return error_none;
}




//==============================================================================
//==============================================================================
 
aioc_error_t aioc_util_spi_init(
              struct no_os_spi_desc ** spi_desc,
              struct no_os_spi_init_param* parm)
{
  struct no_os_spi_desc* desc;

	desc = (struct no_os_spi_desc *)malloc(sizeof(*desc));
	if (!desc)  {  return error_alloc;  }

  desc->device_id = parm->device_id;
  desc->chip_select = parm->chip_select;
    
  // TBD
   
  return error_none;
}
  
//==============================================================================
//==============================================================================
 
aioc_error_t aioc_util_spi_remove(struct no_os_spi_desc* spi_desc)
{
  free(spi_desc);
  
  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_util_spi_transaction(
              struct no_os_spi_desc* spi_desc,
              uint8_t* data,
              uint32_t number_of_bytes)
{
#ifdef AIOC_HW_SIM
  aioc_hw_sim_spi_transaction(spi_desc->device_id, spi_desc->chip_select,
    data, number_of_bytes);
#endif
  // TBD
  
  return error_none;
}




//==============================================================================
//==============================================================================
aioc_error_t aioc_util_i2c_init(void** instance)
{
  if (!instance)  return  error_bad_param;
  
  *instance = 0;
  
  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_util_i2c_write(
  void* instance,
  uint32_t dev_adrs,
  uint32_t reg_adrs,
  uint8_t* data,
  uint32_t num_bytes)
{
#ifdef AIOC_HW_SIM
  aioc_hw_sim_i2c_write(dev_adrs, reg_adrs, data, num_bytes);
#endif
  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_util_i2c_read(
  void* instance,
  uint32_t dev_adrs,
  uint32_t reg_adrs,
  uint8_t* data,
  uint32_t num_bytes)
{
  return error_none;
}

