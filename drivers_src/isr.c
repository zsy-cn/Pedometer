/**
  ******************************************************************************
  * @file    isr.c
  * @brief   ����KL46�ļƲ������-isrԴ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note   
  ******************************************************************************
  */

#include "isr.h"

int16_t ucdate[3];
uint_8 i_M;
uint_8  g_time[2]={0};                     /*��¼ʱ�������,ʱ��g_time[0],�֣�g_time[1]*/
extern uint_8  g_run_mode;
extern uint_8  g_run_mode_remember;       /*��¼����ǰ��״̬                           */
extern uint_8  g_run_step_mode;           /*��¼���ռƲ����ǵ��μƲ�                   */
extern uint_8 g_temp_humi[2];             /*��¼��ʪ��                                 */
extern uint_16 g_info[4];                 /*��ߣ����أ������洢                       */
extern float g_today[4];                 /*��¼���������롣ʱ�䡣��·��               */
extern float g_day1[4];
extern float g_day2[4];
extern float g_day3[4];
extern float g_once[4];
extern uint_8  g_flag[4];                 /*flash�������                              */
extern uint_8 vlpsflag;
float   g_today_buf[4];                   /*���μƲ�ʹ��                               */

//==================�жϺ����������=========================
//MMA8652�жϷ�����
void PORTA_IRQHandler(void)
//void isr_MMA8652(void)
{
    uint_8 accel_data[192]; //
    int16_t temp;
    uint_8 int_source;
    uint_8 j,k;

    //���жϱ�־λ
    PORTA_PCR13 |= PORT_PCR_ISF_MASK;                                                        // Clear the interrupt flag

    int_source = I2C_ReadRegister(MMA8652_I2C_ADDRESS, INT_SOURCE_REG);
    if(int_source & SRC_FIFO_MASK)                                                           // FIFO�жϱ�־
    {
        I2C_ReadMultiRegisters(MMA8652_I2C_ADDRESS, OUT_X_MSB_REG, 192, accel_data); //
        k=0;
        for(i_M = 0;i_M < 32; i_M++)
        {
            for(j =0;j < 3; j++)
            {
                temp = accel_data[k] << 8;
                temp |= accel_data[k+1];
                temp = temp / 16;
                //MMA8652FCRecQ.Axis[j].Array[i_M] =temp;
                ucdate[j]=temp;
                k += 2; 
//                printf("%d\t\n",ucdate[j]);
            }
//            printf("\r\n");
             CountStep();
            
        }

            SLCD_TLight_OFF();
        switch(g_run_mode)
        {
        case NorMode_Timer:                /* ʱ����ʾ             */
            SLCD_Clock_ON();               /* LCDʱ�ӵ���    */
            SLCD_12_ON(g_time[1]);
            SLCD_34_ON(g_time[0]);
            break;
        case NorMode_Stepcount:            /* ��ʾ�ռƲ����� */
            SLCD_ShowNum(g_today[0]);
            SLCD_StepCount_ON();           /* LCD��������   */
            SLCD_StepDo_ON();              /* LCD�ǲ�����   */
            break;
        case NorMode_Temp:                 /* ��ʾ�¶�            */
            SLCD_ShowNum(g_temp_humi[1]);
            SLCD_Temperature_ON();         /* LCD�¶ȵ���   */
            break;
        case NorMode_Humi:                 /* ��ʾʪ��            */
            SLCD_ShowNum(g_temp_humi[0]);
            SLCD_Humidity_ON();            /* LCDʪ�ȵ���   */
            break;
        case NorMode_StepDistDisplay:      /* ��ʾ�ռƲ����� */
            SLCD_Distance_ON();            /* LCD�������    */
            SLCD_StepDo_ON();              /* LCD�ǲ�����    */
            SLCD_ShowNum_F(g_today[1]);
            break;
        case NorMode_StepTimeDisplay:      /* ��ʾ�ռƲ�ʱ�� */
            SLCD_Time_ON();                /* LCDʱ�����    */
            SLCD_StepDo_ON();              /* LCD�ǲ�����    */
            SLCD_ShowNum(g_today[2]);
            break;
        case NorMode_StepEngDisplay:       /* ��ʾ�ռƲ����Ŀ�·�� */
             SLCD_Kcal_ON();               /* LCD���Ŀ�·�����    */
             SLCD_StepDo_ON();             /* LCD�ǲ�����                */
             SLCD_ShowNum_F(g_today[3]);
            break;
        case NorMode_Lastday:              /* ��ʾ�������ݲ���         */
            SLCD_Day1_ON();                /* LCD�������ݵ���        */
            SLCD_StepCount_ON();           /* LCD��������                */
            SLCD_ShowNum(g_day1[0]);
            break;
        case NorMode_Lastday_StepDist:     /* ��ʾ�������ݾ���         */
            SLCD_Day1_ON();                /* LCD�������ݵ���        */
            SLCD_Distance_ON();            /* LCD�������                */
            SLCD_ShowNum_F(g_day1[1]);
            break;
        case NorMode_Lastday_StepTime:     /* ��ʾ��������ʱ��         */
            SLCD_Day1_ON();                /* LCD�������ݵ���        */
            SLCD_Time_ON();                /* LCDʱ�����                */
            SLCD_ShowNum(g_day1[2]);
            break;
        case NorMode_Lastday_StepEng:     /* ��ʾ�����������Ŀ�·��     */
            SLCD_Day1_ON();               /* LCD�������ݵ���                */
            SLCD_Kcal_ON();               /* LCD���Ŀ�·�����            */
            SLCD_ShowNum_F(g_day1[3]);
            break;
        case NorMode_BLastday:            /* ��ʾǰ�����ݲ���              */
            SLCD_Day2_ON();               /* LCDǰ�����ݵ���             */
            SLCD_StepCount_ON();          /* LCD��������                     */
            SLCD_ShowNum(g_day2[0]);
            break;
        case NorMode_BLastday_StepDist:   /* ��ʾǰ�����ݾ���              */
            SLCD_Day2_ON();               /* LCDǰ�����ݵ���             */
            SLCD_Distance_ON();           /* LCD�������                     */
            SLCD_ShowNum_F(g_day2[1]);
            break;
        case NorMode_BLastday_StepTime:   /* ��ʾǰ������ʱ��                   */
            SLCD_Day2_ON();               /* LCDǰ�����ݵ���                  */
            SLCD_Time_ON();               /* LCDʱ�����                          */
            SLCD_ShowNum(g_day2[2]);
            break;
        case NorMode_BLastday_StepEng:    /* ��ʾǰ���������Ŀ�·��       */
            SLCD_Day2_ON();               /* LCDǰ�����ݵ���                   */
            SLCD_Kcal_ON();               /* LCD���Ŀ�·�����               */
            SLCD_ShowNum_F(g_day2[3]);
            break;
        case NorMode_BBLastday:           /* ��ʾ��ǰ�����ݲ���                */
            SLCD_Day3_ON();               /* LCD��ǰ�����ݵ���               */
            SLCD_StepCount_ON();          /* LCD��������                           */
            SLCD_ShowNum(g_day3[0]);
            break;
        case NorMode_BBLastday_StepDist:  /* ��ʾ��ǰ�����ݾ���                 */
            SLCD_Day3_ON();               /* LCD��ǰ�����ݵ���                */
            SLCD_Distance_ON();           /* LCD�������                            */
            SLCD_ShowNum_F(g_day3[1]);
            break;
        case NorMode_BBLastday_StepTime:  /* ��ʾ��ǰ������ʱ��                 */
            SLCD_Day3_ON();               /* LCD��ǰ�����ݵ���                */
            SLCD_Time_ON();               /* LCDʱ�����                            */
            SLCD_ShowNum(g_day3[2]);
            break;
        case NorMode_BBLastday_StepEng:   /* ��ʾ��ǰ���������Ŀ�·��     */
            SLCD_Day3_ON();               /* LCD��ǰ�����ݵ���                */
            SLCD_Kcal_ON();               /* LCD���Ŀ�·�����                */
            SLCD_ShowNum_F(g_day3[3]);
            break;
        case NorMode_OnceStepcount:       /* ��ʾ���μƲ�����                     */
            SLCD_Once_ON();               /* LCD���μƲ�����                    */
            SLCD_StepCount_ON();          /* LCD��������                            */
            SLCD_ShowNum((g_today[0] - g_today_buf[0]));
            break;
        case NorMode_OnceStepDist:        /* ��ʾ���μƲ�����                     */
            SLCD_Once_ON();               /* LCD���μƲ�����                    */
            SLCD_Distance_ON();           /* LCD�������                            */
            SLCD_ShowNum_F((g_today[1] - g_today_buf[1]));
            break;
        case NorMode_OnceStepTime:        /* ��ʾ���μƲ�ʱ��                     */
            SLCD_Once_ON();               /* LCD���μƲ�����                    */
            SLCD_Time_ON();               /* LCDʱ�����                            */
            SLCD_ShowNum((g_today[2] - g_today_buf[2]));
            break;
        case NorMode_OnceStepEng:         /* ��ʾ���μƲ����Ŀ�·��         */
            SLCD_Once_ON();               /* LCD���μƲ�����                    */
            SLCD_Kcal_ON();               /* LCD���Ŀ�·�����                */
            SLCD_ShowNum_F((g_today[3] - g_today_buf[3]));
            break;
        case SetMode_Height:              /* ���������ʾ                              */
            SLCD_Set_ON();                /* LCD���õ���                             */
            SLCD_Height_ON();             /* LCD��ߵ���                             */
            SLCD_ShowNum(g_info[0]);
            break;
        case SetMode_Weight:              /* ����������ʾ                              */
            SLCD_Set_ON();                /* LCD���õ���                             */
            SLCD_Weight_ON();             /* LCD���ص���                             */
            SLCD_ShowNum(g_info[1]);
            break;
        case SetMode_Steplength:          /* ����������ʾ                              */
            SLCD_Set_ON();                /* LCD���õ���                             */
            SLCD_Step_ON();               /* LCD��������                             */
            SLCD_ShowNum(g_info[2]);
            break;
        case SetMode_Timerhour:           /* ʱ����������ʾ                          */
            SLCD_Clock_ON();              /* LCDʱ�ӵ���                             */
            SLCD_Set_ON();                /* LCD���õ���                             */
            SLCD_34_ON(g_time[0]);
            break;
        case SetMode_Timerminu:           /* ������������ʾ                          */
            SLCD_Clock_ON();              /* LCDʱ�ӵ���                             */
            SLCD_Set_ON();                /* LCD���õ���                             */
            SLCD_12_ON(g_time[1]);
            break;
        default:
            break;
        }
    I2C_ReadRegister(MMA8652_I2C_ADDRESS, F_STATUS_REG);                                   // Clear the interrupt flag
    }
}




