#ifndef _HARDWARE_WORK_H
#define _HARDWARE_WORK_H


#include "stm32f10x.h"
#include "main.h"

void set_power_circuts(Status_Type state);
Status_Type get_charging_status(void);
Status_Type get_ext_power_status(void);
uint16_t get_battery_voltage(void);
void update_power_info(void);
Wakeup_Type go_to_sleep_mode(void);
void EXTI_Configuration(FunctionalState state);
void full_reboot(void);
void wake_after_sleep(Sleep_Type sleep_flag);
void i2c_hard_reset(void);
void go_to_baterry_saving_mode(void);

#endif
