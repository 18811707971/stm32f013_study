#ifndef __PRJ_STM32F10X_DRVADC_C__
#define __PRJ_STM32F10X_DRVADC_C__

//---------------------------------------------------------------------------------------------------------------------------------------------
//ƽ    ̨:				STM32F10X
//��    ��:    		 	drvadc.c
//��    ��:       		����AI
//��� ��:   			Vxxx
//�ļ��汾:   			V1.0.0
//��   ��:      		2020��03��11��
//˵   ��:      	 	ADC����ʵ��
//----------------------------------------------------------------------------------------------------------------------------------------------

#include "Typedef.h"
#include "drvadc.h"
#include "delay.h"
#include "stm32f10x_conf.h"

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: Adc_GpioConfig
//	����˵��: ADC����ɼ���������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-11
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void Adc_GpioConfig(void)
{	
	GPIO_InitTypeDef gpio_init;
	
	RCC_APB2PeriphClockCmd(RCC_PCLK_ADC_GPIO, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	
	//PA1 ��Ϊģ��ͨ����������                         
	gpio_init.GPIO_Pin = ADC_IN_PIN;	//ADC��������
	gpio_init.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(PORT_ADC_IN, &gpio_init);	
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: Adc_Config
//	����˵��: ADC����ɼ���������
//	��    ��: ��
//	�� �� ֵ: ��
//  ��    ע: 
//	��    ��: 2020-03-11
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void  Adc_Config(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_PCLK_ADC_CHL, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	ADC_DeInit(ADC_CHL);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode 					= ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode 			= DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode 	= DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign 			= ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel			= 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC_CHL, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

	ADC_Cmd(ADC_CHL, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC_CHL);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC_CHL));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC_CHL);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC_CHL));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: Adc_Init
//	����˵��: ADC��ʼ��
//	��    ��: ��
//	�� �� ֵ: ��
//  ��    ע: 
//	��    ��: 2020-03-11
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void Adc_Init(void)
{
	Adc_GpioConfig();	//IO��ʼ��
	Adc_Config();	//ADC��������
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: Get_AdcConvertVal
//	����˵��: ���ADCת�����
//	��    ��: 	_ucChl��ADC �ɼ�ͨ��
//	�� �� ֵ: �ɼ����ݽ��
//  ��    ע: 
//	��    ��: 2020-03-11
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint16_t Get_AdcConvertVal(uint8_t _ucChl)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC_CHL, _ucChl, 1, ADC_SampleTime_239Cycles5);	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC_CHL, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC_CHL, ADC_FLAG_EOC));	//�ȴ�ת������

	return ADC_GetConversionValue(ADC_CHL);		//�������һ��ADC1�������ת�����
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: Get_Adc_Average
//	����˵��: ת���� ADC �ɼ�����
//	��    ��: 	_ucChl��ADC ͨ����
//				_ucTimes���ɼ�����
//	�� �� ֵ: ת������
//  ��    ע: 
//	��    ��: 2020-03-11
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
uint16_t Get_AdcAverage(uint8_t _ucChl, uint8_t _ucTimes)
{
	uint32_t ulTmpVal = 0;
	uint8_t i = 0;
	
	for(i = 0; i < _ucTimes; i++)
	{
		ulTmpVal += Get_AdcConvertVal(_ucChl);
		delay_ms(5);
	}
	return ulTmpVal / _ucTimes;
} 	

#endif /* __PRJ_STM32F10X_DRVADC_C__ */
