 /**
  ******************************************************************************
  * @file    flash.h
  * @brief   基于KL46的计步器设计-Flash模拟eeprom头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
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
*\note  flash初始化
*/
void flash_init(void);

/**
*\brief flash_erase
*
*\param[in]     sectorNo：扇区号（KL25实际使用0~127）
*\param[out]    none
*\param[in,out] none
*
*\retval 函数执行执行状态：0=正常；非0=异常。
*
*\note  擦除指定flash扇区
*/
uint_8 flash_erase_sector(uint_16 sectorNo);

/**
*\brief flash_write
*
*\param[in]     sectNo：目标扇区号 （KL25实际使用0~127）
				offset:写入扇区内部偏移地址（0~2043）
				cnt：写入字节数目（0~2043）
				buf：源数据缓冲区首地址
*\param[out]    none
*\param[in,out] none
*
*\retval 函数执行状态：0=正常；非0=异常。
*
*\note  flash写入操作
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
*\retval 函数执行状态：0=正常；非0=异常
*
*\note  flash加密操作
*/
uint_8 flash_secure(uint_8 key[]);

/**
*\brief flash_unsecure
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval 函数执行状态：0=正常；非0=异常
*
*\note  flash解密操作
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
*\note  flash保护操作
*/
void flash_protect(void);

#endif /* __FLASH_H__ */


