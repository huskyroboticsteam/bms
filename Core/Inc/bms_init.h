#pragma once

#include "stm32g4xx_hal.h"

// Initialize the BMS IC
HAL_StatusTypeDef BMS_Init(I2C_HandleTypeDef* hi2c);
