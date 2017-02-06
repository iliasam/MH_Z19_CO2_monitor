#include "SSD1306.h"
#include "stm32f10x_i2c.h"
#include "character_table.h"
#include "i2c_functions.h"


#define OLED_COMMAND_MODE 0x80
#define OLED_DATA_MODE 0x40
#define OLED_DATA_ADDR 0x78

//const uint8_t bar_LUT[8] = {0,1,3,7,15,31,63,127};//перевод из числа в пиксели
const uint8_t bar_LUT[8] = {0,128,192,224,240,248,252,254};//перевод из числа в пиксели

// передача команды
void OLED_WriteCommand(uint8_t data)
{
  I2C_StartTransmission(I2C_Direction_Transmitter, OLED_DATA_ADDR);
  I2C_WriteData(OLED_COMMAND_MODE);
  I2C_WriteData((int)(data));
  I2C_EndTransmission();
}

// передача данных
void OLED_WriteData(uint8_t data)
{
  I2C_StartTransmission (I2C_Direction_Transmitter,OLED_DATA_ADDR); //Wire.beginTransmission(_Addr);
  I2C_WriteData(OLED_DATA_MODE);
  I2C_WriteData((int)(data));
  I2C_EndTransmission();
  //I2C_GenerateSTOP(I2C1, ENABLE); //Wire.endTransmission();
}


void OLED_init(void)
{
  /* Init LCD */
  OLED_WriteCommand(0xAE); //display off
  OLED_WriteCommand(0x20); //Set Memory Addressing Mode
  OLED_WriteCommand(0x10); //00,Horizontal Addressing Mode;01,Vertical	Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  OLED_WriteCommand(0xB0); //Set Page Start Address for Page Addressing	Mode,0-7
  OLED_WriteCommand(0xC8); //Set COM Output Scan Direction
  OLED_WriteCommand(0x00); //---set low column address
  OLED_WriteCommand(0x10); //---set high column address
  OLED_WriteCommand(0x40); //--set start line address
  OLED_WriteCommand(0x81); //--set contrast control register
  OLED_WriteCommand(0xFF);
  OLED_WriteCommand(0xA1); //--set segment re-map 0 to 127
  OLED_WriteCommand(0xA6); //--set normal display
  OLED_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
  OLED_WriteCommand(0x3F); //
  OLED_WriteCommand(0xA4); //0xa4,Output follows RAM	content;0xa5,Output ignores RAM content
  OLED_WriteCommand(0xD3); //-set display offset
  OLED_WriteCommand(0x00); //-not offset
  OLED_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
  OLED_WriteCommand(0xF0); //--set divide ratio
  OLED_WriteCommand(0xD9); //--set pre-charge period
  OLED_WriteCommand(0x22); //
  OLED_WriteCommand(0xDA); //--set com pins hardware configuration
  OLED_WriteCommand(0x12);
  OLED_WriteCommand(0xDB); //--set vcomh
  OLED_WriteCommand(0x20); //0x20,0.77xVcc
  OLED_WriteCommand(0x8D); //--set DC-DC enable
  OLED_WriteCommand(0x14); //
  OLED_WriteCommand(0x2E); // stop scrolling
  OLED_WriteCommand(0xAF); //--turn on SSD1306 panel вот здесь должен засветиться "мусор" на экране
}

void OLED_SetPowerOff(void)
{
  OLED_WriteCommand(OLED_CMD_DISPLAY_OFF);
}


void OLED_SetCursorXY(uint8_t X, uint8_t Y)
{
  // Y - 1 unit = 1 page (8 pixel rows)
  // X - 1 unit = 8 pixel columns
  OLED_WriteCommand(0x00 + (8*X & 0x0F));		//set column lower address
  OLED_WriteCommand(0x10 + ((8*X>>4)&0x0F));	//set column higher address
  OLED_WriteCommand(0xB0 + Y); 				//set page address
}

