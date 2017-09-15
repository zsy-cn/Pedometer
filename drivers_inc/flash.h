 /**
  ******************************************************************************
  * @file    flash.h
  * @brief   ����KL46�ļƲ������-Flashģ��eepromͷ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�  
  ******************************************************************************
  */

#ifndef __FLASH_H__
#define __FLASH_H__

#include "common.h"

/**
*\brief flash_init
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  flash��ʼ��
*/
void flash_init(void);

/**
*\brief flash_erase
*
*\param[in]     sectorNo�������ţ�KL25ʵ��ʹ��0~127��
*\param[out]    none
*\param[in,out] none
*
*\retval ����ִ��ִ��״̬��0=��������0=�쳣��
*
*\note  ����ָ��flash����
*/
uint_8 flash_erase_sector(uint_16 sectorNo);

/**
*\brief flash_write
*
*\param[in]     sectNo��Ŀ�������� ��KL25ʵ��ʹ��0~127��
				offset:д�������ڲ�ƫ�Ƶ�ַ��0~2043��
				cnt��д���ֽ���Ŀ��0~2043��
				buf��Դ���ݻ������׵�ַ
*\param[out]    none
*\param[in,out] none
*
*\retval ����ִ��״̬��0=��������0=�쳣��
*
*\note  flashд�����
*/
uint_8 flash_write(uint_16 sectNo,uint_16 offset,uint_16 cnt,uint_8 buf[]);

#define flash_read(sectNo,offset,type)    *((type *)( sectNo * 1024 + offset))

/**
*\brief flash_secure
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval ����ִ��״̬��0=��������0=�쳣
*
*\note  flash���ܲ���
*/
uint_8 flash_secure(uint_8 key[]);

/**
*\brief flash_unsecure
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval ����ִ��״̬��0=��������0=�쳣
*
*\note  flash���ܲ���
*/
uint_8 flash_unsecure(void);

/**
*\brief flash_protect
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  flash��������
*/
void flash_protect(void);

#endif /* __FLASH_H__ */


