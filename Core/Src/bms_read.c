
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
