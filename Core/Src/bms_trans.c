#include "bms_trans.h"
#include "bms_regs.h"
#include "bms_types.h"
#include "stm32g4xx_hal_def.h"
#include "stm32g4xx_hal_i2c.h"
#include <stdint.h>

HAL_StatusTypeDef Read_FT_STS1_Reg(I2C_HandleTypeDef *hi2c,
                                   FT_STS1_faults *faults) {
  uint8_t data[2];
  HAL_StatusTypeDef status =
      HAL_I2C_Mem_Read(hi2c, IC_ADDRESS << 1, FT_STS1_REG, 1, data, 2, 100);
  if (status != HAL_OK)
    return status;

  union {
    uint16_t raw;
    FT_STS1_faults faults;
  } bits_union;
  bits_union.raw = ((uint16_t)data[1]) << 8;
  bits_union.raw |= data[0];

  *faults = bits_union.faults;
  return status;
}
