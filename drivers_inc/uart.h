/**
  ******************************************************************************
  * @file    uart.h
  * @brief   ����KL46�ļƲ������-��������
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�  
  ******************************************************************************
  */
  
#ifndef __CH_LIB_KL_UART_H__
#define __CH_LIB_KL_UART_H__

#include <stdint.h>
#include <stdbool.h>

/*!< UART Ӳ��ģ��� */
#define HW_UART0  (0x00U)
#define HW_UART1  (0x01U)
#define HW_UART2  (0x02U)


/*!< UART ���ٳ�ʼ���� */                      
#define UART1_RX_PE01_TX_PE00   (0x000080E1U)
#define UART2_RX_PE17_TX_PE16   (0x0000A0E2U)
#define UART0_RX_PE21_TX_PE20   (0x0000A920U)
#define UART2_RX_PE23_TX_PE22   (0x0000AD22U)
#define UART0_RX_PA01_TX_PA02   (0x00008280U)
#define UART0_RX_PA15_TX_PA14   (0x00009CC0U)
#define UART1_RX_PA18_TX_PA19   (0x0000A4C1U)
#define UART0_RX_PB16_TX_PB17   (0x0000A0C8U)
#define UART2_RX_PD02_TX_PD03   (0x000084DAU)
#define UART2_RX_PD04_TX_PD05   (0x000088DAU)
#define UART0_RX_PD06_TX_PD07   (0x00008CD8U)


/*!< �жϼ�DMA���� */
typedef enum
{
    kUART_IT_Tx,                // ����ÿ����һ֡��������ж� 
    kUART_DMA_Tx,               // ����ÿ����һ֡������ɴ���DMA 
    kUART_IT_Rx,                // ����ÿ����һ֡��������ж� 
    kUART_DMA_Rx,               // ����ÿ����һ֡������ɴ���DMA 
}UART_ITDMAConfig_Type;

/*!< UART��ʼ���ṹ */
typedef struct
{
    uint32_t                srcClock;       // ʱ��ԴƵ��
    uint8_t                 instance;       // UART ģ��� HW_UART0~HW_UART5
    uint32_t                baudrate;       // UART ������ 
}UART_InitTypeDef;

/*!< UART �ص��������� */
typedef void (*UART_CallBackTxType)(uint16_t * pbyteToSend);
typedef void (*UART_CallBackRxType)(uint16_t byteReceived);

/*!< API functions */
uint8_t UART_QuickInit(uint32_t MAP, uint32_t baudrate);
void UART_Init(UART_InitTypeDef * UART_InitStruct);
int UART_printf(const char *format,...);
uint8_t UART_ReadByte(uint32_t instance, uint16_t *ch);
void UART_WriteByte(uint32_t instance, uint16_t ch);
void UART_SelectDebugInstance(uint32_t instance);

/* Interrupt and DMA functions */
void UART_CallbackTxInstall(uint32_t instance, UART_CallBackTxType AppCBFun);
void UART_CallbackRxInstall(uint32_t instance, UART_CallBackRxType AppCBFun);
void UART_ITDMAConfig(uint32_t instance, UART_ITDMAConfig_Type config, bool status);

#ifdef UART_USE_STDIO
int printf(const char *fmt, ...);
#endif

#endif/*__CH_LIB_KL_UART_H__*/


