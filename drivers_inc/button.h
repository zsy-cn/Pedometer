/**
  ******************************************************************************
  * @file    button.h
  * @brief   基于KL46的计步器设计-按键应用程序头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改
             This file is an internal file, and the user does not need to call and modify it  
  ******************************************************************************
  */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "common.h"
#include "gpio.h"

#define key_plus    (PORTC|6)    /* “+”使用引脚          */
#define key_mode    (PORTC|5)    /* “Mode”使用引脚 */
#define key_minus   (PORTC|4)    /* “-”使用引脚          */

/**
*\brief 按键初始化
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
*\brief 按键中断使能
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
