/**
  ******************************************************************************
  * @file    smc.h
  * @brief   基于KL46的计步器设计-low power头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */

#ifndef __SMC_H__
#define __SMC_H__

void sleep(void);
void deepsleep(void);
void enter_wait(void);
void enter_stop(unsigned char partial_stop_opt);
int enter_vlpr(void);
void exit_vlpr(void);
void enter_vlps(void);
void enter_lls(void);
void enter_vlls3(void);
void enter_vlls2(void);
void enter_vlls1(void);
void enter_vlls0(unsigned char PORPO_value);
void enter_vlls0_nopor(void);

#endif /* __SMC_H__ */
