#include "stm32f10x_i2c.h"
#include "i2c_functions.h"
#include "stm32f10x_it.h"
#include "init_periph.h"
#include "hardware_work.h"

uint8_t i2c_err_flag = 0;

//check with timeout
ErrorStatus I2C_CheckEventT(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t start_time = HAL_GetTick();
	while ((I2C_CheckEvent(I2Cx,I2C_EVENT) == ERROR) &&  ((HAL_GetTick() - start_time) < 5)){}
        if ((HAL_GetTick() - start_time) >= 5) i2c_err_flag = 1;
	return 	SUCCESS;
	//return I2C_CheckEventT(I2Cx,I2C_EVENT);
}

void I2C_WriteData(uint8_t data)
{
	// Просто вызываем готовую функцию из SPL и ждем, пока данные улетят
	I2C_SendData(I2C1, data);
	while(!I2C_CheckEventT(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

void I2C_EndTransmission(void)
{
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_StartTransmission(uint8_t transmissionDirection, uint8_t slaveAddress)
{
        i2c_err_flag = 0;
        uint32_t start_time = HAL_GetTick();
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) && ((HAL_GetTick() - start_time) < 5));// На всякий случай ждем, пока шина осовободится
	I2C_GenerateSTART(I2C1, ENABLE);// Генерируем старт
	while(!I2C_CheckEventT(I2C1, I2C_EVENT_MASTER_MODE_SELECT));// Ждем, пока взлетит нужный флаг
	I2C_Send7bitAddress(I2C1, slaveAddress, transmissionDirection);
	if(transmissionDirection== I2C_Direction_Transmitter)
	{
		while(!I2C_CheckEventT(I2C1,	I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else
	{
		while(!I2C_CheckEventT(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
        i2c_auto_reboot();
}

void i2c_auto_reboot(void)
{
  static uint8_t reboot_cnt = 0;
  if (i2c_err_flag!= 0) 
  {
    if (reboot_cnt == 10)
    {
      i2c_hard_reset();
      reboot_cnt = 0;
    }
    i2c_init();
    i2c_err_flag = 0;
    reboot_cnt++;
    HAL_Delay(20);
  }
  
}