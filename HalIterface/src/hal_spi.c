#ifndef __PRJ_STM32F10X_HAL_SPI_C__
#define __PRJ_STM32F10X_HAL_SPI_C__

#include "Typedef.h"
#include "declares.h"
#include "variable.h"
#include "hal_spi.h"
#include "hardware_spi.h"
#include "drvsfspi.h"

#ifdef SOFT_SPI_COMM
#ifdef HARD_SPI_COMM

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: hal_spi_send_bytes
//	����˵��: SPI ��������,���������Ӳ��ͨ�ŷ�ʽ
//	��    ��: 	mode��ͨ�ŷ�ʽѡ��(0�����SPI;1��Ӳ��SPI)
//				pbdata���������ݵ��׵�ַ
//				send_length���������ݳ���
//	�� �� ֵ: ִ��״̬(true or false)
//	��    ��: 2020-03-12
//  ��    ע: �м���װ�ײ�ӿ�
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
bool hal_spi_send_bytes(uint8_t mode, uint8_t *pbdata, uint16_t send_length)
{
    if (mode == 0)
    {
        for (uint16_t i = 0; i < send_length; i++)
        {
            Spi_WriteByte(pbdata[i]);
        }
		
		return true;
    }
    else if (mode == 1)
    {
        spi_master_send_some_bytes(1, pbdata, send_length);
		
//		for (uint16_t i = 0; i < send_length; i++)
//        {
//            spi_master_send_recv_byte(1, pbdata[i]);
//        }
		
		return true;
    }
	else 
	{
		return false;
	}
    
}

//--------------------------------------------------------------------------------------------------------
//	�� �� ��: hal_spi_recv_bytes
//	����˵��: SPI ��������,���������Ӳ��ͨ�ŷ�ʽ
//	��    ��: 	mode��ͨ�ŷ�ʽѡ��(0�����SPI;1��Ӳ��SPI)
//				pbdata���������ݵ��׵�ַ
//				send_length���������ݳ���
//	�� �� ֵ: ִ��״̬(true or false)
//	��    ��: 2020-03-12
//  ��    ע: �м���װ�ײ�ӿ�
//	��    ��: by ����AI
//--------------------------------------------------------------------------------------------------------
bool hal_spi_recv_bytes(uint8_t mode, uint8_t *pbdata, uint16_t recv_length)
{
    if (mode == 0)
    {
        for (uint16_t i = 0; i < recv_length; i++)
        {
             *pbdata++ = Spi_ReadByte();	//���ģ��SPI
        }   
		
		return true;
    }
    else if (mode == 1)
    {
        spi_master_recv_some_bytes(1, pbdata, recv_length);	//Ӳ��SPI
		
//		for (uint16_t i = 0; i < recv_length; i++)
//        {
//            *pbdata++ = spi_master_send_recv_byte(1, 0xFF);
//        }
		
		return true;
    }
	else 
	{
		return false;
	}
    
}

#endif	// SOFT_SPI_COMM

#endif	// HARD_SPI_COMM

#endif	//__PRJ_STM32F10X_HAL_SPI_C__
