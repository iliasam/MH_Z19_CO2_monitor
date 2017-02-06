#ifndef _MAIN_H
#define _MAIN_H

typedef enum
{
  IS_WORK = 0,
  IS_SLEEP
}Sleep_Type;

typedef enum
{
  NO_WAKEUP = 0,
  IS_BUTTON,
  IS_RTC
}Wakeup_Type;


typedef enum
{
  IS_OFF = 0,
  IS_ON
}Status_Type;

void draw_status_info(void);


#endif
