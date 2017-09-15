 /**
  ******************************************************************************
  * @file    dht11.h
  * @brief   基于KL46的计步器设计-温湿度传感器驱动头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */

#ifndef __DHT11_H__
#define __DHT11_H__

#include "common.h"

#define OK    1
#define ERROR 0
/**
*\brief dht11初始化
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
*\brief 读取一位数据
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
*\brief dht11读取温湿度
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

