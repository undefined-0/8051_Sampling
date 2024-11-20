#ifndef __LCD_H__
#define __LCD_H__

	#define	W_CMD 1 // ����
	#define	W_DAT 0	// ����
	#define Set_LCD_RS  P4 |= 0x08  // �궨�壬��LCD_RS����λ����������LCD��RS�ߣ��Ӷ�ѡ�������ݼĴ���
	#define Clr_LCD_RS  P4 &= ~0x08 // �궨�壬��LCD_RS����λ����������LCD��RS�ߣ��Ӷ�ѡ��������Ĵ���
	#define Set_LCD_RST P4 |= 0x80 	// �궨�壬��LCD_RST����λ����������LCD��RST�ߣ�����ȡ����λ��ͨ������LCD��ʼ��֮��
	#define Clr_LCD_RST P4 &= ~0x80 // �궨�壬��LCD_RST����λ����������LCD��RST�ߣ���������ִ�и�λ����
	// #define High_contrast 0xA2 // 10100010��1/9ƫѹ
	// #define low_contrast 0xA3 // 10100011��1/7ƫѹ

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