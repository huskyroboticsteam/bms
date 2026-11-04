#pragma once

#include "stm32g4xx_hal.h"

HAL_StatusTypeDef Read_FT_STS1_Reg(I2C_HandleTypeDef *hi2c, FT_STS1_faults* faults);
