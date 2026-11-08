#pragma once

#include <stdint.h>

typedef struct FT_STS1_faults {
   uint16_t cell_uv : 1;
   uint16_t cell_ov : 1;
   uint16_t cell_dead : 1;
   uint16_t cell_msmt : 1;
   uint16_t open_wire : 1;
   uint16_t vtop_uv : 1;
   uint16_t vtop_ov : 1;
   uint16_t pcb_mntr : 1;
   uint16_t ntc_cell_chg : 1;
   uint16_t ntc_cell_dsg : 1;
   uint16_t oc1_dchg : 1;
   uint16_t oc2_dchg : 1;
   uint16_t oc_chg : 1;
   uint16_t sc_dchg : 1;
   uint16_t sc_chg : 1;
   uint16_t die_temp : 1;
} FT_STS1_faults;
