 /**
  ******************************************************************************
  * @file    data_storage.h
  * @brief   ����KL46�ļƲ������-Flash�洢����ͷ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�  
  ******************************************************************************
  */

#ifndef __DATA_STORAGE_H__
#define __DATA_STORAGE_H__

#include "common.h"
#include "flash.h"

#define INFO_SECNO        70    /* ������Ϣ�洢������      */
#define FLAG_SECNO        71    /* �����ű�ǩ�洢������  */
#define TODAY_SECNO       72    /* ������Ϣ�洢������      */
#define SECNO1            73    /* ������Ϣ�洢������      */
#define SECNO2            74    /* ǰ����Ϣ�洢������      */
#define SECNO3            75    /* ��ǰ����Ϣ�洢������ */

/**
 * \brief ��Flashд��8λ�޷�����������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_write_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_8 buf[]);

/**
 * \brief ��Flashд��16λ�޷�����������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_write_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_16 buf[]);

/**
 * \brief ��Flashд��32λ�޷�����������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_write_u32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_32 buf[]);

/**
 * \brief ��Flashд�뵥���ȸ���������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_write_32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,float buf[]);

/**
 * \brief ��Flash��ȡ8λ�޷�����������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_read_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_8 buf[]);

/**
 * \brief ��Flash��ȡ16λ�޷�����������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_read_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_16 buf[]);

/**
 * \brief ��Flash��ȡ32λ�޷�����������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_read_u32b(uint_16 sectNo, uint_16 offset, uint_16 cnt, uint_16 buf[]);

/**
 * \brief ��Flash��ȡ�����ȸ���������
 *
 * \param[in] sectNo : ������
 * \param[in] offset : д�������ڲ�ƫ�Ƶ�ַ
 * \param[in] cnt    : д�����ݵ���Ŀ
 * \param[in] buf    : Դ���ݻ������׵�ַ
 *
 * \return ��
 */
void data_read_32b(uint_16 sectNo, uint_16 offset, uint_16 cnt, float buf[]);

/**
 * \brief ����������
 *
 * \details �Ƚ���Flag[0]��Flag[2],�ٽ���Flag[1]��Flag[2]
 *
 * \result Flag[0]Ϊ�������������ţ�Flag[1]ΪǮǰ�����������ţ�Flag[2]Ϊ��ǰ�����������ţ�
 *
 * \param[in] flag : ����������ͷ��ַ
 *
 * \return ��
 */
void data_process_flag(uint_8 *flag);

/**
 * \brief ��Flash�洢������Ϣ
 *
 * \param[in] info : ��Ҫ�洢������
 *
 * \return ��
 */
void data_storage_info(uint_16 info[]);

/**
 * \brief �ѵ������Ϣ��¼��Flash
 *
 * \param[in] today : ��Ҫ�洢������
 *
 * \return ��
 */
void data_storage_today(float today[]);

/**
 * \brief ��Flash�洢�������Ϣ
 *
 * \param[in] today : ��Ҫ��¼������
 *
 * \return ��
 */
void data_storage_days(float today[]);

/**
 * \brief �ϵ��λ�����ݳ�ʼ��
 *
 * \param[in] info  : ��Ҫ��ʼ���ĸ�����Ϣ
 * \param[in] today : ��Ҫ��ʼ���ĵ�������
 * \param[in] day1  : ��Ҫ��ʼ������������
 * \param[in] day2  : ��Ҫ��ʼ����ǰ������
 * \param[in] day3  : ��Ҫ��ʼ���Ĵ�ǰ������
 *
 * \return ��
 */
void data_storage_init(uint_16 info[], float today[], float day1[], float day2[], float day3[]);


#endif /* __DATA_STORAGE_H__ */
