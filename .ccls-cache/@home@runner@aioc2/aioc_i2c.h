#ifndef AIOC_I2C_H
#define AIOC_I2C_H
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

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief aioc platform specific i2c platform ops structure
 */
extern const struct no_os_i2c_platform_ops aioc_i2c_ops;


#endif  // AIOC_I2C_H

