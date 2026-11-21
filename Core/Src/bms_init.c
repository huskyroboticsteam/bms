#include "stm32g4xx_hal.h"

#include <stdint.h>
#include "bms_init.h"
#include "bms_rdwr.h"
#include "bms_regs.h"

static HAL_StatusTypeDef Config_Cell_Count(I2C_HandleTypeDef* hi2c) {
  return Write_Uint16(hi2c, CELLS_CTRL_REG, 0x0005);
}

static HAL_StatusTypeDef Config_Watchdog(I2C_HandleTypeDef* hi2c) {
  uint16_t cfg = 0;

  // set timeouts (setting * 25 + 25)
  cfg |= 0b0100111 << 9;  // bite timeout of 1000 ms
  cfg |= 0b0010011 << 2;  // bark timeout of 500 ms

  cfg |= 0b1;  // enable timeouts

  return Write_Uint16(hi2c, WDT_CFG_REG, cfg);
}

HAL_StatusTypeDef BMS_Init(I2C_HandleTypeDef* hi2c) {
  HAL_StatusTypeDef ret;

  ret = Config_Cell_Count(hi2c);
  if (ret != HAL_OK) return ret;

  ret = Config_Watchdog(hi2c);
  if (ret != HAL_OK) return ret;








  // Enable ADC scans for cells 1-6
  ret = Write_Uint16(hi2c, HR_SCAN1_REG, 0x003F);
  if (ret != HAL_OK) return ret;

  // Enable cell voltage scanning
  ret = Read_Uint16(hi2c, HR_SCAN0_REG, &scan_config);
  if (ret != HAL_OK) return ret;
  uint16_t scan_config = (scan_config & 0x0B7F) | 0x0001;
  ret = Write_Uint16(hi2c, HR_SCAN0_REG, scan_config);
  if (ret != HAL_OK) return ret;

  return HAL_OK;
}
