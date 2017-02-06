#include "stm32f10x.h"
#ifndef _INIT_PERIPH_H
#define _INIT_PERIPH_H


#define I2C_SDA_PIN GPIO_Pin_9
#define I2C_SCL_PIN GPIO_Pin_8
#define I2C_GPIO_PORT GPIOB

#define UART_RX_PIN GPIO_Pin_7
#define UART_TX_PIN GPIO_Pin_6
#define UART_PORT GPIOB

#define SPI_MOSI_PIN GPIO_Pin_5
#define SPI_MISO_PIN GPIO_Pin_4
#define SPI_SCK_PIN  GPIO_Pin_3
#define SPI_PORT GPIOB

#define NRF24_SCN_PIN GPIO_Pin_13//output
#define NRF24_SCN_PORT GPIOC

#define NRF24_CE_PIN GPIO_Pin_15//output
#define NRF24_CE_PORT GPIOA

#define BATT_VOLT_PIN GPIO_Pin_3//adc
#define BATT_VOLT_PORT GPIOA

#define EXT_POWER_PIN GPIO_Pin_12//external power detection - input
#define EXT_POWER_PORT GPIOB

#define BUTTON_PIN GPIO_Pin_7//button input
#define BUTTON_PORT GPIOA

#define POWER_ON_PIN GPIO_Pin_12//enable power cicruts - output
#define POWER_ON_PORT GPIOA

#define CHARGE_DET_PIN GPIO_Pin_8//charge detection - input
#define CHARGE_DET_PORT GPIOA

void init_all_periph(void);
void init_clk(void);
void init_gpio(void);
void i2c_init(void);
void init_adc(void);
void init_uart(void);
void rtc_init(void);

#endif
