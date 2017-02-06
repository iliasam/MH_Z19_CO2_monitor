#include "menu_handler.h"
#include "SSD1306.h"
#include "key_handler.h"
#include "hardware_work.h"
#include <stdio.h>
#include "icons.h"
#include "lm75.h"
#include "string.h"

#define IMAGE_SIZE (uint16_t)(128*6)
Mode_Status_Type mode_status = MAIN_MODE;
volatile int16_t temp = 0;

extern Status_Type cur_charging_status;
extern Status_Type cur_ext_power_status;
extern uint16_t cur_battery_voltage;
extern uint8_t low_battery_flag;

extern uint16_t co2_value;
extern uint16_t prev_co2_value;
extern uint32_t time_from_last_co2_request;

extern uint16_t co2_1m_fifo[128];
extern uint16_t co2_10m_fifo[128];

extern uint32_t last_ext_power_time;//время последней  подачи внешнего питания
extern uint32_t boot_start_time;//время с перезагрузки

uint8_t image_buf[IMAGE_SIZE];

uint8_t current_item_number = 0;//номер отображаемого меню (0 - специальные режимы работы)
uint8_t current_selected_pos = 0;//номер текущей выбранной позиции

uint32_t reboot_time = 0;//используется в меню перезагрузки


#define MENUS_COUNT 2
const uint8_t menu_items_number[MENUS_COUNT] = {3,0};//здесь указывается число элементов в каждом меню

enum
{
  MAIN_MENU = 0,
  EXIT,
  INFO1,
  REBOOT
};

Menu_Item_Type menu_items[] = 
{
  //item_number - name - menu_number - next_item - menu_position - item_mode
  {MAIN_MENU,"МЕНЮ\n",  MAIN_MENU, EXIT_ITEM, 0, MENU_LIST},//сюда тоже можно перейти
  
  {EXIT,     "ВЫХОД\n", MAIN_MENU, EXIT_ITEM, 0, MENU_SUBITEM},
  {INFO1,    "ИНФО\n",  MAIN_MENU, INFO1,     1, MENU_INFO_ITEM},
  {REBOOT,   "СБРОС\n", MAIN_MENU, REBOOT,    2, MENU_CHANGE_ITEM},
};

#define TOTAL_ITEMS_NUMBER (sizeof(menu_items)/sizeof(menu_items[0]))

char status_str[32];

//главный обработчик всеж режимов и меню
void modes_handler(void)
{
  static Mode_Status_Type prev_mode_status = MAIN_MODE;
  
  if (prev_mode_status != mode_status)
  {
    OLED_ClearDisplay();
    prev_mode_status = mode_status;
  }
  
  switch (mode_status)
  {
    case MAIN_MODE: show_main_mode(); break;
    case GRAPH_MODE: show_graph_mode(); break;
    case GRAPH_MODE_10M: show_graph_mode_10min(); break;
    case MENU_MODE: show_menus(); break;
    default: break;
  }
}

void show_menus(void)
{
  if (menu_items[current_item_number].item_mode == MENU_LIST) show_menu_items();
  else
  {
    //тут нужно отображать пункты меню - не содержащие списки
    switch (current_item_number)
    {
      case INFO1: {show_info1(); break;}
      case REBOOT: {show_reboot_menu(); break;}
      default: break;
    }
  }
}

//отображает пункты подменю
void show_menu_items(void)
{
  uint8_t i;
  uint8_t cur_item = 0;
  fill_status_string();
  draw_status_info();
  
  for (i=0;i<TOTAL_ITEMS_NUMBER;i++)
  {
    if ((cur_item <6) && (menu_items[i].menu_number == current_item_number) && (menu_items[i].item_mode != MENU_LIST))
    {
      OLED_PrintString((char*)menu_items[i].name, 1, 2+cur_item, 0);//2 - число строк вверху индикатора (желтые)
      if (cur_item == current_selected_pos) OLED_PrintChar(62, 0, 2+cur_item); else OLED_PrintChar(32, 0, 2+cur_item);//draw ">" oe space
      cur_item++;//еще один пункт отображен
    }
  }
}

//обработка нажатия кнопки в ожном из режимов меню
void prosess_key_press_in_menu(Key_Status_Type key_stat)
{
  switch(current_item_number)
  {
    case MAIN_MENU: {menu_subitem_press(key_stat); break;}
    default: {menu_item_press(key_stat); break;}
  }
}

