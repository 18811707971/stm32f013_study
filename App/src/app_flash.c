//--------------------------------------------------------------------------------------------------------
//
//	ģ������ : SPI Flash���Գ���
//	�ļ����� : app_flash.c
//	��    �� : V1.0
//	˵    �� : 
//				(1) ���� drvexflash.c �����ӿ�
//				(2) 
//				(3) 
//				(4) 
//
//	�޸ļ�¼ :
//		�汾��     ����        ����     ˵��
//		V1.0    2020-03-07   ����AI  ��ʽ����
//		V1.1    
//		V1.2	
//		V1.3	
//
//	Copyright (C), 2020-2030, ΢�Ź��ںš���TECHTIMES
//
//--------------------------------------------------------------------------------------------------------


#ifndef __PRJ_STM32F10X_APP_FLASH_C__
#define __PRJ_STM32F10X_APP_FLASH_C__

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "Typedef.h"
#include "declares.h"
#include "Variable.h"
#include "app_flash.h"
#include "drvexflash.h"
#include "delay.h"

#define FALSH_TEST_ADDR		(0x100)

__align(4) uint16_t g_WriteReadcnt = 0;
__align(4) uint8_t g_WriteData[0x100] = {0};
__align(4) uint16_t g_Count = 0;
__align(4) uint8_t g_ucPos = 0;

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: Flash_TestDataInit
//	����˵��: FLASH �������ݳ�ʼ��(0x00-0xFF����д��FLASH)
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-07
//  ��    ע: 
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void Flash_TestDataInit(void)
{
	u8 usMinData = 0;
	u8 usMaxData = 0xFF;
	u16 usCnt = 0;

    for(usCnt = 0; usCnt < 0x100 ; usCnt++)
	{
		if(g_WriteReadcnt % 2)
		{
			g_WriteData[usCnt] = usMinData;
			usMinData++;		
		}
		else
		{
			g_WriteData[usCnt] = usMaxData;
			usMaxData--;
		}	
		
	}
}


