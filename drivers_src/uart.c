/**
  ******************************************************************************
  * @file    uart.c
  * @brief   ����KL46�ļƲ������-��������Դ����
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note     
  ******************************************************************************
  */
  
#include "uart.h"
#include "gpio.h"
#include "common.h"

#ifdef UART_USE_STDIO
#include <stdio.h>
#endif

#define UARTN_BASES {(void*)UART0, (void*)UART1, (void*)UART2}
/* gloabl const table defination */
const void* UART_InstanceTable[] = UARTN_BASES;
static UART_CallBackTxType UART_CallBackTxTable[ARRAY_SIZE(UART_InstanceTable)] = {NULL};
static UART_CallBackRxType UART_CallBackRxTable[ARRAY_SIZE(UART_InstanceTable)] = {NULL};
/* special use for printf */
static uint8_t UART_DebugInstance;

static const struct reg_ops SIM_UARTClockGateTable[] =
{
    {(void*)&(SIM->SCGC4), SIM_SCGC4_UART0_MASK},
    {(void*)&(SIM->SCGC4), SIM_SCGC4_UART1_MASK},
    {(void*)&(SIM->SCGC4), SIM_SCGC4_UART2_MASK},
};

static const IRQn_Type UART_IRQnTable[] = 
{
    UART0_IRQn,
    UART1_IRQn,
    UART2_IRQn,
};