//обработка нажатия кнопки в режиме выбора между подпунктами
//возможны два варианта реакции на нажатие кнопки - выполнение действия, или переход на следующий пункт меню
void menu_subitem_press(Key_Status_Type key_stat)
{
  uint8_t item_pos  = 0;
  if (key_stat == KEY_SHORT)
  {
    current_selected_pos++;
    if (current_selected_pos >= get_menu_items_count()) current_selected_pos = 0;//переход к началу меню
  }
  else if (key_stat == KEY_HOLD)//нужно выполнить действие
  {
    item_pos = get_current_item_number();
    current_selected_pos = 0;//later than get_current_item_number();
    if (menu_items[item_pos].next_item == EXIT_ITEM)//полный выход в главное меню
    {
      //тут может быть функция сохранения данных
      mode_status = MAIN_MODE;
      current_item_number = 0;
    }
    else 
    {
      OLED_ClearDisplay();//подготовить индикатор к отрисовке нового меню
      current_item_number = menu_items[item_pos].next_item;//переход в следующее меню (возможно, назад)
    }
  }
}

//обработка нажатия кнопки внутри одного из пунктов меню
void menu_item_press(Key_Status_Type key_stat)
{
  //uint8_t item_pos = get_current_item_number();
  if (menu_items[current_item_number].item_mode == MENU_INFO_ITEM)
  {
      mode_status = MAIN_MODE;//полный выход из меню
      current_item_number = 0;
  }
  
  if (menu_items[current_item_number].item_number == REBOOT) 
  {
      mode_status = MAIN_MODE;//полный выход из меню
      current_item_number = 0;
      reboot_time = 0;
  }
}

//возвращает число позиций в текущем меню
uint8_t get_menu_items_count(void)
{
  uint8_t current_menu_number = menu_items[current_item_number].menu_number;//это номер того общего меню, в котором находимся сейчас
  return menu_items_number[current_menu_number];//получаем число позиций в этом меню
}

//возвращает порядковый номер выбранной позиции из всего массива menu_items
uint8_t get_current_item_number(void)
{
  uint8_t i;
  for (i=0;i<TOTAL_ITEMS_NUMBER;i++)
  {
    if ((menu_items[i].menu_number == current_item_number) && (menu_items[i].menu_position == current_selected_pos)) return i;
  }
  return 0;//не совсем правильно
  
}

void process_key_action(Key_Status_Type key_stat)
{
  if ((key_stat == KEY_HOLD) && (mode_status != MENU_MODE))
  {
    mode_status = MENU_MODE;//вход в режим меню
    current_item_number = 0;
    return;
  }
  
  switch (mode_status)
  {
    case MAIN_MODE: 
    {
      if (key_stat == KEY_SHORT) mode_status = GRAPH_MODE;
      break;
    }
    case GRAPH_MODE: 
    {
      if (key_stat == KEY_SHORT) mode_status = GRAPH_MODE_10M;
      break;
    }
    case GRAPH_MODE_10M: 
    {
      if (key_stat == KEY_SHORT) mode_status = MAIN_MODE;
      break;
    }
    case MENU_MODE:
    {
      prosess_key_press_in_menu(key_stat);
      break;
    }
    
  default: break;
  }
  

}

void fill_status_string(void)
{
  
  if (low_battery_flag == 1)
  {
    sprintf((char*)&status_str,"LOW BATERY\n");
    return;
  }
  
  switch (mode_status)
  {
    case MAIN_MODE: 
    {
      sprintf((char*)&status_str,"  %d СЕК      \n",(uint16_t)time_from_last_co2_request);
      break;
    }
    case GRAPH_MODE: 
    {
      sprintf((char*)&status_str,"  1 МИН\n");
      break;
    }
    case GRAPH_MODE_10M: 
    {
      sprintf((char*)&status_str,"  10 МИН\n");
      break;
    }
    case MENU_MODE:
    {
      sprintf((char*)&status_str,"  МЕНЮ\n");
      break;
    }
    
    
  default: break;
  }
  
}

//отображение меню с различной информацией
void show_info1(void)
{
  char tmp_str[32];
  fill_status_string();
  draw_status_info();
  
  uint32_t time_now = RTC_GetCounter();
  
  sprintf((char*)&tmp_str,"ВКЛЮЧЕН: %d ч\n",(time_now/3600));
  OLED_PrintString((char*)&tmp_str,0, 2+0,16);
  
  if (last_ext_power_time == 0)
  {
    sprintf((char*)&tmp_str,"ОТ БАТАРЕИ: Неизв.\n");
  }
  else
  {
    uint32_t batt_time = (time_now - last_ext_power_time)/3600;
    sprintf((char*)&tmp_str,"ОТ БАТАРЕИ: %d ч\n",batt_time);
  }
  OLED_PrintString((char*)&tmp_str,0, 2+1,20);
  
  uint32_t reboot_time = (time_now - boot_start_time)/3600;//время с перезагрузки
  sprintf((char*)&tmp_str,"ОТ ПЕРЕЗАГР: %d ч\n",reboot_time);
  OLED_PrintString((char*)&tmp_str,0, 2+2,0);
  
  OLED_PrintString("Версия: 4.1\n",0, 2+3,0);
  OLED_PrintString("Сборка: 27-11-2016\n",0, 2+4,0);
}

