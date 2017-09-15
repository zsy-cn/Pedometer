/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   基于KL46的计步器设计-i2c头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */
  
#include "common.h"

#define I2C_DisableAck()       I2C0_C1 |= I2C_C1_TXAK_MASK
#define I2C_EnableAck()        I2C0_C1 &= ~I2C_C1_TXAK_MASK
#define I2C_RepeatedStart()    I2C0_C1 |= I2C_C1_RSTA_MASK
#define I2C_EnterRxMode()      I2C0_C1 &= ~I2C_C1_TX_MASK
#define I2C_write_byte(data)   I2C0_D = data
#define I2C_Start()            I2C0_C1 |= I2C_C1_TX_MASK;\
                               I2C0_C1 |= I2C_C1_MST_MASK
#define I2C_Stop()             I2C0_C1 &= ~I2C_C1_MST_MASK;\
                               I2C0_C1 &= ~I2C_C1_TX_MASK
#define I2C_Wait()             while((I2C0_S & I2C_S_IICIF_MASK)==0) {} \
                               I2C0_S |= I2C_S_IICIF_MASK

void I2C_WriteRegister(uint_8 u8SlaveAddress, uint_8 u8RegisterAddress, uint_8 u8Data);
uint_8 I2C_ReadRegister(uint_8 u8SlaveAddress, uint_8 u8RegisterAddress);
void I2C_ReadMultiRegisters(uint_8 u8SlaveAddress, uint_8 u8RegisterAddress, int_16 n, uint_8 *r);
void Pause(int_32 number);
