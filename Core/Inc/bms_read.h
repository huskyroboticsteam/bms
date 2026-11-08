#pragma once

#include <stdint.h>

#include "bms_types.h"
#include "stm32g4xx_hal_i2c.h"

// Read FT_STS1 register. Outputs a struct of faults, where a high bit indicates a fault.
HAL_StatusTypeDef Read_FT_STS1(I2C_HandleTypeDef* hi2c, FT_STS1_faults* faults);

// Read RD_ITOP register. Outputs the battery pack current in mA.
HAL_StatusTypeDef Read_RD_ITOP(I2C_HandleTypeDef* hi2c, int32_t* current_mA);
