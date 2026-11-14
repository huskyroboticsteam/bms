
#include <stdint.h>

#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_def.h"

#include "bms_regs.h"
#include "bms_read.h"
#include "bms_types.h"

// Read a 16-bit value from BMS IC
static HAL_StatusTypeDef Read_Uint16(I2C_HandleTypeDef* hi2c, uint16_t reg_addr, uint16_t* out) {
   uint8_t data[2];
   HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(hi2c, IC_ADDRESS << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, data, 2, 100);
   if (ret != HAL_OK) return ret;

   *out = (uint16_t)((data[1] << 8) | data[0]);
   return HAL_OK;
}

// Write a 16-bit register
static HAL_StatusTypeDef Write_Uint16(I2C_HandleTypeDef* hi2c, uint16_t reg_addr, uint16_t value) {
   // Stores the two bytes to be transmitted
   uint8_t data[2];

   // Store the low byte first
   data[0] = (uint8_t)(value & 0xFF);

   // Store the high byte second
   data[1] = (uint8_t)(value >> 8);

   // Write the two bytes through I2C 
   HAL_StatusTypeDef ret = HAL_I2C_Mem_Write(hi2c, IC_ADDRESS << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, data, 2, 100);

   // Return the I2C write status
   return ret;
}

// Initialize the MP2790
HAL_StatusTypeDef BMS_Init(I2C_HandleTypeDef* hi2c) {
   
   HAL_StatusTypeDef ret;
   uint16_t scan_config;
   
   // Configure six stacked cells
   ret = Write_Uint16(hi2c, CELLS_CTRL_REG, 0x0005);
   if (ret != HAL_OK) return ret;

   // Enable ADC scans for cells 1-6
   ret = Write_Uint16(hi2c, HR_SCAN1_REG, 0x003F);
   if (ret != HAL_OK) return ret;

   // Read the existing ADC scan configuration
   ret = Read_Uint16(hi2c, HR_SCAN0_REG, &scan_config);
   if (ret != HAL_OK) return ret;
   // Enable cell voltage scanning and clear reserved bits
   scan_config = (scan_config & 0x0B7F) | 0x0001;
   // Write the updated ADC configuration
   ret = Write_Uint16(hi2c, HR_SCAN0_REG, scan_config);
   if (ret != HAL_OK) return ret;

   // enable watchdog timer with default bark/bite timeouts
   ret = Write_Uint16(hi2c, WDT_CFG_REG, 0x01);
   if (ret != HAL_OK) return ret;

   return HAL_OK;
}

HAL_StatusTypeDef Read_FT_STS1(I2C_HandleTypeDef* hi2c, FT_STS1_faults* faults) {
   union {
      uint16_t raw;
      FT_STS1_faults faults;
   } bits_union;

   HAL_StatusTypeDef ret = Read_Uint16(hi2c, FT_STS1_REG, &bits_union.raw);
   if (ret != HAL_OK) return ret;

   *faults = bits_union.faults;
   return HAL_OK;
}

HAL_StatusTypeDef Read_RD_ITOP(I2C_HandleTypeDef* hi2c, int32_t* current_mA) {
   uint16_t raw;
   HAL_StatusTypeDef ret = Read_Uint16(hi2c, RD_ITOP_REG, &raw);
   if (ret != HAL_OK) return ret;

   int16_t data = (int16_t)raw;
   *current_mA = (int32_t)(((int64_t)data * 100000) / 32768 / RSENSE);
   return ret;
}

// Read an individual cell voltage (1-6) in millivolts
HAL_StatusTypeDef Read_CellVoltage(
    I2C_HandleTypeDef* hi2c,
    uint8_t cell,
    uint32_t* voltage_mV
) {
   // Check that the cell number is valid for a 65 battery
   if (cell < 1 || cell > 6) return HAL_ERROR;

   uint16_t raw;
   uint16_t reg_addr = RD_VCELL1_REG + (cell - 1) * 2;
   HAL_StatusTypeDef ret = Read_Uint16(hi2c, reg_addr, &raw);
   if (ret != HAL_OK) return ret;

   *voltage_mV = ((uint32_t)(raw & 0x7FFF) * 5000) / 32768;
   
   // Return successful read status
   return HAL_OK;
}

HAL_StatusTypeDef WDT_Reset(I2C_HandleTypeDef* hi2c) {
   return Write_Uint16(hi2c, WDT_RST_REG, 0x01);
}
