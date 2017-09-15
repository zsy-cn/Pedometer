/**
  ******************************************************************************
  * @file    step.h
  * @brief   基于KL46的计步器设计-计步算法头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */

#ifndef __STEP_H__
#define __STEP_H__

#include "common.h"
#include "mma8652fc.h"
#include "slcd.h"

extern int StepCount;
extern int StepCountFlag;

void step_data_process(float step_data[], uint_16 info[]);   /*距离，能量，时间计算*/
unsigned char AxisSelect(void);                              /*选择那个轴用来计步  */
void CountStep(void);                                        /*计步主函数          */

#endif/* __STEP_H__ */