/**
 * @brief  �жϴ��������
 * @param  LPTimer_IRQHandler :LPTM�жϴ�����
 * @note �����ڲ������ж��¼�����
 */
void LPTimer_IRQHandler(void)
{
    LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;
    minu_add1(g_time);
    step_data_process(g_today, g_info);              //ÿ���Ӵ���һ������
    if((g_time[1] % 10) == 0)                        //ÿʮ���Ӷ�ȡһ����ʪ��
    {
        DHT_ReadTempHumi();
    }
    if(g_time[1] == 0)
    {
        data_storage_today(g_today);
    }
    if(g_time[1] == 0 && g_time[0] == 0)
    {
        data_storage_days(g_today);
    }

    vlpsflag=1;

    
}



//�����ж�
void PORTC_PORTD_IRQHandler(void)
{
DelayMs(50);                            /* ��ʱ50����                               */
    if(PORTC_ISFR & 0x0040)                 /* PTC6�ж�,key_plus  */
    {
        switch(g_run_mode)
        {
        /* ʱ�ӡ��¶ȡ�ʪ����ʾʱ����Plus����Ч */
        case NorMode_Timer:
        case NorMode_Temp:
        case NorMode_Humi:
            break;
        /* �Ʋ�ʱ����PLUS������->��·��->ʱ��->���룬ѭ�� */
        case NorMode_Stepcount:
            g_run_mode = NorMode_StepEngDisplay;
            break;
        case NorMode_StepDistDisplay:
            g_run_mode = NorMode_Stepcount;
            break;
        case NorMode_StepTimeDisplay:
            g_run_mode = NorMode_StepDistDisplay;
            break;
        case NorMode_StepEngDisplay:
            g_run_mode = NorMode_StepTimeDisplay;
            break;
        /* ���μƲ�ʱ����Plus������->��·��->ʱ��->���룬ѭ�� */
        case NorMode_OnceStepcount:
            g_run_mode = NorMode_OnceStepEng;
            break;
        case NorMode_OnceStepDist:
            g_run_mode = NorMode_OnceStepcount;
            break;
        case NorMode_OnceStepTime:
            g_run_mode = NorMode_OnceStepDist;
            break;
        case NorMode_OnceStepEng:
            g_run_mode = NorMode_OnceStepTime;
            break;
        /* ���졢ǰ�졢��ǰ�졢ǰ����������ʾʱ����Plus������->��·��->ʱ��->���룬ѭ�� */
        case NorMode_Lastday:
            g_run_mode = NorMode_Lastday_StepEng;
            break;
        case NorMode_Lastday_StepDist:
            g_run_mode = NorMode_Lastday;
            break;
        case NorMode_Lastday_StepTime:
            g_run_mode = NorMode_Lastday_StepDist;
            break;
        case NorMode_Lastday_StepEng:
            g_run_mode = NorMode_Lastday_StepTime;
            break;
        case NorMode_BLastday:
            g_run_mode = NorMode_BLastday_StepEng;
            break;
        case NorMode_BLastday_StepDist:
            g_run_mode = NorMode_BLastday;
            break;
        case NorMode_BLastday_StepTime:
            g_run_mode = NorMode_BLastday_StepDist;
            break;
        case NorMode_BLastday_StepEng:
            g_run_mode = NorMode_BLastday_StepTime;
            break;
        case NorMode_BBLastday:
            g_run_mode = NorMode_BBLastday_StepEng;
            break;
        case NorMode_BBLastday_StepDist:
            g_run_mode = NorMode_BBLastday;
            break;
        case NorMode_BBLastday_StepTime:
            g_run_mode = NorMode_BBLastday_StepDist;
            break;
        case NorMode_BBLastday_StepEng:
            g_run_mode = NorMode_BBLastday_StepTime;
            break;
        /* �������ʱ����Plus����߼�1 */
        case SetMode_Height:
            g_info[0] ++;
            if(g_info[0] == 9999)
            {
                g_info[0] = 0;
            }
            break;
        /* ��������ʱ����Plus�����ؼ�1 */
        case SetMode_Weight:
            g_info[1] ++;
            if(g_info[1] == 9999)
            {
                g_info[1] = 0;
            }
            break;
        /* ��������ʱ����Plus��������1 */
        case SetMode_Steplength:
            g_info[2] ++;
            if(g_info[2] == 9999)
            {
                g_info[2] = 0;
            }
            break;
        /* ʱ����ʱ����Plus��ʱ��1 */
        case SetMode_Timerhour:
            g_time[0] ++;
            if(g_time[0] == 24)
            {
                g_time[0] = 0;
            }
            break;
        /* ������ʱ����Plus���ּ�1 */
        case SetMode_Timerminu:
            g_time[1] ++;
            if(g_time[1] == 60)
            {
                g_time[1] = 0;
            }
            break;
        default:
            break;
        }

        PORTC_PCR6 |= PORT_PCR_ISF_MASK;        /* ���жϱ�־λ                             */
    }
    if(PORTC_ISFR & 0x0020)                     /* PTC5�ж�,key_mode  */
    {
        DelayMs(100);                           /* ��ʱ50����                               */
         if(GPIO_ReadBit(HW_GPIOC, 5) == 0)               /* key_mode����                     */
        {
            switch(g_run_mode)
            {
            /* �Ʋ���ʱ�ӣ��¶ȡ�ʪ�ȡ��������ݡ�ǰ�����ݡ���ǰ�����ݡ����μƲ��У�����Mode����������ģʽ */
            case NorMode_Stepcount:
            case NorMode_StepDistDisplay:
            case NorMode_StepTimeDisplay:
            case NorMode_StepEngDisplay:
            case NorMode_Timer:
            case NorMode_Temp:
            case NorMode_Humi:
            case NorMode_OnceStepcount:
            case NorMode_OnceStepDist:
            case NorMode_OnceStepTime:
            case NorMode_OnceStepEng:
            case NorMode_Lastday:
            case NorMode_Lastday_StepDist:
            case NorMode_Lastday_StepTime:
            case NorMode_Lastday_StepEng:
            case NorMode_BLastday:
            case NorMode_BLastday_StepDist:
            case NorMode_BLastday_StepTime:
            case NorMode_BLastday_StepEng:
            case NorMode_BBLastday:
            case NorMode_BBLastday_StepDist:
            case NorMode_BBLastday_StepTime:
            case NorMode_BBLastday_StepEng:
                g_run_mode_remember = g_run_mode;
                g_run_mode = SetMode_Height;
                break;
            /* ��������ģʽ�г���Mode���ж����õ���ߡ����ء������Ƿ���Ч����Ч����SetMode_Height����Ч���˳�����ģʽ����ʼ�Ʋ���������֮ǰ��ģʽ */
            case SetMode_Height:
            case SetMode_Weight:
            case SetMode_Steplength:
            case SetMode_Timerhour:
            case SetMode_Timerminu:
                if(g_info[0] == 0)
                {
                    g_run_mode = SetMode_Height;
                }
                else if(g_info[1] == 0)
                {
                    g_run_mode = SetMode_Weight;
                }
                else if(g_info[2] == 0)
                {
                    g_run_mode = SetMode_Steplength;
                }
                else
                {
                    data_storage_info(g_info);            /* �洢��ߡ����ء�������Ϣ */
                    g_run_mode = g_run_mode_remember;
                }
                break;
            default:
                break;
            }
        }
        else            /* key_mode�̰�*/
        {
            switch(g_run_mode)
            {
            /* ʱ����ʾ�ж̰�Mode������Ʋ�������ʾ���� */
            case NorMode_Timer:
                g_run_mode = NorMode_Stepcount;
                break;
            /* �Ʋ��ж̰�Mode���Ʋ����жϣ������¶���ʾ */
            case NorMode_Stepcount:
                g_run_mode = NorMode_Temp;
                break;
            /* �¶���ʾʱ�̰�Mode������ʪ����ʾ */
            case NorMode_Temp:
                g_run_mode = NorMode_Humi;
                break;
            /* ʪ����ʾʱ�̰�Mode�����뵥�μƲ� */
            case NorMode_Humi:
                g_today_buf[0] = g_today[0];  /* ��¼  */
                g_today_buf[1] = g_today[1];
                g_today_buf[2] = g_today[3];
                g_today_buf[3] = g_today[3];
                g_run_mode = NorMode_OnceStepcount;
                break;
            /* �Ʋ��У���ʾ���롢ʱ�䡢��·��̰�Mode�������¶���ʾ */
            case NorMode_StepDistDisplay:
            case NorMode_StepTimeDisplay:
            case NorMode_StepEngDisplay:
                g_run_mode = NorMode_Temp;
                break;
            /* ���μƲ��У���ʾ���롢ʱ���·��̰�Mode����ȡ�������ݣ�������μƲ���Ϣ����������������ʾ */
            case NorMode_OnceStepcount:
            case NorMode_OnceStepDist:
            case NorMode_OnceStepTime:
            case NorMode_OnceStepEng:
                data_read_u8b(FLAG_SECNO, 0, 4, g_flag);
                data_read_32b(g_flag[0], 0, 4, g_day1);
                g_run_mode = NorMode_Lastday;
                break;
            /* ����������ʾ�ж̰�Mode����ȡǰ�����ݣ�����ǰ������ */
            case NorMode_Lastday:
            case NorMode_Lastday_StepDist:
            case NorMode_Lastday_StepTime:
            case NorMode_Lastday_StepEng:
                data_read_u8b(FLAG_SECNO, 0, 4, g_flag);
                data_read_32b(g_flag[1], 0, 4, g_day2);
                g_run_mode = NorMode_BLastday;
                break;
            /* ǰ��������ʾ�ж̰�Mode����ȡ��ǰ�����ݣ������ǰ������ */
            case NorMode_BLastday:
            case NorMode_BLastday_StepDist:
            case NorMode_BLastday_StepTime:
            case NorMode_BLastday_StepEng:
                data_read_u8b(FLAG_SECNO, 0, 4, g_flag);
                data_read_32b(g_flag[2], 0, 4, g_day3);
                g_run_mode = NorMode_BBLastday;
                break;
            /* ��ǰ��������ʾ�ж̰�Mode������ʱ����ʾ */
            case NorMode_BBLastday:
            case NorMode_BBLastday_StepDist:
            case NorMode_BBLastday_StepTime:
            case NorMode_BBLastday_StepEng:
                g_run_mode = NorMode_Timer;
                break;
            /* ��������ж̰�Mode�������������� */
            case SetMode_Height:
                g_run_mode = SetMode_Weight;
                break;
            /* ���������ж̰�Mode�����벽������ */
            case SetMode_Weight:
                g_run_mode = SetMode_Steplength;
                break;
            /* ���������ж̰�Mode������ʱ���� */
            case SetMode_Steplength:
                g_run_mode = SetMode_Timerhour;
                break;
            /* ʱ�����ж̰�Mode����������� */
            case SetMode_Timerhour:
                g_run_mode = SetMode_Timerminu;
                break;
            /* �������ж̰�Mode�������������*/
            case SetMode_Timerminu:
                g_run_mode = SetMode_Height;
                break;
            default:
                break;
            }
        }

        PORTC_PCR5 |= PORT_PCR_ISF_MASK;    /* ���жϱ�־λ */
    }
    if(PORTC_ISFR & 0x0010)        /* PTC4�ж�,key_minus */
    {
        DelayMs(50);               /*��ʱ50����                                  */
        switch(g_run_mode)
        {
        case NorMode_Timer:
        case NorMode_Temp:
        case NorMode_Humi:
            break;
        case NorMode_Stepcount:
            g_run_mode = NorMode_StepDistDisplay;
            break;
        case NorMode_StepDistDisplay:
            g_run_mode = NorMode_StepTimeDisplay;
            break;
        case NorMode_StepTimeDisplay:
            g_run_mode = NorMode_StepEngDisplay;
            break;
        case NorMode_StepEngDisplay:
            g_run_mode = NorMode_Stepcount;
            break;
        case NorMode_OnceStepcount:
            g_run_mode = NorMode_OnceStepDist;
            break;
        case NorMode_OnceStepDist:
            g_run_mode = NorMode_OnceStepTime;
            break;
        case NorMode_OnceStepTime:
            g_run_mode = NorMode_OnceStepEng;
            break;
        case NorMode_OnceStepEng:
            g_run_mode = NorMode_OnceStepcount;
            break;
        case NorMode_Lastday:
            g_run_mode = NorMode_Lastday_StepDist;
            break;
        case NorMode_Lastday_StepDist:
            g_run_mode = NorMode_Lastday_StepTime;
            break;
        case NorMode_Lastday_StepTime:
            g_run_mode = NorMode_Lastday_StepEng;
            break;
        case NorMode_Lastday_StepEng:
            g_run_mode = NorMode_Lastday;
            break;
        case NorMode_BLastday:
            g_run_mode = NorMode_BLastday_StepDist;
            break;
        case NorMode_BLastday_StepDist:
            g_run_mode = NorMode_BLastday_StepTime;
            break;
        case NorMode_BLastday_StepTime:
            g_run_mode = NorMode_BLastday_StepEng;
            break;
        case NorMode_BLastday_StepEng:
            g_run_mode = NorMode_BLastday;
            break;
        case NorMode_BBLastday:
            g_run_mode = NorMode_BBLastday_StepDist;
            break;
        case NorMode_BBLastday_StepDist:
            g_run_mode = NorMode_BBLastday_StepTime;
            break;
        case NorMode_BBLastday_StepTime:
            g_run_mode = NorMode_BBLastday_StepEng;
            break;
        case NorMode_BBLastday_StepEng:
            g_run_mode = NorMode_BBLastday;
            break;
        case SetMode_Height:
            if(g_info[0] <= 0)
            {
                g_info[0] = 0;
            }
            else
            {
                g_info[0] --;
            }
            break;
        case SetMode_Weight:
            if(g_info[1] <= 0)
            {
                g_info[1] = 0;
            }
            else
            {
                g_info[1] --;
            }
            break;
        case SetMode_Steplength:
            if(g_info[2] <= 0)
            {
                g_info[2] = 0;
            }
            else
            {
                g_info[2] --;
            }
            break;
        case SetMode_Timerhour:
            g_time[0] --;
            if(g_time[0] < 1)
            {
                g_time[0] = 23;
            }
            break;
        case SetMode_Timerminu:
            g_time[1] --;
            if(g_time[1] < 1)
            {
                g_time[1] = 59;
            }
            break;
        default:
            break;
        }

        PORTC_PCR4 |= PORT_PCR_ISF_MASK;        /* ���жϱ�־λ */
    }
    vlpsflag = 0;
}

