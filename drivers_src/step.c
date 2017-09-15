/**
  ******************************************************************************
  * @file    step.c
  * @brief   基于KL46的计步器设计-计步算法源文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    
  ******************************************************************************
  */

#include "step.h"

/*********************************************************************************************************
  全局变量
*********************************************************************************************************/
static int f = 0;               /*起始步数标定参数            */
static int StepCountOld = 0;    /*没进入步数统计前的步数      */
extern uint_16 g_today[4];      /*记录步数，距离, 时间, 卡路里*/
extern int16_t ucdate[3];       /*单组加速度数据              */
extern float g_once[4];         /*单次计步数组                */
int StepCount   = 0;            /*计步统计参数                */
int StepCountFlag = 0;          /*计步状态参数                */
uint_8 StepLimitFlag = 0;       /*数据是否过动态阈值参数      */
uint_8 InitDataBuffer = 0;      /*滤波缓冲区更新标志          */
uint_8 m_count  = 0;            /*更新阈值标志                */
uint_8 m = 0;                   /*更新阈值计数                */
uint_8 n = 0;                   /*更新滤波缓冲区计数          */

int16_t DateBufferX[10] = {0};  /*滑动平均值滤波缓冲区        */
int16_t DateBufferY[10] = {0};
int16_t DateBufferZ[10] = {0};

int16_t X_Max = -2048,X_Min = +2047,X_Base = 0,X_UpLimit = 0,X_DownLimit = 0,X_Data[64],X_MaxMark = 0,X_MinMark = 0; /*参数初值*/
int16_t Y_Max = -2048,Y_Min = +2047,Y_Base = 0,Y_UpLimit = 0,Y_DownLimit = 0,Y_Data[64],Y_MaxMark = 0,Y_MinMark = 0;
int16_t Z_Max = -2048,Z_Min = +2047,Z_Base = 0,Z_UpLimit = 0,Z_DownLimit = 0,Z_Data[64],Z_MaxMark = 0,Z_MinMark = 0;

/**
*\brief 用来选择哪个轴作为计步依据
*
*\param[in]     none
*\param[out]    选择的轴X，Y，Z
*\param[in,out] none
*
*\retval flag
*\retval none
*
*\note  none
*/
uint_8 AxisSelect()
{
    int tempX = 0, tempY = 0, tempZ = 0, tempMax;
    uint_8 flag = 0;
    tempX = X_Max - X_Min;
    tempY = Y_Max - Y_Min;
    tempZ = Z_Max - Z_Min;
    if(tempX > tempY) {
        if(tempX > tempZ) {
            flag = 1;
            tempMax = tempX;
        } else {
            flag = 3;
            tempMax = tempZ;
        }
    } else {
        if(tempY > tempZ) {
            flag = 2;
            tempMax = tempY;
        } else {
            flag = 3;
            tempMax = tempZ;
        }
    }
    if(tempMax > 950) {
        return flag;
    } else {
        return 0;
    }
}

