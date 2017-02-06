#include "init_periph.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_it.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"

void init_all_periph(void)
{
  init_clk();
  init_gpio();
  i2c_init();
  init_adc();
  init_uart();
  rtc_init();
}

void init_gpio(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	//OUTPUT
	GPIO_InitStructure.GPIO_Pin   = POWER_ON_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(POWER_ON_PORT, &GPIO_InitStructure);

	//INPUT
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin   = EXT_POWER_PIN;
	GPIO_Init(EXT_POWER_PORT, &GPIO_InitStructure);

	//PULL UP INPUT
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = BUTTON_PIN;
	GPIO_Init(BUTTON_PORT, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);

	GPIO_InitStructure.GPIO_Pin   = CHARGE_DET_PIN;
	GPIO_Init(CHARGE_DET_PORT, &GPIO_InitStructure);

	//ADC
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin   = BATT_VOLT_PIN;
	GPIO_Init(BATT_VOLT_PORT, &GPIO_InitStructure);
}



void init_clk(void)
{
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_OFF);
  RCC_PLLCmd(DISABLE);/* Enable PLL */
}

void i2c_init(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(I2C_GPIO_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);//REMAP I2C

	I2C_DeInit(I2C1);
	I2C_StructInit(&I2C_InitStructure);

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
        
	if (I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY)) {
          // Reset the I2C block
          I2C_SoftwareResetCmd(I2C1, ENABLE);
          I2C_SoftwareResetCmd(I2C1, DISABLE);
        }
}

void init_adc(void)
{
	ADC_InitTypeDef  ADC_InitStructure;

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO,ENABLE);

	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;

	ADC_Init(ADC1,&ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	//while(ADC_GetResetCalibrationStatus(ADC1)){}; //?????????????????

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)){};
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_71Cycles5);
}

void init_uart(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable GPIOA clock                                                   */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_USART1, ENABLE);

	/* Configure USART1 Rx as input floating                         */
	GPIO_InitStructure.GPIO_Pin   = UART_RX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(UART_PORT, &GPIO_InitStructure);

	/* Configure USART1 Tx as alternate function push-pull            */
	GPIO_InitStructure.GPIO_Pin   = UART_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(UART_PORT, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//REMAP UART

	USART_StructInit(&USART_InitStructure);
	USART_DeInit(USART1);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void rtc_init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  PWR_BackupAccessCmd(ENABLE);
  //BKP_DeInit();
  RCC_LSEConfig(RCC_LSE_ON);
  HAL_Delay(10);
  
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
  RCC_RTCCLKCmd(ENABLE); 
  RTC_WaitForSynchro();
  RTC_WaitForLastTask();
  RTC_SetPrescaler(32767);
  RTC_WaitForLastTask();
  //RTC_SetCounter(0);
}




