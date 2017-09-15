/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   基于KL46的计步器设计-i2c源文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note     
  ******************************************************************************
  */

#include "i2c0.h"

void I2C_WriteRegister(uint_8 u8SlaveAddress, uint_8 u8RegisterAddress, uint_8 u8Data)
{
    I2C_Start();              
    I2C0_D = u8SlaveAddress << 1;                                    /* Send I2C device address with W/R bit = 0 */
    I2C_Wait();

    I2C0_D = u8RegisterAddress;                                        /* Send register address */
    I2C_Wait();

    I2C0_D = u8Data;                                                /* Send the data */
    I2C_Wait();

    I2C_Stop();

    Pause(50);
}

uint_8 I2C_ReadRegister(uint_8 u8SlaveAddress, uint_8 u8RegisterAddress)
{
    uint_8 result;
      
    I2C_Start();              
    I2C0_D = u8SlaveAddress << 1;                                    /* Send I2C device address with W/R bit = 0 */
    I2C_Wait();                                        

    I2C0_D = u8RegisterAddress;                                        /* Send register address */
    I2C_Wait();

    I2C_RepeatedStart();
    
    I2C0_D = (u8SlaveAddress << 1) | 0x01;                            /* Send I2C device address this time with W/R bit = 1 */
    I2C_Wait();    

    I2C_EnterRxMode();
    I2C_DisableAck();

    result = I2C0_D;
    I2C_Wait();
    I2C_Stop();  
    result = I2C0_D;
    Pause(50);
    return result;
}

void I2C_ReadMultiRegisters(uint_8 u8SlaveAddress, uint_8 u8RegisterAddress, int_16 n, uint_8 *r)
{
    int_16 i;
    
    I2C_Start();              
    I2C0_D = u8SlaveAddress << 1;                                    /* Send I2C device address with W/R bit = 0 */
    I2C_Wait();                                        

    I2C0_D = u8RegisterAddress;                                        /* Send register address */
    I2C_Wait();

    I2C_RepeatedStart();
        
    I2C0_D = (u8SlaveAddress << 1) | 0x01;                            /* Send I2C device address this time with W/R bit = 1 */
    I2C_Wait();    

    I2C_EnterRxMode();
    I2C_EnableAck();
    
    i = I2C0_D;
    I2C_Wait();
    
    for(i=0; i<n-2; i++) 
    {
        *r = I2C0_D;
        r++;
        I2C_Wait();
    }
    
    I2C_DisableAck();
    *r = I2C0_D;
    r++;
    I2C_Wait();
    I2C_Stop();
    *r = I2C0_D;
    Pause(50);        
}

void Pause(int_32 number)
{
    int_32 cnt;
    for(cnt=0; cnt<number; cnt++)
    {
        __asm("nop");
    };
}
