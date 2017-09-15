/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   ����KL46�ļƲ������-ͨ���������ͷ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�  
  ******************************************************************************
  */
#ifndef __CH_LIB_KL_GPIO_H__
#define __CH_LIB_KL_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "common.h"
#include <stdint.h>

/* GPIO�˿ڶ��� */
#define HW_GPIOA  (0x00U)   //PTA���Ŷ˿ڶ���
#define HW_GPIOB  (0x01U)   //PTB���Ŷ˿ڶ���
#define HW_GPIOC  (0x02U)   //PTC���Ŷ˿ڶ���
#define HW_GPIOD  (0x03U)   //PTD���Ŷ˿ڶ���
#define HW_GPIOE  (0x04U)   //PTE���Ŷ˿ڶ���
#define HW_GPIOF  (0x05U)   //PTF���Ŷ˿ڶ���


/* �˿ڸ���ѡ�� �����ֲ� Signal Multiplexing and Signal Descriptions �½�ѡ����*/
typedef enum
{
    kPinAlt0,  //0���ܸ���
    kPinAlt1,  //1���ܸ���
    kPinAlt2,  //2���ܸ���
    kPinAlt3,  //3���ܸ���
    kPinAlt4,  //4���ܸ���
    kPinAlt5,  //5���ܸ���
    kPinAlt6,  //6���ܸ���
    kPinAlt7,  //7���ܸ���
}PORT_PinMux_Type;

/* �˿����������� ��������ֵԼΪ20K*/
typedef enum
{
    kPullDisabled,  //�ر����������蹦��
    kPullUp,        //�����������蹦��
    kPullDown,      //�����������蹦��
}PORT_Pull_Type;

/* GPIO�˿�ģʽ���� */
typedef enum
{
    kGPIO_Mode_IFT = 0x00,       //��������
    kGPIO_Mode_IPD = 0x01,       //��������
    kGPIO_Mode_IPU = 0x02,       //��������
    kGPIO_Mode_OPP = 0x04,       //�������
}GPIO_Mode_Type;

/* �˿��������ģʽѡ�� */
typedef enum
{
    kInput,                  //��������ģʽ
    kOutput,                 //�������ģʽ
}GPIO_PinConfig_Type;

/* �˿��жϼ�DMA����ѡ�� */
typedef enum
{
    kGPIO_DMA_RisingEdge,	      //�����ش���DMA
    kGPIO_DMA_FallingEdge,        //�½��ش���DMA
    kGPIO_DMA_RisingFallingEdge,  //�����غ��½��ش���DMA
    kGPIO_IT_Low,                 //�͵�ƽ�����ж�
    kGPIO_IT_RisingEdge,          //�����ش����ж�
    kGPIO_IT_FallingEdge,         //�½��ش����ж�
    kGPIO_IT_RisingFallingEdge,   //�����غ��½��ش����ж�
    kGPIO_IT_High,                //�ߵ�ƽ�����ж�
}GPIO_ITDMAConfig_Type;

/* �˿ڳ�ʼ���ṹ�� */
typedef struct
{
    uint8_t                instance;    //���Ŷ˿�HW_GPIOA~HW_GPIOF
    GPIO_Mode_Type         mode;        //����ģʽ
    uint32_t               pinx;        //���ź�0~31
}GPIO_InitTypeDef;

/* �˿��жϻص��������� */
typedef void (*GPIO_CallBackType)(uint32_t pinxArray);
//typedef void (*GPIO_CallBackType)(void);

/* �������� */
#define IS_GPIO_ALL_INSTANCE(INSTANCE)  (INSTANCE < ARRAY_SIZE(GPIO_InstanceTable))
#define IS_PORT_ALL_INSTANCE(INSTANCE)  (INSTANCE < ARRAY_SIZE(PORT_InstanceTable))
#define IS_GPIO_ALL_PIN(PIN)  (PIN < 32)



//!< API functions
void GPIO_Init(GPIO_InitTypeDef * GPIO_InitStruct);
uint8_t GPIO_QuickInit(uint32_t instance, uint32_t pinx, GPIO_Mode_Type mode);
void GPIO_WriteBit(uint32_t instance, uint8_t pinIndex, uint8_t data);
uint8_t GPIO_ReadBit(uint32_t instance, uint8_t pinIndex);
void GPIO_ToggleBit(uint32_t instance, uint8_t pinIndex);
void GPIO_ITDMAConfig(uint32_t instance, uint8_t pinIndex, GPIO_ITDMAConfig_Type config, bool status);
void GPIO_CallbackInstall(uint32_t instance, GPIO_CallBackType AppCBFun);
//!< low level functions
void PORT_PinPullConfig(uint32_t instance, uint8_t pinIndex, PORT_Pull_Type pull);
void GPIO_PinConfig(uint32_t instance, uint8_t pinIndex, GPIO_PinConfig_Type mode);
void PORT_PinMuxConfig(uint32_t instance, uint8_t pinIndex, PORT_PinMux_Type pinMux);
uint32_t GPIO_ReadPort(uint32_t instance);
void GPIO_WritePort(uint32_t instance, uint32_t data);


#ifdef __cplusplus
}
#endif

#endif/* __CH_LIB_KL_GPIO_H__ */


