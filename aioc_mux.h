#ifndef AIOC_MUX_H
#define AIOC_MUX_H

// MERCURY HEADER GOES HERE
// TBD

/**
 * @file:    aioc_mux.h
 * @author:  Russell Shahenian
 * @since:   4/4/23
 * @brief:   This file contains the public AIOC mux module specifications.
 */

#include "aioc_defs.h"
#include "aioc_gpio.h"
#include "aioc_i2c_gpio.h"


//================================
// Public specifications.
//================================

typedef enum
{
  AIOC_MUX_BANKS_5V,
  AIOC_MUX_BANKS_7V,
  AIOC_MUX_BANKS_95mV,
  AIOC_MUX_BANKS_RTD,
  AIOC_MUX_BANKS_EP10
}
aioc_mux_banks_t;

typedef enum
{
  AIOC_MUX_LINES_EXTERNAL = 0,
  AIOC_MUX_LINES_BIT_LOW,
  AIOC_MUX_LINES_BIT_HIGH
}
aioc_mux_lines_t;


// MUX (ADG5209) Line Switch Truth Table
// A1  A0  EN  On Switch Pair
// X   X   0   None
// 0   0   1   1              External lines
// 0   1   1   2              BIT Low lines
// 1   0   1   3              BIT High lines
// 1   1   1   4              NA
// X is don’t care.


/**
 * Switch in external, bit high, or bit low lines per specified mux bank.
 *
 * @param aioc_mux_banks is the specific mux bank to switch lines on.
 *
 * @param aioc_mux_lines is specific set of lines to switch to.
 *
 * @return error handling result code.
 */
aioc_error_t aioc_mux_switch_lines(
  aioc_mux_banks_t aioc_mux_banks,
  aioc_mux_lines_t aioc_mux_lines);


struct aioc_mux_bank_init_param

/**
 * @struct aioc_mux_bank_init_param
 * @brief  Structure containing the init parameters needed by the
 *         aioc mux bank descriptor.
 */
struct aioc_mux_bank_init_param {
	/** SW BANK EN GPIO initialization parameters. */
	struct no_os_gpio_init_param	*en_line;
	/** SW BANK A0 GPIO initialization parameters */
	struct no_os_gpio_init_param *a0_line;
	/** SW BANK A1 GPIO initialization parameters */
	struct no_os_gpio_init_param *a1_line;
	};

/**
 * @struct aioc_mux_bank_dev
 * @brief  Structure representing an aioc mux bank descriptor
 */
struct aioc_mux_bank_dev {

	/** SW_BANK_EN line descriptor. */
	struct no_os_gpio_desc	*en_line;
	/** SW_BANK_A0 line descriptor. */
	struct no_os_gpio_desc *a0_line;
	/** SW_BANK_A0 line descriptor. */
	struct no_os_gpio_desc *a1_line;
};

aioc_error_t aioc_mux_bank_init(
  struct aioc_mux_bank_dev** dev,
  struct aioc_mux_bank_init_param* aioc_mux_bank_init_param);

#endif  // AIOC_MUX_H
