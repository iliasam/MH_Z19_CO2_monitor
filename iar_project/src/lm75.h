#include "stm32f10x.h"
#ifndef _LM75_H
#define _LM75_H

/* LM75 registers */
#define LM75_REG_TEMP                 0x00 // Temperature
#define LM75_REG_CONF                 0x01 // Configuration
#define LM75_REG_THYS                 0x02 // Hysteresis
#define LM75_REG_TOS                  0x03 // Overtemperature shutdown

uint16_t LM75_ReadReg(uint8_t reg);
int16_t LM75_Temperature(void);
void LM75_WriteConf(uint8_t value) ;
void LM75_Shutdown(uint8_t newstate);
#endif
