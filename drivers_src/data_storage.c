 /**
  ******************************************************************************
  * @file    data_storage.c
  * @brief   ����KL46�ļƲ������-Flash�洢����Դ����
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    
  ******************************************************************************
  */

#include"data_storage.h"

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
void data_write_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_8 buf[])
{
    flash_erase_sector(sectNo);
    flash_write(sectNo, offset, cnt, buf);
}

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
void data_write_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_16 buf[])
{
    uint_16 i = 0;
    uint_16 j = 0;
    uint_8 buf_t[16]={0};                                 /* ������  */

    /* ��ȡ�߰�λ�͵Ͱ�λ */
    for(j = 0;j < cnt;j++)
    {
        buf_t[i]   = (uint_8)(buf[j] & 0x00FF);           /* �޷��ŵͰ�λ  */
        buf_t[i+1] = (uint_8)((buf[j] >> 8) & 0x00FF);    /* �޷��Ÿ߰�λ  */
        i += 2;
    }

    flash_erase_sector(sectNo);
    flash_write(sectNo, offset, (cnt*2), buf_t);
}

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
void data_write_u32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_32 buf[])
{
    uint_16 i = 0;
    uint_16 j = 0;
    uint_8 buf_t[16]={0};        /* ��λ������������ӦΪ (cnt*2) */

    /* ��ȡ����λ  */
    for(j = 0;j < cnt;j++)
    {
        buf_t[i]   = (uint_8)(buf[j] & 0x000000FF);           /*  7~0λ             */
        buf_t[i+1] = (uint_8)((buf[j] >> 8) & 0x000000FF);    /* 15~8λ         */
        buf_t[i+2] = (uint_8)((buf[j] >> 16) & 0x000000FF);   /* 23~16λ     */
        buf_t[i+3] = (uint_8)((buf[j] >> 24) & 0x000000FF);   /* 32~24λ     */
        i += 4;
    }

    flash_erase_sector(sectNo);
    flash_write(sectNo, offset, (cnt*2), buf_t);
}

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
void data_write_32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,float buf[])
{
    uint_32 *buf_t[4];                /* 32λ������������ӦΪ (cnt*2) */

    /* ǿ��ת��Ϊ32λ�޷��ŵ�ַ  */
    buf_t[0] = (uint_32*)&buf[0];
    buf_t[1] = (uint_32*)&buf[1];
    buf_t[2] = (uint_32*)&buf[2];
    buf_t[3] = (uint_32*)&buf[3];

    uint_32 buf_tt[4];                /* ������ */
    buf_tt[0] = *buf_t[0];
    buf_tt[1] = *buf_t[1];
    buf_tt[2] = *buf_t[2];
    buf_tt[3] = *buf_t[3];

    flash_erase_sector(sectNo);
    data_write_u32b(sectNo, 0, 4, buf_tt);
}

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
void data_read_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_8 buf[])
{
    uint_16 i = 0;
    for(i = 0;i < cnt; i++)
    {
        buf[i] = flash_read(sectNo, offset, uint_8);
        offset += 1;
    }
}

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
void data_read_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_16 buf[])
{
    uint_16 i = 0;
    for(i = 0;i < cnt; i++)
    {
        buf[i] = flash_read(sectNo, offset, uint_16);
        offset += 2;
    }
}

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
void data_read_u32b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_16 buf[])
{
    uint_16 i = 0;
    for(i = 0;i < cnt; i++)
    {
        buf[i] = flash_read(sectNo, offset, uint_32);
        offset += 4;
    }
}

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
void data_read_32b(uint_16 sectNo,uint_16 offset, uint_16 cnt, float buf[])
{
    uint_16 i = 0;
    for(i = 0;i < cnt; i++)
    {
        buf[i] = flash_read(sectNo, offset, float);
        offset += 4;
    }
}

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
void data_process_flag(uint_8 *flag)
{
    uint_16 temp;

    temp = *flag;
    *flag = *(flag + 2);
    *(flag + 2) = temp;

    temp = *flag;
    *flag = *(flag + 1);
    *(flag + 1) = temp;
}

/**
 * \brief ��Flash�洢������Ϣ
 *
 * \param[in] info : ��Ҫ�洢������
 *
 * \return ��
 */
void data_storage_info(uint_16 info[])
{
    data_write_u16b(INFO_SECNO , 0, 4, info);
}

/**
 * \brief �ѵ������Ϣ��¼��Flash
 *
 * \param[in] today : ��Ҫ��¼������
 *
 * \return ��
 */