//меню с обратным отсчетом до перезагрузки
void show_reboot_menu(void)
{
  char tmp_str[32];
  
  
  fill_status_string();
  draw_status_info();
  
  if (reboot_time == 0) reboot_time =  RTC_GetCounter() + 5;//5 seconds
  
  OLED_PrintString((char*)"ПЕРЕЗАГРУЗКА ЧЕРЕЗ\n",0, 2+2,0);
  
  uint32_t time_ramain = reboot_time - RTC_GetCounter();
  sprintf((char*)&tmp_str,"%d сек\n",time_ramain);
  OLED_PrintString((char*)&tmp_str,0, 2+3,16);
  
  if (time_ramain == 0) full_reboot();
}

//отображение основного режима (с уровнем CO2)
void show_main_mode(void)
{
  char tmp_str[32];
  fill_status_string();
  draw_status_info();
  sprintf((char*)&tmp_str,"%4d\n",co2_value);
  OLED_PrintBigNumber((char*)&tmp_str,0, 2, 4);
  
  sprintf((char*)&tmp_str,"PREV: %d  \n",prev_co2_value);
  OLED_PrintString((char*)&tmp_str,0, 6,0);
}

//1 minute interval
void show_graph_mode(void)
{
  fill_status_string();
  draw_status_info();
  memset(&image_buf[0],0,IMAGE_SIZE);//clean image buffer
  
  draw_bar(&co2_1m_fifo[0]);
  draw_time_markers(10);//every 10 min
  OLED_draw_image(&image_buf[0]);
}

//10 minute interval
void show_graph_mode_10min(void)
{
  fill_status_string();
  draw_status_info();
  memset(&image_buf[0],0,IMAGE_SIZE);//clean image buffer
  
  draw_bar(&co2_10m_fifo[0]);
  draw_time_markers(6);//every hour
  OLED_draw_image(&image_buf[0]);
}


//отрисовка графика CO2
void draw_bar(uint16_t *data)
{
  uint8_t i;
  uint32_t tmp_val = 0;
  for (i=0;i<128;i++) //i - x position
  {
    
    if (data[i] < 401)
    {
      tmp_val = 0;
      if (data[i] == 5) draw_vert_dots(127-i);
    }
    else if (data[i] < 2000) {tmp_val = (data[i] - 400)*47/(2000-400);}
    else tmp_val = 47;

    draw_vert_line(127-i, 1, (uint8_t)tmp_val);
  }
}

void draw_vert_line(uint8_t x, uint8_t start, uint8_t height)
{
  uint8_t i;
  if (height > 47) height = 47;
  for (i=start;i<height;i++){set_point(x, 47-i);}
}

//отрисовывает вертикальный ряд чередующихся точек
//x- координата ряда
void draw_vert_dots(uint8_t x)
{
  uint8_t i;  
  for (i=1;i<47;i++)
  {
    if ((i&2)==0) set_point(x, 47-i);//каждые 2 точки
  }
}

void draw_time_markers(uint8_t period)
{
  uint8_t i;
  for (i=0;i<128;i=i+period) {set_point(127-i, 47);}
}

inline void set_point(uint8_t x, uint8_t y)
{
  uint8_t tmp_y = y/8;
  uint8_t tmp_y2 = y%8;
  image_buf[tmp_y*128+x]|= (1<<tmp_y2);
}



void draw_status_info(void)
{
  char tmp_str[16];
  uint8_t *tmp_pointer;
  
  //Battery
  sprintf((char*)&tmp_str,"%d.%02dV\n",(cur_battery_voltage/100),(cur_battery_voltage%100));
  OLED_PrintString((char*)&tmp_str,12,0,0);
  
  if (cur_ext_power_status == IS_OFF){tmp_pointer =(uint8_t*)&down_icon;}//нет питания
  else
  {
    if (cur_charging_status == IS_ON) tmp_pointer = (uint8_t*)&up_icon; else tmp_pointer = (uint8_t*)&external_icon;
  }
  
  OLED_DrawIcon(tmp_pointer,0, 0);
  
  temp = LM75_Temperature();
  
  //Temperature
  sprintf((char*)&tmp_str,"%d.%dC\n",(temp/10),(temp%10));
  OLED_PrintString((char*)&tmp_str,5,0,0);
  
  
  OLED_PrintString((char*)&status_str,3,1,0);
  memset(&status_str[0],0,10);
}