//--------------------------------------------------------------------------------------------------------
//
//	ģ������ : uart�շ�����
//	�ļ����� : drvuart.c
//	��    �� : V1.0
//	˵    �� : 
//				(1) drvuart.c �շ�,��ѯ+�ж�
//				(2) 
//				(3) 
//				(4) 
//
//	�޸ļ�¼ :
//		�汾��     ����        ����     ˵��
//		V1.0    2020-03-28   ����AI  ��ʽ����
//		V1.1    
//		V1.2	
//		V1.3	
//
//	Copyright (C), 2020-2030, ΢�Ź��ںš���TECHTIMES
//
//--------------------------------------------------------------------------------------------------------

#ifndef __PRJ_STM32F10X_DRVUART_C__
#define __PRJ_STM32F10X_DRVUART_C__

#include "Typedef.h"
#include "drvuart.h"
#include "stm32f10x_conf.h"
#include <stdio.h>
#include <string.h>

int fputc(int ch, FILE *f)
{      
//	while((USART1->SR & 0X40) == 0);//ѭ������,ֱ���������   
//    USART1->DR = (uint8_t)ch;      
	
//	 uart_send_byte(1, (uint8_t)ch);

	uart_send_serial_bytes(1, (uint8_t *)&ch, 1);
	
	return ch;
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_gpio_init
//	����˵��: ����GPIO��ʼ��
//	��    ��: 	uart_chl�����ڱ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-25
//  ��    ע: ����GPIO��ʼ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
static void uart_gpio_init(uint8_t uart_chl)
{
    GPIO_InitTypeDef gpio_config_init;

    if (uart_chl == 1)
    {
        RCC_APB2PeriphClockCmd(RCC_PCLK_USART1_GPIO, ENABLE);	//ʹ��UART1 GPIOʱ��,APB2����

		gpio_config_init.GPIO_Pin 	= USART1_TXD_IO; //PA9
		gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
		gpio_config_init.GPIO_Mode 	= GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(USART1_TXD_PORT, &gpio_config_init);//��ʼ��GPIOA9

		gpio_config_init.GPIO_Pin 	= USART1_RXD_IO;//PA10
		gpio_config_init.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(USART1_RXD_PORT, &gpio_config_init);//��ʼ��GPIOA10
    }
    else if (uart_chl == 2)
    {
        RCC_APB2PeriphClockCmd(RCC_PCLK_USART2_GPIO, ENABLE);	//ʹ��UART2 GPIOʱ��,ABP2����

		gpio_config_init.GPIO_Pin = USART2_TXD_IO; //PA2
		gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
		gpio_config_init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(USART2_TXD_PORT, &gpio_config_init);//��ʼ��GPIOA2

		gpio_config_init.GPIO_Pin = USART2_RXD_IO;//PA3
		gpio_config_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(USART2_RXD_PORT, &gpio_config_init);//��ʼ��GPIOA3  
    }
    else if (uart_chl == 3)
    {
        RCC_APB2PeriphClockCmd(RCC_PCLK_USART3_GPIO, ENABLE);	//ʹ��UART3 GPIOʱ��,ABP2����

		gpio_config_init.GPIO_Pin = USART3_TXD_IO; //PB10
		gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
		gpio_config_init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(USART3_TXD_PORT, &gpio_config_init);//��ʼ��GPIOB10

		gpio_config_init.GPIO_Pin = USART3_RXD_IO;//PB11
		gpio_config_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(USART3_RXD_PORT, &gpio_config_init);//��ʼ��GPIOB11 
    }
    else if (uart_chl == 4)
    {
        RCC_APB2PeriphClockCmd(RCC_PCLK_USART4_GPIO, ENABLE);	//ʹ��UART4 GPIOʱ��,ABP2����

		gpio_config_init.GPIO_Pin = USART4_TXD_IO; //PC10
		gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
		gpio_config_init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(USART4_TXD_PORT, &gpio_config_init);//��ʼ��GPIOC10

		gpio_config_init.GPIO_Pin = USART4_RXD_IO;//PC11
		gpio_config_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
		GPIO_Init(USART4_RXD_PORT, &gpio_config_init);//��ʼ��GPIOC11 
    }
     else if (uart_chl == 5)
    {
        RCC_APB2PeriphClockCmd(RCC_PCLK_USART5_GPIO, ENABLE);	//ʹ��UART4 GPIOʱ��,ABP2����

		gpio_config_init.GPIO_Pin = USART5_TXD_IO; //PC12
		gpio_config_init.GPIO_Speed = GPIO_Speed_50MHz;
		gpio_config_init.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(USART5_TXD_PORT, &gpio_config_init);	//��ʼ��GPIOC12

		gpio_config_init.GPIO_Pin = USART5_RXD_IO;	//PC11
		gpio_config_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
		GPIO_Init(USART5_RXD_PORT, &gpio_config_init);	//��ʼ��GPIOD2
    }
    else 
    {
//        printf("error! \r\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_config
//	����˵��: �������ò�����ʼ��
//	��    ��: 	uart_chl�����ڱ��
//              uart_bound��������
//	�� �� ֵ: ��
//	��    ��: 2020-03-25
//  ��    ע: ���ڱ�Ŵ�1-5(UART1-5),�����ж�ʹ����Nvic������������
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
static void uart_config(uint8_t uart_chl, uint32_t uart_bound)
{
    USART_InitTypeDef uart_config_init;

    if (uart_chl == 1)
    {
		RCC_APB2PeriphClockCmd(RCC_PCLK_USART1, ENABLE);
		
		uart_config_init.USART_BaudRate              = uart_bound;	//���ڲ�����
		uart_config_init.USART_WordLength            = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
		uart_config_init.USART_StopBits              = USART_StopBits_1;	//һ��ֹͣλ
		uart_config_init.USART_Parity                = USART_Parity_No;	//����żУ��λ
		uart_config_init.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;	//��Ӳ������������
		uart_config_init.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART1, &uart_config_init); //��ʼ������1
		// USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�(���ڲ�����ʼ��֮����ܿ����ж�)
		USART_Cmd(USART1, ENABLE); 		//ʹ�ܴ���1 
    }
    else if (uart_chl == 2)
    {
		RCC_APB2PeriphClockCmd(RCC_PCLK_USART2, ENABLE);
		
		uart_config_init.USART_BaudRate             = uart_bound;//���ڲ�����
		uart_config_init.USART_WordLength           = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		uart_config_init.USART_StopBits             = USART_StopBits_1;//һ��ֹͣλ
		uart_config_init.USART_Parity               = USART_Parity_No;//����żУ��λ
		uart_config_init.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;//��Ӳ������������
		uart_config_init.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART2, &uart_config_init); //��ʼ������1
		// USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(USART2, ENABLE); 		//ʹ�ܴ���1 
    }
    else if (uart_chl == 3)
    {
		RCC_APB2PeriphClockCmd(RCC_PCLK_USART3, ENABLE);
		
		uart_config_init.USART_BaudRate             = uart_bound;//���ڲ�����
		uart_config_init.USART_WordLength           = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		uart_config_init.USART_StopBits             = USART_StopBits_1;//һ��ֹͣλ
		uart_config_init.USART_Parity               = USART_Parity_No;//����żУ��λ
		uart_config_init.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;//��Ӳ������������
		uart_config_init.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART3, &uart_config_init); //��ʼ������1
		// USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(USART3, ENABLE); 		//ʹ�ܴ���1 
    }
    else if (uart_chl == 4)
    {
		RCC_APB2PeriphClockCmd(RCC_PCLK_USART4, ENABLE);
		
		uart_config_init.USART_BaudRate             = uart_bound;//���ڲ�����
		uart_config_init.USART_WordLength           = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		uart_config_init.USART_StopBits             = USART_StopBits_1;//һ��ֹͣλ
		uart_config_init.USART_Parity               = USART_Parity_No;//����żУ��λ
		uart_config_init.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;//��Ӳ������������
		uart_config_init.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(UART4, &uart_config_init); //��ʼ������1
//		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(UART4, ENABLE); 		//ʹ�ܴ���1 
    }
    else if (uart_chl == 5)
    {
		RCC_APB2PeriphClockCmd(RCC_PCLK_USART5, ENABLE);
		
		uart_config_init.USART_BaudRate             = uart_bound;//���ڲ�����
		uart_config_init.USART_WordLength           = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		uart_config_init.USART_StopBits             = USART_StopBits_1;//һ��ֹͣλ
		uart_config_init.USART_Parity               = USART_Parity_No;//����żУ��λ
		uart_config_init.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;//��Ӳ������������
		uart_config_init.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(UART5, &uart_config_init); //��ʼ������1
//		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(UART5, ENABLE); 		//ʹ�ܴ���1 
    }
    else 
    {
//        printf("error! \r\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_irq_set
//	����˵��: �����жϳ�ʼ������
//	��    ��: 	uart_chl�����ڱ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-27
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
static void uart_irq_set(uint8_t uart_chl)
{
	NVIC_InitTypeDef uart_nvic_config = {0};

	if (uart_chl == 1)
    {
        uart_nvic_config.NVIC_IRQChannel 					= USART1_IRQn;
		uart_nvic_config.NVIC_IRQChannelPreemptionPriority 	= 3 ;//��ռ���ȼ�3
		uart_nvic_config.NVIC_IRQChannelSubPriority 		= 3;		//�����ȼ�3
		uart_nvic_config.NVIC_IRQChannelCmd 				= ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&uart_nvic_config);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    }
    else if (uart_chl == 2)
    {
        uart_nvic_config.NVIC_IRQChannel 					= USART2_IRQn;
		uart_nvic_config.NVIC_IRQChannelPreemptionPriority 	= 3 ;//��ռ���ȼ�3
		uart_nvic_config.NVIC_IRQChannelSubPriority 		= 3;		//�����ȼ�3
		uart_nvic_config.NVIC_IRQChannelCmd 				= ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&uart_nvic_config);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    }
    else if (uart_chl == 3)
    {
        uart_nvic_config.NVIC_IRQChannel 					= USART3_IRQn;
		uart_nvic_config.NVIC_IRQChannelPreemptionPriority 	= 3 ;//��ռ���ȼ�3
		uart_nvic_config.NVIC_IRQChannelSubPriority 		= 3;		//�����ȼ�3
		uart_nvic_config.NVIC_IRQChannelCmd 				= ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&uart_nvic_config);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    }
    else if (uart_chl == 4)
    {
        uart_nvic_config.NVIC_IRQChannel 					= UART4_IRQn;
		uart_nvic_config.NVIC_IRQChannelPreemptionPriority 	= 3 ;//��ռ���ȼ�3
		uart_nvic_config.NVIC_IRQChannelSubPriority 		= 3;		//�����ȼ�3
		uart_nvic_config.NVIC_IRQChannelCmd 				= ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&uart_nvic_config);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    }
    else if (uart_chl == 5)
    {
        uart_nvic_config.NVIC_IRQChannel 					= UART5_IRQn;
		uart_nvic_config.NVIC_IRQChannelPreemptionPriority 	= 3 ;//��ռ���ȼ�3
		uart_nvic_config.NVIC_IRQChannelSubPriority 			= 3;		//�����ȼ�3
		uart_nvic_config.NVIC_IRQChannelCmd 				= ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&uart_nvic_config);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    }
    else 
    {
//        printf("error! \r\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_init
//	����˵��: ����G���ò�����ʼ��
//	��    ��: 	uart_chl�����ڱ��
//              uart_bound��������
//	�� �� ֵ: ��
//	��    ��: 2020-03-25
//  ��    ע: ͳһ���õײ�ӿ�(�����֣�GPIO + UART + NVIC)
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
void uart_init(uint8_t uart_chl, uint32_t uart_bound)
{
    if (uart_chl == 1)
    {
        uart_gpio_init(uart_chl);
        uart_config(uart_chl, uart_bound);
		uart_irq_set(uart_chl);
    }
    else if (uart_chl == 2)
    {
        uart_gpio_init(uart_chl);
        uart_config(uart_chl, uart_bound);
		uart_irq_set(uart_chl);
    }
    else if (uart_chl == 3)
    {
        uart_gpio_init( uart_chl);
        uart_config(uart_chl, uart_bound);
		uart_irq_set(uart_chl);
    }
    else if (uart_chl == 4)
    {
        uart_gpio_init(uart_chl);
        uart_config(uart_chl, uart_bound);
		uart_irq_set(uart_chl);
    }
    else if (uart_chl == 5)
    {
        uart_gpio_init(uart_chl);
        uart_config(uart_chl, uart_bound);
		uart_irq_set(uart_chl);
    }
    else 
    {
        printf("error! \r\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_send_byte
//	����˵��: ���ڷ���һ�ֽ�����
//	��    ��: 	uart_chl�����ڱ��
//              send_byte�����͵�����
//	�� �� ֵ: ��
//	��    ��: 2020-03-27
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
bool uart_send_byte(uint8_t uart_chl, uint8_t send_byte)
{
	if (uart_chl == 1)
    {
	#if 0
		while((USART1->SR & 0X40) == 0);//ѭ������,ֱ���������   
		USART1->DR = (uint8_t)send_byte; 
	#else
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	//�ȴ����ڷ��ͱ�־λ��λ

		USART_SendData(USART1, (uint8_t)send_byte);	//��������

	#endif
    }
    else if (uart_chl == 2)
    {
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	//�ȴ����ڷ��ͱ�־λ��λ

		USART_SendData(USART2, (uint8_t)send_byte);	//��������
    }
    else if (uart_chl == 3)
    {
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	//�ȴ����ڷ��ͱ�־λ��λ

		USART_SendData(USART3, (uint8_t)send_byte);	//��������
    }
    else if (uart_chl == 4)
    {
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	//�ȴ����ڷ��ͱ�־λ��λ

		USART_SendData(UART4, (uint8_t)send_byte);	//��������
    }
    else if (uart_chl == 5)
    {
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);	//�ȴ����ڷ��ͱ�־λ��λ

		USART_SendData(UART5, (uint8_t)send_byte);	//��������
    }
    else 
    {
        printf("error! \r\n");
    }

	return true;
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_send_serial_bytes
//	����˵��: ���ڷ��Ͷ��ֽ�����
//	��    ��: 	uart_chl�����ڱ��
//              pbdata�����͵����ݵ�ַ
//				length���������ݵĳ���
//	�� �� ֵ: ��
//	��    ��: 2020-03-28
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
bool uart_send_serial_bytes(uint8_t uart_chl, uint8_t *pbdata, uint16_t length)
{
	for (uint16_t i = 0; i < length; i++)
	{
		uart_send_byte(uart_chl, pbdata[i]);
	}
	
	// while (length--)
	// {
	// 	uart_send_byte(uart_chl, *pbdata++);
	// }

	return true;
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_recv_byte
//	����˵��: ���ڽ���һ�ֽ�����
//	��    ��: 	uart_chl�����ڱ��
//	�� �� ֵ: recv_byte�����յ�����
//	��    ��: 2020-03-28
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
uint8_t uart_recv_byte(uint8_t uart_chl)
{
	uint8_t recv_byte = 0;

	if (uart_chl == 1)
    {
	#if 1
		while((USART1->SR & 0X20) == 0);//ѭ������,ֱ���������   
		recv_byte = USART1->DR; 
	#else
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);	//�ȴ����ڽ��ձ�־λ��λ
		recv_byte = USART_ReceiveData(USART1);	//��������

	#endif
    }
    else if (uart_chl == 2)
    {
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);	//�ȴ����ڽ��ձ�־λ��λ
		recv_byte = USART_ReceiveData(USART2);	//��������
    }
    else if (uart_chl == 3)
    {
		while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);	//�ȴ����ڽ��ձ�־λ��λ
		recv_byte = USART_ReceiveData(USART3);	//��������
    }
    else if (uart_chl == 4)
    {
		while (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);	//�ȴ����ڽ��ձ�־λ��λ
		recv_byte = USART_ReceiveData(UART4);	//��������
    }
    else if (uart_chl == 5)
    {
		while (USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);	//�ȴ����ڽ��ձ�־λ��λ
		recv_byte = USART_ReceiveData(UART5);	//��������
    }
    else 
    {
        printf("error! \r\n");
    }
	
	return recv_byte;
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_recv_serial_bytes
//	����˵��: ���ڽ��ն��ֽ�����
//	��    ��: 	uart_chl�����ڱ��
//              pbdata�����͵����ݵ�ַ
//				length���������ݵĳ���
//	�� �� ֵ: ��
//	��    ��: 2020-03-28
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
bool uart_recv_serial_bytes(uint8_t uart_chl, uint8_t *pbdata, uint16_t length)
{
	for (uint16_t i = 0; i < length; i++)
	{
		*pbdata++ = uart_recv_byte(1);
	}
	
	return true;
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: USART1_IRQHandler
//	����˵��: �����жϷ�����
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-28
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)	//�������жϱ�־λ
	{	
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		uart_test();	//���յ����ݴ���

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//������ڽ����жϱ�־
	}
}

//--------------------------------------------------------------------------------------------------------------------------
//	�� �� ��: uart_test
//	����˵��: �����շ����Ժ���
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-28
//  ��    ע: ��
//	��    ��: by ����AI
//-------------------------------------------------------------------------------------------------------------------------
void uart_test(void)
{
	uint8_t tmp_buff[6] = {0};
	uint8_t err_flag[6] = "error";

	uart_recv_serial_bytes(1, tmp_buff, sizeof(tmp_buff));

	if (tmp_buff[0] == 0x55)
	{
		uart_send_serial_bytes(1, tmp_buff, sizeof(tmp_buff));
	}
	else
	{
		uart_send_serial_bytes(1, err_flag, 6);
	}
}
#endif /* __PRJ_STM32F10X_DRVUART_C__ */
