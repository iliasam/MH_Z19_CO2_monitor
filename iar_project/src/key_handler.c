#include "key_handler.h"
#include "init_periph.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_it.h"

volatile Key_Struct_Type main_key = {KEY_LOW,0,0};

void keys_handler(void)
{
  static uint32_t old_time = 0;
  uint16_t delta_time = (uint16_t)(HAL_GetTick() - old_time);
  if (delta_time > 10)
  {
    old_time = HAL_GetTick();
    
    uint8_t new_key_state = 0;
    if (GPIO_ReadInputDataBit(BUTTON_PORT,BUTTON_PIN) == Bit_RESET) new_key_state = 1; else new_key_state = 0;
    update_key_state((Key_Struct_Type*)&main_key,new_key_state,delta_time);
  }
  
}

void update_key_state(Key_Struct_Type *key_state, uint8_t cur_state,uint16_t delta_time)
{
  if (key_state->lock_time_remain > 0)//lock key
  {
    key_state->key_status = KEY_LOW;
    key_state->lock_time_remain = key_state->lock_time_remain-delta_time;//count time
    if (key_state->lock_time_remain > 32768) key_state->lock_time_remain = 0;//zero cross
    return;
  }
  
  if (cur_state == 0)//not pressed
  {
    if (key_state->key_status == KEY_PRESSED)
    {
      if (key_state->time_pressed > 100)//key was pressed more tan 150 ms and than released
      {
        key_state->key_status = KEY_SHORT;//time counting is 0 (see down)
      }
      else//short pulse
      {
        key_state->key_status = KEY_LOW;//time counting is 0 (see down)
      }
    }
    key_state->time_pressed = 0;//if button is not pressed than clear counter
  }//end if - not pressed
  if (cur_state == 1)//pressed
  {
    if (key_state->key_status == KEY_PRESSED) {key_state->time_pressed+=delta_time;}//count press time
    
    if (key_state->key_status == KEY_LOW) {key_state->key_status = KEY_PRESSED;key_state->time_pressed+=delta_time;}
    else if ((key_state->key_status == KEY_PRESSED) && (key_state->time_pressed > 900))//key was pressed more than 1000ms
    {
      key_state->key_status = KEY_HOLD;//time counting stopped
    }
  }
}

Key_Status_Type get_key_state(Key_Struct_Type *key_state)
{
  Key_Status_Type result = key_state->key_status;
  //временно заблокировать кнопку
  if ((key_state->key_status == KEY_SHORT) || (key_state->key_status == KEY_HOLD))//reset button state
  {
    key_state->key_status = KEY_LOW;
    key_state->time_pressed = 0;
    key_state->lock_time_remain = 600;//enable lock
  }
  return result;
}

void manual_key_lock(Key_Struct_Type *key_state)
{
    key_state->key_status = KEY_LOW;
    key_state->time_pressed = 0;
    key_state->lock_time_remain = 600;//enable lock
}
