/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F020.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"
#include "math.h"
#include "string.h"


unsigned int func_flag = 0; // 0->单次存储、连续显示  1->实时存储、实时显示
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
    CKCON     = 0x20; // 定时器 2 使用系统时钟，定时器 1 使用系统时钟的 12 分频
    TMR3CN    = 0x06; // 定时器 3 允许，使用系统时钟
    TMR3RLL   = 0xA0;
    TMR3RLH   = 0xFF;
}

void ADC_Init()
{
    ADC0CN    = 0x84;// ADC0使能，定时器3溢出启动 ADC0 转换，ADC0L寄存器数据右对齐
}

void DAC_Init()
{
    DAC0CN    = 0x88; // DAC0 使能，DAC 输出更新发生在定时器3溢出时
    DAC1CN    = 0x80; // DAC1 使能，DAC 输出更新发生在写 DAC1H 时
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x03; // 内部偏压发生器工作，内部电压基准缓冲器工作，内部电压基准提供从 VREF 引脚输出。
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

    P3MDOUT   = 0x30; // P3.2-P3.7为漏极开路输出，P3.4和P3.5为推挽输出
    XBR2      = 0x40; // 交叉开关使能
}

void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0); // 直到OSCXCN最高位为1（晶体振荡器正在运行并且工作稳定）时才跳出循环往下执行
    OSCICN    = 0x08; // 选择外部振荡器作为系统时钟
}

void Interrupts_Init()
{
    IE        = 0x80; // 允许所有中断
    EIE2      = 0x03; // 允许 ADC0 转换结束中断，允许定时器 3 中断（允许 TF3 标志位（TMR3CN.7）的中断请求）
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
	 LCDWrite(W_CMD,0xA6);	  //正常显命令           
	 while(1)
	 {
	   j++;	        
	   if(j>10000) {j=0;Clear();//P5=P5+1;
	   } 
   	   if(j<128){ DrawPoint(j,(adcmem[(j*20)%1000])>>6);}	   //在屏上显示波形

       key = KeyScan();
	   if(key == 1){Clear();func_flag = !func_flag;} // 按下key1，模式切换
	   	   /*
		if(key != 0)
		{
			switch(key)
			{
			   case 1:	Clear();
			   			for(x=0;x<128;x++)
			             {
							LCD_draw_point(x,0); // LCD左上角为原点哟！ X：0－127  Y：0－7 位置画点  一次一列八个点哟！ 
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
							DrawPoint(x,0);	    // LCD左下角为坐标原点 x:0~127 y :0~63	  连续操作同一显示字节时,保留原始数据，画点！
						 }   
						 break;
			   case 4:  Clear();
			   			for(x=0;x<128;x++)
			             {
							DrawPoint(x,1);
						 }   
						 break;
			   case 5:	DrawPoint(63,0);		//画一个点
						break;
			   case 6:  LCD_draw_point(63,0);   //画八个点
						break;
			   case 7:	for(i=0;i<127;i++)		//画一十字，注意先后哟！
						{
							DrawPoint(i,31);
						}

		    		   for(i=0;i<64;i++)
						{
							DrawPoint(63,i);	
						}
						break;
			   case 8:  Clear();
			            DrawcharS("abcdefghijklmnopqrstuvwxyz",0,0);  //每行最多16个字符，多于16个换行！共4行，LCD左上角为原点哟！
			            P5&=(~0x01);	 //点亮LED
						break;
			   case 9:	Clear();
			            for(i=0;i<64;i++)
   					    DrawPoint(i,i);
			            for(i=64;i<127;i++)
   					    DrawPoint(i,127-i);
			            P5|=0x01;	 //灭LED
						break;
			}
		 x=0;
		 y=0;
		 key=0;

	    }
		*/
	 }
}
