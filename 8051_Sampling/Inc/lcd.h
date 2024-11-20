#ifndef __LCD_H__
#define __LCD_H__

	#define	W_CMD 1 // 命令
	#define	W_DAT 0	// 数据
	#define Set_LCD_RS  P4 |= 0x08  // 宏定义，对LCD_RS进行位操作。拉高LCD的RS线，从而选择了数据寄存器
	#define Clr_LCD_RS  P4 &= ~0x08 // 宏定义，对LCD_RS进行位操作。拉低LCD的RS线，从而选择了命令寄存器
	#define Set_LCD_RST P4 |= 0x80 	// 宏定义，对LCD_RST进行位操作。拉高LCD的RST线，用于取消复位（通常是在LCD初始化之后）
	#define Clr_LCD_RST P4 &= ~0x80 // 宏定义，对LCD_RST进行位操作。拉低LCD的RST线，用于用于执行复位操作
	// #define High_contrast 0xA2 // 10100010，1/9偏压
	// #define low_contrast 0xA3 // 10100011，1/7偏压

	void Delayms(unsigned int ms);
	void WriteCMD(unsigned char cmd);
	void WriteData(unsigned char dat);
	void LCDWrite(unsigned char type,unsigned char dat);
	void LCDInit();
	void LCD_setXY(unsigned char X, unsigned char Y);
	void LCD_draw_point(unsigned char x,unsigned char y);
	void DrawPoint(unsigned char pixel_x,unsigned char pixel_y);
	void Clear();
	void Drawchar(unsigned char C,unsigned char row,unsigned char col);
	void DrawcharS(unsigned char *C,unsigned char row,unsigned char col);



#endif