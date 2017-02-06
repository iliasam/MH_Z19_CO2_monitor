#include "lm75.h"
#include "stm32f10x_i2c.h"
#include "i2c_functions.h"

//code taken from: https://github.com/LonelyWolf/stm32/tree/master/lm75

#define I2C_PORT I2C1
#define LM75_ADDR	0x9E // LM75 address

// Read 16-bit LM75 register
uint16_t LM75_ReadReg(uint8_t reg) {
	uint16_t value;

	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	I2C_AcknowledgeConfig(I2C_PORT,ENABLE); // Enable I2C acknowledgment
	I2C_GenerateSTART(I2C_PORT,ENABLE);
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_MODE_SELECT)); // Wait for EV5
	I2C_Send7bitAddress(I2C_PORT,LM75_ADDR,I2C_Direction_Transmitter); // Send slave address
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Wait for EV6

	I2C_SendData(I2C_PORT,reg); // Send register address
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Wait for EV8
	I2C_GenerateSTART(I2C_PORT,ENABLE); // Send repeated START condition (aka Re-START)
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_MODE_SELECT)); // Wait for EV5
	I2C_Send7bitAddress(I2C_PORT,LM75_ADDR,I2C_Direction_Receiver); // Send slave address for READ
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // Wait for EV6
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_BYTE_RECEIVED)); // Wait for EV7 (Byte received from slave)
	value = (I2C_ReceiveData(I2C_PORT) << 8); // Receive high byte
	I2C_AcknowledgeConfig(I2C_PORT,DISABLE); // Disable I2C acknowledgment
	I2C_GenerateSTOP(I2C_PORT,ENABLE); // Send STOP condition
	while (!I2C_CheckEventT(I2C_PORT,I2C_EVENT_MASTER_BYTE_RECEIVED)); // Wait for EV7 (Byte received from slave)
	value |= I2C_ReceiveData(I2C_PORT); // Receive low byte

	return value;
}

// Read value from LM75 configuration register (8 bit)
uint8_t LM75_ReadConf(void) {
	uint8_t value;

	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	I2C_AcknowledgeConfig(I2C_PORT,ENABLE); // Enable I2C acknowledgment
	I2C_GenerateSTART(I2C_PORT,ENABLE);
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_MODE_SELECT)); // Wait for EV5
	I2C_Send7bitAddress(I2C_PORT,LM75_ADDR,I2C_Direction_Transmitter); // Send slave address
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Wait for EV6
	I2C_SendData(I2C_PORT,LM75_REG_CONF); // Send register address
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Wait for EV8
	I2C_GenerateSTART(I2C_PORT,ENABLE); // Send repeated START condition (aka Re-START)
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_MODE_SELECT)); // Wait for EV5
	I2C_Send7bitAddress(I2C_PORT,LM75_ADDR,I2C_Direction_Receiver); // Send slave address for READ
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // Wait for EV6
	I2C_AcknowledgeConfig(I2C_PORT,DISABLE); // Disable I2C acknowledgment
	I2C_GenerateSTOP(I2C_PORT,ENABLE); // Send STOP condition
	while (!I2C_CheckEventT(I2C_PORT,I2C_EVENT_MASTER_BYTE_RECEIVED)); // Wait for EV7 (Byte received from slave)
	value = I2C_ReceiveData(I2C_PORT);

	return value;
}




// Write value to LM75 configuration register  (8 bit)
void LM75_WriteConf(uint8_t value)
{
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	I2C_AcknowledgeConfig(I2C_PORT,ENABLE); // Enable I2C acknowledgment
	I2C_GenerateSTART(I2C_PORT,ENABLE);
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_MODE_SELECT)); // Wait for EV5
	I2C_Send7bitAddress(I2C_PORT,LM75_ADDR,I2C_Direction_Transmitter); // Send slave address
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Wait for EV6
	I2C_SendData(I2C_PORT,LM75_REG_CONF); // Send register address
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Wait for EV8
	I2C_SendData(I2C_PORT,value);
	while (!I2C_CheckEvent(I2C_PORT,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Wait for EV8
	I2C_GenerateSTOP(I2C_PORT,ENABLE);
}

// Set LM75 shutdown mode
// newstate:
//    1 = put LM75 into powerdown mode
//    0 = wake up LM75
void LM75_Shutdown(uint8_t newstate)
{
	LM75_WriteConf((newstate == 1) ? 0x01 : 0x00);
}

// Read temperature readings from LM75 in decimal format
// IIIF where:
//   III - integer part
//   F   - fractional part
// e.g. 355 means 35.5C
int16_t LM75_Temperature(void) {
	uint16_t raw;
	int16_t temp;

	raw = LM75_ReadReg(LM75_REG_TEMP) >> 7;
	if (raw & 0x0100) {
		// Negative temperature
		temp = -10 * (((~(uint8_t)(raw & 0xFE) + 1) & 0x7F) >> 1) - (raw & 0x01) * 5;
	} else {
		// Positive temperature
		temp = ((raw & 0xFE) >> 1) * 10 + (raw & 0x01) * 5;
	}

	return temp;
}