//accurate
void OLED_SetCursorXY_accur(uint8_t X, uint8_t Y)
{
  // Y - 1 unit = 1 page (8 pixel rows)
  // X - 1 unit = 1 pixel columns
  OLED_WriteCommand(0x00 + (X & 0x0F));		//set column lower address
  OLED_WriteCommand(0x10 + ((X>>4)&0x0F));	//set column higher address
  OLED_WriteCommand(0xB0 + Y); 				//set page address
}

void OLED_ClearDisplay(void)
{
  uint8_t page, column;
  for(page=0; page<8; page++)
  {
    OLED_SetCursorXY(0, page);
    for(column=0; column<128; column++){OLED_WriteData(0);}//clear all columns
  }
  OLED_SetCursorXY(0,0);
}


void OLED_PrintChar(uint8_t C, uint8_t X, uint8_t Y)
{
	uint8_t i;
	if ( X < 128 )	OLED_SetCursorXY(X, Y);

	if (C>191) C=C-192+128;

	uint8_t bb = 0;
	for(i=0; i<5; i++)
	{
		//read bytes from code memory
		if (C!=208 && C!=209)
		{
			bb=BasicFont[C-32][i];
			OLED_WriteData(bb); //font array starts at 0, ASCII starts at 32. Hence the translation
		}
	}
	if  (C!=208 && C!=209 && bb!=0x00)  OLED_WriteData(0x00);
}

void OLED_PrintString(char *str, uint8_t X, uint8_t Y, uint8_t length)
{
  if ( X < (128/5) )	OLED_SetCursorXY(X, Y);
  
  if (length == 0) length = 25;//protection
  
  uint8_t count=0;
  while(str[count] && count<length && (str[count] != 10))
  {
    OLED_PrintChar((uint8_t)str[count++],255,0);//255 - do not move cursor
  }
  
}

void OLED_PrintBigNumber(char *number, uint8_t X, uint8_t Y, uint8_t length)
{
	// big number: 24 x 32
	// Y - page
	uint8_t column = 0;
	uint8_t count = 0;
	uint8_t i;

	while(number[count] && count<length)
	{
		OLED_SetCursorXY(X, Y);

		for(i=0; i<96; i++)
		{
			// if character is not "0-9" or ':'
			if(number[count] < 48 || number[count] > 58)
				OLED_WriteData(0);
			else
				OLED_WriteData(bigNumbers[number[count]-48][i]);

			if(column >= 23)
			{
				column = 0;
				OLED_SetCursorXY(X, ++Y);
			}
			else
				column++;
		}

		count++;
		X = X + 3;
		Y = Y - 4;
	}
}

void test_OLED(void)
{
  OLED_PrintString("ABCDEF", 0, 0, 6);
  OLED_PrintString("Привет", 0, 1, 6);
  OLED_PrintBigNumber("1234",0, 2, 4);
  
}

//16X16 only
void OLED_DrawIcon(uint8_t *pointer,uint8_t X, uint8_t Y)
{
	uint8_t i;
	OLED_SetCursorXY(X, Y);
	for (i=0;i<16;i++) {OLED_WriteData(pointer[i]);}
	OLED_SetCursorXY(X, Y+1);
	for (i=0;i<16;i++) {OLED_WriteData(pointer[i+16]);}
}

/*
void OLED_draw_bar(uint16_t *data)
{
  uint8_t i;
  for (i=0;i<128;i++)
  {
    OLED_draw_single_bar(i, (uint8_t)data[i]);
  }
}

void OLED_draw_single_bar(uint8_t X, uint8_t height)
{
  uint8_t i;
  for (i=0;i<6;i++)//48/8=6
  {
    OLED_SetCursorXY_accur(X, 7-i);//отрисовка снизу вверх
    if (height > 7) {OLED_WriteData(255);height-=8;}
    else  {OLED_WriteData(bar_LUT[height]);height = 0;}
  }
}
*/

void OLED_draw_image(uint8_t *data)
{
  uint16_t i;
  OLED_SetCursorXY(0, 2);
  for (i=0;i<(128*6);i++)//48/8=6
  {
    OLED_WriteData(data[i]);
  }
}
