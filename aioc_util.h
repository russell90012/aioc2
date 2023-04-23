#ifndef AIOC_UTIL_H
#define AIOC_UTIL_H

#include "aioc_defs.h"

//
// Misc. routines
//

aioc_error_t
aioc_util_delay_ns(uint32_t delay);


//
// SPI related.
//
/**
 * @enum no_os_spi_bit_order
 * @brief SPI configuration for bit order (MSB/LSB).
 */
enum no_os_spi_bit_order {
	/** Most-significant bit (MSB) first */
	NO_OS_SPI_BIT_ORDER_MSB_FIRST = 0,
	/** Least-significant bit (LSB) first */
	NO_OS_SPI_BIT_ORDER_LSB_FIRST = 1,
};

/**
 * @struct no_os_spi_init_param
 * @brief Structure holding the parameters for SPI initialization
 */
struct no_os_spi_init_param {
	/** Device ID */
	uint32_t	device_id;
	/** SPI chip select */
	uint8_t		chip_select;
	/**  SPI extra parameters (device specific) */
	void		*extra;
	/** Parent of the device */
	struct no_os_spi_desc *parent;
};

/**
 * @struct no_os_spi_desc
 * @brief Structure holding SPI descriptor.
 */
struct no_os_spi_desc {
	/** Device ID */
	uint32_t	device_id;
	/** SPI chip select */
	uint8_t		chip_select;
		/**  SPI extra parameters (device specific) */
	void		*extra;
	/** Parent of the device */
	struct no_os_spi_desc *parent;
};



aioc_error_t aioc_util_spi_init(
              struct no_os_spi_desc ** spi_desc,
              struct no_os_spi_init_param* parm);

aioc_error_t aioc_util_spi_remove(struct no_os_spi_desc* spi_desc);


aioc_error_t aioc_util_spi_transaction(
              struct no_os_spi_desc * spi_desc,
              uint8_t* data,
              uint32_t number_of_bytes);

//
// I2C related.
//

aioc_error_t aioc_util_i2c_init(void** instance);


aioc_error_t aioc_util_i2c_write(
  void* instance,
  uint32_t dev_adrs,
  uint32_t reg_adrs,
  uint8_t* data,
  uint32_t num_bytes);

aioc_error_t aioc_util_i2c_read(
  void* instance,
  uint32_t dev_adrs,
  uint32_t reg_adrs,
  uint8_t* data,
  uint32_t num_bytes);




#endif  // AIOC_UTIL_H
