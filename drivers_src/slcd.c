/**
  ******************************************************************************
  * @file    slcd.c
  * @brief   基于KL46的计步器设计-段码LCD源程序
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note      
  ******************************************************************************
  */

#include "slcd.h"

/**
*\brief LCD初始化，所有段全亮
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
void SLCD_Init()
{
    SIM_SCGC5|=SIM_SCGC5_SLCD_MASK;         /*开启时钟                  */

    LCD->GCR|=LCD_GCR_CPSEL_MASK;
    LCD->GCR|=LCD_GCR_DUTY(3);              /*设置占空比                */
    LCD->GCR|=LCD_GCR_SOURCE_MASK;          /*selectaltclockIRC         */
    LCD->GCR|=LCD_GCR_LCDSTP_MASK;          /*低功耗关闭                */
    LCD->GCR|=LCD_GCR_LCDEN_MASK;           /*EnableLCD                 */
    LCD->PEN[0]=0x08F0F000;                 /*设置0-31位对应LCD引脚使能 */
    LCD->BPEN[0]=0x00F00000;                /*设置0-31位COM端使能       */
    LCD->PEN[1]=0x00007F00;                 /*设置32-63位对应LCD引脚使能*/

    LCD->WF[3] =0x0F0F0F0F;                 /*对应LCD引脚波形使能       */
    LCD->WF[5] =0x08040201;
    LCD->WF[6] =0x0F000000;
    LCD->WF[10]=0x0F0F0F0F;
    LCD->WF[11]=0x000F0F0F;
}

/**
*\brief LCD全亮
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
void SLCD_ON()
{
    LCD->WF[3] =0x0F0F0F0F;                 /*对应LCD引脚波形使能*/
    LCD->WF[6] =0x0F000000;
    LCD->WF[10]=0x0F0F0F0F;
    LCD->WF[11]=0x000F0F0F;
}

/**
*\brief LCD全关
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
void SLCD_OFF()
{
    LCD->WF[3] =0x00000000;                 /*对应LCD引脚波形禁能*/
    LCD->WF[6] =0x00000000;
    LCD->WF[10]=0x00000000;
    LCD->WF[11]=0x00000000;
}

