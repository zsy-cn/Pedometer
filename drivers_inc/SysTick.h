/**
  ******************************************************************************
  * @file    systick.h
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为芯片ARM内核中的SysTick模块的底层功能函数
  ******************************************************************************
  */
  
#ifndef __CH_LIB_KL_SYSTICK_H__
#define __CH_LIB_KL_SYSTICK_H__

#include <stdint.h>
#include <stdbool.h>

void SYSTICK_DelayInit(void);
void SYSTICK_Init(uint32_t timeInUs);
void SYSTICK_Cmd(bool NewState);
void SYSTICK_ITConfig(bool NewState);
void SYSTICK_DelayUs(uint32_t us);
void SYSTICK_DelayMs(uint32_t ms);

#endif

