/**
  ******************************************************************************
  * @file    isr.c
  * @brief   基于KL46的计步器设计-isr源文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note   
  ******************************************************************************
  */

#include "isr.h"

int16_t ucdate[3];
uint_8 i_M;
uint_8  g_time[2]={0};                     /*记录时间的数组,时：g_time[0],分：g_time[1]*/
extern uint_8  g_run_mode;
extern uint_8  g_run_mode_remember;       /*记录设置前的状态                           */
extern uint_8  g_run_step_mode;           /*记录是日计步还是单次计步                   */
extern uint_8 g_temp_humi[2];             /*记录温湿度                                 */
extern uint_16 g_info[4];                 /*身高，体重，步长存储                       */
extern float g_today[4];                 /*记录步数，距离。时间。卡路里               */
extern float g_day1[4];
extern float g_day2[4];
extern float g_day3[4];
extern float g_once[4];
extern uint_8  g_flag[4];                 /*flash扇区标记                              */
extern uint_8 vlpsflag;
float   g_today_buf[4];                   /*当次计步使用                               */

//==================中断函数服务程序=========================
//MMA8652中断服务函数
void PORTA_IRQHandler(void)
//void isr_MMA8652(void)
{
    uint_8 accel_data[192]; //
    int16_t temp;
    uint_8 int_source;
    uint_8 j,k;

    //清中断标志位
    PORTA_PCR13 |= PORT_PCR_ISF_MASK;                                                        // Clear the interrupt flag

    int_source = I2C_ReadRegister(MMA8652_I2C_ADDRESS, INT_SOURCE_REG);
    if(int_source & SRC_FIFO_MASK)                                                           // FIFO中断标志
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
        case NorMode_Timer:                /* 时钟显示             */
            SLCD_Clock_ON();               /* LCD时钟灯亮    */
            SLCD_12_ON(g_time[1]);
            SLCD_34_ON(g_time[0]);
            break;
        case NorMode_Stepcount:            /* 显示日计步步数 */
            SLCD_ShowNum(g_today[0]);
            SLCD_StepCount_ON();           /* LCD步数灯亮   */
            SLCD_StepDo_ON();              /* LCD记步灯亮   */
            break;
        case NorMode_Temp:                 /* 显示温度            */
            SLCD_ShowNum(g_temp_humi[1]);
            SLCD_Temperature_ON();         /* LCD温度灯亮   */
            break;
        case NorMode_Humi:                 /* 显示湿度            */
            SLCD_ShowNum(g_temp_humi[0]);
            SLCD_Humidity_ON();            /* LCD湿度灯亮   */
            break;
        case NorMode_StepDistDisplay:      /* 显示日计步距离 */
            SLCD_Distance_ON();            /* LCD距离灯亮    */
            SLCD_StepDo_ON();              /* LCD记步灯亮    */
            SLCD_ShowNum_F(g_today[1]);
            break;
        case NorMode_StepTimeDisplay:      /* 显示日计步时间 */
            SLCD_Time_ON();                /* LCD时间灯亮    */
            SLCD_StepDo_ON();              /* LCD记步灯亮    */
            SLCD_ShowNum(g_today[2]);
            break;
        case NorMode_StepEngDisplay:       /* 显示日计步消耗卡路里 */
             SLCD_Kcal_ON();               /* LCD消耗卡路里灯亮    */
             SLCD_StepDo_ON();             /* LCD记步灯亮                */
             SLCD_ShowNum_F(g_today[3]);
            break;
        case NorMode_Lastday:              /* 显示昨天数据步数         */
            SLCD_Day1_ON();                /* LCD昨天数据灯亮        */
            SLCD_StepCount_ON();           /* LCD步数灯亮                */
            SLCD_ShowNum(g_day1[0]);
            break;
        case NorMode_Lastday_StepDist:     /* 显示昨天数据距离         */
            SLCD_Day1_ON();                /* LCD昨天数据灯亮        */
            SLCD_Distance_ON();            /* LCD距离灯亮                */
            SLCD_ShowNum_F(g_day1[1]);
            break;
        case NorMode_Lastday_StepTime:     /* 显示昨天数据时间         */
            SLCD_Day1_ON();                /* LCD昨天数据灯亮        */
            SLCD_Time_ON();                /* LCD时间灯亮                */
            SLCD_ShowNum(g_day1[2]);
            break;
        case NorMode_Lastday_StepEng:     /* 显示昨天数据消耗卡路里     */
            SLCD_Day1_ON();               /* LCD昨天数据灯亮                */
            SLCD_Kcal_ON();               /* LCD消耗卡路里灯亮            */
            SLCD_ShowNum_F(g_day1[3]);
            break;
        case NorMode_BLastday:            /* 显示前天数据步数              */
            SLCD_Day2_ON();               /* LCD前天数据灯亮             */
            SLCD_StepCount_ON();          /* LCD步数灯亮                     */
            SLCD_ShowNum(g_day2[0]);
            break;
        case NorMode_BLastday_StepDist:   /* 显示前天数据距离              */
            SLCD_Day2_ON();               /* LCD前天数据灯亮             */
            SLCD_Distance_ON();           /* LCD距离灯亮                     */
            SLCD_ShowNum_F(g_day2[1]);
            break;
        case NorMode_BLastday_StepTime:   /* 显示前天数据时间                   */
            SLCD_Day2_ON();               /* LCD前天数据灯亮                  */
            SLCD_Time_ON();               /* LCD时间灯亮                          */
            SLCD_ShowNum(g_day2[2]);
            break;
        case NorMode_BLastday_StepEng:    /* 显示前天数据消耗卡路里       */
            SLCD_Day2_ON();               /* LCD前天数据灯亮                   */
            SLCD_Kcal_ON();               /* LCD消耗卡路里灯亮               */
            SLCD_ShowNum_F(g_day2[3]);
            break;
        case NorMode_BBLastday:           /* 显示大前天数据步数                */
            SLCD_Day3_ON();               /* LCD大前天数据灯亮               */
            SLCD_StepCount_ON();          /* LCD步数灯亮                           */
            SLCD_ShowNum(g_day3[0]);
            break;
        case NorMode_BBLastday_StepDist:  /* 显示大前天数据距离                 */
            SLCD_Day3_ON();               /* LCD大前天数据灯亮                */
            SLCD_Distance_ON();           /* LCD距离灯亮                            */
            SLCD_ShowNum_F(g_day3[1]);
            break;
        case NorMode_BBLastday_StepTime:  /* 显示大前天数据时间                 */
            SLCD_Day3_ON();               /* LCD大前天数据灯亮                */
            SLCD_Time_ON();               /* LCD时间灯亮                            */
            SLCD_ShowNum(g_day3[2]);
            break;
        case NorMode_BBLastday_StepEng:   /* 显示大前天数据消耗卡路里     */
            SLCD_Day3_ON();               /* LCD大前天数据灯亮                */
            SLCD_Kcal_ON();               /* LCD消耗卡路里灯亮                */
            SLCD_ShowNum_F(g_day3[3]);
            break;
        case NorMode_OnceStepcount:       /* 显示当次计步步数                     */
            SLCD_Once_ON();               /* LCD单次计步灯亮                    */
            SLCD_StepCount_ON();          /* LCD步数灯亮                            */
            SLCD_ShowNum((g_today[0] - g_today_buf[0]));
            break;
        case NorMode_OnceStepDist:        /* 显示当次计步距离                     */
            SLCD_Once_ON();               /* LCD单次计步灯亮                    */
            SLCD_Distance_ON();           /* LCD距离灯亮                            */
            SLCD_ShowNum_F((g_today[1] - g_today_buf[1]));
            break;
        case NorMode_OnceStepTime:        /* 显示当次计步时间                     */
            SLCD_Once_ON();               /* LCD单次计步灯亮                    */
            SLCD_Time_ON();               /* LCD时间灯亮                            */
            SLCD_ShowNum((g_today[2] - g_today_buf[2]));
            break;
        case NorMode_OnceStepEng:         /* 显示当次计步消耗卡路里         */
            SLCD_Once_ON();               /* LCD单次计步灯亮                    */
            SLCD_Kcal_ON();               /* LCD消耗卡路里灯亮                */
            SLCD_ShowNum_F((g_today[3] - g_today_buf[3]));
            break;
        case SetMode_Height:              /* 身高设置显示                              */
            SLCD_Set_ON();                /* LCD设置灯亮                             */
            SLCD_Height_ON();             /* LCD身高灯亮                             */
            SLCD_ShowNum(g_info[0]);
            break;
        case SetMode_Weight:              /* 体重设置显示                              */
            SLCD_Set_ON();                /* LCD设置灯亮                             */
            SLCD_Weight_ON();             /* LCD体重灯亮                             */
            SLCD_ShowNum(g_info[1]);
            break;
        case SetMode_Steplength:          /* 步长设置显示                              */
            SLCD_Set_ON();                /* LCD设置灯亮                             */
            SLCD_Step_ON();               /* LCD步长灯亮                             */
            SLCD_ShowNum(g_info[2]);
            break;
        case SetMode_Timerhour:           /* 时设置设置显示                          */
            SLCD_Clock_ON();              /* LCD时钟灯亮                             */
            SLCD_Set_ON();                /* LCD设置灯亮                             */
            SLCD_34_ON(g_time[0]);
            break;
        case SetMode_Timerminu:           /* 分设置设置显示                          */
            SLCD_Clock_ON();              /* LCD时钟灯亮                             */
            SLCD_Set_ON();                /* LCD设置灯亮                             */
            SLCD_12_ON(g_time[1]);
            break;
        default:
            break;
        }
    I2C_ReadRegister(MMA8652_I2C_ADDRESS, F_STATUS_REG);                                   // Clear the interrupt flag
    }
}




