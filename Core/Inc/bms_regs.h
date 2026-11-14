/*
 * bms_reg.h
 *
 *  Created on: Jan 3, 2026
 *      Author: luckyellasiri
 */

#pragma once

// Abbreviations:
// OTP - One-Time Programmable
// MTP - Multi-Time Programmable
// WDT - Watch-dog Timer
// ADC - Analog-Digital Converter
// CTRL - Control
// FT - Fault
// STS - Status
// REG - Register
// CFG - Configuration
// OC - Over-current
// HR - high-resolution

// General hardware/pin configuration registers
#define CELLS_CTRL_REG 0x00       // controls number of stacked cells being monitored
#define MOSFET_ACT_CFG_REG 0x05  // selects the possible commands of MOSFET transition logic
#define GPIO_STATUS_REG 0x0A     // reports GPIO status (low/high)
#define GPIO_CFG_REG 0x0C        // enables pull-up capability for GPIO pins, and defines direction and input type (OTP)
#define GPIO_OUT_REG 0x0B        // sets output level for GPIO (OTP)
#define PINS_CFG_REG 0x0D        // defines direction of GPIOHV1, sets behavior of WDFT and xALERT pins (OTP)
#define OPEN_CFG_REG 0x57        // configures the open-wire threshold and length of each pull-up, pull-down phase

// FET DSG monitoring registers
#define FET_STATUS_REG 0x11  // reports the status of the DSG drivers and charge pump
#define FET_CTRL_REG 0x12    // turns the SBYDSG drivers on/off
#define FET_MODE_REG 0x13    // configures soft start for DSG MOSFET, enables manual control of SBYDSG MOSFET
#define FET_CFG_REG 0x14     // configures the driver voltages of CHG and DSG MOSFETs

// Watch-dog timer/interrupt configuration and status registers
#define WDT_STATUS_REG 0x0E  // reports the status of watch-dog timer
#define WDT_RST_REG 0x0F     // controls the reset of the watch-dog timer
#define WDT_CFG_REG 0x10     // enables WDT communication, bite & bark timeout
#define RD_INT0_REG 0x15     // reports interrupt events (current status change, FT_REC, NTC discharging etc.)
#define RD_INT1_REG 0x16     // also reports interrupt events (driver error, pack voltage change, cell mismatch etc.)
#define INT0_CLR_REG 0x17    // clears interrupts
#define INT1_CLR_REG 0x18    // also clears interrupts
#define INT0_EN_REG 0x19     // enables interrupts
#define INT1_EN_REG 0x1A     // enables interrupts
#define INT_TYPE0 0x1B       // configures triggering logic for interrupt (rising/falling edge)
#define INT_TYPE1 0x1C       // same as TYPE0
#define INT_TYPE2 0x1D       // same as TYPE0
#define MASK_INT0 0x1E       // masks triggering interrupts (enables clearing)
#define MASK_INT1 0x1F       // same as prior register

// Over-current protection registers
#define OC_STATUS_REG 0x20  // reports status of discharge OC events
#define OCFT_CTRL_REG 0x23  // controls triggering logic for OC interrupt events (rising/falling edge)
#define DSGOC_LIM_REG 0x24  // configures threshold for discharge OC events
#define DSGOC_DEG_REG 0x25  // configures de-glitch range for discharge over-current events
#define SC_STATUS_REG 0x27  // configures real time status for short circuit and discharge SC events
#define SCFT_CTRL_REG 0x2A  // enables fault protection, interrupts for discharge SC events
#define DSGSC_CFG_REG 0x2B  // configures de-glitch and threshold range for discharge SC events
#define RD_OPENH_REG 0x53   // detects open wire for each of the cells
#define SFT_GO_REG 0x55     // reports open wire detection and completion

// Over-temperature protection registers
#define RD_NTC_DIE_REG 0x3E     // reports the NTC hot temperature and hot/cold discharging status for each cell
#define RD_V_NTC4_LR 0x3F       // reports NTC for cells 1-4 discharging hot/cold status (reports NTC4 ADC reading)
#define RD_V_NTC2_LR 0x41       // reports NTC2's ADC reading
#define RD_V_NTC1_LR 0x42       // reports NTC1's ADC reading
#define RD_T_DIE 0x43           // reports die's temperature reading
#define NTC_CLR 0x44            // clears event triggers from when die is too hot. Reports real-time NTC status
#define DIE_CFG 0x46            // enables die temperature monitoring and fault protection
#define NTC_CFG 0x47            // configures NTC fault protection and monitoring
#define NTCC_OTHR_DSG_REG 0x48  // configures discharge hot voltage threshold for NTC
#define NTCC_UTHR_DSG_REG 0x49  // configures discharge cold voltage threshold for NTC
#define NTCM_OTHR 0x4C          // configures NTC hot PCB monitor threshold
#define DIE_OT 0x4D             // configures die temperature threshold and hysteresis
#define SELF_STS_REG 0x4E       // reports NVM CRC check outcome and over/under-voltage self-test detection results

// Registers that deal with reading from regulation registers (just in case)
#define RD_VA1P8_REG 0x4F  // reports the VDD regulator ADC reading result
#define RD_VA3P3_REG 0x50  // reports the 3V3 regulator ADC reading result
#define RD_VA5_REG 0x51    // reports the REGIN ADC reading result
#define RD_VASELF 0x52     // reports the ADC self-test reading result
#define SELF_CFG_REG 0x56  // enables fault protection for the prior registers as well as open wire fault protection
#define RD_V1P8 0x94       // reports the 1.8V regulator’s high-resolution ADC reading
#define RD_V3P3 0x95       // reports the 3.3V regulator’s high-resolution ADC reading
#define RD_V5 0x96         // reports REGIN’s high-resolution ADC reading
#define SELF_THR_REG 0x5B  // configures thresholds for self-test over/under-voltage events

