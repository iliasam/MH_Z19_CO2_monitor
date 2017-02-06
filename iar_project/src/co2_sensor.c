#include "co2_sensor.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_it.h"

#define SENSOR_REFRESH_TIME (uint32_t)8
#define SENSOR_RTC_REFRESH_TIME (uint32_t)60

uint16_t co2_value = 0;
uint16_t prev_co2_value = 0;


uint16_t co2_1m_fifo[128] = {400};
uint16_t co2_10m_fifo[128] = {400};

uint32_t old_rtc_value_long = 0;
uint32_t time_from_last_co2_request = 0;

uint8_t minute_counter = 0;
uint16_t co2_10min_integration = 0;

void co2_sensor_handler(void)
{
  static uint32_t old_rtc_value = 0;
  
  time_from_last_co2_request = RTC_GetCounter() - old_rtc_value;
  
  if (time_from_last_co2_request > SENSOR_REFRESH_TIME)
  {
    prev_co2_value = co2_value;
    request_co2_data();
    old_rtc_value = RTC_GetCounter();
    
  }
  //1 minute
  if ((RTC_GetCounter() - old_rtc_value_long) > (SENSOR_RTC_REFRESH_TIME-2))
  {
    old_rtc_value_long = RTC_GetCounter();
    co2_fifo_add_val(co2_value);
    minute_counter++;
    if (co2_value<400){co2_10min_integration+=prev_co2_value;}//error
    else {co2_10min_integration+=co2_value;}
    
    if (minute_counter == 10)
    {
      minute_counter = 0;
      co2_fifo_10min_add_val(co2_10min_integration/10);
      co2_10min_integration = 0;
    }
  }
}

void request_co2_data(void)
{
  uint8_t i;
  
  for (i=0;i<3;i++)
  {
    single_request_co2_data();
    if (co2_value > 400) break;
  }
}

void single_request_co2_data(void)
{
  uint8_t tx_array[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  uint8_t rx_array[9] = {0x00};
  uint8_t i;
  uint32_t start_time = 0;
  
  //USART_ClearFlag(USART1, USART_FLAG_RXNE);//do not work
  rx_array[8] = USART_ReceiveData(USART1);//for cleaning USART_FLAG_RXNE
  
  for (i=0;i<9;i++)
  {
    USART_SendData(USART1, (uint16_t)tx_array[i]);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
  }
  
  for (i=0;i<9;i++)
  {
    start_time = HAL_GetTick();
    while((!USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) && ((HAL_GetTick() - start_time) < 10));
    if ((HAL_GetTick() - start_time) < 10)
    {
      rx_array[i] = USART_ReceiveData(USART1);
    }
    else
    {
      rx_array[i] = 1;
    }
  }
  
  if (rx_array[1] == 0x86)
  {
    co2_value = (uint16_t)rx_array[2]*256 + (uint16_t)rx_array[3];
  }
  else
  {
    co2_value = 10;
  }
}

//0 значение - самое новое
void co2_fifo_add_val(uint16_t value)
{
  uint8_t i;
  if ((value < 400) && (value != 5) && (co2_1m_fifo[0] !=5))
  {
      value = co2_1m_fifo[0];//защита от ошибок - добавляется старое значение
  }
  for (i=127;i>0;i--){co2_1m_fifo[i] = co2_1m_fifo[i-1];}
  co2_1m_fifo[0] = value;
}

void co2_fifo_10min_add_val(uint16_t value)
{
  uint8_t i;
  if ((value < 400) && (value != 5) && (co2_10m_fifo[0] !=5))
  {
      value = co2_10m_fifo[0];//защита от ошибок - добавляется старое значение
  }
  
  for (i=127;i>0;i--){co2_10m_fifo[i] = co2_10m_fifo[i-1];}
  co2_10m_fifo[0] = value;
}

//возвращает оставшееся время в сек до автомат. включения (кажые 1МИН)
uint32_t get_time_remain_to_wake(void)
{
  uint32_t tmp_val = (SENSOR_RTC_REFRESH_TIME) - (RTC_GetCounter() - old_rtc_value_long);
  if (tmp_val > SENSOR_RTC_REFRESH_TIME) tmp_val = SENSOR_RTC_REFRESH_TIME;//защита
  return tmp_val;
}

//в оба fifo добавляются значение 5 - будет отображено специальной линией
//нужно, чтобы на графике было видно перезагрузку датчика co2
void add_start_value_to_fifo(void)
{
  co2_fifo_add_val(5);
  co2_fifo_10min_add_val(5);
}
