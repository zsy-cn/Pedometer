/**
  ******************************************************************************
  * @file    button.c
  * @brief   ����KL46�ļƲ������-����Ӧ�ó���Դ����
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note      
  ******************************************************************************
  */

#include "button.h"

/**
 * \brief ������ʼ��
 */
void button_init(void)
{
    /* ��ʼ��Ϊ�������ţ�����ߵ�ƽ  */
    GPIO_QuickInit(HW_GPIOC, 6, kGPIO_Mode_IFT);
    GPIO_QuickInit(HW_GPIOC, 5, kGPIO_Mode_IFT);
    GPIO_QuickInit(HW_GPIOC, 4, kGPIO_Mode_IFT);
}

/**
 * \brief �����ж�ʹ��
 */
void button_int(void)
{
    /* �½��ش��� */
    GPIO_ITDMAConfig(HW_GPIOC, 6, kGPIO_IT_FallingEdge, true); 
    GPIO_ITDMAConfig(HW_GPIOC, 5, kGPIO_IT_FallingEdge, true); 
    GPIO_ITDMAConfig(HW_GPIOC, 4, kGPIO_IT_FallingEdge, true);

}