/**
*\brief LCD数字全亮
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
void SLCD_Num_ON()
{
    LCD->WF[6] =0x0E000000;
    LCD->WF[10]=0x0E0F0E0F;
    LCD->WF[11]=0x000F0E0F;
}

/**
*\brief LCD数字全关
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
void SLCD_Num_OFF()
{
    LCD->WF[6] =0x00000000;
    LCD->WF[10]=0x00000000;
    LCD->WF[11]=0x00000000;
}

/**
*\brief 指示灯全关
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
void SLCD_TLight_OFF()
{
    LCD->WF[3] =0x00000000;
}

/**
*\brief LCD第一位亮数字
*
*\param[in]     要显示的数字0～9
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_1_ON(uint_8 x)
{
    LCD->WF[6] &= ~(S1_8_1);
    LCD->WF[10]&= ~(S1_8_2);
    
    switch(x)
    {
        case 0:
            LCD->WF[6] |= S1_0_1;
            LCD->WF[10]|= S1_0_2;
            break;
        case 1:
            LCD->WF[6] |= S1_1_1;
            break;
        case 2:
            LCD->WF[6] |= S1_2_1;
            LCD->WF[10]|= S1_2_2;
            break;
        case 3:
            LCD->WF[6] |= S1_3_1;
            LCD->WF[10]|= S1_3_2;
            break;
        case 4:
            LCD->WF[6] |= S1_4_1;
            LCD->WF[10]|= S1_4_2;
            break;
        case 5:
            LCD->WF[6] |= S1_5_1;
            LCD->WF[10]|= S1_5_2;
            break;
        case 6:
            LCD->WF[6] |= S1_6_1;
            LCD->WF[10]|= S1_6_2;
            break;
        case 7:
            LCD->WF[6] |= S1_7_1;
            break;
        case 8:
            LCD->WF[6] |= S1_8_1;
            LCD->WF[10]|= S1_8_2;
            break;
        case 9:
            LCD->WF[6] |= S1_9_1;
            LCD->WF[10]|= S1_9_2;
            break;
        default:
            LCD->WF[6] |= DP0;
            break;
    }
}

/**
*\brief LCD第二位亮数字
*
*\param[in]     要显示的数字0～9
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_2_ON(uint_8 x)
{
    LCD->WF[10]&= ~(S2_8_1+S2_8_2);
    
    switch(x)
    {
        case 0:
            LCD->WF[10]|= (S2_0_1+S2_0_2);
            break;
        case 1:
            LCD->WF[10]|= (S2_1_1);
            break;
        case 2:
            LCD->WF[10]|= (S2_2_1+S2_2_2);
            break;
        case 3:
            LCD->WF[10]|= (S2_3_1+S2_3_2);
            break;
        case 4:
            LCD->WF[10]|= (S2_4_1+S2_4_2);
            break;
        case 5:
            LCD->WF[10]|= (S2_5_1+S2_5_2);
            break;
        case 6:
            LCD->WF[10]|= (S2_6_1+S2_6_2);
            break;
        case 7:
            LCD->WF[10]|= (S2_7_1);
            break;
        case 8:
            LCD->WF[10]|= (S2_8_1+S2_8_2);
            break;
        case 9:
            LCD->WF[10]|= (S2_9_1+S2_9_2);
            break;
        default:
            LCD->WF[10]|= DP1;
            break;
    }
}

/**
*\brief LCD第三位亮数字
*
*\param[in]     要显示的数字0～9
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_3_ON(uint_8 x)
{
    LCD->WF[10]&= ~(S1_8_1);
    LCD->WF[11]&= ~(S1_8_2);
    
    switch(x)
    {
        case 0:
            LCD->WF[10]|= S3_0_1;
            LCD->WF[11]|= S3_0_2;
            break;
        case 1:
            LCD->WF[10]|= S3_1_1;
            break;
        case 2:
            LCD->WF[10]|= S3_2_1;
            LCD->WF[11]|= S3_2_2;
            break;
        case 3:
            LCD->WF[10]|= S3_3_1;
            LCD->WF[11]|= S3_3_2;
            break;
        case 4:
            LCD->WF[10]|= S3_4_1;
            LCD->WF[11]|= S3_4_2;
            break;
        case 5:
            LCD->WF[10]|= S3_5_1;
            LCD->WF[11]|= S3_5_2;
            break;
        case 6:
            LCD->WF[10]|= S3_6_1;
            LCD->WF[11]|= S3_6_2;
            break;
        case 7:
            LCD->WF[10]|= S3_7_1;
            break;
        case 8:
            LCD->WF[10]|= S3_8_1;
            LCD->WF[11]|= S3_8_2;
            break;
        case 9:
            LCD->WF[10]|= S3_9_1;
            LCD->WF[11]|= S3_9_2;
            break;
        default:
            LCD->WF[10]|= DP2;
            break;
    }
}

/**
*\brief LCD第四位亮数字
*
*\param[in]     要显示的数字0～9
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_4_ON(uint_8 x)
{
    LCD->WF[11]&= ~(S2_8_1+S2_8_2);
    
    switch(x)
    {
        case 0:
            LCD->WF[11]|= (S4_0_1+S4_0_2);
            break;
        case 1:
            LCD->WF[11]|=(S4_1_1);
            break;
        case 2:
            LCD->WF[11]|=(S4_2_1+S4_2_2);
            break;
        case 3:
            LCD->WF[11]|=(S4_3_1+S4_3_2);
            break;
        case 4:
            LCD->WF[11]|=(S4_4_1+S4_4_2);
            break;
        case 5:
            LCD->WF[11]|=(S4_5_1+S4_5_2);
            break;
        case 6:
            LCD->WF[11]|=(S4_6_1+S4_6_2);
            break;
        case 7:
            LCD->WF[11]|=(S4_7_1);
            break;
        case 8:
            LCD->WF[11]|=(S4_8_1+S4_8_2);
            break;
        case 9:
            LCD->WF[11]|=(S4_9_1+S4_9_2);
            break;
        default:
            LCD->WF[11]|= DP3;
            break;
    }
}

/**
*\brief LCD显示数字
*
*\param[in]     要显示的数字0～9999
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_ShowNum(uint16_t x)
{
    uint_8 th,h,t,b;            /*th千位，h百位，t十位，b个位*/
    
    SLCD_Num_OFF();

    if( (x>= 1)&&(x<10000))
    {
        th = x/1000;
        x  = x%1000;
        h  = x/100;
        x  = x%100;
        t  = x/10;
        x  = x%10;
        b  = x;

        if(th != 0)
        {
            SLCD_4_ON(th);
        }

        if(th != 0)
        {
            if(h >= 1)
            {
                SLCD_3_ON(h);
            }
        }
        else
        {
            if(h != 0)
            {
                SLCD_3_ON(h);
            }
        }

        if( h != 0)
        {
            if(t >= 1)
            {
                SLCD_2_ON(t);
            }
        }
        else
        {
            if(t != 0)
            {
                SLCD_2_ON(t);
            }
        }

        if(1)
        {
            SLCD_1_ON(b);
        }
    }
    else
    {
        LCD->WF[6] |= DP0;
        LCD->WF[10]|= (DP1+DP2);
        LCD->WF[11]|= DP3;
    }

}

