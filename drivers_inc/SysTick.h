/**
  ******************************************************************************
  * @file    systick.h
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�ΪоƬARM�ں��е�SysTickģ��ĵײ㹦�ܺ���
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