/**
*\brief 计算步数主函数
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
void CountStep()
{
    uint_8 i = 0;
    int16_t x = 0, y = 0, z = 0;
        
    StepCountFlag = StepCount;                    /*计数标志        */

    x=ucdate[0];                                  /*读取一组数据    */
    y=ucdate[1];
    z=ucdate[2];

    if(m == 64) {                                 /*判断是否更新数据*/
        m = 0;
        f++;
        if(m_count == 0) {
            m_count = 1;
        }
     }
    if(n == 10){
        n = 0;
     }
        
    DateBufferX[n] = x;                           /*写入数据缓冲区   */
    DateBufferY[n] = y;
    DateBufferZ[n] = z;
        
    if(InitDataBuffer < 9) {                      /*第一次写缓冲区判断*/
        X_Data[m] = x;
        Y_Data[m] = y;
        Z_Data[m] = z;
        InitDataBuffer++;
    } else {
        X_Data[m] = (DateBufferX[0] + DateBufferX[1] + DateBufferX[2] + DateBufferX[3] + DateBufferX[4] + DateBufferX[5] + DateBufferX[6] + DateBufferX[7] + DateBufferX[8] + DateBufferX[9]) / 10;
        Y_Data[m] = (DateBufferY[0] + DateBufferY[1] + DateBufferY[2] + DateBufferY[3] + DateBufferY[4] + DateBufferY[5] + DateBufferY[6] + DateBufferY[7] + DateBufferY[8] + DateBufferY[9]) / 10;
        Z_Data[m] = (DateBufferZ[0] + DateBufferZ[1] + DateBufferZ[2] + DateBufferZ[3] + DateBufferZ[4] + DateBufferZ[5] + DateBufferZ[6] + DateBufferZ[7] + DateBufferZ[8] + DateBufferZ[9]) / 10;
    }
    if(m_count == 1) {                             /*是否更新阈值参数 */
        if(X_MaxMark == m || X_MinMark == m || Y_MaxMark == m || Y_MinMark == m || Z_MaxMark == m || Z_MinMark == m) {
            uint_8 tempXMaxMark = X_MaxMark;
            uint_8 tempXMinMark = X_MinMark;
            uint_8 tempYMaxMark = Y_MaxMark;
            uint_8 tempYMinMark = Y_MinMark;
            uint_8 tempZMaxMark = Z_MaxMark;
            uint_8 tempZMinMark = Z_MinMark;
            if(X_MaxMark == m) {
                X_Max = -2048;
            }
            if(X_MinMark == m) {
                X_Min = +2047;
            }
            if(Y_MaxMark == m) {
                Y_Max = -2048;
            }
            if(Y_MinMark == m) {
                Y_Min = +2047;
            }
            if(Z_MaxMark == m) {
                Z_Max = -2048;
            }
            if(Z_MinMark == m) {
                Z_Min = +2047;
            }
            for(i = 0; i < 64; i++) {
                if(X_MaxMark == m) {
                    if(X_Data[i] >= X_Max) {
                        X_Max = X_Data[i];
                        tempXMaxMark = i;
                     }
                }
                if(X_MinMark == m) {
                    if(X_Data[i] <= X_Min) {
                        X_Min = X_Data[i];
                        tempXMinMark = i;
                    }
                }
                if(Y_MaxMark == m) {
                    if(Y_Data[i] >= Y_Max) {
                        Y_Max = Y_Data[i];
                        tempYMaxMark = i;
                    }
                }
                if(Y_MinMark == m) {
                    if(Y_Data[i] <= Y_Min) {
                        Y_Min = Y_Data[i];
                        tempYMinMark = i;
                    }
                }
                if(Z_MaxMark == m) {
                    if(Z_Data[i] >= Z_Max) {
                        Z_Max = Z_Data[i];
                        tempZMaxMark = i;
                    }
                }
                if(Z_MinMark == m) {
                    if(Z_Data[i] <= Z_Min) {
                        Z_Min = Z_Data[i];
                        tempZMinMark = i;
                    }
                }
            }
            
            X_MaxMark = tempXMaxMark;
            X_MinMark = tempXMinMark;
            Y_MaxMark = tempYMaxMark;
            Y_MinMark = tempYMinMark;
            Z_MaxMark = tempZMaxMark;
            Z_MinMark = tempZMinMark;
        }
    }
        
    if(X_Data[m] >= X_Max) {
        X_Max = X_Data[m];
        X_MaxMark = m;
    }
    if(X_Data[m] <= X_Min) {
        X_Min = X_Data[m];
        X_MaxMark = m;
    }
    if(Y_Data[m] >= Y_Max) {
        Y_Max = Y_Data[m];
        Y_MaxMark = m;
    }
    if(Y_Data[m] <= Y_Min) {
        Y_Min = Y_Data[m];
        Y_MinMark = m;
    }
    if(Z_Data[m] >= Z_Max) {
        Z_Max = Z_Data[m];
        Z_MaxMark = m;
    }
    if(Z_Data[m] <= Z_Min) {
        Z_Min = Z_Data[m];
        Z_MinMark = m;
    }
        
    X_Base      = (X_Max + X_Min) / 2;                                /*更新阈值               */
    Y_Base      = (Y_Max + Y_Min) / 2;
    Z_Base      = (Z_Max + Z_Min) / 2;
    X_UpLimit   = (X_Base + X_Max * 2) / 3;
    Y_UpLimit   = (Y_Base + Y_Max * 2) / 3;
    Z_UpLimit   = (Z_Base + Z_Max * 2) / 3;
    X_DownLimit = (X_Base + X_Min * 2) / 3;
    Y_DownLimit = (Y_Base + Y_Min * 2) / 3;
    Z_DownLimit = (Z_Base + Z_Min * 2) / 3;
    
    switch(AxisSelect()) {
    case 1:
        if((X_Data[m] > X_UpLimit) && StepLimitFlag == 0) {
            StepLimitFlag = 1;                                        /*通过一次阈值上限        */
        }
        if((X_Data[m] < X_DownLimit) && StepLimitFlag ==1) {
            StepLimitFlag = 0;                                        /*通过一次阈值下限，计一步*/
            StepCount++;
        }
        break;
    case 2:
        if((Y_Data[m] > Y_UpLimit) && StepLimitFlag == 0) {
            StepLimitFlag = 1;
        }
        if((Y_Data[m] < Y_DownLimit) && StepLimitFlag ==1) {
            StepLimitFlag = 0;
            StepCount++;
        }
        break;
    case 3:
        if((Z_Data[m] > Z_UpLimit) && StepLimitFlag == 0) {
            StepLimitFlag = 1;
        }
        if((Z_Data[m] < Z_DownLimit) && StepLimitFlag ==1) {
            StepLimitFlag = 0;
            StepCount++;
        }
        break;
    default:
        break;
    }
    m++;
    n++;

    StepCountFlag = StepCount - StepCountFlag;
    g_today[0] = StepCount;
    
    if((f>62) && (StepCountOld<5))                                                   /*时间窗口判断*/
    {
        StepCountOld=0;
        f=0;
    }
    if((f<62) && (StepCountOld >= 5))                                                /*起始计步判断*/
    {
        StepCountOld=0;
        f=0;
        g_once[0] = StepCount - StepCountFlag;
        StepCount =  StepCount + StepCountOld;
        g_today[0] = StepCount;
        
    }

}

/**
*\brief 距离，能量，时间计算
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
void step_data_process(float step_data[], uint_16 info[])
{
    step_data[2] ++;                                                                  /*计步时间    */
    step_data[3] = 0.53*info[0] + 0.58*info[1] + 0.37*step_data[0] + 1.51 - 100;      /*能量计算    */
    step_data[1] = step_data[0] * info[2] / 100000.0;                                 /*距离计算    */
}

/* end of file */

