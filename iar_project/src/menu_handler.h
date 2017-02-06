#ifndef _MENU_HANDLER_H
#define _MENU_HANDLER_H

#include "key_handler.h"
typedef enum
{
  MAIN_MODE = 0,
  GRAPH_MODE,
  GRAPH_MODE_10M,//10 minute
  MENU_MODE
}Mode_Status_Type;

#define EXIT_ITEM 0

/*
//различные виды меню с возможностью выбирать подпункты (menu_items_number[])
enum
{
  MAIN_MENU = 0,
  MENU_2,
  MENUS_COUNT //ѕќ—Ћ≈ƒЌяя позици€ - число меню с возможностью выбирать позиции
};
*/



//общие типы подпунктов меню
typedef enum
{
  MENU_LIST = 0,//это меню, содержащее список подпунктов
  MENU_SUBITEM,//это подпункт меню
  MENU_CHANGE_ITEM,//это пункт меню, где можно что-то мен€ть (возвращение - в меню)
  MENU_INFO_ITEM,//это пункт меню, где можно смотреть информацию (возвращение - в главный режим)
  MENU_GOBACK_ITEM,//это пункт меню, возвращающий в предыдущее меню
}Menu_Item_Mode_Type;

typedef struct
{
  uint8_t item_number;//пор€дковый номер пункта меню
  const char     *name;//название пункта
  uint8_t menu_number;//номер меню, к которому принадлежит пункт
  uint8_t next_item;//номер следующего пункта (только дл€ подпункта меню)
  uint8_t menu_position;//номер позиции в текущем меню
  Menu_Item_Mode_Type item_mode;//тип подпункта
} Menu_Item_Type;

void modes_handler(void);
void process_key_action(Key_Status_Type key_stat);
void prosess_key_press_in_menu(Key_Status_Type key_stat);
void menu_item_press(Key_Status_Type key_stat);

void menu_subitem_press(Key_Status_Type key_stat);
uint8_t get_current_item_number(void);
uint8_t get_menu_items_count(void);
void show_menus(void);


void show_main_mode(void);
void show_graph_mode(void);
void show_graph_mode_10min(void);
void show_menu_items(void);
void show_info1(void);
void show_reboot_menu(void);

void fill_status_string(void);

void draw_vert_line(uint8_t x, uint8_t start, uint8_t height);
void draw_vert_dots(uint8_t x);
inline void set_point(uint8_t x, uint8_t y);
void draw_bar(uint16_t *data);
void draw_time_markers(uint8_t period);




#endif
