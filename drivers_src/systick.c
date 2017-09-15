/**
  ******************************************************************************
  * @file    systick.c
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    ���ļ�ΪоƬARM�ں��е�SysTickģ��ĵײ㹦�ܺ���
  ******************************************************************************
  */
  
#include "systick.h"
#include "common.h"

static uint32_t fac_us = 0;     //!< usDelay Mut
static uint32_t fac_ms = 0;


//! @defgroup CHKinetis
//! @{


//! @defgroup SysTick
//! @brief SysTick API functions
//! @{

 /**
 * @brief  ��ʼ��SysTickʱ��
 * @code
 *     // ��ʼ��SysTickʱ�� �趨�ж�����Ϊ10000us(10ms)
 *      SYSTICK_Init(10000);
 * @endcode
 * @param  timeInUs: �ж����� ��λus
 * @retval None
 */
void SYSTICK_Init(uint32_t timeInUs)
{
    /* Set clock source = core clock */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
    CLOCK_GetClockFrequency(kCoreClock, &fac_us);
    fac_us /= 1000000;
    fac_ms = fac_us * 1000;
    /* every 100ms in a int */
    SysTick->LOAD = fac_us * timeInUs;
}

 /**
 * @brief  ��ʼ��SysTickΪ��ʱӦ�� ��ʼ����Ϳ��Ե��� DelayMs DelayUs
 * @code
 *      //��SysTick������ʱ�ĳ�ʼ�� ��ʼ����ϵͳ��ʱ20ms
 *      SYSTICK_DelayInit();
 *      SYSTICK_DelayMs(20);
 * @endcode
 * @param  None
 * @retval None
 */
void SYSTICK_DelayInit(void)
{
    SYSTICK_Init(1234);
    SYSTICK_Cmd(true);
    SYSTICK_ITConfig(false);
}

 /**
 * @brief  ��������ֹͣSysTickʱ��
 * @code
 *      //����ʱ��
 *      SYSTICK_Cmd(true);
 * @endcode
 * @param  NewState:ʹ�ܻ��߹ر�
 *         @arg true :ʹ��
 *         @arg false:ֹͣ
 * @retval None
 */
void SYSTICK_Cmd(bool NewState)
{
    (true == NewState)?(SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk):(SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk);
}

 /**
 * @brief  ����SysTick�ж�
 * @code
 *      //�����жϹ���
 *      SYSTICK_ITConfig(true);
 * @endcode
 * @param  NewState:ʹ�ܻ��߹ر�
 *         @arg true :ʹ��
 *         @arg false:��ֹ
 * @retval None
 */
void SYSTICK_ITConfig(bool NewState)
{
    (true == NewState)?(SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk):(SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk);
}

 /**
 * @brief ΢�뼶��ʱ����
 * @code
 *      //��ʱ100us
 *      SYSTICK_DelayUs(100);
 * @endcode
 * @param  us:��ʱʱ�� ��λus
 * @retval None
 */
void SYSTICK_DelayUs(uint32_t us)
{
    uint32_t temp;
    SysTick->LOAD = us * fac_us;
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
}

 /**
 * @brief  ���뼶��ʱ����
 * 
 * @code
 *      //��ʱ100ms
 *      SYSTICK_DelayMs(100);
 * @endcode
 * @param  us:��ʱ
 * @retval None
 */
void SYSTICK_DelayMs(uint32_t ms)
{
    uint32_t temp;
    uint32_t i;
    SysTick->LOAD = fac_ms;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    for(i = 0; i < ms; i++)
	{
		SysTick->VAL = 0;
		do
		{
			temp = SysTick->CTRL;
		}
        while((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
	}
}
 
 
//! @}

//! @}

