 /**
  ******************************************************************************
  * @file    dht11.h
  * @brief   ����KL46�ļƲ������-��ʪ�ȴ���������ͷ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�  
  ******************************************************************************
  */

#ifndef __DHT11_H__
#define __DHT11_H__

#include "common.h"

#define OK    1
#define ERROR 0
/**
*\brief dht11��ʼ��
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
void DHT11_Init(void);                 

/**
*\brief ��ȡһλ����
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
static uint_8 DHT11_ReadValue(void);   

/**
*\brief dht11��ȡ��ʪ��
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
uint_8 DHT_ReadTempHumi(void);         

#endif /* __DHT11_H__ */