/**
*\brief LCD设置灯亮
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
void SLCD_Set_ON()
{
    LCD->WF[3]|= T3;
}

/**
*\brief LCD身高设置灯亮
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
void SLCD_Height_ON()
{
    LCD->WF[3]|= T2;
}

/**
*\brief LCD体重设置灯亮
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
void SLCD_Weight_ON()
{
    LCD->WF[3]|= T1;
}

/**
*\brief LCD步长设置灯亮
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
void SLCD_Step_ON()
{
    LCD->WF[3]|= T0;
}

/**
*\brief LCD步数设置灯亮
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
void SLCD_StepCount_ON()
{
    LCD->WF[3]|= T15;
}

/**
*\brief LCD距离灯亮
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
void SLCD_Distance_ON()
{
    LCD->WF[3]|= T14;
}

/**
*\brief LCD时间灯亮
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
void SLCD_Time_ON()
{
    LCD->WF[3]|= T13;
}

/**
*\brief LCD消耗卡路里灯亮
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
void SLCD_Kcal_ON()
{
    LCD->WF[3]|= T12;
}

/**
*\brief LCD单次计步灯亮
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
void SLCD_Once_ON(void)
{
    LCD->WF[3]|= T8;
}

/**
*\brief LCD昨天步数灯亮
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
void SLCD_Day1_ON()
{
    LCD->WF[3]|= T9;
}

/**
*\brief LCD前天步数灯亮
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
void SLCD_Day2_ON()
{
    LCD->WF[3]|= T10;
}

/**
*\brief LCD大前天步数灯亮
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
void SLCD_Day3_ON()
{
    LCD->WF[3]|= T11;
}

/**
*\brief LCD前三天统计灯亮
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
void SLCD_DayAll_ON()
{
    LCD->WF[3]|= T11;
}

/**
*\brief LCD湿度灯亮
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
void SLCD_Humidity_ON()
{
    LCD->WF[3]|= T7;
}

/**
*\brief LCD温度灯亮
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
void SLCD_Temperature_ON()
{
    LCD->WF[3]|= T6;
}

/**
*\brief LCD记步灯亮
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
void SLCD_StepDo_ON()
{
    LCD->WF[3]|= T5;
}

/**
*\brief LCD时钟灯亮
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
void SLCD_Clock_ON()
{
    LCD->WF[3]|= T4;
    LCD->WF[10]|= DP2;
}

/**
*\brief LCD设置灯关
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
void SLCD_Set_OFF()
{
    LCD->WF[3]&= ~T3;
}

/**
*\brief LCD身高设置灯关
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
void SLCD_Height_OFF()
{
    LCD->WF[3]&= ~T2;
}

/**
*\brief LCD体重设置灯关
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
void SLCD_Weight_OFF()
{
    LCD->WF[3]&= ~T1;
}

/**
*\brief LCD步长设置灯关
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
void SLCD_Step_OFF()
{
    LCD->WF[3]&= ~T0;
}

/**
*\brief LCD步数设置灯关
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
void SLCD_StepCount_OFF()
{
    LCD->WF[3]&= ~T15;
}

/**
*\brief LCD距离灯关
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
void SLCD_Distance_OFF()
{
    LCD->WF[3]&= ~T14;
}

/**
*\brief LCD时间灯关
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
void SLCD_Time_OFF()
{
    LCD->WF[3]&= ~T13;
}

/**
*\brief LCD消耗卡路里灯关
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
void SLCD_Kcal_OFF()
{
    LCD->WF[3]&= ~T12;
}

/**
*\brief LCD昨天步数灯关
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
void SLCD_Day1_OFF()
{
    LCD->WF[3]&= ~T8;
}

/**
*\brief LCD前天步数灯关
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
void SLCD_Day2_OFF()
{
    LCD->WF[3]&= ~T9;
}

/**
*\brief LCD大前天步数灯关
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
void SLCD_Day3_OFF()
{
    LCD->WF[3]&= ~T10;
}

/**
*\brief LCD前三天统计灯关
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
void SLCD_DayAll_OFF()
{
    LCD->WF[3]&= ~T11;
}

/**
*\brief LCD湿度灯关
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
void SLCD_Humidity_OFF()
{
    LCD->WF[3]&= ~T7;
}

/**
*\brief LCD温度灯关
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
void SLCD_Temperature_OFF()
{
    LCD->WF[3]&= ~T6;
}

/**
*\brief LCD记步灯关
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
void SLCD_StepDo_OFF()
{
    LCD->WF[3]&= ~T5;
}

/**
*\brief LCD时钟灯关
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
void SLCD_Clock_OFF()
{
    LCD->WF[3]&= ~T4;
    LCD->WF[10]&= ~DP2;
}

/**
*\brief 选择功能灯亮
*
*\param[in]     想要亮的功能等
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_Select_Light_ON(int x)
{
    switch(x)
    {
        case 0:
           SLCD_Set_ON();                /*LCD设置灯亮      */
            break;
        case 1:
           SLCD_Height_ON( );            /*LCD身高设置灯亮  */
            break;
        case 2:
           SLCD_Weight_ON( );            /*LCD体重设置灯亮  */
            break;
        case 3:
           SLCD_Step_ON( );              /*LCD步长设置灯亮  */
            break;
        case 4:
           SLCD_StepCount_ON( );         /*LCD步数设置灯亮  */
            break;
        case 5:
           SLCD_Distance_ON( );          /*LCD距离灯亮      */
            break;
        case 6:
           SLCD_Time_ON( );              /*LCD时间灯亮      */
            break;
        case 7:
           SLCD_Kcal_ON( );              /*LCD消耗卡路里灯亮*/
            break;
        case 8:
           SLCD_Day1_ON( );              /*LCD昨天步数灯亮  */
            break;
        case 9:
           SLCD_Day2_ON( );              /*LCD前天步数灯亮  */
            break;
        case 10:
           SLCD_Day3_ON( );              /*LCD大前天步数灯亮*/
            break;
        case 11:
           SLCD_DayAll_ON( );            /*LCD前三天统计灯亮*/
            break;
        case 12:
           SLCD_Humidity_ON( );          /*LCD湿度灯亮      */
            break;
        case 13:
           SLCD_Temperature_ON( );       /*LCD温度灯亮      */
            break;
        case 14:
           SLCD_StepDo_ON( );            /*LCD记步灯亮      */
            break;
        case 15:
           SLCD_Clock_ON( );             /*LCD时钟灯亮      */
            break;
        default:
           LCD->WF[11]|= (DP3+DP1+DP0);
            break;
    }
}

