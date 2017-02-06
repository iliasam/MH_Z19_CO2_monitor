#include "stm32f10x.h"
#ifndef _SSD1306_H
#define _SSD1306_H

// commands
#define OLED_CMD_DISPLAY_OFF		0xAE
#define OLED_CMD_DISPLAY_ON			0xAF
#define OLED_CMD_NORMAL_DISPLAY		0xA6
#define OLED_CMD_INVERSE_DISPLAY	0xA7
#define OLED_CMD_SET_BRIGHTNESS		0x81


void OLED_init(void);
void OLED_WriteData(uint8_t data);
void OLED_WriteCommand(uint8_t data);

void OLED_SetCursorXY(uint8_t X, uint8_t Y);
void OLED_ClearDisplay(void);
void OLED_PrintChar(uint8_t C, uint8_t X, uint8_t Y);

void test_OLED(void);
void test_OLED2(void);

void OLED_PrintString(char  *str, uint8_t X, uint8_t Y, uint8_t length);
void OLED_PrintBigNumber(char *number, uint8_t X, uint8_t Y, uint8_t length);

void OLED_DrawIcon(uint8_t *pointer,uint8_t X, uint8_t Y);

void OLED_SetPowerOff(void);
void OLED_SetCursorXY_accur(uint8_t X, uint8_t Y);
//void OLED_draw_bar(uint16_t *data);
//void OLED_draw_single_bar(uint8_t X, uint8_t height);
void OLED_draw_image(uint8_t *data);


#endif
