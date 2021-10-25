#include "oled.h"
#include "oledfont.h"

byte LCD_Buffer[128][8];

void delayms(void)
{
	//delay(1);
	//usleep(2);
	int ms=10;                    
	word a;
	while(ms)
	{
		a=10;
		while(a--);
		ms--;
	}
}

void LCD_WrDat(byte data)
{
	byte i;			  
	 LCD_DC_HIGH;	  
	LCD_CS_LOW;
	delayms();
	for(i=0;i<8;i++)
	{			  
		LCD_SCL_LOW;
		delayms();
		if(data&0x80)
		{
		   LCD_SDA_HIGH;
		}
		else
		   LCD_SDA_LOW;
		LCD_SCL_HIGH;
		data<<=1;   
		delayms();
	}	
delayms();	
	LCD_CS_HIGH;
	LCD_DC_HIGH;
delayms();	
}

void LCD_WrCmd(byte cmd)
{
	byte i;			  
	LCD_DC_LOW;		  
	LCD_CS_LOW;
	delayms();
	for(i=0;i<8;i++)
	{			  
		LCD_SCL_LOW;
		delayms();
		if(cmd&0x80)
		{
		   LCD_SDA_HIGH;
		}
		else
		   LCD_SDA_LOW;
	   
		LCD_SCL_HIGH;
		cmd<<=1;   
		delayms();
	}	
delayms();	
	LCD_CS_HIGH;
	LCD_DC_HIGH;  
	delayms();
}

void LCD_Set_Pos(byte x, byte y)
{ 
	LCD_WrCmd(0xb0+y);
	LCD_WrCmd(((x&0xf0)>>4)|0x10);
	LCD_WrCmd((x&0x0f)|0x00); 
} 
void LCD_W_Pos(byte x, byte y,byte b) //x(0-127) y(0-63)
{
	byte y0=0;
	y0 = y/8;
	if(b)
		LCD_Buffer[x][y0] = ((char)(0x01<<(y%8))|LCD_Buffer[x][y0]);
	else LCD_Buffer[x][y0] = ((char)(~(0x01<<(y%8)))&LCD_Buffer[x][y0]);
}
void LCD_CW_Pos(byte x, byte y) //x(0-127) y(0-63)
{
	byte y0=0;
	y0 = y/8;
	LCD_Set_Pos(x,y0);
	LCD_WrDat(0x01<<(y%8));
}

void LCD_Fill(unsigned char bmp_dat)
{
	unsigned char y,x;
	
	for(y=0;y<8;y++)
	{
		LCD_WrCmd(0xb0+y);
		LCD_WrCmd(0x01);
		LCD_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
			LCD_WrDat(bmp_dat);
	}
}
void LCD_CLS(void)
{
	byte y,x;	
	for(y=0;y<8;y++)
	{
		LCD_WrCmd(0xb0+y);
		LCD_WrCmd(0x01);
		LCD_WrCmd(0x10); 
		for(x=0;x<X_WIDTH;x++)
			LCD_WrDat(0x00);
	}
}
void LCD_DLY_ms(word ms)
{                         
	word a;
	while(ms)
	{
		a=50;
		while(a--);
		ms--;
	}
	return;
} 

//初始化SSD1306					    
void LCD_Init(void)
{
 
	byte i;
	wiringPiSetup();  
    for( i = 0 ; i < 8 ; i++ )  
        pinMode(i, OUTPUT);  
 
    LCD_RST_HIGH;
	LCD_DLY_ms(100);
	LCD_RST_LOW;
	LCD_DLY_ms(100);
	LCD_RST_HIGH; 

	LCD_WrCmd(0xAE);//--turn off oled panel
	LCD_WrCmd(0x00);//---set low column address
	LCD_WrCmd(0x10);//---set high column address
	LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	LCD_WrCmd(0x81);//--set contrast control register
	LCD_WrCmd(0xCF); // Set SEG Output Current Brightness
	LCD_WrCmd(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	LCD_WrCmd(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	LCD_WrCmd(0xA6);//--set normal display
	LCD_WrCmd(0xA8);//--set multiplex ratio(1 to 64)
	LCD_WrCmd(0x3f);//--1/64 duty
	LCD_WrCmd(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	LCD_WrCmd(0x00);//-not offset
	LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	LCD_WrCmd(0xD9);//--set pre-charge period
	LCD_WrCmd(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	LCD_WrCmd(0xDA);//--set com pins hardware configuration
	LCD_WrCmd(0x12);
	LCD_WrCmd(0xDB);//--set vcomh
	LCD_WrCmd(0x40);//Set VCOM Deselect Level
	LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	LCD_WrCmd(0x02);//
	LCD_WrCmd(0x8D);//--set Charge Pump enable/disable
	LCD_WrCmd(0x14);//--set(0x10) disable
	LCD_WrCmd(0xA4);// Disable Entire Display On (0xa4/0xa5)
	LCD_WrCmd(0xA6);// Disable Inverse Display On (0xa6/a7) 
	LCD_WrCmd(0xAF);//--turn on oled panel

	LCD_Fill(0xF0);  //初始清屏
	LCD_Set_Pos(0,0); 	
}  

void LCD_P6x8Str(byte x,byte y,byte ch[],byte b)
{
	unsigned char c=0,i=0,j=0;      
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		for(i=0;i<6;i++)   
		{
			if(b)
				LCD_Buffer[x][y]=(F6x8[c][i]);  
			else
				LCD_Buffer[x][y]=(~F6x8[c][i])&LCD_Buffer[x][y];
			x++;
		}
		j++;
	}
}

void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		LCD_Set_Pos(x,y);    
		for(i=0;i<8;i++)     
			LCD_WrDat(F8X16[c*16+i]);
		LCD_Set_Pos(x,y+1);    
		for(i=0;i<8;i++)     
			LCD_WrDat(F8X16[c*16+i+8]);  
		x+=8;
		j++;
	}
}

void Draw_BMP(byte bmp[])
{ 	
	byte x,y;
	word ii=0;
	
	for(x=0;x<128;x++)
		for(y=0;y<8;y++)
		{
			LCD_Set_Pos(x,y);	
			LCD_WrDat(bmp[ii++]);
		}
}
void LCD_W_BMP(byte x,byte y,byte L,byte W,byte bmp[],byte b)
{
	byte x0,y0,Wei=0;
	word ii=0;
	for(x0=x;x0<x+L;x0++)
		for(y0=y;y0<y+W;y0++)
		{
				if((bmp[ii]>>Wei)&0x01)
					if(b)
						LCD_W_Pos(x0,y0,1);
					else
						LCD_W_Pos(x0,y0,0);
			Wei++;
			if(Wei==8)
			{
				Wei=0;
				ii++;
			}
		}	
}
//m^n
word LCD_Pow(byte m,byte n)
{
	word result=1;	 
	while(n--)result*=m;    
	return result;
}	

void Num2String(word num,byte len,byte NumString[])
{         	
	byte t,temp;
	byte enshow=0;				
//	byte NumString[10];
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				NumString[t]=' ';
				continue;
			}else enshow=1; 
		 	 
		}
	 	NumString[t] = temp+'0'; 
	}
	NumString[t] = '\0'; 
//	LCD_P6x8Str(x,y,NumString,byte);
} 