/**
*\brief 选择功能灯关
*
*\param[in]     想要关的功能灯
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_Select_Light_OFF(int x)
{
    switch(x)
    {
        case 0:
           SLCD_Set_OFF();               /*LCD设置灯关     */
            break;
        case 1:
           SLCD_Height_OFF( );           /*LCD身高设置灯关 */
            break;
        case 2:
           SLCD_Weight_OFF( );           /*LCD体重设置灯关 */
            break;
        case 3:
           SLCD_Step_OFF( );             /*LCD步长设置灯关 */
            break;
        case 4:
           SLCD_StepCount_OFF( );        /*LCD步数设置灯关 */
            break;
        case 5:
           SLCD_Distance_OFF( );         /*LCD距离灯关     */
            break;
        case 6:
           SLCD_Time_OFF( );             /*LCD时间灯关     */
            break;
        case 7:
           SLCD_Kcal_OFF( );             /*LCD消耗卡路里灯关*/
            break;
        case 8:
           SLCD_Day1_OFF( );             /*LCD昨天步数灯关  */
            break;
        case 9:
           SLCD_Day2_OFF( );             /*LCD前天步数灯关  */
            break;
        case 10:
           SLCD_Day3_OFF( );             /*LCD大前天步数灯关*/
            break;
        case 11:
           SLCD_DayAll_OFF( );           /*LCD前三天统计灯关*/
            break;
        case 12:
           SLCD_Humidity_OFF( );         /*LCD湿度灯关      */
            break;
        case 13:
           SLCD_Temperature_OFF( );      /*LCD温度灯关      */
            break;
        case 14:
           SLCD_StepDo_OFF( );           /*LCD记步灯关      */
            break;
        case 15:
           SLCD_Clock_OFF( );            /*LCD时钟灯关      */
            break;
        default:
           LCD->WF[11]|= (DP3+DP1+DP0);
            break;
       }
}

