/**
  ******************************************************************************
  * @file    mma8652fc.c
  * @brief   基于KL46的计步器设计-加速度计源文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note  
  ******************************************************************************
  */

#include "mma8652fc.h"

/**
 * \brief MMA8652FC initialization
 */
void mma8652_init(void)
{
    /* I2C0 module initialization */
    SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;    /* Turn on clock to I2C0 module */
    PORTE_PCR24 = PORT_PCR_MUX(5);       /* I2C0 SCL                     */
    PORTE_PCR25 = PORT_PCR_MUX(5);       /* I2C0 SDA                     */
    I2C0_F  |= I2C_F_ICR(0x14);          /* SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us */
    I2C0_C1 |= I2C_C1_IICEN_MASK;         /* Enable I2C0 module           */

//    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG2, 0x40);        /* Reset all registers to POR values */
//    Pause(0x631);                                                    /* ~1ms delay                        */

    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG1, DATA_RATE_200HZ);    /* Set the data rate as 200Hz */
}

/**
 * \brief Set MMA8652FC to Standby Model
 */
void mma8652_standby(void)
{
    uint_8 crtl_reg1_data;
    crtl_reg1_data  = I2C_ReadRegister(MMA8652_I2C_ADDRESS, CTRL_REG1);    /* Read the value of CRTL_REG1 */
    crtl_reg1_data &= ~ACTIVE_MASK;
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG1, crtl_reg1_data);     /* Active = 0(standby)         */
}

/**
 * \brief Enable the DATAREADY interrupt
 */
void mma8652_enable_dataready_int(void)
{
    /* Configure the PTA13 pin (connected to the INT1 of the MMA8652) for falling edge interrupts */
    PORTA_PCR13 |= (0|PORT_PCR_ISF_MASK|    /* Clear the interrupt flag                           */
                    PORT_PCR_MUX(0x1)|      /* PTA13 is configured as GPIO                        */
                    PORT_PCR_IRQC(0xA));    /* PTA13 is configured for falling edge interrupts    */

    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG1, (I2C_ReadRegister(MMA8652_I2C_ADDRESS, CTRL_REG1) & ~FREAD_MASK));
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG3, 0x00);
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG4, INT_EN_DRDY_MASK);
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG5, INT_CFG_DRDY_MASK);

    //Enable PORTC interrupt on NVIC
//    enable_irq((INT_PORTA - 16));
//    set_irq_priority((INT_PORTA - 16), 3);
}

/**
 * \brief Enable the FIFO interrupt
 */
void mma8652_enable_fifo_int(void)
{
    /* Configure the PTA13 pin (connected to the INT1 of the MMA8652) for falling edge interrupts    */
    PORTA_PCR13 |= (0|PORT_PCR_ISF_MASK|           /* Clear the interrupt flag                       */
                    PORT_PCR_MUX(0x1)|               /* PTA13 is configured as GPIO                    */
                    PORT_PCR_IRQC(0xA));           /* PTA13 is configured for falling edge interrupts*/

    I2C_WriteRegister(MMA8652_I2C_ADDRESS, F_SETUP_REG,F_MODE_CIRCULAR);                /* FIFO set to CIRCULAR mode             */
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG3, 0x00);                            /* Push-pull, active low interrupt       */
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG4, INT_EN_FIFO_MASK);                /* Enable FIFO interrupt                 */
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG5, INT_CFG_FIFO_MASK);                /* FIFO interrupt routed to INT1 - PTA13 */

    //Enable PORTC interrupt on NVIC
//    enable_irq((INT_PORTA - 16));
//    set_irq_priority((INT_PORTA - 16), 3);
}

/**
 * \brief Set MMA8652FC to Active Model
 */
void mma8652_active (void)
{
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, XYZ_DATA_CFG_REG, FULL_SCALE_2G);       /* HPF_OUT not set, 2g dynamic range value */
    uint_8 crtl_reg1_data;
    crtl_reg1_data  = I2C_ReadRegister(MMA8652_I2C_ADDRESS, CTRL_REG1);            /* Read the value of CRTL_REG1             */
    crtl_reg1_data |= ACTIVE_MASK;
    I2C_WriteRegister(MMA8652_I2C_ADDRESS, CTRL_REG1, crtl_reg1_data);             /* Active = 1                              */
}
