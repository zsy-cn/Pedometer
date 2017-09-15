 /**
  ******************************************************************************
  * @file    dht11.c
  * @brief   基于KL46的计步器设计-温湿度传感器驱动源程序
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note   
  ******************************************************************************
  */

#include "common.h"
#include "dht11.h"
#include "uart.h"
#include "gpio.h"
#include "slcd.h"

/*********************************************************************************************************
  全局变量
*********************************************************************************************************/
static uint_8 status;          /*读取是否成功标志*/
static uint_8 value_array[5];  /*存放五字节数据的数组*/
extern uint_16 g_temp_humi[2]; /*温湿度存放数组*/

/**
*\brief 温湿度传感器初始化
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
void DHT11_Init(void)
{
    SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;              /*开启GPIOD时钟                                           */
    PORT_PinMuxConfig(HW_GPIOD, 7, kPinAlt1);      /*将PTD7设置成GPIO功能                                    */
}

/**
*\brief 读取一位数据，26-28us的高电平表示该位是0，70us高电平表该位为1
*
*\param[in]     none
*\param[out]    0或1
*\param[in,out] none
*
*\retval value
*\retval none
*
*\note  none
*/
static uint_8 DHT11_ReadValue(void)
{
    unsigned char value=0,i;
    status=OK;                                     /*设定标志为正常状态                                      */
    for(i=8;i>0;i--)
    {
        value<<=1;                                 /*高位在先,在此移位                                       */

        while((GPIO_ReadBit(HW_GPIOD, 7))==0);     /*每一位数据前会有一个50us的低电平时间，等待50us低电平结束*/

        DelayUs(50);                               /*延时50us后检测数据线是否还是高电平                      */

        if((GPIO_ReadBit(HW_GPIOD, 7))!=0) {
            value++;                               /*进入这里表示该位为1                                     */
            while((GPIO_ReadBit(HW_GPIOD, 7))!=0); /*等待剩余约40us的高电平结束                              */
        }
    }
    return(value);
}

/**
*\brief 读温度和湿度函数，读一次的数据共五字节
*
*\param[in]     none
*\param[out]    读出成功函数返回OK，错误返回ERROR
*\param[in,out] none
*
*\retval status
*\retval none
*
*\note  none
*/
uint_8 DHT_ReadTempHumi()
{
    uint_8 i=0,check_value=0;

    GPIO_PinConfig(HW_GPIOD, 7, kOutput);      /*配置PTD7为输出                                                       */
    GPIO_WriteBit(HW_GPIOD, 7, 0);             /*拉低数据线大于18ms发送开始信号                                       */
    DelayMs(20);
    GPIO_PinConfig(HW_GPIOD, 7, kInput);       /*释放数据线，用于检测低电平的应答信号                                 */
    DelayUs(20);                               /*延时20-40us，等待一段时间后检测应答信号，应答信号是从机拉低数据线80us*/

    if((GPIO_ReadBit(HW_GPIOD, 7))!=0) {       /*检测应答信号，应答信号是低电平                                       */
        return ERROR;                          /*没应答信号                                                           */
    } else {
        while((GPIO_ReadBit(HW_GPIOD, 7))==0); /*有应答信号，等待应答信号结束                                         */
        while((GPIO_ReadBit(HW_GPIOD, 7))!=0);

        for(i=0;i<4;i++)                       /*读出湿，温度值                                                       */
        {
            value_array[i]=DHT11_ReadValue();
            if(status==ERROR) {                /*调用ReadValue()读数据出错会设定status为ERROR                         */
                return ERROR;
            }
            if(i!=4) {                         /*读出的最后一个值是校验值不需要加上去                                 */
                check_value+=value_array[i];   /*读出的五字节数据中的前四字节数据和等于第五字节数据表示成功           */
            }
        }
        if(check_value==value_array[4]) {      /*在没用发生函数调用失败时进行校验                                     */
            g_temp_humi[0]= value_array[0];    /*湿度                                                                 */
            g_temp_humi[1]= value_array[2];    /*温度                                                                 */
            return OK;                         /*正确读出DHT11输出的数据                                              */
        } else {
            return ERROR;                      /*没有读出DHT11输出的数据                                              */
        }
    }
}

/* end of file */