/**
*\brief LCD第一二位亮数字
*
*\param[in]     想要显示的数字0～99
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_12_ON(int x)
{
    SLCD_1_ON((x % 10));               /*LCD第一位亮个位*/
    SLCD_2_ON((x / 10));               /*LCD第二位亮十位*/
}

/**
*\brief LCD第三四位亮数字
*
*\param[in]     想要显示的数字0～99
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_34_ON(int x)
{
    SLCD_3_ON((x % 10));               /*LCD第三位亮个位*/
    if((x / 10) != 0)
    {
        SLCD_4_ON((x / 10));           /*LCD第四位亮十位*/
    }
}

/**
*\brief LCD第二三四位亮数字
*
*\param[in]     想要显示的数字0～999
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_234_ON(int x)
{
    SLCD_2_ON((x % 10));              /*个位*/
    if((x / 10) != 0)
    {
        SLCD_3_ON(((x / 10) % 10));   /*十位*/
        if((x / 100) != 0)
        {
            SLCD_4_ON((x / 100));
        }
    }
}

/**
*\brief LCD显示浮点型数字
*
*\param[in]     想要显示的数字0.000～9999
*\param[out]    none
*\param[in,out] none
*
*\retval none
*\retval none
*
*\note  none
*/
void SLCD_ShowNum_F(float x)
{
    if(x >= 1000)                     /*无小数位  */
    {
        uint_16 y = x;
        SLCD_ShowNum(y);
    }
    else if(x >= 100 && x < 1000)    /*一位小数位 */
    {
        uint_16 y = x;               /*整数部分   */
        SLCD_234_ON(y);
        LCD->WF[10] |= DP1;
        x *= 10;
        y = x;
        SLCD_1_ON((y % 10));         /*小数位     */
    }
    else if(x >= 10 && x < 100)      /*两位小数位 */
    {
        uint_16 y = x;               /*整数部分   */
        SLCD_34_ON(y);
        LCD->WF[10]|= DP2;
        x *=100;
        y = x;
        SLCD_1_ON((y % 10));         /*第二位小数位*/
        y /= 10;
        SLCD_2_ON((y % 10));         /*第一位小数位*/
    }
    else if(x > 0 && x < 10)         /*三位小数    */
    {
        uint_16 y = x;               /*整数部分    */
        SLCD_4_ON(y);
        LCD->WF[11]|= DP3;
        x *=1000;
        y = x;
        SLCD_1_ON((y % 10));         /*第三位小数位*/
        y /= 10;
        SLCD_2_ON((y % 10));         /*第二位小数位*/
        y /= 10;
        SLCD_3_ON((y % 10));         /*第一位小数位*/
    }
    else
    {
        SLCD_1_ON(0);
    }
}

/* end of file */