void data_storage_today(float today[])
{
    data_write_32b(TODAY_SECNO, 0, 4, today);
}

/**
 * \brief ��Flash�洢�������Ϣ
 *
 * \param[in] today : ��Ҫ�洢������
 *
 * \return ��
 */
void data_storage_days(float today[])
{
    /*
     * flag[0] : ��������������
     * flag[1] : ǰ������������
     * flag[2] : ��ǰ������������
     * flag[3] : ��λ
     */
    uint_8 flag[4] = {0};

    data_read_u8b(FLAG_SECNO, 0, 4, flag);       /* ��ȡ������                                                                      */
    data_write_32b(flag[2], 0, 4, today);        /* �ѽ�������ݴ���������Ϊflag[2]������ */

    data_process_flag(flag);                     /* ����������                                                                       */
    data_write_u8b(FLAG_SECNO, 0, 4, flag);      /* ��������                                                                            */

    /* ������������ */
    today[0] = 0;
    today[1] = 0;
    today[2] = 0;
    today[3] = 0;
}

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
void data_storage_init(uint_16 info[], float today[], float day1[], float day2[], float day3[])
{
    uint_8  i, j;
    uint_8  flag[4] = {0};
    uint_32 buf[4]  = {0};
    /* ��������,����������Ŵ�������д */
    data_read_u8b(FLAG_SECNO, 0, 4, flag);
    if((flag[0] != SECNO1 && flag[0] != SECNO2 && flag[0] != SECNO3) || \
       (flag[1] != SECNO1 && flag[1] != SECNO2 && flag[1] != SECNO3) || \
       (flag[2] != SECNO1 && flag[2] != SECNO2 && flag[2] != SECNO3))
    {
        flag[0] = SECNO1;
        flag[1] = SECNO2;
        flag[2] = SECNO3;
        flag[3] = 0;
        data_write_u8b(FLAG_SECNO, 0, 4, flag);
    }

    /* ���������ݣ�����д�������дΪ0 */
    data_read_32b(flag[0], 0, 4, day1);
    for(i = 0; i < 4;i++)
    {
        buf[i] = (uint_32)day1[i];
        if(buf[i] == 0 || buf[i] >= 9999)
        {
            for(j = 0; j < 4; j++)
            {
                day1[j] = 0;
            }
            data_write_32b(flag[0] , 0, 4, day1);
        }
        break;
    }

    /* ��ǰ�����ݣ�����д�������дΪ0 */
    data_read_32b(flag[1], 0, 4, day2);
    for(i = 0; i < 4;i++)
    {
        buf[i] = (uint_32)day2[i];
        if(buf[i] == 0 || buf[i] >= 9999)
        {
            for(j = 0; j < 4; j++)
            {
                day1[j] = 0;
            }
            data_write_32b(flag[1] , 0, 4, day2);
        }
        break;
    }

    /* ����ǰ�����ݣ�����д�������дΪ0 */
    data_read_32b(flag[2], 0, 4, day3);
    for(i = 0; i < 4;i++)
    {
        buf[i] = (uint_32)day3[i];
        if(buf[i] == 0 || buf[i] >= 9999)
        {
            for(j = 0; j < 4; j++)
            {
                day1[j] = 0;
            }
            data_write_32b(flag[2] , 0, 4, day3);
        }
        break;
    }
    /* ����ߡ����ء��������ݣ�����д�������дĬ��ֵ */
    data_read_u16b(INFO_SECNO, 0, 4, info);
    if(info[0] < 1 || info[0] > 9999 || \
       info[1] < 1 || info[1] > 9999 || \
       info[2] < 1 || info[2] > 9999)
    {
        info[0] = 170;        /* ��߳�ʼֵΪ170cm */
        info[1] = 50;         /* ���س�ʼֵΪ50kg  */
        info[2] = 75;         /* ������ʼֵΪ75cm  */
        info[3] = 0;          /* ��λ                                       */
        data_write_u16b(INFO_SECNO , 0, 4, info);
    }

    /* ���������ݣ�����д�������дΪ0 */
    data_read_32b(TODAY_SECNO, 0, 4, today);
    for(i = 0; i < 4;i++)
    {
        buf[i] = (uint_32)today[i];
        if(buf[i] == 0 || buf[i] >= 9999)
        {
            for(j = 0; j < 4; j++)
            {
                today[j] = 0;
            }
            data_write_32b(TODAY_SECNO, 0, 4, today);
        }
        break;
    }
}