#ifdef UART_USE_STDIO
#ifdef __CC_ARM // MDK Support
struct __FILE 
{ 
	int handle;
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;
FILE __stdin;
int fputc(int ch,FILE *f)
{
	UART_WriteByte(UART_DebugInstance, ch);
	return ch;
}

int fgetc(FILE *f)
{
    uint16_t ch;
    while(UART_ReadByte(UART_DebugInstance, &ch));
    return (ch & 0xFF);
}
#elif __ICCARM__ /* IAR support */
size_t __write(int handle, const unsigned char * buffer, size_t size)
{
    size_t nChars = 0;
    if (buffer == 0)
    {
        /* This means that we should flush internal buffers.  Since we*/
        /* don't we just return.  (Remember, "handle" == -1 means that all*/
        /* handles should be flushed.)*/
        return 0;
    }
    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ((handle != _LLIO_STDOUT) && (handle != _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }
    /* Send data.*/
    while (size--)
    {
        UART_WriteByte(UART_DebugInstance, *buffer++);
        ++nChars;
    }
    return nChars;
}

size_t __read(int handle, unsigned char * buffer, size_t size)
{
    size_t nChars = 0;
    uint16_t ch = 0;
    if (buffer == 0)
    {
        /* This means that we should flush internal buffers.  Since we*/
        /* don't we just return.  (Remember, "handle" == -1 means that all*/
        /* handles should be flushed.)*/
        return 0;
    }
    /* This function only writes to "standard out" and "standard err",*/
    /* for all other file handles it returns failure.*/
    if ((handle != _LLIO_STDIN) && (handle != _LLIO_STDERR))
    {
        return _LLIO_ERROR;
    }
    /* read data.*/
    while (size--)
    {
        while(UART_ReadByte(UART_DebugInstance, &ch));
        *buffer++ = (char)ch & 0xFF;
        ++nChars;
    }
    return nChars;
}


#endif /* comiler support */

#else /* DO NOT USE STDIO */
static void UART_putstr(uint32_t instance, const char *str)
{
    while(*str != '\0')
    {
        UART_WriteByte(instance, *str++);
    }
}

static void printn(unsigned int n, unsigned int b)
{
    static char *ntab = "0123456789ABCDEF";
    unsigned int a, m;
    if (n / b)
    {
        a = n / b;
        printn(a, b);  
    }
    m = n % b;
    UART_WriteByte(UART_DebugInstance, ntab[m]);
}

int UART_printf(const char *fmt, ...)
{
    char c;
    unsigned int *adx = (unsigned int*)(void*)&fmt + 1;
_loop:
    while((c = *fmt++) != '%')
    {
        if (c == '\0') return 0;
        UART_WriteByte(UART_DebugInstance, c);
    }
    c = *fmt++;
    if (c == 'd' || c == 'l')
    {
        printn(*adx, 10);
    }
    if (c == 'o' || c == 'x')
    {
        printn(*adx, c=='o'? 8:16 );
    }
    if (c == 's')
    {
        UART_putstr(UART_DebugInstance, (char*)*adx);
    }
    adx++;
    goto _loop;
    return 0;
}
#endif /*end of UART_USE_STDIO */

uint8_t UART_QuickInit(uint32_t MAP, uint32_t baudrate)
{
    uint8_t i;
    uint32_t clock;
    UART_InitTypeDef UART_InitStruct1;
    QuickInit_Type * pq = (QuickInit_Type*)&(MAP);
    UART_InitStruct1.baudrate = baudrate;
    UART_InitStruct1.instance = pq->ip_instance;
    
    /* clock source */
    if(pq->ip_instance == HW_UART0)
    {
        CLOCK_GetClockFrequency(kMCGOutClock, &clock);
        
        /* use PLL/2 or FLL */
        SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
        SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);  
	
        if(MCG->C6 & MCG_C6_PLLS_MASK) /* PLL */
        {
            SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
            clock /= 2;
        }
        else /* FLL */
        {
            SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
        }
    }
    else
    {
        CLOCK_GetClockFrequency(kBusClock, &clock);
    }
    UART_InitStruct1.srcClock = clock;
    
    /* init pinmux */
    for(i = 0; i < pq->io_offset; i++)
    {
        PORT_PinMuxConfig(pq->io_instance, pq->io_base + i, (PORT_PinMux_Type) pq->mux); 
    }
    
    /* init UART */
    UART_Init(&UART_InitStruct1);
    
    return pq->ip_instance;
}

/**
 * @brief  ����UARTģ����жϻ�DMA����
 * @code
 *      //����UART0ģ�鿪�������жϹ���
 *      UART_ITDMAConfig(HW_UART0, kUART_IT_Rx, true);
 * @endcode
 * @param  instance      :оƬ���ڶ˿�
 *         @arg HW_UART0 :оƬ��UART0�˿�
 *         @arg HW_UART1 :оƬ��UART1�˿�
 *         @arg HW_UART2 :оƬ��UART2�˿�
 *         @arg HW_UART3 :оƬ��UART3�˿�
 *         @arg HW_UART4 :оƬ��UART4�˿�
 *         @arg HW_UART5 :оƬ��UART5�˿�
 * @param  status      :����
 * @param  config: ����ģʽѡ��
 *         @arg kUART_IT_Tx:
 *         @arg kUART_DMA_Tx:
 *         @arg kUART_IT_Rx:
 *         @arg kUART_DMA_Rx:
 * @retval None
 */
void UART_ITDMAConfig(uint32_t instance, UART_ITDMAConfig_Type config, bool status)
{
    /* enable clock gate */
    *((uint32_t*) SIM_UARTClockGateTable[instance].addr) |= SIM_UARTClockGateTable[instance].mask;
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[instance];
    
    switch(config)
    {
        case kUART_IT_Tx:
            (status)?
            (UARTx->C2 |= UART_C2_TIE_MASK):
            (UARTx->C2 &= ~UART_C2_TIE_MASK);
            NVIC_EnableIRQ(UART_IRQnTable[instance]);
            break; 
        case kUART_IT_Rx:
            (status)?
            (UARTx->C2 |= UART_C2_RIE_MASK):
            (UARTx->C2 &= ~UART_C2_RIE_MASK);
            NVIC_EnableIRQ(UART_IRQnTable[instance]);
            break;
        case kUART_DMA_Tx:
            (status)?
            (UARTx->C2 |= UART_C2_TIE_MASK):
            (UARTx->C2 &= ~UART_C2_TIE_MASK);
            if(instance == HW_UART0)
            {
                (status)?
                (UART0->C5 |= UART0_C5_TDMAE_MASK):
                (UART0->C5 &= ~UART0_C5_TDMAE_MASK);
            }
            else
            {
                (status)?
                (UARTx->C4 |= UART_C4_TDMAS_MASK):
                (UARTx->C4 &= ~UART_C4_TDMAS_MASK);
            }
            break;
        case kUART_DMA_Rx:
            (status)?
            (UARTx->C2 |= UART_C2_RIE_MASK):
            (UARTx->C2 &= ~UART_C2_RIE_MASK);
            if(instance == HW_UART0)
            {
                (status)?
                (UART0->C5 |= UART0_C5_RDMAE_MASK):
                (UART0->C5 &= ~UART0_C5_RDMAE_MASK);
            }
            else
            {
                (status)?
                (UARTx->C4 |= UART_C4_RDMAS_MASK):
                (UARTx->C4 &= ~UART_C4_RDMAS_MASK); 
            }
            break;
        default:
            break;
    }
}

/**
 * @brief  ע������жϻص�����
 * @param  instance      :оƬ���ڶ˿�
 *         @arg HW_UART0 :оƬ��UART0�˿�
 *         @arg HW_UART1 :оƬ��UART1�˿�
 *         @arg HW_UART2 :оƬ��UART2�˿�
 *         @arg HW_UART3 :оƬ��UART3�˿�
 *         @arg HW_UART4 :оƬ��UART4�˿�
 *         @arg HW_UART5 :оƬ��UART5�˿�
 * @param AppCBFun: �ص�����ָ�����
 * @retval None
 * @note ���ڴ˺����ľ���Ӧ�������Ӧ��ʵ��
 */
void UART_CallbackRxInstall(uint32_t instance, UART_CallBackRxType AppCBFun)
{
    /* enable clock gate */
    *((uint32_t*) SIM_UARTClockGateTable[instance].addr) |= SIM_UARTClockGateTable[instance].mask;
    if(AppCBFun != NULL)
    {
        UART_CallBackRxTable[instance] = AppCBFun;
    }
}

/**
 * @brief  ע�ᷢ���жϻص�����
 * @param  instance      :оƬ���ڶ˿�
 *         @arg HW_UART0 :оƬ��UART0�˿�
 *         @arg HW_UART1 :оƬ��UART1�˿�
 *         @arg HW_UART2 :оƬ��UART2�˿�
 *         @arg HW_UART3 :оƬ��UART3�˿�
 *         @arg HW_UART4 :оƬ��UART4�˿�
 *         @arg HW_UART5 :оƬ��UART5�˿�
 * @param AppCBFun: �ص�����ָ�����
 * @retval None
 * @note ���ڴ˺����ľ���Ӧ�������Ӧ��ʵ��
 */
void UART_CallbackTxInstall(uint32_t instance, UART_CallBackTxType AppCBFun)
{
    /* enable clock gate */
    *((uint32_t*) SIM_UARTClockGateTable[instance].addr) |= SIM_UARTClockGateTable[instance].mask;
    if(AppCBFun != NULL)
    {
        UART_CallBackTxTable[instance] = AppCBFun;
    }
}

void UART_Init(UART_InitTypeDef* UART_InitStruct)
{
    uint16_t sbr;
    static bool is_fitst_init = true;
    /* enable clock gate */
    *((uint32_t*) SIM_UARTClockGateTable[UART_InitStruct->instance].addr) |= SIM_UARTClockGateTable[UART_InitStruct->instance].mask;
    
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[UART_InitStruct->instance];
    
    /* disable Tx Rx first */
    UARTx->C2 &= ~((UART_C2_TE_MASK)|(UART_C2_RE_MASK));
    /* disable Tx Rx */
    UARTx->C2 &= ~((UART_C2_TE_MASK)|(UART_C2_RE_MASK));
    
    /* config baudrate */
    sbr = UART_InitStruct->srcClock/((UART_InitStruct->baudrate)*16);
    UARTx->BDH &= ~(UART_BDH_SBR_MASK);
    UARTx->BDH |= (sbr>>8) & UART_BDH_SBR_MASK;
    UARTx->BDL = (sbr & UART_BDL_SBR_MASK);
    
    /* enable Tx Rx */
    UARTx->C2 |= ((UART_C2_TE_MASK)|(UART_C2_RE_MASK));
    
    /* link debug instance */
    /* if it's first initalized ,link getc and putc to it */
    if(is_fitst_init)
    {
        UART_DebugInstance = UART_InitStruct->instance;
    }
    is_fitst_init = false;
}

void UART_WriteByte(uint32_t instance, uint16_t ch)
{
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[instance];
    while(!(UARTx->S1 & UART_S1_TDRE_MASK));
    UARTx->D = (uint8_t)ch;
}

uint8_t UART_ReadByte(uint32_t instance, uint16_t *ch)
{
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[instance];
    
    /* clear OverRun */
    //UARTx->S1 |= UART_S1_OR_MASK;
    
    if(UARTx->S1 & UART_S1_RDRF_MASK)
    {
        *ch = (uint8_t)(UARTx->D);	
        return 0; 		  
    }
    return 1;
}

void UART0_IRQHandler(void)
{
    uint16_t ch;
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[HW_UART0];
    /* Tx */
    if((UARTx->S1 & UART_S1_TDRE_MASK) && (UARTx->C2 & UART_C2_TIE_MASK))
    {
        if(UART_CallBackTxTable[HW_UART0])
        {
            UART_CallBackTxTable[HW_UART0](&ch);
        }
        UARTx->D = (uint8_t)ch;
    }
    /* Rx */
    if((UARTx->S1 & UART_S1_RDRF_MASK) && (UARTx->C2 & UART_C2_RIE_MASK))
    {
        ch = (uint8_t)UARTx->D;
        if(UART_CallBackRxTable[HW_UART0])
        {
            UART_CallBackRxTable[HW_UART0](ch);
        }    
    }
}

void UART1_IRQHandler(void)
{
    uint16_t ch;
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[HW_UART1];
    /* Tx */
    if((UARTx->S1 & UART_S1_TDRE_MASK) && (UARTx->C2 & UART_C2_TIE_MASK))
    {
        if(UART_CallBackTxTable[HW_UART1])
        {
            UART_CallBackTxTable[HW_UART1](&ch);
        }
        UARTx->D = (uint8_t)ch;
    }
    /* Rx */
    if((UARTx->S1 & UART_S1_RDRF_MASK) && (UARTx->C2 & UART_C2_RIE_MASK))
    {
        ch = (uint8_t)UARTx->D;
        if(UART_CallBackRxTable[HW_UART1])
        {
            UART_CallBackRxTable[HW_UART1](ch);
        }    
    }
}

void UART2_IRQHandler(void)
{
    uint16_t ch;
    UART_Type * UARTx = (UART_Type*)UART_InstanceTable[HW_UART2];
    /* Tx */
    if((UARTx->S1 & UART_S1_TDRE_MASK) && (UARTx->C2 & UART_C2_TIE_MASK))
    {
        if(UART_CallBackTxTable[HW_UART2])
        {
            UART_CallBackTxTable[HW_UART2](&ch);
        }
        UARTx->D = (uint8_t)ch;
    }
    /* Rx */
    if((UARTx->S1 & UART_S1_RDRF_MASK) && (UARTx->C2 & UART_C2_RIE_MASK))
    {
        ch = (uint8_t)UARTx->D;
        if(UART_CallBackRxTable[HW_UART2])
        {
            UART_CallBackRxTable[HW_UART2](ch);
        }    
    } 
}

