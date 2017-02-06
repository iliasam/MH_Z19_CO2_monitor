#ifndef _CO2_SENSOR_H
#define _CO2_SENSOR_H
#include <stdint.h>
#include "main.h"

void request_co2_data(void);
void single_request_co2_data(void);
void co2_sensor_handler(void);
void co2_fifo_add_val(uint16_t value);
void co2_fifo_10min_add_val(uint16_t value);
uint32_t get_time_remain_to_wake(void);
void add_start_value_to_fifo(void);


#endif
