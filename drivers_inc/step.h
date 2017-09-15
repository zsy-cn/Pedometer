/**
  ******************************************************************************
  * @file    step.h
  * @brief   ����KL46�ļƲ������-�Ʋ��㷨ͷ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�Ϊ�ڲ��ļ����û�������ú��޸�  
  ******************************************************************************
  */

#ifndef __STEP_H__
#define __STEP_H__

#include "common.h"
#include "mma8652fc.h"
#include "slcd.h"

extern int StepCount;
extern int StepCountFlag;

void step_data_process(float step_data[], uint_16 info[]);   /*���룬������ʱ�����*/
unsigned char AxisSelect(void);                              /*ѡ���Ǹ��������Ʋ�  */
void CountStep(void);                                        /*�Ʋ�������          */

#endif/* __STEP_H__ */