// Fault protection registers
#define FT_STS1_REG 0x5D  // reports fault status for die-temp, DSG SC, OC1, OC2, NTC, open wire, cell OV events
#define FT_STS2_REG 0x5E  // reports fault status for SC removal detection and UV events
#define FT_CLR_REG 0x5F   // clears faults from FT_STS1_REG
#define FT_REC_REG 0x60   // controls manual fault clearing for 3.3V and 1.8V UV, OTP CRC, MOSFET driver events
#define FT0_CFG_REG 0x61  // enables/sets auto cell OV/UV fault recovery logic, configures MOSFET behavior in events
#define FT1_CFG_REG 0x62  // configures the battery pack pull-up current and time during SC removal detection

// Current reading registers (how many being used is subject)
#define RD_ITOP_REG 0x6B     // reads pack current
#define RD_ICELL1_REG 0x6D   // reads current in cell 1
#define RD_ICELL2_REG 0x6F   // reads current in cell 2
#define RD_ICELL3_REG 0x71   // reads current in cell 3
#define RD_ICELL4_REG 0x73   // reads current in cell 4
#define RD_ICELL5_REG 0x75   // reads current in cell 5
#define RD_ICELL6_REG 0x77   // reads current in cell 6
#define RD_ICELL7_REG 0x79   // reads current in cell 7
#define RD_ICELL8_REG 0x7B   // reads current in cell 8
#define RD_ICELL9_REG 0x7D   // reads current in cell 19
#define RD_ICELL10_REG 0x7F  // reads current in cell 10
#define TRIMG_IPCB_REG 0x9B  // configures PCB gain correction form sensing resistors and SMT variation

// Cell voltage reading registers
#define RD_VCELL1_REG 0x6C  // reports cell 1's high-resolution ADC voltage reading
#define RD_VCELL2_REG 0x6E  // reports cell 2's high-resolution ADC voltage reading
#define RD_VCELL3_REG 0x70  // reports cell 3's high-resolution ADC voltage reading
#define RD_VCELL4_REG 0x72  // reports cell 4's high-resolution ADC voltage reading
#define RD_VCELL5_REG 0x74  // reports cell 5's high-resolution ADC voltage reading
#define RD_VCELL6_REG 0x76  // reports cell 6's high-resolution ADC voltage reading

// NTC reading registers
#define RD_VNTC4_REG 0x8C  // reports NTC 4’s high-resolution ADC reading
#define RD_VNTC3_REG 0x8D  // reports NTC 3’s high-resolution ADC reading
#define RD_VNTC2_REG 0x8E  // reports NTC 2’s high-resolution ADC reading
#define RD_VNTC1_REG 0x8F  // reports NTC 1’s high-resolution ADC reading
#define RD_TDIE_REG 0x93   // reports die temperature ADC reading

// GPIO reading registers
#define RD_VGPIO3_REG 0x90  // reports GPIO3’s high-resolution ADC reading
#define RD_VGPIO2_REG 0x91  // reports GPIO2’s high-resolution ADC reading
#define RD_VGPIO1_REG 0x92  // reports GPIO1’s high-resolution ADC reading

// ADC regulator reading registers
#define RD_V1P8_REG 0x94  // reports the 1.8V regulator’s high-resolution ADC reading
#define RD_3P3_REG 0x95   // reports the 3.3V regulator’s high-resolution ADC reading
#define RD_V5_REG 0x96    // reports the 5V regulator’s high-resolution ADC reading

// ADC error detection registers
#define ADC_STS_REG 0x98  // reports the status of the internal scheduler
#define ADC_CTRL 0x99     // reports whether an error has occurred when starting the HR voltage scan

// high resolution scanning
#define HR_SCAN0_REG 0x9C  // enables ADC cell measurement compensation for voltage drop
// enables voltage and current ADC scanning for the synchronous TOP
// current, synchronous cell current, LDOs, die temperature, NTCs, GPIO, PACKP, TOP voltage, and cell
// voltage

#define HR_SCAN1_REG 0x9D  // enables the high-resolution ADC scans for cells 1~10
#define HE_SCAN2_REG 0x9E  // enables the ADC voltage scans for NTC1~4 and HR voltage scans for GPIO1~3

// CRC registers & device address configuration
#define SILC_INFO1_REG 0xA0  // defines the size of the read-back (in words) before appending a CRC
#define COMM_CFG_REG 0xA3    // defines the configurable device address and enables using the CRC across
// the communication protocol

// Passive cell balancing registers
#define BAL_STS_REG 0xA4   // reports auto-balancing cycle status and detects current events
#define BAL_LIST_REG 0xA5  // reports which cell will be balanced during the next balancing session
#define BAL_CTRL_REG 0xA6  // reports whether an error occurs when balancing starts or cell-balancing is completed
#define BAL_CFG_REG 0xA7   // configures the number of repetitions to execute the balancing list
#define BAL_THR_REG 0xA8   // configures the cell-balancing threshold and the minimum cell voltage

// MTP registers
#define MEM_STATUS_REG 0xB4             // reports the status of the MTP
#define OTP_STORE_CMD_REG 0xB8          // reports whether the store function is in progress
#define STORE_CMD_ACCESS_CODE_REG 0xB9  // controls the access to the store command

#define IC_ADDRESS 0x01

// TODO: Current sense resistor value (mOhm)
#define RSENSE 1
