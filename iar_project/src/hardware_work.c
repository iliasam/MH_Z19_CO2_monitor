#include "hardware_work.h"
#include "init_periph.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_it.h"
#include "stm32f10x_rtc.h"
#include "LM75.h"
#include "SSD1306.h"
#include "key_handler.h"
#include "co2_sensor.h"
#include "main.h"


Status_Type cur_charging_status = IS_OFF;
Status_Type cur_ext_power_status = IS_OFF;
uint16_t cur_battery_voltage = 0;
uint8_t low_battery_flag = 0;
uint32_t last_ext_power_time  = 0;//время последней  подачи внешнего питания

void update_power_info(void)
{
  cur_charging_status  = get_charging_status();
  cur_ext_power_status = get_ext_power_status();
  cur_battery_voltage  = get_battery_voltage();
  if ((cur_battery_voltage < 360) && (low_battery_flag == 0)) {low_battery_flag = 1;}
  else if ((cur_battery_voltage > 360) && (low_battery_flag == 1)) {low_battery_flag = 0;}
  
  if (cur_ext_power_status == IS_ON) last_ext_power_time = RTC_GetCounter();
}

void set_power_circuts(Status_Type state)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Pin   = POWER_ON_PIN;
  if (state == IS_ON)
  {
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_ResetBits(POWER_ON_PORT,POWER_ON_PIN);
  }
  else
  {
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//to use external pull-up
  }
  GPIO_Init(POWER_ON_PORT, &GPIO_InitStructure);
}

//состояние процесса заряда аккумулятора
Status_Type get_charging_status(void)
{
  if (GPIO_ReadInputDataBit(CHARGE_DET_PORT,CHARGE_DET_PIN) == Bit_RESET) {return IS_ON;} else  {return IS_OFF;}
}

//состояние внешнего питания
Status_Type get_ext_power_status(void)
{
  if (GPIO_ReadInputDataBit(EXT_POWER_PORT,EXT_POWER_PIN) == Bit_SET) {return IS_ON;} else  {return IS_OFF;}
}

uint16_t get_battery_voltage(void)
{
  uint16_t adc_result = 0;
  
  uint8_t i;
  for (i=0;i<4;i++)
  {
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    adc_result+= ADC_GetConversionValue(ADC1);
  }
  adc_result = adc_result/4;//adc value
  adc_result = adc_result*4/25;//voltage
  return adc_result;
}

//функция ухода в спящий режим
//при выходе из спящего режима по RTC или кнопке эта функция продолжает выполняться
//возвращает код события, вызвавшего просыпание
Wakeup_Type go_to_sleep_mode(void)
{
  I2C_DeInit(I2C1);
  ADC_Cmd(ADC1, DISABLE);
  HAL_Delay(20);
  EXTI_Configuration(ENABLE);
  
  RTC_SetAlarm(RTC_GetCounter()+get_time_remain_to_wake());
  RTC_WaitForLastTask();
  
  if (low_battery_flag == 1) go_to_baterry_saving_mode();
  
  PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFE);
  //here program is running again
  
  EXTI_Configuration(DISABLE);
  
  if (GPIO_ReadInputDataBit(BUTTON_PORT,BUTTON_PIN) == Bit_RESET) {return IS_BUTTON;}//button pressed now
  else {return IS_RTC;}//rtc
}

void EXTI_Configuration(FunctionalState state)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  EXTI_ClearITPendingBit(EXTI_Line7);
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = state;
  EXTI_Init(&EXTI_InitStructure);
  
  
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = state;
  EXTI_Init(&EXTI_InitStructure);
}

#define I2C_MAX_RESET_FAIL_COUNT 20

static inline void i2c_delay(void)
{
  for (__IO int j = 0; j < 50; j++) {asm("nop");}
}

//taken from docs.paparazziuav.org
void i2c_hard_reset(void)
{
  uint8_t timeout_fails=0;
  //I2C_TypeDef *regs = (I2C_TypeDef *) p->reg_addr;

  I2C_DeInit(I2C1);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN | I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_SetBits(I2C_GPIO_PORT, I2C_SDA_PIN | I2C_SCL_PIN);
  GPIO_Init(I2C_GPIO_PORT, &GPIO_InitStructure);

  while((GPIO_ReadInputDataBit(I2C_GPIO_PORT, I2C_SDA_PIN) == Bit_RESET) && timeout_fails < I2C_MAX_RESET_FAIL_COUNT) 
  {
    // Raise SCL, wait until SCL is high (in case of clock stretching)
    GPIO_SetBits(I2C_GPIO_PORT, I2C_SCL_PIN);
    while ((GPIO_ReadInputDataBit(I2C_GPIO_PORT, I2C_SCL_PIN) == Bit_RESET) && timeout_fails < I2C_MAX_RESET_FAIL_COUNT) 
    {
      i2c_delay();
      timeout_fails++;
    }
    i2c_delay();

    // Lower SCL, wait
    GPIO_ResetBits(I2C_GPIO_PORT, I2C_SCL_PIN);
    i2c_delay();

    // Raise SCL, wait
    GPIO_SetBits(I2C_GPIO_PORT, I2C_SCL_PIN);
    i2c_delay();
    timeout_fails++;
  }

  // Generate a start condition followed by a stop condition
  GPIO_SetBits(I2C_GPIO_PORT, I2C_SCL_PIN);
  i2c_delay();
  GPIO_ResetBits(I2C_GPIO_PORT, I2C_SDA_PIN);
  i2c_delay();
  GPIO_ResetBits(I2C_GPIO_PORT, I2C_SDA_PIN);
  i2c_delay();

  // Raise both SCL and SDA and wait for SCL high (in case of clock stretching)
  GPIO_SetBits(I2C_GPIO_PORT, I2C_SCL_PIN | I2C_SDA_PIN);
  while (GPIO_ReadInputDataBit(I2C_GPIO_PORT, I2C_SCL_PIN) == Bit_RESET && timeout_fails < I2C_MAX_RESET_FAIL_COUNT)
  {
    i2c_delay();
    timeout_fails++;
  }

  // Wait for SDA to be high
  while (GPIO_ReadInputDataBit(I2C_GPIO_PORT, I2C_SDA_PIN) != Bit_SET && timeout_fails < I2C_MAX_RESET_FAIL_COUNT)
  {
    i2c_delay();
    timeout_fails++;
  }

  // SCL and SDA should be high at this point, bus should be free
  // Return the GPIO pins to the alternate function
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(I2C_GPIO_PORT, &GPIO_InitStructure);

  I2C_DeInit(I2C1);

  if (I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY)) {
    // Reset the I2C block
    I2C_SoftwareResetCmd(I2C1, ENABLE);
    I2C_SoftwareResetCmd(I2C1, DISABLE);
  }
}

void full_reboot(void)
{
  set_power_circuts(IS_OFF);
  HAL_Delay(200);
  NVIC_SystemReset();
}

void go_to_baterry_saving_mode(void)
{
  set_power_circuts(IS_OFF);
  RCC_RTCCLKCmd(DISABLE);
}


void wake_after_sleep(Sleep_Type sleep_flag)
{
  set_power_circuts(IS_ON);
  RCC_RTCCLKCmd(ENABLE);
  HAL_Delay(100);
  if (sleep_flag == IS_WORK)//key was pressed
  {
    init_all_periph();
    LM75_Shutdown(0);
    OLED_init();
    OLED_PrintString("RUN   \n",8,7,0);
  }
  else
  {
    init_adc();//for controlling votage
    i2c_init();
    //init_all_periph();
    //LM75_Shutdown(0);
    //alarm happened
  }
}


