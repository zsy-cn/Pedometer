 /**
  ******************************************************************************
  * @file    data_storage.h
  * @brief   基于KL46的计步器设计-Flash存储功能头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */

#ifndef __DATA_STORAGE_H__
#define __DATA_STORAGE_H__

#include "common.h"
#include "flash.h"

#define INFO_SECNO        70    /* 个人信息存储扇区号      */
#define FLAG_SECNO        71    /* 扇区号标签存储扇区号  */
#define TODAY_SECNO       72    /* 今天信息存储扇区号      */
#define SECNO1            73    /* 昨天信息存储扇区号      */
#define SECNO2            74    /* 前天信息存储扇区号      */
#define SECNO3            75    /* 大前天信息存储扇区号 */

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
void data_write_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_8 buf[]);

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
void data_write_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_16 buf[]);

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
void data_write_u32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,uint_32 buf[]);

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
void data_write_32b(uint_16 sectNo,uint_16 offset, uint_16 cnt,float buf[]);

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
void data_read_u8b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_8 buf[]);

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
void data_read_u16b(uint_16 sectNo,uint_16 offset, uint_16 cnt, uint_16 buf[]);

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
void data_read_u32b(uint_16 sectNo, uint_16 offset, uint_16 cnt, uint_16 buf[]);

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
void data_read_32b(uint_16 sectNo, uint_16 offset, uint_16 cnt, float buf[]);

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
void data_process_flag(uint_8 *flag);

/**
 * \brief 向Flash存储个人信息
 *
 * \param[in] info : 需要存储的数据
 *
 * \return 无
 */
void data_storage_info(uint_16 info[]);

/**
 * \brief 把当天的信息记录到Flash
 *
 * \param[in] today : 需要存储的数据
 *
 * \return 无
 */
void data_storage_today(float today[]);

/**
 * \brief 向Flash存储当天的信息
 *
 * \param[in] today : 需要记录的数据
 *
 * \return 无
 */
void data_storage_days(float today[]);

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
void data_storage_init(uint_16 info[], float today[], float day1[], float day2[], float day3[]);


#endif /* __DATA_STORAGE_H__ */
