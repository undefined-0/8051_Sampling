#include "C8051F020.h"
#include "adc.h"
extern unsigned int func_flag;
static unsigned int display_index = 0; // 用于循环显示的索引
unsigned int k=0; // 计数变量（遍历数组用）
int xdata adcmem[SAMPLES_NUM];
sfr16 ADC0     = 0xbe;                 // ADC0 data
//正弦波数据表,俺用wps的表格功能算的哟！
code unsigned int sintab[100]={2048 ,2178 ,2307 ,2436 ,2562 ,2687 ,2809 ,
2928 ,3044 ,3155 ,3262 ,3364 ,3461 ,3552 ,3638 ,3716 ,3788 ,3853 ,3911 ,
3961 ,4004 ,4038 ,4065 ,4083 ,4094 ,4095 ,4090 ,4075 ,4053 ,4022 ,3983 ,
3937 ,3883 ,3822 ,3753 ,3678 ,3596 ,3508 ,3414 ,3314 ,3209 ,3100 ,2986 ,
2869 ,2748 ,2625 ,2499 ,2372 ,2243 ,2113 ,1983 ,1853 ,1724 ,1597 ,1471 ,
1348 ,1227 ,1110 ,996 ,887 ,782 ,682 ,588 ,500 ,418 ,343 ,274 ,213 ,
159 ,113 ,74 ,43 ,21 ,6 ,0 ,2 ,13 ,31 ,58 ,92 ,135 ,185 ,243 ,308 ,
380 ,458 ,544 ,635 ,732 ,834 ,941 ,1052 ,1168 ,1287 ,1409 ,1534 ,
1660 ,1789 ,1918 ,2048 };

void TIMER3_ISR(void) interrupt 14	   //TIME3 
{
   TMR3CN &= ~0x80;                    // 清除定时器3溢出标志
}
void ADC0_ISR(void) interrupt 15 // ADC0
{

   AD0INT = 0; // 将ADC0转换结束中断标志清零

   if(func_flag) // 实时存储、实时显示
   {
      adcmem[k] = ADC0; // 存储转换结果
      DAC0L = ADC0L; // 直接将ADC低字节输出到DAC
      DAC0H = ADC0H; // 直接将ADC高字节输出到DAC
      k = (k++) % SAMPLES_NUM; // 更新索引并循环
   }
   else // 单次存储、连续显示
   {
      if(k < SAMPLES_NUM) // 如果未采到1500个点
      {
         adcmem[k] = ADC0; // 存储转换结果
         k++; // 增加存储索引
      }
      else // 已采到1500个点，开始循环显示
      {
         DAC0L = adcmem[display_index] & 0xFF; // 输出存储数据的低字节到DAC
         DAC0H = (adcmem[display_index] >> 8) & 0xFF; // 输出存储数据的高字节到DAC
         display_index = (display_index++) % SAMPLES_NUM; // 更新显示索引并循环
      }
   }
}