#ifndef __PRJ_STM32F10X_DRVNRF2401_C__
#define __PRJ_STM32F10X_DRVNRF2401_C__

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
#include "drvnrf2401.h"
#include "hardware_spi.h"
#include "delay.h"

//---------------------------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: nrf24l01_gpio_init
//	����˵��: nrf24l01 gpio ��ʼ��
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-11
//  ��    ע: 
//	��    ��: by ����AI
//---------------------------------------------------------------------------------------------------------------------------------------------
void nrf24l01_gpio_init(void)
{
    GPIO_InitTypeDef gpio_config_init;

	RCC_APB2PeriphClockCmd(RCC_PCLK_NRF_GPIO, ENABLE);		//����NRF CS GPIOʱ��

	gpio_config_init.GPIO_Pin = NRF_CS_IO;	//NRF_CS_IO IO��ʼ��
	gpio_config_init.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_NRF_GPIO, &gpio_config_init);

	GPIO_SetBits(PORT_NRF_GPIO, NRF_CS_IO);	//IO��ʼ״̬������Ϊ�ߵ�ƽ
}

#endif /* __PRJ_STM32F10X_DRVNRF2401_C__ */
