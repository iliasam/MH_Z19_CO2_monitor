#include "stdint.h"
#ifndef _KEY_HANDLER_H
#define _KEY_HANDLER_H

typedef enum
{
  KEY_LOW = 0,//отпущена
  KEY_PRESSED,//нажата
  KEY_SHORT,//было одиночное нажатие
  KEY_HOLD//было длинное нажатие
}Key_Status_Type;

typedef struct
{
	Key_Status_Type key_status;
	uint16_t time_pressed;
	uint16_t lock_time_remain;//counter for key lock (0- unlocked)
}Key_Struct_Type;

void keys_handler(void);
void update_key_state(Key_Struct_Type *key_state, uint8_t cur_state,uint16_t delta_time);
Key_Status_Type get_key_state(Key_Struct_Type *key_state);
void manual_key_lock(Key_Struct_Type *key_state);

#endif