#ifdef SOFT_SPI_COMM	//���ģ��SPI
//--------------------------------------------------------------------------------------------------------
//	�� �� ��: W25_CircleWriteRead
//	����˵��: FLASH ��ҳд�����,��������оƬ
//	��    ��: 	_ucFlashSize��FLASHҳ��
//				
//	�� �� ֵ: ��
//	��    ��: 2020-03-07
//  ��    ע: 
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void W25_CircleWriteRead(uint8_t _ucFlashSize,uint32_t _ulAddr, uint8_t *ucpWBuf, uint8_t *ucpRBuf, uint16_t _usLen)
{
    uint16_t usPageSum = 0;	//flash��ҳ��
    uint16_t usCnt = 0;

	switch (_ucFlashSize)
	{
		case FLASH_SIZE_1MBYTE:
					usPageSum = MAX_PAGE_1MBYTE;
					break;
		case FLASH_SIZE_2MBYTE:
					usPageSum = MAX_PAGE_2MBYTE;
					break;
		case FLASH_SIZE_4MBYTE:
					usPageSum = MAX_PAGE_4MBYTE;
					break;
		case FLASH_SIZE_8MBYTE:
					usPageSum = MAX_PAGE_8MBYTE;
		default:
					break;
	}

    printf("Write Data -> \r\n");
	for(usCnt = 0; usCnt < _usLen; usCnt++)
	{
		 printf("0x%02X ", ucpWBuf[usCnt]);	
	}
	printf("\r\n");
	Flash_EraseChip();	//��һ����Ƭ����
	
	{
		printf("Flash erase is ok! \r\n");
		
		Flash_ReadSomeBytes(ucpRBuf, 0x00, 256);
		
		printf("Data is after flash erase: \r\n");
		for(uint16_t usCnt = 0; usCnt < _usLen ; usCnt++)
		{
			printf("0x%02X ",ucpRBuf[usCnt]);
			
			if (ucpRBuf[usCnt] == 0xFF)	//��֤�����������
			{
//				printf("Flash erase verify is ok! \r\n");
			}
			else 
			{
				printf("Flash erase is failed! \r\n");
				while (1);
			}
		}
		printf("\r\n");
		printf("Flash erase verify is ok! \r\n");
	}
	
    for (uint16_t i = 0; i < usPageSum; i++)
    {
		printf("\r\n");
		printf("************************---------********************************** \r\n");
        printf("Flash Addr is 0x%08x \r\n",_ulAddr);
        Flash_WriteSomeBytes(ucpWBuf, _ulAddr, _usLen);	//д 256 Byte ����
//		Flash_WritePage(ucpWBuf, _ulAddr, _usLen);
        printf("Write Page %d -> \r\n",i);
		for(usCnt = 0; usCnt < _usLen ; usCnt++)
		{
			printf("0x%02X ", ucpWBuf[usCnt]);	
		}
		printf("\r\n");
		Sys_delay_ms(500);
        Flash_ReadSomeBytes(ucpRBuf, _ulAddr, _usLen);	//read 256 byte data 
        printf("Read Page %d -> \r\n",i);
		for(usCnt = 0; usCnt < _usLen; usCnt++)
		{
			 printf("0x%02X ",ucpRBuf[usCnt]);	
		}
        	printf("\r\n");
        _ulAddr += 0x100;	//��ַ����һҳ

		for(usCnt = 0; usCnt < _usLen ; usCnt++)
		{
			if(ucpWBuf[usCnt] != ucpRBuf[usCnt])	//д��������������Ƚ�
			{
				printf("Flash Write != Read failed!\r\n");
				printf("Check Please!\r\n");
				while (1);
			}	
		}
		printf("Flash Write == Read sucessed!\r\n");
		printf("Flash g_WriteReadcnt is  Running %d \r\n", g_WriteReadcnt);

		if(i >= (usPageSum-1))
		{
			i = 0;
			g_WriteReadcnt ++;
			Flash_TestDataInit();
			printf("Flash 16M Bits is Test Sucessed! \r\n");
			printf("Flash g_WriteReadcnt is %d \r\n", g_WriteReadcnt);
			printf("Flash will go to Next Test\r\n");
			Flash_EraseChip();	//д������оƬ,����һ��
			Sys_delay_ms(500);
		}
		printf("************************@@@@@@@@@********************************** \r\n");
		printf("\r\n");
    } 
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: W25_WriteReadBytes
//	����˵��: SPI FLASH ��д����
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-06
//  ��    ע: ���ģ��SPI
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void W25_WriteReadBytes(void)
{
	uint8_t ucWriteBuf[10] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
	uint8_t ucReadBuf[10] = {0};
	
	if (g_Count)
	{
		if (g_ucPos > 250)
		{
			g_Count = 0;
			g_ucPos = 0;
		}
		
		memset(ucWriteBuf, 0, 10);
		memcpy(ucWriteBuf, g_WriteData + g_ucPos, 10);
		g_ucPos += 10;
	}
	
	Flash_WriteSomeBytes((uint8_t *)ucWriteBuf, FALSH_TEST_ADDR, 10);
	
//	Flash_EraseSector(0);
//	Flash_WriteNoCheck(ucWriteBuf, FALSH_TEST_ADDR, 10);
	printf("Write Data is ---->\r\n");
	for (uint16_t i = 0; i < 10; i++)
	{
		printf("Write Data is  % d ----> 0x%02X \r\n", i, ucWriteBuf[i]);
	}
	printf("\r\n");
	
	Sys_delay_ms(500);
	Flash_ReadSomeBytes(ucReadBuf, FALSH_TEST_ADDR, 10);	//����Ƿ����
	printf("Read Data is ---->\r\n");
	for (uint16_t i = 0; i < 10; i++)
	{
		printf("Read Data is  % d ----> 0x%02X \r\n", i, ucReadBuf[i]);
	}
	printf("Read Data is Over\r\n");
	printf("\r\n");
	
	for (uint16_t i = 0; i < 10; i++)
	{
		if(ucWriteBuf[i] != ucReadBuf[i])	//д��������������Ƚ�
		{
			printf("Flash Write != Read failed!\r\n");
			printf("Check please!\r\n");
			while (1);
		}
	}
	
	printf("W25 operate is ok! \r\n");
	
	memset(ucReadBuf, 0, 10);
	g_Count++;
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: W25_EraseTest
//	����˵��: SPI FLASH ��������
//	��    ��: ��
//	�� �� ֵ: ��
//	��    ��: 2020-03-06
//  ��    ע: ���ģ��SPI
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
void W25_EraseTest(void)
{
	uint16_t i = 0;
	uint8_t ucaTmpBuf[0x100] = {0};
	
	Flash_EraseChip();	//��Ƭ����
	Sys_delay_ms(500);	//����֮����Ҫ��ʱ
	Flash_ReadSomeBytes(ucaTmpBuf, 0x00, 0x100);	//��ȡ��һҳ������֤
	
	for (i = 0; i < 256; i++)
	{
		printf("0x%02X ", ucaTmpBuf[i]);
			
		if (ucaTmpBuf[i] == 0xFF)	//��֤�����������
		{
//				printf("Flash erase verify is ok! \r\n");
		}
		else 
		{
			printf("\r\n");
			printf("Flash erase is failed! \r\n");
			while (1);
		}
	}
	printf("\r\n");
	printf("Flash erase verify is ok! \r\n");
	memset(ucaTmpBuf, 0, 0x100);
}

#endif	//SOFT_SPI_COMM

#endif	//__PRJ_STM32F10X_APP_FLASH_C__
