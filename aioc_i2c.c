
// MERCURY HEADER GOES HERE
// TBD

/**
 * @file:    aioc_i2c.c
 * @author:  Russell Shahenian
 * @since:   4/22/23
 * @brief:   This file contains the public AIOC i2c module specifications.
 */

#include "aioc_defs.h"
#include "no_os_i2c.h"
#include "errno.h"

#include <stdint.h>
#include <stdbool.h>





/* Initialize the I2C communication peripheral. */
int32_t
aioc_i2c_init(
  struct no_os_i2c_desc **desc,
	const struct no_os_i2c_init_param *param)
{
  struct no_os_i2c_desc* descriptor;
  
	// Allocate the descriptor.
  descriptor = (struct no_os_i2c_desc *)malloc(sizeof(*descriptor));
  if (!descriptor)  return -EINVAL;

  // Assign parameters.
  descriptor->slave_address = param->slave_address;

	*desc = descriptor;

	return 0;
}

/* Free the resources allocated by no_os_i2c_init(). */
int32_t
aioc_i2c_remove(struct no_os_i2c_desc *desc)
{
  return 0;
}

/* Write data to a slave device. */
int32_t
aioc_i2c_write(
  struct no_os_i2c_desc *desc,
	uint8_t *data,
	uint8_t bytes_number,
	uint8_t stop_bit)
{
  return 0;
}

/* Read data from a slave device. */
int32_t
aioc_i2c_read(
  struct no_os_i2c_desc *desc,
	uint8_t *data,
	uint8_t bytes_number,
	uint8_t stop_bit)
{
  return 0;
}





/**
 * @brief AIOC platform specific I2C platform ops structure
 */
const struct no_os_i2c_platform_ops aioc_i2c_ops =
{
	/** i2c initialization function pointer */
	.i2c_ops_init = &aioc_i2c_init,
	/** i2c write function pointer */
	 .i2c_ops_write = &aioc_i2c_write,
	/** i2c read function pointer */
  .i2c_ops_read = &aioc_i2c_read,
	/** i2c remove function pointer */
  .i2c_ops_remove = &aioc_i2c_remove
};
