#ifndef __OLED_H__
#define __OLED_H__


#include <wiringPi.h>

#define byte  unsigned char
#define word  unsigned int
#define dword unsigned long  

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF 
#define X_WIDTH 128
#define Y_WIDTH 64

#define LCD_CS_LOW     digitalWrite(0, 0)
#define LCD_CS_HIGH    digitalWrite(0, 1)

#define LCD_DC_LOW     digitalWrite(1, 0)
#define LCD_DC_HIGH    digitalWrite(1, 1)

#define LCD_SCL_LOW    digitalWrite(4, 0)
#define LCD_SCL_HIGH  digitalWrite(4, 1)

#define LCD_SDA_LOW    digitalWrite(5, 0)
#define LCD_SDA_HIGH  digitalWrite(5, 1)

#define LCD_RST_LOW   digitalWrite(6, 0)
#define LCD_RST_HIGH digitalWrite(6, 1)

//0-CS
//1-DC
//4-SCL
//5-SDA
//6-RST

extern byte LCD_Buffer[128][8];

void LCD_Init(void);
void LCD_CLS(void);
void LCD_P6x8Str(byte x,byte y,byte ch[],byte b);
void LCD_P8x16Str(byte x,byte y,byte ch[]);  
void LCD_Fill(byte dat);
void Num2String(word num,byte len,byte NumString[]);
word LCD_Pow(byte m,byte n);
void LCD_W_Pos(byte x, byte y,byte b);
void LCD_W_BMP(byte x,byte y,byte L,byte W,byte bmp[],byte b);




#endif
