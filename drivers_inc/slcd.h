/**
  ******************************************************************************
  * @file    slcd.h
  * @brief   基于KL46的计步器设计-段码LCD头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */
  
#ifndef __SLCD_H__
#define __SLCD_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "common.h"
   
/*********************************************************************************************************
  宏定义
*********************************************************************************************************/
#define COM1    0x00000001
#define COM2    0x00000200
#define COM3    0x00040000
#define COM4    0x08000000

#define T3      0x00000001
#define T2      0x00000002
#define T1      0x00000004
#define T0      0x00000008
#define T7      0x00000100
#define T6      0x00000200
#define T5      0x00000400
#define T4      0x00000800
#define T8      0x00010000
#define T9      0x00020000
#define T10     0x00040000
#define T11     0x00080000
#define T12     0x01000000
#define T13     0x02000000
#define T14     0x04000000
#define T15     0x08000000
   
#define DP0     0x01000000
#define DP1     0x00000100
#define DP2     0x01000000
#define DP3     0x00000100

#define A0      0x08000000
#define B0      0x04000000
#define C0      0x02000000
#define D0      0x00000001
#define E0      0x00000002
#define F0      0x00000008
#define G0      0x00000004

#define A1      0x00000800
#define B1      0x00000400
#define C1      0x00000200
#define D1      0x00010000
#define E1      0x00020000
#define F1      0x00080000
#define G1      0x00040000

#define A2      0x08000000
#define B2      0x04000000
#define C2      0x02000000
#define D2      0x00000001
#define E2      0x00000002
#define F2      0x00000008
#define G2      0x00000004

#define A3      0x00000800
#define B3      0x00000400
#define C3      0x00000200
#define D3      0x00010000
#define E3      0x00020000
#define F3      0x00080000
#define G3      0x00040000

#define S1_0_1  A0+B0+C0
#define S1_0_2  D0+E0+F0
#define S1_1_1  B0+C0
#define S1_2_1  A0+B0
#define S1_2_2  G0+D0+E0
#define S1_3_1  A0+B0+C0
#define S1_3_2  D0+G0
#define S1_4_1  B0+C0
#define S1_4_2  F0+G0
#define S1_5_1  A0+C0
#define S1_5_2  D0+F0+G0
#define S1_6_1  A0+C0
#define S1_6_2  G0+D0+E0+F0
#define S1_7_1  A0+B0+C0
#define S1_8_1  A0+B0+C0
#define S1_8_2  D0+E0+F0+G0
#define S1_9_1  A0+B0+C0
#define S1_9_2  D0+G0+F0

#define S2_0_1  A1+B1+C1
#define S2_0_2  D1+E1+F1
#define S2_1_1  B1+C1
#define S2_2_1  A1+B1
#define S2_2_2  G1+D1+E1
#define S2_3_1  A1+B1+C1
#define S2_3_2  D1+G1
#define S2_4_1  B1+C1
#define S2_4_2  F1+G1
#define S2_5_1  A1+C1
#define S2_5_2  D1+F1+G1
#define S2_6_1  A1+C1
#define S2_6_2  G1+D1+E1+F1
#define S2_7_1  A1+B1+C1
#define S2_8_1  A1+B1+C1
#define S2_8_2  D1+E1+F1+G1
#define S2_9_1  A1+B1+C1
#define S2_9_2  D1+G1+F1

#define S3_0_1  A2+B2+C2
#define S3_0_2  D2+E2+F2
#define S3_1_1  B2+C2
#define S3_2_1  A2+B2
#define S3_2_2  G2+D2+E2
#define S3_3_1  A2+B2+C2
#define S3_3_2  D2+G2
#define S3_4_1  B2+C2
#define S3_4_2  F2+G2
#define S3_5_1  A2+C2
#define S3_5_2  D2+F2+G2
#define S3_6_1  A2+C2
#define S3_6_2  G2+D2+E2+F2
#define S3_7_1  A2+B2+C2
#define S3_8_1  A2+B2+C2
#define S3_8_2  D2+E2+F2+G2
#define S3_9_1  A2+B2+C2
#define S3_9_2  D2+G2+F2

#define S4_0_1  A3+B3+C3
#define S4_0_2  D3+E3+F3
#define S4_1_1  B3+C3
#define S4_2_1  A3+B3
#define S4_2_2  G3+D3+E3
#define S4_3_1  A3+B3+C3
#define S4_3_2  D3+G3
#define S4_4_1  B3+C3
#define S4_4_2  F3+G3
#define S4_5_1  A3+C3
#define S4_5_2  D3+F3+G3
#define S4_6_1  A3+C3
#define S4_6_2  G3+D3+E3+F3
#define S4_7_1  A3+B3+C3
#define S4_8_1  A3+B3+C3
#define S4_8_2  D3+E3+F3+G3
#define S4_9_1  A3+B3+C3
#define S4_9_2  D3+G3+F3

