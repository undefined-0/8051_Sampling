#include "C8051F020.h"
#include "adc.h"
extern unsigned int func_flag;
static unsigned int display_index = 0; // ����ѭ����ʾ������
unsigned int k=0; // �������������������ã�
int xdata adcmem[SAMPLES_NUM];
sfr16 ADC0     = 0xbe;                 // ADC0 data
//���Ҳ����ݱ�,����wps�ı�������Ӵ��
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
   TMR3CN &= ~0x80;                    // �����ʱ��3�����־
}
void ADC0_ISR(void) interrupt 15 // ADC0
{

   AD0INT = 0; // ��ADC0ת�������жϱ�־����

   if(func_flag) // ʵʱ�洢��ʵʱ��ʾ
   {
      adcmem[k] = ADC0; // �洢ת�����
      DAC0L = ADC0L; // ֱ�ӽ�ADC���ֽ������DAC
      DAC0H = ADC0H; // ֱ�ӽ�ADC���ֽ������DAC
      k = (k++) % SAMPLES_NUM; // ����������ѭ��
   }
   else // ���δ洢��������ʾ
   {
      if(k < SAMPLES_NUM) // ���δ�ɵ�1500����
      {
         adcmem[k] = ADC0; // �洢ת�����
         k++; // ���Ӵ洢����
      }
      else // �Ѳɵ�1500���㣬��ʼѭ����ʾ
      {
         DAC0L = adcmem[display_index] & 0xFF; // ����洢���ݵĵ��ֽڵ�DAC
         DAC0H = (adcmem[display_index] >> 8) & 0xFF; // ����洢���ݵĸ��ֽڵ�DAC
         display_index = (display_index++) % SAMPLES_NUM; // ������ʾ������ѭ��
      }
   }
}