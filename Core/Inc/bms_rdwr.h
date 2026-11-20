#pragma once

#include <stdint.h>

#include "bms_types.h"
#include "stm32g4xx_hal_i2c.h"

// Read a 16-bit BMS register. Updates *out only if the read succeeds.
HAL_StatusTypeDef Read_Uint16(I2C_HandleTypeDef* hi2c, uint16_t reg_addr, uint16_t* out);

// Write a 16-bit BMS register, sending the low byte first.
HAL_StatusTypeDef Write_Uint16(I2C_HandleTypeDef* hi2c, uint16_t reg_addr, uint16_t value);

// Read FT_STS1 register. Outputs a struct of faults, where a high bit indicates a fault.
HAL_StatusTypeDef Read_FT_STS1(I2C_HandleTypeDef* hi2c, FT_STS1_faults* faults);

// Read RD_ITOP register. Outputs the battery pack current in mA.
HAL_StatusTypeDef Read_RD_ITOP(I2C_HandleTypeDef* hi2c, int32_t* current_mA);

// Start a high-resolution voltage scan and poll for completion.
HAL_StatusTypeDef BMS_ScanCellVoltages(I2C_HandleTypeDef* hi2c, uint32_t timeout_ms);

// Reads the voltage of an individual cell (1-6) in millivolts
HAL_StatusTypeDef Read_CellVoltage(I2C_HandleTypeDef* hi2c, uint8_t cell, uint32_t* voltage_mV);

// Reset watchdog timer. Must be called periodically before it times out
HAL_StatusTypeDef WDT_Reset(I2C_HandleTypeDef* hi2c);
