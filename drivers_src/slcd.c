/**
  ******************************************************************************
  * @file    slcd.c
  * @brief   ����KL46�ļƲ������-����LCDԴ����
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note      
  ******************************************************************************
  */

#include "slcd.h"

/**
*\brief LCD��ʼ�������ж�ȫ��
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
    SIM_SCGC5|=SIM_SCGC5_SLCD_MASK;         /*����ʱ��                  */

    LCD->GCR|=LCD_GCR_CPSEL_MASK;
    LCD->GCR|=LCD_GCR_DUTY(3);              /*����ռ�ձ�                */
    LCD->GCR|=LCD_GCR_SOURCE_MASK;          /*selectaltclockIRC         */
    LCD->GCR|=LCD_GCR_LCDSTP_MASK;          /*�͹��Ĺر�                */
    LCD->GCR|=LCD_GCR_LCDEN_MASK;           /*EnableLCD                 */
    LCD->PEN[0]=0x08F0F000;                 /*����0-31λ��ӦLCD����ʹ�� */
    LCD->BPEN[0]=0x00F00000;                /*����0-31λCOM��ʹ��       */
    LCD->PEN[1]=0x00007F00;                 /*����32-63λ��ӦLCD����ʹ��*/

    LCD->WF[3] =0x0F0F0F0F;                 /*��ӦLCD���Ų���ʹ��       */
    LCD->WF[5] =0x08040201;
    LCD->WF[6] =0x0F000000;
    LCD->WF[10]=0x0F0F0F0F;
    LCD->WF[11]=0x000F0F0F;
}

/**
*\brief LCDȫ��
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
    LCD->WF[3] =0x0F0F0F0F;                 /*��ӦLCD���Ų���ʹ��*/
    LCD->WF[6] =0x0F000000;
    LCD->WF[10]=0x0F0F0F0F;
    LCD->WF[11]=0x000F0F0F;
}

/**
*\brief LCDȫ��
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
    LCD->WF[3] =0x00000000;                 /*��ӦLCD���Ų��ν���*/
    LCD->WF[6] =0x00000000;
    LCD->WF[10]=0x00000000;
    LCD->WF[11]=0x00000000;
}

/**
*\brief LCD����ȫ��
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
*\brief LCD����ȫ��
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
*\brief ָʾ��ȫ��
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
*\brief LCD��һλ������
*
*\param[in]     Ҫ��ʾ������0��9
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
*\brief LCD�ڶ�λ������
*
*\param[in]     Ҫ��ʾ������0��9
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
*\brief LCD����λ������
*
*\param[in]     Ҫ��ʾ������0��9
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
*\brief LCD����λ������
*
*\param[in]     Ҫ��ʾ������0��9
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
*\brief LCD��ʾ����
*
*\param[in]     Ҫ��ʾ������0��9999
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
    uint_8 th,h,t,b;            /*thǧλ��h��λ��tʮλ��b��λ*/
    
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
*\brief LCD���õ���
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
*\brief LCD������õ���
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
*\brief LCD�������õ���
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
*\brief LCD�������õ���
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
*\brief LCD�������õ���
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
*\brief LCD�������
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
*\brief LCDʱ�����
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
*\brief LCD���Ŀ�·�����
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
*\brief LCD���μƲ�����
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
*\brief LCD���첽������
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
*\brief LCDǰ�첽������
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
*\brief LCD��ǰ�첽������
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
*\brief LCDǰ����ͳ�Ƶ���
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
*\brief LCDʪ�ȵ���
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
*\brief LCD�¶ȵ���
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
*\brief LCD�ǲ�����
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
*\brief LCDʱ�ӵ���
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
*\brief LCD���õƹ�
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
*\brief LCD������õƹ�
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
*\brief LCD�������õƹ�
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
*\brief LCD�������õƹ�
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
*\brief LCD�������õƹ�
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
*\brief LCD����ƹ�
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
*\brief LCDʱ��ƹ�
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
*\brief LCD���Ŀ�·��ƹ�
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
*\brief LCD���첽���ƹ�
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
*\brief LCDǰ�첽���ƹ�
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
*\brief LCD��ǰ�첽���ƹ�
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
*\brief LCDǰ����ͳ�Ƶƹ�
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
*\brief LCDʪ�ȵƹ�
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
*\brief LCD�¶ȵƹ�
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
*\brief LCD�ǲ��ƹ�
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
*\brief LCDʱ�ӵƹ�
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
*\brief ѡ���ܵ���
*
*\param[in]     ��Ҫ���Ĺ��ܵ�
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
           SLCD_Set_ON();                /*LCD���õ���      */
            break;
        case 1:
           SLCD_Height_ON( );            /*LCD������õ���  */
            break;
        case 2:
           SLCD_Weight_ON( );            /*LCD�������õ���  */
            break;
        case 3:
           SLCD_Step_ON( );              /*LCD�������õ���  */
            break;
        case 4:
           SLCD_StepCount_ON( );         /*LCD�������õ���  */
            break;
        case 5:
           SLCD_Distance_ON( );          /*LCD�������      */
            break;
        case 6:
           SLCD_Time_ON( );              /*LCDʱ�����      */
            break;
        case 7:
           SLCD_Kcal_ON( );              /*LCD���Ŀ�·�����*/
            break;
        case 8:
           SLCD_Day1_ON( );              /*LCD���첽������  */
            break;
        case 9:
           SLCD_Day2_ON( );              /*LCDǰ�첽������  */
            break;
        case 10:
           SLCD_Day3_ON( );              /*LCD��ǰ�첽������*/
            break;
        case 11:
           SLCD_DayAll_ON( );            /*LCDǰ����ͳ�Ƶ���*/
            break;
        case 12:
           SLCD_Humidity_ON( );          /*LCDʪ�ȵ���      */
            break;
        case 13:
           SLCD_Temperature_ON( );       /*LCD�¶ȵ���      */
            break;
        case 14:
           SLCD_StepDo_ON( );            /*LCD�ǲ�����      */
            break;
        case 15:
           SLCD_Clock_ON( );             /*LCDʱ�ӵ���      */
            break;
        default:
           LCD->WF[11]|= (DP3+DP1+DP0);
            break;
    }
}

