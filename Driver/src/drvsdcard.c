#ifndef __PRJ_STM32F10X_DRVSDCARD_C__
#define __PRJ_STM32F10X_DRVSDCARD_C__

//---------------------------------------------------------------------------------------------------------------------------------------------
//ƽ    ̨:				STM32F10X
//��    ��:    		 	drvadc.c
//��    ��:       		����AI
//��� ��:   			Vxxx
//�ļ��汾:   			V1.0.0
//��   ��:      		2020��03��11��
//˵   ��:      	 	ADC����ʵ��
//----------------------------------------------------------------------------------------------------------------------------------------------

#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h" 
#include "stm32f10x_rcc.h"
#include "drvsdcard.h"
#include "delay.h"

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: sd_gpio_init
//	����˵��: SD��gpio��ʼ��
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-14
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void sd_gpio_init(void)
{
    GPIO_InitTypeDef gpio_config_init;

	RCC_APB2PeriphClockCmd(RCC_PCLK_SD_GPIO, ENABLE);		//����SD CS GPIOʱ��

	gpio_config_init.GPIO_Pin = SD_CS_IO;	//SD_CS_IO IO��ʼ��
	gpio_config_init.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_SD_GPIO, &gpio_config_init);

	GPIO_SetBits(PORT_SD_GPIO, SD_CS_IO);	//IO��ʼ״̬������Ϊ�ߵ�ƽ
}

#endif /* __PRJ_STM32F10X_DRVSDCARD_C__ */