#define SET         0
#define HEIGHT      1
#define WEIGHT      2
#define STEP        3
#define STEPCOUNT   4
#define DISTANCE    5
#define TIME        6
#define KCAL        7
#define DAY1        8
#define DAY2        9
#define DAY3        10
#define DAYALL      11
#define HUMI        12
#define TEMP        13
#define STEPDO      14
#define CLOCK       15

/*********************************************************************************************************
  函数声明 
*********************************************************************************************************/
void SLCD_ShowNum_F(float x);           /*LCD显示浮点数字    */
void SLCD_Init(void);                   /*LCD初始化          */
void SLCD_ON(void);                     /*LCD全亮            */
void SLCD_OFF(void);                    /*LCD全关            */
void SLCD_Num_ON(void);                 /*LCD数字全亮        */
void SLCD_Num_OFF(void);                /*LCD数字全关        */
void SLCD_1_ON(uint_8 x);               /*LCD第一位亮数字    */
void SLCD_2_ON(uint_8 x);               /*LCD第二位亮数字    */
void SLCD_3_ON(uint_8 x);               /*LCD第三位亮数字    */
void SLCD_4_0N(int x);                  /*LCD第四位亮数字    */
void SLCD_12_ON(int x);                 /*LCD第一二位亮数字  */
void SLCD_34_ON(int x);                 /*LCD第三四位亮数字  */
void SLCD_234_ON(int x);                /*LCD第二三四位亮数字*/
void SLCD_TLight_OFF(void);             /*指示灯全关         */
void SLCD_Select_Light_ON(int x);       /*对应功能灯亮       */
void SLCD_Select_Light_OFF(int x);      /*对应功能灯关       */
void SLCD_ShowNum(uint_16 x);           /*LCD显示数字        */
void SLCD_Set_ON(void);                 /*LCD设置灯亮        */
void SLCD_Height_ON(void);              /*LCD身高灯亮        */
void SLCD_Weight_ON(void);              /*LCD体重灯亮        */
void SLCD_Step_ON(void);                /*LCD步长灯亮        */
void SLCD_StepCount_ON(void);           /*LCD步数灯亮        */
void SLCD_Distance_ON(void);            /*LCD距离灯亮        */
void SLCD_Time_ON(void);                /*LCD时间灯亮        */
void SLCD_Kcal_ON(void);                /*LCD消耗卡路里灯亮  */
void SLCD_Once_ON(void);                /*LCD单次计步灯亮    */
void SLCD_Day1_ON(void);                /*LCD昨天数据灯亮    */
void SLCD_Day2_ON(void);                /*LCD前天数据灯亮    */
void SLCD_Day3_ON(void);                /*LCD大前天数据灯亮  */
void SLCD_DayAll_ON(void);              /*LCD前三天统计灯亮  */
void SLCD_Humidity_ON(void);            /*LCD湿度灯亮        */
void SLCD_Temperature_ON(void);         /*LCD温度灯亮        */
void SLCD_StepDo_ON(void);              /*LCD记步灯亮        */
void SLCD_Clock_ON(void);               /*LCD时钟灯亮        */
void SLCD_set_OFF(void);                /*LCD设置灯关        */
void SLCD_Height_OFF(void);             /*LCD身高灯关        */
void SLCD_Weight_OFF(void);             /*LCD体重灯关        */
void SLCD_Step_OFF(void);               /*LCD步长灯关        */
void SLCD_StepCount_OFF(void);          /*LCD步数灯关        */
void SLCD_Distance_OFF(void);           /*LCD距离灯关        */
void SLCD_Time_OFF(void);               /*LCD时间灯关        */
void SLCD_Kcal_OFF(void);               /*LCD消耗卡路里灯关  */
void SLCD_Day1_OFF(void);               /*LCD昨天步数灯关    */
void SLCD_Day2_OFF(void);               /*LCD前天步数灯关    */
void SLCD_Day3_OFF(void);               /*LCD大前天步数灯关  */
void SLCD_DayAll_OFF(void);             /*LCD前三天统计灯关  */
void SLCD_Humidity_OFF(void);           /*LCD湿度灯关        */
void SLCD_Temperature_OFF(void);        /*LCD温度灯关        */
void SLCD_StepDo_OFF(void);             /*LCD记步灯关        */
void SLCD_Clock_OFF(void);              /*LCD时钟灯关        */
void SLCD_DP2_OFF(void);                /*关闭时钟时灭       */


#ifdef __cplusplus
}
#endif

#endif/* __SLCD_H__*/



