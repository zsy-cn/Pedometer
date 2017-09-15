 /**
  ******************************************************************************
  * @file    data_storage.c
  * @brief   基于KL46的计步器设计-Flash存储功能源程序
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    
  ******************************************************************************
  */

#include"data_storage.h"

/**
 * \brief 向Flash写入8位无符号整型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
 */
void data_write_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_8 buf[])
{
    flash_erase_sector(sectNo);
    flash_write(sectNo, offset, cnt, buf);
}

/**
 * \brief 向Flash写入16位无符号整型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
 */
void data_write_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_16 buf[])
{
    uint_16 i = 0;
    uint_16 j = 0;
    uint_8 buf_t[16]={0};                                 /* 缓冲区  */

    /* 提取高八位和低八位 */
    for(j = 0;j < cnt;j++)
    {
        buf_t[i]   = (uint_8)(buf[j] & 0x00FF);           /* 无符号低八位  */
        buf_t[i+1] = (uint_8)((buf[j] >> 8) & 0x00FF);    /* 无符号高八位  */
        i += 2;
    }

    flash_erase_sector(sectNo);
    flash_write(sectNo, offset, (cnt*2), buf_t);
}

/**
 * \brief 向Flash写入32位无符号整型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
 */
void data_write_u32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_32 buf[])
{
    uint_16 i = 0;
    uint_16 j = 0;
    uint_8 buf_t[16]={0};        /* 八位缓冲区，长度应为 (cnt*2) */

    /* 提取数据位  */
    for(j = 0;j < cnt;j++)
    {
        buf_t[i]   = (uint_8)(buf[j] & 0x000000FF);           /*  7~0位             */
        buf_t[i+1] = (uint_8)((buf[j] >> 8) & 0x000000FF);    /* 15~8位         */
        buf_t[i+2] = (uint_8)((buf[j] >> 16) & 0x000000FF);   /* 23~16位     */
        buf_t[i+3] = (uint_8)((buf[j] >> 24) & 0x000000FF);   /* 32~24位     */
        i += 4;
    }

    flash_erase_sector(sectNo);
    flash_write(sectNo, offset, (cnt*2), buf_t);
}

/**
 * \brief 向Flash写入单精度浮点型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
 */
void data_write_32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,float buf[])
{
    uint_32 *buf_t[4];                /* 32位缓冲区，长度应为 (cnt*2) */

    /* 强制转换为32位无符号地址  */
    buf_t[0] = (uint_32*)&buf[0];
    buf_t[1] = (uint_32*)&buf[1];
    buf_t[2] = (uint_32*)&buf[2];
    buf_t[3] = (uint_32*)&buf[3];

    uint_32 buf_tt[4];                /* 缓冲区 */
    buf_tt[0] = *buf_t[0];
    buf_tt[1] = *buf_t[1];
    buf_tt[2] = *buf_t[2];
    buf_tt[3] = *buf_t[3];

    flash_erase_sector(sectNo);
    data_write_u32b(sectNo, 0, 4, buf_tt);
}

/**
 * \brief 从Flash读取8位无符号整型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
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
 * \brief 从Flash读取16位无符号整型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
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
 * \brief 从Flash读取32位无符号整型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
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
 * \brief 从Flash读取单精度浮点型数据
 *
 * \param[in] sectNo : 扇区号
 * \param[in] offset : 写入扇区内部偏移地址
 * \param[in] cnt    : 写入数据的数目
 * \param[in] buf    : 源数据缓冲区首地址
 *
 * \return 无
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
 * \brief 交换扇区号
 *
 * \details 先交换Flag[0]和Flag[2],再交换Flag[1]和Flag[2]
 *
 * \result Flag[0]为昨天数据扇区号，Flag[1]为钱前天数据扇区号，Flag[2]为大前天数据扇区号，
 *
 * \param[in] flag : 扇区号数组头地址
 *
 * \return 无
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
 * \brief 向Flash存储个人信息
 *
 * \param[in] info : 需要存储的数据
 *
 * \return 无
 */
void data_storage_info(uint_16 info[])
{
    data_write_u16b(INFO_SECNO , 0, 4, info);
}

/**
 * \brief 把当天的信息记录到Flash
 *
 * \param[in] today : 需要记录的数据
 *
 * \return 无
 */
void data_storage_today(float today[])
{
    data_write_32b(TODAY_SECNO, 0, 4, today);
}

/**
 * \brief 向Flash存储当天的信息
 *
 * \param[in] today : 需要存储的数据
 *
 * \return 无
 */
void data_storage_days(float today[])
{
    /*
     * flag[0] : 昨天数据扇区号
     * flag[1] : 前天数据扇区号
     * flag[2] : 大前天数据扇区号
     * flag[3] : 凑位
     */
    uint_8 flag[4] = {0};

    data_read_u8b(FLAG_SECNO, 0, 4, flag);       /* 读取扇区号                                                                      */
    data_write_32b(flag[2], 0, 4, today);        /* 把今天的数据存在扇区号为flag[2]的扇区 */

    data_process_flag(flag);                     /* 处理扇区号                                                                       */
    data_write_u8b(FLAG_SECNO, 0, 4, flag);      /* 存扇区号                                                                            */

    /* 清除今天的数据 */
    today[0] = 0;
    today[1] = 0;
    today[2] = 0;
    today[3] = 0;
}

/**
 * \brief 上电或复位后数据初始化
 *
 * \param[in] info  : 需要初始化的个人信息
 * \param[in] today : 需要初始化的当天数据
 * \param[in] day1  : 需要初始化的昨天数据
 * \param[in] day2  : 需要初始化的前天数据
 * \param[in] day3  : 需要初始化的大前天数据
 *
 * \return 无
 */
void data_storage_init(uint_16 info[], float today[], float day1[], float day2[], float day3[])
{
    uint_8  i, j;
    uint_8  flag[4] = {0};
    uint_32 buf[4]  = {0};
    /* 读扇区号,如果有扇区号错误，则重写 */
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

    /* 读昨天数据，如果有错误，则重写为0 */
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

    /* 读前天数据，如果有错误，则重写为0 */
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

    /* 读大前天数据，如果有错误，则重写为0 */
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
    /* 读身高、体重、步长数据，如果有错误，则重写默认值 */
    data_read_u16b(INFO_SECNO, 0, 4, info);
    if(info[0] < 1 || info[0] > 9999 || \
       info[1] < 1 || info[1] > 9999 || \
       info[2] < 1 || info[2] > 9999)
    {
        info[0] = 170;        /* 身高初始值为170cm */
        info[1] = 50;         /* 体重初始值为50kg  */
        info[2] = 75;         /* 步长初始值为75cm  */
        info[3] = 0;          /* 凑位                                       */
        data_write_u16b(INFO_SECNO , 0, 4, info);
    }

    /* 读今天数据，如果有错误，则重写为0 */
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