/**
*\brief ѡ���ܵƹ�
*
*\param[in]     ��Ҫ�صĹ��ܵ�
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
           SLCD_Set_OFF();               /*LCD���õƹ�     */
            break;
        case 1:
           SLCD_Height_OFF( );           /*LCD������õƹ� */
            break;
        case 2:
           SLCD_Weight_OFF( );           /*LCD�������õƹ� */
            break;
        case 3:
           SLCD_Step_OFF( );             /*LCD�������õƹ� */
            break;
        case 4:
           SLCD_StepCount_OFF( );        /*LCD�������õƹ� */
            break;
        case 5:
           SLCD_Distance_OFF( );         /*LCD����ƹ�     */
            break;
        case 6:
           SLCD_Time_OFF( );             /*LCDʱ��ƹ�     */
            break;
        case 7:
           SLCD_Kcal_OFF( );             /*LCD���Ŀ�·��ƹ�*/
            break;
        case 8:
           SLCD_Day1_OFF( );             /*LCD���첽���ƹ�  */
            break;
        case 9:
           SLCD_Day2_OFF( );             /*LCDǰ�첽���ƹ�  */
            break;
        case 10:
           SLCD_Day3_OFF( );             /*LCD��ǰ�첽���ƹ�*/
            break;
        case 11:
           SLCD_DayAll_OFF( );           /*LCDǰ����ͳ�Ƶƹ�*/
            break;
        case 12:
           SLCD_Humidity_OFF( );         /*LCDʪ�ȵƹ�      */
            break;
        case 13:
           SLCD_Temperature_OFF( );      /*LCD�¶ȵƹ�      */
            break;
        case 14:
           SLCD_StepDo_OFF( );           /*LCD�ǲ��ƹ�      */
            break;
        case 15:
           SLCD_Clock_OFF( );            /*LCDʱ�ӵƹ�      */
            break;
        default:
           LCD->WF[11]|= (DP3+DP1+DP0);
            break;
       }
}

/**
*\brief LCD��һ��λ������
*
*\param[in]     ��Ҫ��ʾ������0��99
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
    SLCD_1_ON((x % 10));               /*LCD��һλ����λ*/
    SLCD_2_ON((x / 10));               /*LCD�ڶ�λ��ʮλ*/
}

/**
*\brief LCD������λ������
*
*\param[in]     ��Ҫ��ʾ������0��99
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
    SLCD_3_ON((x % 10));               /*LCD����λ����λ*/
    if((x / 10) != 0)
    {
        SLCD_4_ON((x / 10));           /*LCD����λ��ʮλ*/
    }
}

/**
*\brief LCD�ڶ�����λ������
*
*\param[in]     ��Ҫ��ʾ������0��999
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
    SLCD_2_ON((x % 10));              /*��λ*/
    if((x / 10) != 0)
    {
        SLCD_3_ON(((x / 10) % 10));   /*ʮλ*/
        if((x / 100) != 0)
        {
            SLCD_4_ON((x / 100));
        }
    }
}

/**
*\brief LCD��ʾ����������
*
*\param[in]     ��Ҫ��ʾ������0.000��9999
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
    if(x >= 1000)                     /*��С��λ  */
    {
        uint_16 y = x;
        SLCD_ShowNum(y);
    }
    else if(x >= 100 && x < 1000)    /*һλС��λ */
    {
        uint_16 y = x;               /*��������   */
        SLCD_234_ON(y);
        LCD->WF[10] |= DP1;
        x *= 10;
        y = x;
        SLCD_1_ON((y % 10));         /*С��λ     */
    }
    else if(x >= 10 && x < 100)      /*��λС��λ */
    {
        uint_16 y = x;               /*��������   */
        SLCD_34_ON(y);
        LCD->WF[10]|= DP2;
        x *=100;
        y = x;
        SLCD_1_ON((y % 10));         /*�ڶ�λС��λ*/
        y /= 10;
        SLCD_2_ON((y % 10));         /*��һλС��λ*/
    }
    else if(x > 0 && x < 10)         /*��λС��    */
    {
        uint_16 y = x;               /*��������    */
        SLCD_4_ON(y);
        LCD->WF[11]|= DP3;
        x *=1000;
        y = x;
        SLCD_1_ON((y % 10));         /*����λС��λ*/
        y /= 10;
        SLCD_2_ON((y % 10));         /*�ڶ�λС��λ*/
        y /= 10;
        SLCD_3_ON((y % 10));         /*��һλС��λ*/
    }
    else
    {
        SLCD_1_ON(0);
    }
}

/* end of file */