/**
 * @brief  中断处理函数入口
 * @param  LPTimer_IRQHandler :LPTM中断处理函数
 * @note 函数内部用于中断事件处理
 */
void LPTimer_IRQHandler(void)
{
    LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;
    minu_add1(g_time);
    step_data_process(g_today, g_info);              //每分钟处理一次数据
    if((g_time[1] % 10) == 0)                        //每十分钟读取一次温湿度
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



//按键中断
void PORTC_PORTD_IRQHandler(void)
{
DelayMs(50);                            /* 延时50毫秒                               */
    if(PORTC_ISFR & 0x0040)                 /* PTC6中断,key_plus  */
    {
        switch(g_run_mode)
        {
        /* 时钟、温度、湿度显示时按下Plus，无效 */
        case NorMode_Timer:
        case NorMode_Temp:
        case NorMode_Humi:
            break;
        /* 计步时按下PLUS，步数->卡路里->时间->距离，循环 */
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
        /* 单次计步时按下Plus，步数->卡路里->时间->距离，循环 */
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
        /* 昨天、前天、大前天、前三天数据显示时按下Plus，步数->卡路里->时间->距离，循环 */
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
        /* 身高设置时按下Plus，身高加1 */
        case SetMode_Height:
            g_info[0] ++;
            if(g_info[0] == 9999)
            {
                g_info[0] = 0;
            }
            break;
        /* 体重设置时按下Plus，体重加1 */
        case SetMode_Weight:
            g_info[1] ++;
            if(g_info[1] == 9999)
            {
                g_info[1] = 0;
            }
            break;
        /* 步长设置时按下Plus，步长加1 */
        case SetMode_Steplength:
            g_info[2] ++;
            if(g_info[2] == 9999)
            {
                g_info[2] = 0;
            }
            break;
        /* 时设置时按下Plus，时加1 */
        case SetMode_Timerhour:
            g_time[0] ++;
            if(g_time[0] == 24)
            {
                g_time[0] = 0;
            }
            break;
        /* 分设置时按下Plus，分加1 */
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

        PORTC_PCR6 |= PORT_PCR_ISF_MASK;        /* 清中断标志位                             */
    }
    if(PORTC_ISFR & 0x0020)                     /* PTC5中断,key_mode  */
    {
        DelayMs(100);                           /* 延时50毫秒                               */
         if(GPIO_ReadBit(HW_GPIOC, 5) == 0)               /* key_mode长按                     */
        {
            switch(g_run_mode)
            {
            /* 计步、时钟，温度、湿度、昨天数据、前天数据、大前天数据、单次计步中，长按Mode，进入设置模式 */
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
            /* 正在设置模式中长按Mode先判断设置的身高、体重、步长是否有效，无效跳到SetMode_Height，有效则退出设置模式，开始计步，并进入之前的模式 */
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
                    data_storage_info(g_info);            /* 存储身高、体重、步长信息 */
                    g_run_mode = g_run_mode_remember;
                }
                break;
            default:
                break;
            }
        }
        else            /* key_mode短按*/
        {
            switch(g_run_mode)
            {
            /* 时钟显示中短按Mode，进入计步，并显示步数 */
            case NorMode_Timer:
                g_run_mode = NorMode_Stepcount;
                break;
            /* 计步中短按Mode，计步不中断，进入温度显示 */
            case NorMode_Stepcount:
                g_run_mode = NorMode_Temp;
                break;
            /* 温度显示时短按Mode，进入湿度显示 */
            case NorMode_Temp:
                g_run_mode = NorMode_Humi;
                break;
            /* 湿度显示时短按Mode，进入单次计步 */
            case NorMode_Humi:
                g_today_buf[0] = g_today[0];  /* 记录  */
                g_today_buf[1] = g_today[1];
                g_today_buf[2] = g_today[3];
                g_today_buf[3] = g_today[3];
                g_run_mode = NorMode_OnceStepcount;
                break;
            /* 计步中（显示距离、时间、卡路里）短按Mode，进入温度显示 */
            case NorMode_StepDistDisplay:
            case NorMode_StepTimeDisplay:
            case NorMode_StepEngDisplay:
                g_run_mode = NorMode_Temp;
                break;
            /* 单次计步中（显示距离、时间或卡路里）短按Mode，读取昨天数据，清除单次计步信息，进入昨天数据显示 */
            case NorMode_OnceStepcount:
            case NorMode_OnceStepDist:
            case NorMode_OnceStepTime:
            case NorMode_OnceStepEng:
                data_read_u8b(FLAG_SECNO, 0, 4, g_flag);
                data_read_32b(g_flag[0], 0, 4, g_day1);
                g_run_mode = NorMode_Lastday;
                break;
            /* 昨天数据显示中短按Mode，读取前天数据，进入前天数据 */
            case NorMode_Lastday:
            case NorMode_Lastday_StepDist:
            case NorMode_Lastday_StepTime:
            case NorMode_Lastday_StepEng:
                data_read_u8b(FLAG_SECNO, 0, 4, g_flag);
                data_read_32b(g_flag[1], 0, 4, g_day2);
                g_run_mode = NorMode_BLastday;
                break;
            /* 前天数据显示中短按Mode，读取大前天数据，进入大前天数据 */
            case NorMode_BLastday:
            case NorMode_BLastday_StepDist:
            case NorMode_BLastday_StepTime:
            case NorMode_BLastday_StepEng:
                data_read_u8b(FLAG_SECNO, 0, 4, g_flag);
                data_read_32b(g_flag[2], 0, 4, g_day3);
                g_run_mode = NorMode_BBLastday;
                break;
            /* 大前天数据显示中短按Mode，进入时钟显示 */
            case NorMode_BBLastday:
            case NorMode_BBLastday_StepDist:
            case NorMode_BBLastday_StepTime:
            case NorMode_BBLastday_StepEng:
                g_run_mode = NorMode_Timer;
                break;
            /* 身高设置中短按Mode，进入体重设置 */
            case SetMode_Height:
                g_run_mode = SetMode_Weight;
                break;
            /* 体重设置中短按Mode，进入步长设置 */
            case SetMode_Weight:
                g_run_mode = SetMode_Steplength;
                break;
            /* 步长设置中短按Mode，进入时设置 */
            case SetMode_Steplength:
                g_run_mode = SetMode_Timerhour;
                break;
            /* 时设置中短按Mode，进入分设置 */
            case SetMode_Timerhour:
                g_run_mode = SetMode_Timerminu;
                break;
            /* 分设置中短按Mode，进入身高设置*/
            case SetMode_Timerminu:
                g_run_mode = SetMode_Height;
                break;
            default:
                break;
            }
        }

        PORTC_PCR5 |= PORT_PCR_ISF_MASK;    /* 清中断标志位 */
    }
    if(PORTC_ISFR & 0x0010)        /* PTC4中断,key_minus */
    {
        DelayMs(50);               /*延时50毫秒                                  */
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

        PORTC_PCR4 |= PORT_PCR_ISF_MASK;        /* 清中断标志位 */
    }
    vlpsflag = 0;
}

