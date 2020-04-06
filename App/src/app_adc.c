#ifndef __PRJ_STM32F10X_APP_ADC_C__
#define __PRJ_STM32F10X_APP_ADC_C__

#include <stdio.h>
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "declares.h"
#include "Typedef.h"
#include "app_adc.h"
#include "drvadc.h"
#include "delay.h"
#include "usart.h"

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: App_AdcTest
//	����˵��: ADC��ͨ����������
//	��    ��: ��
//	�� �� ֵ: ��
//  ��    ע: 
//	��    ��: 2020-03-11
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void App_AdcTest(void)
{
	uint16_t usAdcVal = 0;
	float fTmpVal = 0.0;
	
	usAdcVal = Get_AdcAverage(ADC_Channel_1, 10);
//	LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
	
	//INPUT VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
	fTmpVal = (float)usAdcVal * (3.3 / 4096);	//12λADC
	printf("voltage is %04fv.\r\n", fTmpVal);
	
//	usAdcVal = fTmpVal;	//��������
//	printf("Voltage integer of usAdcVal is :%d \r\n", usAdcVal);
//	LCD_ShowxNum(156,150,adcx,1,16,0);//��ʾ��ѹֵ
	
//	fTmpVal -= usAdcVal;	//С������
//	printf("Voltage float of is :%f \r\n",fTmpVal);
//	fTmpVal *= 1000;
//	LCD_ShowxNum(172, 150, fTmpVal, 3, 16, 0X80);
	
	delay_ms(250);	
}


#endif	//__PRJ_STM32F10X_APP_ADC_C__
