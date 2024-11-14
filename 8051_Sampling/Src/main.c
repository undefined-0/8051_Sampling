/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F020.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"
#include "math.h"
#include "string.h"


unsigned int func_flag = 0; // 0->���δ洢��������ʾ  1->ʵʱ�洢��ʵʱ��ʾ
// Peripheral specific initialization functions,
// Called from the Init_Device() function
void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
    RSTSRC    = 0x04;
}

void Timer_Init()
{
    CKCON     = 0x20; // ��ʱ�� 2 ʹ��ϵͳʱ�ӣ���ʱ�� 1 ʹ��ϵͳʱ�ӵ� 12 ��Ƶ
    TMR3CN    = 0x06; // ��ʱ�� 3 ����ʹ��ϵͳʱ��
    TMR3RLL   = 0xA0;
    TMR3RLH   = 0xFF;
}

void ADC_Init()
{
    ADC0CN    = 0x84;// ADC0ʹ�ܣ���ʱ��3������� ADC0 ת����ADC0L�Ĵ��������Ҷ���
}

void DAC_Init()
{
    DAC0CN    = 0x88; // DAC0 ʹ�ܣ�DAC ������·����ڶ�ʱ��3���ʱ
    DAC1CN    = 0x80; // DAC1 ʹ�ܣ�DAC ������·�����д DAC1H ʱ
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x03; // �ڲ�ƫѹ�������������ڲ���ѹ��׼�������������ڲ���ѹ��׼�ṩ�� VREF ���������
}

void Port_IO_Init()
{
    // P0.0  -  Unassigned,  Open-Drain, Digital
    // P0.1  -  Unassigned,  Open-Drain, Digital
    // P0.2  -  Unassigned,  Open-Drain, Digital
    // P0.3  -  Unassigned,  Open-Drain, Digital
    // P0.4  -  Unassigned,  Open-Drain, Digital
    // P0.5  -  Unassigned,  Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Push-Pull,  Digital
    // P3.5  -  Unassigned,  Push-Pull,  Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Open-Drain, Digital

    P3MDOUT   = 0x30; // P3.2-P3.7Ϊ©����·�����P3.4��P3.5Ϊ�������
    XBR2      = 0x40; // ���濪��ʹ��
}

void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0); // ֱ��OSCXCN���λΪ1�����������������в��ҹ����ȶ���ʱ������ѭ������ִ��
    OSCICN    = 0x08; // ѡ���ⲿ������Ϊϵͳʱ��
}

void Interrupts_Init()
{
    IE        = 0x80; // ���������ж�
    EIE2      = 0x03; // ���� ADC0 ת�������жϣ�����ʱ�� 3 �жϣ����� TF3 ��־λ��TMR3CN.7�����ж�����
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    Reset_Sources_Init();
    Timer_Init();
    ADC_Init();
    DAC_Init();
    Voltage_Reference_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}


main()
{

 	 unsigned char key=0,x=0,y=0;
	 unsigned int i=0,j=0;
	 Init_Device();
     memset(adcmem, 0, sizeof(adcmem));
	 newLCDInit();
	 Clear();
	 LCDWrite(W_CMD,0xA6);	  //����������           
	 while(1)
	 {
	   j++;	        
	   if(j>10000) {j=0;Clear();//P5=P5+1;
	   } 
   	   if(j<128){ DrawPoint(j,(adcmem[(j*20)%1000])>>6);}	   //��������ʾ����

       key = KeyScan();
	   if(key == 1){Clear();func_flag = !func_flag;} // ����key1��ģʽ�л�
	   	   /*
		if(key != 0)
		{
			switch(key)
			{
			   case 1:	Clear();
			   			for(x=0;x<128;x++)
			             {
							LCD_draw_point(x,0); // LCD���Ͻ�Ϊԭ��Ӵ�� X��0��127  Y��0��7 λ�û���  һ��һ�а˸���Ӵ�� 
						 }   
						 break;
			   case 2:  Clear();
			   			for(x=0;x<128;x++)
			             {
							LCD_draw_point(x,1);
						 }   
						 break;
			   case 3:	Clear();
			   			for(x=0;x<128;x++)
			             {
							DrawPoint(x,0);	    // LCD���½�Ϊ����ԭ�� x:0~127 y :0~63	  ��������ͬһ��ʾ�ֽ�ʱ,����ԭʼ���ݣ����㣡
						 }   
						 break;
			   case 4:  Clear();
			   			for(x=0;x<128;x++)
			             {
							DrawPoint(x,1);
						 }   
						 break;
			   case 5:	DrawPoint(63,0);		//��һ����
						break;
			   case 6:  LCD_draw_point(63,0);   //���˸���
						break;
			   case 7:	for(i=0;i<127;i++)		//��һʮ�֣�ע���Ⱥ�Ӵ��
						{
							DrawPoint(i,31);
						}

		    		   for(i=0;i<64;i++)
						{
							DrawPoint(63,i);	
						}
						break;
			   case 8:  Clear();
			            DrawcharS("abcdefghijklmnopqrstuvwxyz",0,0);  //ÿ�����16���ַ�������16�����У���4�У�LCD���Ͻ�Ϊԭ��Ӵ��
			            P5&=(~0x01);	 //����LED
						break;
			   case 9:	Clear();
			            for(i=0;i<64;i++)
   					    DrawPoint(i,i);
			            for(i=64;i<127;i++)
   					    DrawPoint(i,127-i);
			            P5|=0x01;	 //��LED
						break;
			}
		 x=0;
		 y=0;
		 key=0;

	    }
		*/
	 }
}
