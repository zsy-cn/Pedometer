/**
  ******************************************************************************
  * @file    isr.h
  * @brief   基于KL46的计步器设计-isr头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */

#include "common.h"
#include "i2c0.h"
#include "mma8652fc.h"
#include "step.h"
#include "timer.h"
#include "gpio.h"
#include "slcd.h"
#include "dht11.h"
#include "uart.h"
#include "data_storage.h"


#ifndef __ISR_H__
#define __ISR_H__

void enter_vlps(void);
extern uint_8  g_time[2];        /*remember time,hour：g_time[0],minute：g_time[1],secend：g_time[2]*/
extern int16_t ucdate[3];


enum{
    NorMode_Timer,
    NorMode_Stepcount,           /*NorMode_StepCountDisplay*/
    NorMode_Temp,
    NorMode_Humi,
    NorMode_StepDistDisplay,
    NorMode_StepTimeDisplay,
    NorMode_StepEngDisplay,

    NorMode_OnceStepcount,
    NorMode_OnceStepDist,
    NorMode_OnceStepTime,
    NorMode_OnceStepEng,

    NorMode_Lastday,             //NorMode_Lastday_Stetcount
    NorMode_Lastday_StepDist,
    NorMode_Lastday_StepTime,
    NorMode_Lastday_StepEng,

    NorMode_BLastday,
    NorMode_BLastday_StepDist,
    NorMode_BLastday_StepTime,
    NorMode_BLastday_StepEng,

    NorMode_BBLastday,
    NorMode_BBLastday_StepDist,
    NorMode_BBLastday_StepTime,
    NorMode_BBLastday_StepEng,

    SetMode_Height,
    SetMode_Weight,
    SetMode_Steplength,
    SetMode_Timerhour,
    SetMode_Timerminu
};

#endif/* __ISR_H__ */





