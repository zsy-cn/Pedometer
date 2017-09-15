/**
  ******************************************************************************
  * @file    button.h
  * @brief   ����KL46�ļƲ������-����Ӧ�ó���ͷ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�
             This file is an internal file, and the user does not need to call and modify it  
  ******************************************************************************
  */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "common.h"
#include "gpio.h"

#define key_plus    (PORTC|6)    /* ��+��ʹ������          */
#define key_mode    (PORTC|5)    /* ��Mode��ʹ������ */
#define key_minus   (PORTC|4)    /* ��-��ʹ������          */

/**
*\brief ������ʼ��
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/

void button_init(void);

/**
*\brief �����ж�ʹ��
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/

void button_int(void);

#endif /* __BUTTON_H__ */
