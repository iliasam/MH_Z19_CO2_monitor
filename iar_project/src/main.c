#include "main.h"
#include "init_periph.h"
#include "stm32f10x_rcc.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f10x_it.h"
#include "lm75.h"
#include "SSD1306.h"

#include "hardware_work.h"

#include "key_handler.h"
#include "co2_sensor.h"
#include "i2c_functions.h"
#include "stm32f10x_rtc.h"//убрать?
#include "menu_handler.h"


RCC_ClocksTypeDef RCC_Clocks;
void Delay_ms(uint32_t ms);

uint32_t i;

uint32_t start_time;
uint32_t boot_start_time;//время перезанрузки

extern volatile Key_Struct_Type main_key;
extern uint8_t low_battery_flag;

Sleep_Type sleep_mode_flag = IS_WORK;//1- прибор работает в спящем режиме
Wakeup_Type wakeup_signal = NO_WAKEUP;//причина wakeup


volatile uint32_t tmp_val = 0;
int main(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq (&RCC_Clocks);
  if (SysTick_Config (RCC_Clocks.SYSCLK_Frequency/1000)) { /* Setup SysTick for 1 msec interrupts */;while (1);}
  
  init_all_periph();
  set_power_circuts(IS_ON);
  HAL_Delay(1000);
  
  OLED_init();
  LM75_Shutdown(0);
  
  HAL_Delay(100);
  OLED_ClearDisplay();
  test_OLED();
  HAL_Delay(1000);
  
  OLED_ClearDisplay();
  
  start_time = RTC_GetCounter();
  boot_start_time = start_time;
  
  add_start_value_to_fifo();//отметить старт на графиках
        
  while(1)
  {
    wakeup_signal = NO_WAKEUP;//initial state
    co2_sensor_handler();
    update_power_info();
    
    if (sleep_mode_flag == IS_WORK)
    {
      modes_handler();
    }
    
    if (low_battery_flag == 1) HAL_Delay(500);
    
    Key_Status_Type key_stat = get_key_state((Key_Struct_Type*)&main_key);
    if ((key_stat == KEY_SHORT) || (key_stat == KEY_HOLD)) {start_time = RTC_GetCounter(); process_key_action(key_stat);}

    if  (((RTC_GetCounter() - start_time) > 40) || (low_battery_flag == 1))//go to sleep
    {
      //while (get_key_state((Key_Struct_Type*)&main_key) != KEY_LOW) {}//ждем, пока конопку не отпустят
      
      if (low_battery_flag == 1) add_start_value_to_fifo();//отметить просадку напряжения на графиках
      
      OLED_PrintString("SLEEP\n",8,7,0);
      HAL_Delay(1000);
      LM75_Shutdown(1);
      OLED_SetPowerOff();
      sleep_mode_flag = IS_SLEEP;//переход в спящий режим
      wakeup_signal = go_to_sleep_mode();
    }
    /*
    else if (key_stat == KEY_HOLD)
    {
      OLED_PrintString("REBOOT\n",8,7,0);
      full_reboot();
    }
    */
    else if (sleep_mode_flag == IS_SLEEP)
    {
      wakeup_signal = go_to_sleep_mode();
    }
    
    if (wakeup_signal != NO_WAKEUP)//wakeup happened
    {  
      if (wakeup_signal == IS_BUTTON)//key was pressed, must run
      {
        sleep_mode_flag = IS_WORK;
        manual_key_lock((Key_Struct_Type*)&main_key);
      }
      else if (wakeup_signal == IS_RTC) sleep_mode_flag = IS_SLEEP;//так как источником просыпания был RTC, нужно продолжать спать
      wake_after_sleep(sleep_mode_flag);
      start_time = RTC_GetCounter();
    }
  }
}


