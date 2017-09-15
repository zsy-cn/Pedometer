/**
  ******************************************************************************
  * @file    button.c
  * @brief   基于KL46的计步器设计-按键应用程序源程序
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note      
  ******************************************************************************
  */

#include "button.h"

/**
 * \brief 按键初始化
 */
void button_init(void)
{
    /* 初始化为输入引脚，输出高电平  */
    GPIO_QuickInit(HW_GPIOC, 6, kGPIO_Mode_IFT);
    GPIO_QuickInit(HW_GPIOC, 5, kGPIO_Mode_IFT);
    GPIO_QuickInit(HW_GPIOC, 4, kGPIO_Mode_IFT);
}

/**
 * \brief 按键中断使能
 */
void button_int(void)
{
    /* 下降沿触发 */
    GPIO_ITDMAConfig(HW_GPIOC, 6, kGPIO_IT_FallingEdge, true); 
    GPIO_ITDMAConfig(HW_GPIOC, 5, kGPIO_IT_FallingEdge, true); 
    GPIO_ITDMAConfig(HW_GPIOC, 4, kGPIO_IT_FallingEdge, true);

}


