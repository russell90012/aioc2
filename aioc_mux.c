// MERCURY HEADER GOES HERE
// TBD

#include "aioc_defs.h"
#include "aioc_mux.h"
#include "aioc_tca9555.h"


//================================
// Public  definitions.
//================================

//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_bank_init(
  struct aioc_mux_bank_dev** device,
  struct aioc_mux_bank_init_param* aioc_mux_bank_init)
{
  struct aioc_mux_bank_dev* dev = 0;
	int32_t ret;

  // TBD
  dev = malloc(sizeof(*dev));
	if (!dev)
  {
    return error_alloc;
  }
  
  ret = no_os_gpio_get_optional(&dev->en_line, aioc_mux_bank_init->en_line);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->en_line, NO_OS_GPIO_HIGH);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_get_optional(&dev->a0_line, aioc_mux_bank_init->a0_line);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a0_line, NO_OS_GPIO_LOW);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_get_optional(&dev->a1_line, aioc_mux_bank_init->a1_line);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a1_line, NO_OS_GPIO_LOW);
	if (ret != 0)
		return ret;

  *device = dev;

  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_bank_set_external(struct aioc_mux_bank_dev* dev)
{
	int32_t ret;

  ret = no_os_gpio_direction_output(dev->en_line, NO_OS_GPIO_HIGH);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a0_line, NO_OS_GPIO_LOW);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a1_line, NO_OS_GPIO_LOW);
	if (ret != 0)
		return ret;

  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_bank_set_bit_high(struct aioc_mux_bank_dev* dev)
{
	int32_t ret;

  ret = no_os_gpio_direction_output(dev->en_line, NO_OS_GPIO_HIGH);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a0_line, NO_OS_GPIO_LOW);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a1_line, NO_OS_GPIO_HIGH);
	if (ret != 0)
		return ret;

  return error_none;
}

//==============================================================================
//==============================================================================
aioc_error_t aioc_mux_bank_set_bit_low(struct aioc_mux_bank_dev* dev)
{
	int32_t ret;

  ret = no_os_gpio_direction_output(dev->en_line, NO_OS_GPIO_HIGH);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a0_line, NO_OS_GPIO_HIGH);
	if (ret != 0)
		return ret;

	ret = no_os_gpio_direction_output(dev->a1_line, NO_OS_GPIO_LOW);
	if (ret != 0)
		return ret;

  return error_none;
}

