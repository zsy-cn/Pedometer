/*********************************************************************************************************
*                           Pedometer
*                       -----------------
*                       The embed Project
*
* Contact information:
* web site:    https://zsy-cn.github.io
* e-mail:      zgjlzsy@foxmail.com
*********************************************************************************************************/
/**
 * \file 
 * \brief 计步器主程序
 * 
 * detailed descriptions for this file (optional).
 * 
 * \internal
 * \par Modification hisroty
 * 
 * -1.00 15-04-28 zhaoshouyang,first implementation
 * \endinternal
 */

#include "common.h"
#include "gpio.h"
#include "uart.h"
#include "systick.h"
#include "dht11.h"
#include "slcd.h"
#include "isr.h"
#include "mma8652fc.h"
#include "button.h"
#include "timer.h"
#include "flash.h"
#include "data_storage.h"
#include "lptmr.h"
#include "smc.h"

uint_8  vlpsflag;                                                   /*低功耗进入判断标志                */
uint_8  g_run_mode;                                                 /*运行模式                          */
uint_8  g_run_mode_remember;                                        /*记录设置前的状态                  */
uint_8  g_run_step_mode;                                            /*记录是日计步还是单次计步          */
uint_8  g_temp_humi[2];                                             /*记录温湿度                        */
uint_8  g_flag[4];                                                  /*flash扇区标记                     */
uint_16 g_height;                                                   /*记录身高                          */
uint_16 g_weight;                                                   /*记录体重                          */
uint_16 g_steplength;                                               /*记录步长                          */
uint_16 g_info[4];                                                  /*身高，体重，步长存储              */

float   g_today[4];                                                 /*记录当天步数，距离，时间，卡路里  */
float   g_once[4];                                                  /*记录当次步数，距离，时间，卡路里  */
float   g_day1[4];                                                  /*记录昨天步数，距离，时间，卡路里  */
float   g_day2[4];                                                  /*记录前天步数，距离，时间，卡路里  */
float   g_day3[4];                                                  /*记录大前天步数，距离，时间，卡路里*/

/**
*\brief 主函数
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
int main(void)
{
    SystemCoreClockUpdate ();                                       /*更新时钟                      */
    SMC_PMPROT =  SMC_PMPROT_AVLLS_MASK | SMC_PMPROT_AVLP_MASK;     /* 使能MCU低功耗模式切换        */
    DelayInit();                                                    /*systick初始化                 */
    button_init();                                                  /*按键初始化                    */
    DHT11_Init();                                                   /*温湿度传感器初始化            */
    SLCD_Init();                                                    /*LCD屏初始化                   */
    SLCD_Num_ON();                                                  /*LCD全亮                       */
    LPTMR_TC_Init();                                                /*定时一分钟                    */
    LPTMR_ITDMAConfig(kLPTMR_IT_TOF, true);                         /*开定时器中断                  */
    mma8652_init();                                                 /*加速度传感器初始化 Standby模式*/
    flash_init();                                                   /*Flash初始化                   */
    data_storage_init(g_info, g_today, g_day1, g_day2, g_day3);     /*读取用户数据                  */

    g_run_mode      = NorMode_Stepcount;                            /*初始运行状态                  */
    g_run_step_mode = 0;                                            /*运行状态标志                  */

    NVIC_EnableIRQ(PORTC_PORTD_IRQn);                               /*使能按键中断                  */
    NVIC_SetPriority(PORTC_PORTD_IRQn, 1);
    NVIC_EnableIRQ(PORTA_IRQn);                                     /*使能加速度传感器中断          */
    NVIC_SetPriority(PORTA_IRQn, 2);

    button_int();                                                   /*使能按键引脚中断              */
    mma8652_enable_fifo_int();                                      /*使能加速度传感器FIFO中断      */
    mma8652_active();                                               /*配置加速度传感器2G，200Hz模式 */
    
    while(1)
    {
        if(vlpsflag==0)                                             /*判断进入低功耗条件            */
        {
            if(~((PORTC->ISFR & 0x0040)|(PORTC->ISFR & 0x0020)|(PORTC->ISFR & 0x0010)))
            {
                DelayMs(10000);
                enter_vlps();
            }
        }
        else
        {
            enter_vlps();                                            /*进入低功耗模式               */
        }
    }
}

/* end of file */


