/**
  ******************************************************************************
  * @file    step.c
  * @brief   ����KL46�ļƲ������-�Ʋ��㷨Դ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    
  ******************************************************************************
  */

#include "step.h"

/*********************************************************************************************************
  ȫ�ֱ���
*********************************************************************************************************/
static int f = 0;               /*��ʼ�����궨����            */
static int StepCountOld = 0;    /*û���벽��ͳ��ǰ�Ĳ���      */
extern uint_16 g_today[4];      /*��¼����������, ʱ��, ��·��*/
extern int16_t ucdate[3];       /*������ٶ�����              */
extern float g_once[4];         /*���μƲ�����                */
int StepCount   = 0;            /*�Ʋ�ͳ�Ʋ���                */
int StepCountFlag = 0;          /*�Ʋ�״̬����                */
uint_8 StepLimitFlag = 0;       /*�����Ƿ����̬��ֵ����      */
uint_8 InitDataBuffer = 0;      /*�˲����������±�־          */
uint_8 m_count  = 0;            /*������ֵ��־                */
uint_8 m = 0;                   /*������ֵ����                */
uint_8 n = 0;                   /*�����˲�����������          */

int16_t DateBufferX[10] = {0};  /*����ƽ��ֵ�˲�������        */
int16_t DateBufferY[10] = {0};
int16_t DateBufferZ[10] = {0};

int16_t X_Max = -2048,X_Min = +2047,X_Base = 0,X_UpLimit = 0,X_DownLimit = 0,X_Data[64],X_MaxMark = 0,X_MinMark = 0; /*������ֵ*/
int16_t Y_Max = -2048,Y_Min = +2047,Y_Base = 0,Y_UpLimit = 0,Y_DownLimit = 0,Y_Data[64],Y_MaxMark = 0,Y_MinMark = 0;
int16_t Z_Max = -2048,Z_Min = +2047,Z_Base = 0,Z_UpLimit = 0,Z_DownLimit = 0,Z_Data[64],Z_MaxMark = 0,Z_MinMark = 0;

/**
*\brief ����ѡ���ĸ�����Ϊ�Ʋ�����
*
*\param[in]     none
*\param[out]    ѡ�����X��Y��Z
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
*\brief ���㲽��������
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
        
    StepCountFlag = StepCount;                    /*������־        */

    x=ucdate[0];                                  /*��ȡһ������    */
    y=ucdate[1];
    z=ucdate[2];

    if(m == 64) {                                 /*�ж��Ƿ��������*/
        m = 0;
        f++;
        if(m_count == 0) {
            m_count = 1;
        }
     }
    if(n == 10){
        n = 0;
     }
        
    DateBufferX[n] = x;                           /*д�����ݻ�����   */
    DateBufferY[n] = y;
    DateBufferZ[n] = z;
        
    if(InitDataBuffer < 9) {                      /*��һ��д�������ж�*/
        X_Data[m] = x;
        Y_Data[m] = y;
        Z_Data[m] = z;
        InitDataBuffer++;
    } else {
        X_Data[m] = (DateBufferX[0] + DateBufferX[1] + DateBufferX[2] + DateBufferX[3] + DateBufferX[4] + DateBufferX[5] + DateBufferX[6] + DateBufferX[7] + DateBufferX[8] + DateBufferX[9]) / 10;
        Y_Data[m] = (DateBufferY[0] + DateBufferY[1] + DateBufferY[2] + DateBufferY[3] + DateBufferY[4] + DateBufferY[5] + DateBufferY[6] + DateBufferY[7] + DateBufferY[8] + DateBufferY[9]) / 10;
        Z_Data[m] = (DateBufferZ[0] + DateBufferZ[1] + DateBufferZ[2] + DateBufferZ[3] + DateBufferZ[4] + DateBufferZ[5] + DateBufferZ[6] + DateBufferZ[7] + DateBufferZ[8] + DateBufferZ[9]) / 10;
    }
    if(m_count == 1) {                             /*�Ƿ������ֵ���� */
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
        
    X_Base      = (X_Max + X_Min) / 2;                                /*������ֵ               */
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
            StepLimitFlag = 1;                                        /*ͨ��һ����ֵ����        */
        }
        if((X_Data[m] < X_DownLimit) && StepLimitFlag ==1) {
            StepLimitFlag = 0;                                        /*ͨ��һ����ֵ���ޣ���һ��*/
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
    
    if((f>62) && (StepCountOld<5))                                                   /*ʱ�䴰���ж�*/
    {
        StepCountOld=0;
        f=0;
    }
    if((f<62) && (StepCountOld >= 5))                                                /*��ʼ�Ʋ��ж�*/
    {
        StepCountOld=0;
        f=0;
        g_once[0] = StepCount - StepCountFlag;
        StepCount =  StepCount + StepCountOld;
        g_today[0] = StepCount;
        
    }

}

/**
*\brief ���룬������ʱ�����
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
    step_data[2] ++;                                                                  /*�Ʋ�ʱ��    */
    step_data[3] = 0.53*info[0] + 0.58*info[1] + 0.37*step_data[0] + 1.51 - 100;      /*��������    */
    step_data[1] = step_data[0] * info[2] / 100000.0;                                 /*�������    */
}

/* end of file */

