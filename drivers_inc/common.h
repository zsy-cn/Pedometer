/**
  ******************************************************************************
  * @file    common.h
  * @brief   基于KL46的计步器设计-驱动模块公用定义头文件
  * @author  赵守阳
  * @version V1.0
  * @date    2015.4.28
  * @note    此文件为内部文件，用户无需调用和修改  
  ******************************************************************************
  */

#ifndef __CH_LIB_KL_COMMON_H__
#define __CH_LIB_KL_COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#ifdef LIB_DEBUG
#include <stdio.h>
#endif

#ifdef MKL46Z4
#include "MKL46Z4.h"
#else
#error "No CPU defined!"
#endif

/* means you can use printf via UART */
#define UART_USE_STDIO

/* version information */
#define CHK_VERSION                   2L              //!< major version number
#define CHK_SUBVERSION                5L              //!< minor version number
#define CHK_REVISION                  0L              //!< revise version number

/* CH_Kinetis version */
#define FW_VERSION                ((CHK_VERSION * 10000) + \
                                  (CHK_SUBVERSION * 100) + CHK_REVISION)

/* parameter detector */
#if defined(LIB_DEBUG)

/**
*\brief The assert_param macro is used for function's parameters check.
*
*\param[in]     expr: If expr is false, it calls assert_failed function which reports 
*         		the name of the source file and the source line number of the call 
*         		that failed. If expr is true, it returns no value.
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((char *)__FILE__, __LINE__))
void assert_failed(char * file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif
  
#if defined(LIB_DEBUG)
#define LIB_TRACE	printf
#else
#define LIB_TRACE(...)
#endif

#define NVIC_PriorityGroup_0         ((uint32_t)0x7) /*!< 0 bits for pre-emption priority   4 bits for subpriority */                                               
#define NVIC_PriorityGroup_1         ((uint32_t)0x6) /*!< 1 bits for pre-emption priority   3 bits for subpriority */                                                  
#define NVIC_PriorityGroup_2         ((uint32_t)0x5) /*!< 2 bits for pre-emption priority   2 bits for subpriority */                                                   
#define NVIC_PriorityGroup_3         ((uint32_t)0x4) /*!< 3 bits for pre-emption priority   1 bits for subpriority */                                                   
#define NVIC_PriorityGroup_4         ((uint32_t)0x3) /*!< 4 bits for pre-emption priority   0 bits for subpriority */

#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define ABS(a)         (((a) < 0) ? (-(a)) : (a))
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))

#define BSWAP_16(x)     (uint16_t)((((x) & 0xFF00) >> 0x8) | (((x) & 0xFF) << 0x8))
#define BSWAP_32(val)	(uint32_t)((BSWAP_16((uint32_t)(val) & (uint32_t)0xFFFF) << 0x10) |  \
                                   (BSWAP_16((uint32_t)((val) >> 0x10))))

/* QuickInitType */
typedef struct
{
    uint32_t ip_instance:3;
    uint32_t io_instance:3;
    uint32_t mux:3;
    uint32_t io_base:5;
    uint32_t io_offset:5;
    uint32_t channel:5;
    uint32_t reserved:8;
}QuickInit_Type;

/* clock source */
typedef enum
{
    kCoreClock,
    kSystemClock,
    kBusClock,
    kFlashClock,
    kMCGOutClock,
    kClockNameCount,
}CLOCK_Source_Type; 

struct reg_ops
{
    void *      addr;
    uint32_t    mask;
};

/* API functions */
#define EnableInterrupts()   __enable_irq()
#define DisableInterrupts()  __disable_irq()
#define SystemSoftReset    NVIC_SystemReset
uint32_t QuickInitEncode(QuickInit_Type * type)；
void QuickInitDecode(uint32_t map, QuickInit_Type* type);

/**
*\brief delay ms
*
*\param[in]     ms
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
void DelayMs(uint32_t ms);

/**
*\brief delay s
*
*\param[in]     ms
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
void DelayUs(uint32_t ms);

/**
*\brief delay function initialization
*
*\param[in]     none
*\param[out]    none
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
void DelayInit(void);

/**
*\brief get clock frequency
*
*\param[in]     clockName,FrequenctInHz
*\param[out]    frequency at int32_t
*\param[in,out] none
*
*\retval none
*
*\note  none
*/
int32_t CLOCK_GetClockFrequency(CLOCK_Source_Type clockName, uint32_t* FrequenctInHz);

/* Define switch interrupt */
#define ENABLE_INTERRUPTS   __asm(" CPSIE i")  //开总中断
#define DISABLE_INTERRUPTS  __asm("CPSID  i")  //关总中断

#define ARM_INTERRUPT_LEVEL_BITS   2       //MQX操作系统使用

/* 位操作宏函数（置位、清位、获得寄存器一位的状态）*/
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //获得寄存器一位的状态

/* 重定义基本数据类型（类型别名宏定义）*/
typedef unsigned char        uint_8;   // 无符号8位数，字节
typedef unsigned short int   uint_16;  // 无符号16位数，字
typedef unsigned long int    uint_32;  // 无符号32位数，长字
typedef char                 int_8;    // 有符号8位数
typedef short int            int_16;   // 有符号16位数
typedef int                  int_32;   // 有符号32位数
/* 不优化类型*/
typedef volatile uint_8      vuint_8;  // 不优化无符号8位数，字节
typedef volatile uint_16     vuint_16; // 不优化无符号16位数，字
typedef volatile uint_32     vuint_32; // 不优化无符号32位数，长字
typedef volatile int_8       vint_8;   // 不优化有符号8位数
typedef volatile int_16      vint_16;  // 不优化有符号16位数
typedef volatile int_32      vint_32;  // 不优化有符号32位数

/* 喂狗*/
#define WDI_FEED() {SIM_SRVCOP = 0x55;	SIM_SRVCOP = 0xAA;}



#endif /* __CH_LIB_KL_COMMON_H__ */
