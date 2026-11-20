#include "stm32g4xx_hal.h"

#include "bms_init.h"
#include "bms_rdwr.h"
#include "bms_regs.h"

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

  // Enable watchdog communication while preserving the configured timeouts.
  uint16_t wdt_config;
  ret = Read_Uint16(hi2c, WDT_CFG_REG, &wdt_config);
  if (ret != HAL_OK) return ret;

  ret = Write_Uint16(hi2c, WDT_CFG_REG, wdt_config | 0x0001U);
  if (ret != HAL_OK) return ret;

  return HAL_OK;
}
