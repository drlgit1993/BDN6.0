#include "AsclinApp.h"
#include <stdarg.h>
#include <string.h>

IfxAsclin_Asc UART0;
#define UART0_TX_BUFFER_SIZE 64
static uint8 UART0_TxBuffer[UART0_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
#define UART0_RX_BUFFER_SIZE 64
static uint8 UART0_RxBuffer[UART0_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


IfxAsclin_Asc UART1;
#define UART1_TX_BUFFER_SIZE 64
static uint8 UART1_TxBuffer[UART1_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
#define UART1_RX_BUFFER_SIZE 64
static uint8 UART1_RxBuffer[UART1_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


IfxAsclin_Asc UART2;
#define UART2_TX_BUFFER_SIZE 64
static uint8 UART2_TxBuffer[UART2_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
#define UART2_RX_BUFFER_SIZE 64
static uint8 UART2_RxBuffer[UART2_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


IfxAsclin_Asc UART3;
#define UART3_TX_BUFFER_SIZE 512
static uint8 UART3_TxBuffer[UART3_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
#define UART3_RX_BUFFER_SIZE 512
static uint8 UART3_RxBuffer[UART3_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

//static IfxDma_Dma_Channel Dma_Channel_uart3;
#define INTPRIO_DMA_UART3       (10)
#define UART3_DMA_RX_CHANNEL_ID (IfxDma_ChannelId_0)
IfxDma_Dma uart3_dma;


IFX_INTERRUPT(UART0_Tx_IRQHandler, 0, UART0_TX_ISR_PRIORITY);
void UART0_Tx_IRQHandler(void)
{
    IfxAsclin_Asc_isrTransmit(&UART0);
}

IFX_INTERRUPT(UART0_Rx_IRQHandler, 0, UART0_RX_ISR_PRIORITY);
void UART0_Rx_IRQHandler(void)
{
    IfxAsclin_Asc_isrReceive(&UART0);
}
IFX_INTERRUPT(UART0_ER_IRQHandler, 0, UART0_ER_ISR_PRIORITY);
void UART0_ER_IRQHandler(void)
{
    IfxAsclin_Asc_isrError(&UART0);
}

IFX_INTERRUPT(UART1_Tx_IRQHandler, 0, UART1_TX_ISR_PRIORITY);
void UART1_Tx_IRQHandler(void)
{
    IfxAsclin_Asc_isrTransmit(&UART1);
}
IFX_INTERRUPT(UART1_Rx_IRQHandler, 0, UART1_RX_ISR_PRIORITY);
void UART1_Rx_IRQHandler(void)
{
    IfxAsclin_Asc_isrReceive(&UART1);
}
IFX_INTERRUPT(UART1_ER_IRQHandler, 0, UART1_ER_ISR_PRIORITY);
void UART1_ER_IRQHandler(void)
{
    IfxAsclin_Asc_isrError(&UART1);
}

IFX_INTERRUPT(UART2_Tx_IRQHandler, 0, UART2_TX_ISR_PRIORITY);
void UART2_Tx_IRQHandler(void)
{
    IfxAsclin_Asc_isrTransmit(&UART2);
}
IFX_INTERRUPT(UART2_Rx_IRQHandler, 0, UART2_RX_ISR_PRIORITY);
void UART2_Rx_IRQHandler(void)
{
    IfxAsclin_Asc_isrReceive(&UART2);
}
IFX_INTERRUPT(UART2_ER_IRQHandler, 0, UART2_ER_ISR_PRIORITY);
void UART2_ER_IRQHandler(void)
{
    IfxAsclin_Asc_isrError(&UART2);
}

uint8 uart3_flag=0;
IFX_INTERRUPT(UART3_Tx_IRQHandler, 0, UART3_TX_ISR_PRIORITY);
void UART3_Tx_IRQHandler(void)
{
    IfxAsclin_Asc_isrTransmit(&UART3);
}

IFX_INTERRUPT(UART3_Rx_IRQHandler, 0, UART3_RX_ISR_PRIORITY);
void UART3_Rx_IRQHandler(void)
{
    IfxAsclin_Asc_isrReceive(&UART3);
    uart3_flag=1;
}

IFX_INTERRUPT(UART3_ER_IRQHandler, 0, UART3_ER_ISR_PRIORITY);
void UART3_ER_IRQHandler(void)
{
    IfxAsclin_Asc_isrError(&UART3);
}

/*
IFX_INTERRUPT(prio_DMA, 0, INTPRIO_DMA_UART3)
{
	g_correctTransactions ++;
}
*/
void bsp_UART0_init(void)
{
	/* disable interrupts */
	boolean interrupt_state = disableInterrupts();

    /* create module config */
    IfxAsclin_Asc_Config UART0_Config;
    IfxAsclin_Asc_initModuleConfig(&UART0_Config, &MODULE_ASCLIN0);

    /* set the desired baudrate */
    UART0_Config.baudrate.prescaler    = 4;
    UART0_Config.baudrate.baudrate     = 115200; /* FDR values will be calculated in initModule */
    UART0_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    // ISR priorities and interrupt target
    UART0_Config.interrupt.txPriority = UART0_TX_ISR_PRIORITY;
    UART0_Config.interrupt.rxPriority = UART0_RX_ISR_PRIORITY;
    UART0_Config.interrupt.erPriority = UART0_ER_ISR_PRIORITY;
    UART0_Config.interrupt.typeOfService =   IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    UART0_Config.txBuffer = &UART0_TxBuffer;
    UART0_Config.txBufferSize = UART0_TX_BUFFER_SIZE;

    UART0_Config.rxBuffer = &UART0_RxBuffer;
    UART0_Config.rxBufferSize = UART0_RX_BUFFER_SIZE;


    IfxAsclin_Asc_Pins pins =
    {
        NULL,                     IfxPort_InputMode_pullUp,
        &IfxAsclin0_RXA_P14_1_IN, IfxPort_InputMode_pullUp,
        NULL,                     IfxPort_OutputMode_pushPull,
        &IfxAsclin0_TX_P14_0_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };

    UART0_Config.pins = &pins;

    /* initialize module */
    IfxAsclin_Asc_initModule(&UART0, &UART0_Config);

    restoreInterrupts(interrupt_state);
}
void bsp_UART1_init(void)
{
	/* disable interrupts */ //���д��뽫CUP�жϹرղ���״̬����interruptState���б�ʾ
	IfxCpu_disableInterrupts();

    /* create module config */
    IfxAsclin_Asc_Config UART1_Config;   //����һ��ascConfig�Ľṹ�壬���ڱ�ʾasc����
    IfxAsclin_Asc_initModuleConfig(&UART1_Config, &MODULE_ASCLIN1); //�����õ�ASCLIN1����ʼ���ոն����asc�ṹ��

    /* set the desired baudrate */
    UART1_Config.baudrate.prescaler    = 4;
    UART1_Config.baudrate.baudrate     = 115200; /* FDR values will be calculated in initModule */
    UART1_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    // ISR priorities and interrupt target
    UART1_Config.interrupt.txPriority = UART1_TX_ISR_PRIORITY;
    UART1_Config.interrupt.rxPriority = UART1_RX_ISR_PRIORITY;
    UART1_Config.interrupt.erPriority = UART1_ER_ISR_PRIORITY;
    UART1_Config.interrupt.typeOfService =   IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    UART1_Config.txBuffer = &UART1_TxBuffer;
    UART1_Config.txBufferSize = UART1_TX_BUFFER_SIZE;

    UART1_Config.rxBuffer = &UART1_RxBuffer;
    UART1_Config.rxBufferSize = UART1_RX_BUFFER_SIZE;

    const IfxAsclin_Asc_Pins pins = {
        NULL,                     IfxPort_InputMode_pullUp,
        &IfxAsclin1_RXF_P33_13_IN, IfxPort_InputMode_pullUp,
        NULL,                     IfxPort_OutputMode_pushPull,
        &IfxAsclin1_TX_P33_12_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };



    UART1_Config.pins = &pins;

    /* initialize module */
    IfxAsclin_Asc_initModule(&UART1, &UART1_Config);

    IfxCpu_enableInterrupts();
}

void bsp_UART2_init(void)
{
	/* disable interrupts */ //���д��뽫CUP�жϹرղ���״̬����interruptState���б�ʾ
	IfxCpu_disableInterrupts();

    /* create module config */
    IfxAsclin_Asc_Config UART2_Config;   //����һ��ascConfig�Ľṹ�壬���ڱ�ʾasc����
    IfxAsclin_Asc_initModuleConfig(&UART2_Config, &MODULE_ASCLIN2); //�����õ�ASCLIN1����ʼ���ոն����asc�ṹ��

    /* set the desired baudrate */
    UART2_Config.baudrate.prescaler    = 4;
    UART2_Config.baudrate.baudrate     = 115200; /* FDR values will be calculated in initModule */
    UART2_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    // ISR priorities and interrupt target
    UART2_Config.interrupt.txPriority = UART2_TX_ISR_PRIORITY;
    UART2_Config.interrupt.rxPriority = UART2_RX_ISR_PRIORITY;
    UART2_Config.interrupt.erPriority = UART2_ER_ISR_PRIORITY;
    UART2_Config.interrupt.typeOfService =   IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    UART2_Config.txBuffer = &UART2_TxBuffer;
    UART2_Config.txBufferSize = UART2_TX_BUFFER_SIZE;

    UART2_Config.rxBuffer = &UART2_RxBuffer;
    UART2_Config.rxBufferSize = UART2_RX_BUFFER_SIZE;


    /* pin configuration */ //��������
    const IfxAsclin_Asc_Pins pins = {
        NULL,                     IfxPort_InputMode_pullUp,        /* CTS pin not used */
        &IfxAsclin2_RXE_P33_8_IN, IfxPort_InputMode_pullUp,        /* P33_8 Rx pin */
        NULL,                     IfxPort_OutputMode_pushPull,     /* RTS pin not used */
        &IfxAsclin2_TX_P33_9_OUT, IfxPort_OutputMode_pushPull,     /* P33_9 Tx pin */
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    UART2_Config.pins = &pins;

    /* initialize module */
    IfxAsclin_Asc_initModule(&UART2, &UART2_Config);

    IfxCpu_enableInterrupts();
}

//static void bsp_usart3_dma_init(void)
//{
//	/* Initialize an instance of IfxDma_Dma_Config with default values */
//	    IfxDma_Dma_Config dmaConfig;
//	    IfxDma_Dma_initModuleConfig(&dmaConfig, &MODULE_DMA);
//
//	    /* Initialize module */
//	    IfxDma_Dma_initModule(&uart3_dma, &dmaConfig);
//
//	    /* Initial configuration for all channels */
//	    IfxDma_Dma_ChannelConfig cfg;
//	    IfxDma_Dma_initChannelConfig(&cfg, &uart3_dma);
//
//	    /* Following configuration is used by the DMA channel */
//	    cfg.transferCount = 256;
//	    cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
//	    cfg.blockMode = IfxDma_ChannelMove_1;
//
//	    /* DMA completes a full transaction on requests */
//	    cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
//
//	    /* DMA as Interrupt Service Provider */
//	    cfg.hardwareRequestEnabled = TRUE;
//
//	    /* DMA channel stays enabled after one request */
//	    cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
//
//
//	    /*************** Source and destination addresses ***************/
//
//	    /* Source address is not modified after a transfer */
//	    cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
//
//	    /* The element to transfer is always at the same location */
//	    cfg.sourceCircularBufferEnabled = TRUE;
//	    cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
//
//	    /* Copy the elements sequentially next to each others */
//	    cfg.destinationCircularBufferEnabled = FALSE;
//
//
//	    /*************** Channel specific configurations ***************/
//
//	    /* Select the Channel 12, related to the interruption on AscLin RX */
//	    cfg.channelId = (IfxDma_ChannelId) IFX_INTPRIO_ASCLIN3_RX;
//
//	    /* Address of the UART RX FIFO */
//	    cfg.sourceAddress = (uint32) &UART3.asclin->RXDATA.U;
//
//	    /* Address of LMURAM */
//	    cfg.destinationAddress = (uint32)&UART3_RxBuffer;
//	    cfg.channelInterruptEnabled = TRUE;
//
//	    /* DMA triggers an interrupt once the full transaction is done */
//	    cfg.channelInterruptControl = IfxDma_ChannelInterruptControl_thresholdLimitMatch;
//
//	    /* Priority of the channel interrupt trigger */
//	    cfg.channelInterruptPriority = INTPRIO_DMA_UART3;
//
//	    /* Interrupt service provider */
//	    cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;
//
//	    /* Initialize the DMA channel */
//	    IfxDma_Dma_initChannel(&Dma_Channel_uart3, &cfg);
//}

void bsp_UART3_init(void)
{
	//volatile Ifx_SRC_SRCR *src;

    /* create module config */
    IfxAsclin_Asc_Config UART3_Config;   //����һ��ascConfig�Ľṹ�壬���ڱ�ʾasc����
    IfxAsclin_Asc_initModuleConfig(&UART3_Config, &MODULE_ASCLIN3); //�����õ�ASCLIN1����ʼ���ոն����asc�ṹ��

    /* set the desired baudrate */
    UART3_Config.baudrate.prescaler    = 4;
    UART3_Config.baudrate.baudrate     = 115200; /* FDR values will be calculated in initModule */
    UART3_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    // ISR priorities and interrupt target
    UART3_Config.interrupt.txPriority = UART3_TX_ISR_PRIORITY;
    UART3_Config.interrupt.rxPriority = UART3_RX_ISR_PRIORITY;
    UART3_Config.interrupt.erPriority = UART3_ER_ISR_PRIORITY;
    UART3_Config.interrupt.typeOfService =   IfxSrc_Tos_cpu0;

    UART3_Config.txBuffer = &UART3_TxBuffer;
    UART3_Config.txBufferSize = UART3_TX_BUFFER_SIZE;

    UART3_Config.rxBuffer = &UART3_RxBuffer;
    UART3_Config.rxBufferSize = UART3_RX_BUFFER_SIZE;


    /* pin configuration */ //��������
    const IfxAsclin_Asc_Pins pins = {
        NULL,                     IfxPort_InputMode_pullUp,        /* CTS pin not used */
        &IfxAsclin3_RXE_P00_1_IN, IfxPort_InputMode_pullUp,        /* Rx pin */
        NULL,                     IfxPort_OutputMode_pushPull,     /* RTS pin not used */
        &IfxAsclin3_TX_P00_0_OUT, IfxPort_OutputMode_pushPull,     /* Tx pin */
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    UART3_Config.pins = &pins;

    /* initialize module */
    IfxAsclin_Asc_initModule(&UART3, &UART3_Config);
/*
    src = IfxAsclin_getSrcPointerRx(UART3_Config.asclin);

    IfxSrc_init(src,IfxSrc_Tos_dma,IFX_INTPRIO_ASCLIN3_RX);
    IfxAsclin_enableRxFifoFillLevelFlag(UART3_Config.asclin, TRUE);
    IfxSrc_enable(src);

    bsp_usart3_dma_init();
    */
}
uint8 UART0_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART0) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART0);
	}
	return 0;
}
uint8 UART1_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART1) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART1);
	}
	return 0;
}
uint8 UART2_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART2) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART2);
	}
	return 0;
}
uint8 UART3_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART3) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART3);
	}
	return 0;
}

boolean UART0_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART0,data,cnt,TIME_INFINITE);
}

boolean UART1_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART1,data,cnt,TIME_INFINITE);
}
boolean UART2_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART2,data,cnt,TIME_INFINITE);
}
boolean UART3_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART3,data,cnt,TIME_INFINITE);
}

void sendUARTMessage(char * msg, Ifx_SizeT count)
{
    IfxAsclin_Asc_write(&UART3, msg, &count, TIME_INFINITE);            /* Transfer of data                         */
}

/*
  @brief      串口字节输出
  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
  @param      dat             需要发送的字节
  @return     void
  Sample usage:               uart_putchar(UART_0, 0xA5);       // 串口0发送0xA5
*/
void uart_putchar(uint8 dat)
{
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(&UART0, &dat, &count, TIME_INFINITE);
}
/*
  @brief      串口发送字符串
  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
  @param      *str            要发送的字符串地址
  @return     void
  Sample usage:               uart_putstr(UART_0,"i lvoe you");
*/
void uart_putstr(const uint8 *str)
{
    while(*str)
    {
        uart_putchar(*str++);
    }
}
void uart_putbuff(uint8 *buff, uint32 len)
{
	while(len)
	{
		uart_putchar(*buff);
		len--;
		buff++;
	}
}
/*
  @brief      读取串口接收的数据（whlie等待）
  @param      *dat            接收数据的地址
  @return     void
  Sample usage:               uint8 dat; uart_getchar(UART_0,&dat);       // 接收串口0数据  存在在dat变量里
*/
void uart_getchar(uint8 *dat)
{
	while(!IfxAsclin_Asc_getReadCount(&UART0));
	*dat = IfxAsclin_Asc_blockingRead(&UART0);
}

/*
  @brief      读取串口接收的数据（查询接收）
  @param      *dat            接收数据的地址
  @return     uint8           1：接收成功   0：未接收到数据
  Sample usage:               uint8 dat; uart_query(UART_0,&dat);       // 接收串口0数据  存在在dat变量里
*/
uint8 uart_query(uint8 *dat)
{
	if(IfxAsclin_Asc_getReadCount(&UART0) >0)
	{
		*dat = IfxAsclin_Asc_blockingRead(&UART0);
		return 1;
	}
    return 0;
}

/*
  @brief      重定义printf 到串口
  @param      ch      需要打印的字节
  @param      stream  数据流
  @note       此函数由编译器自带库里的printf所调用
*/
int fputc(int ch, FILE *stream)
{
    uart_putchar((char)ch);
    return(ch);
}

uint8 number_conversion_ascii(uint32 dat, int8 *p, uint8 neg_type, uint8 radix)
{
    int32   neg_dat;
    uint32  pos_dat;
    uint8   temp_data = 0;
    uint8   valid_num = 0;

    if(neg_type)
    {
        neg_dat = (int32)dat;
        if(neg_dat<0)   neg_dat = -neg_dat;
        while(1)
        {
            *p = (char)(neg_dat%radix + '0');
            neg_dat = neg_dat/radix;
            valid_num++;

            if(!neg_dat) break;
            p++;
        }
    }
    else
    {
        pos_dat = dat;
        while(1)
        {
            temp_data = pos_dat%radix;
            if(10 <= temp_data) temp_data += 'A'-10;
            else                temp_data += '0';

            *p = temp_data;

            pos_dat = pos_dat/radix;
            valid_num++;

            if(!pos_dat) break;
            p++;
        }
    }
    return valid_num;
}

void printf_reverse_order(int8 *d_buff, uint32 len)
{
    uint32 i;
    int8  temp_data;
    for(i=0;i<len/2;i++)
    {
        temp_data = d_buff[len-1-i];
        d_buff[len-1-i] = d_buff[i];
        d_buff[i] = temp_data;
    }
}
void uart0_printf(const int8 *format, ...)
{

    va_list arg;
	va_start(arg, format);

	while (*format)
	{
		int8 ret = *format;
		if (ret == '%')
		{
			switch (*++format)
			{
                case 'a':// 十六进制p计数法输出浮点数 暂未实现
                {


                }break;


                case 'c':// 一个字符
                {
                    int8 ch = (int8)va_arg(arg, uint32);
                    uart_putchar((int8)ch);

                }break;


                case 'd':
                case 'i':// 有符号十进制整数
                {
                    int8 vstr[33];
                    int32 ival = (int32)va_arg(arg, int32);
                    uint8 vlen = number_conversion_ascii((uint32)ival, vstr, 1, 10);
                    if(ival<0)
                    	{
                    	   uart_putchar('-');
                    	}
                    printf_reverse_order(vstr,vlen);
                    uart_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'f':// 浮点数，输出小数点后六位  不能指定输出精度
                case 'F':// 浮点数，输出小数点后六位  不能指定输出精度
                {
                    int8 vstr[33];
                    double ival = (double)va_arg(arg, double);
                    uint8 vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
                    if(ival<0)  uart_putchar('-');
                    printf_reverse_order(vstr,vlen);
                    uart_putbuff((uint8 *)vstr,vlen);
                    uart_putchar('.');

                    ival = ((double)ival - (int32)ival)*1000000;
                    vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
				      while(6>vlen)
                    {
                        vstr[vlen] = '0';
                        vlen++;
                    }
                    printf_reverse_order(vstr,vlen);
                    uart_putbuff((uint8 *)vstr,vlen);
                    break;
                }

                case 'u':// 无符号十进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 10);
                    printf_reverse_order(vstr,vlen);
                    uart_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'o':// 无符号八进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 8);
                    printf_reverse_order(vstr,vlen);
                    uart_putbuff((uint8 *)vstr,vlen);

                }break;

                case 'x':// 无符号十六进制整数
                case 'X':// 无符号十六进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,vlen);
                    uart_putbuff((uint8 *)vstr,vlen);
                }break;


                case 's':// 字符串
                {
                    int8 *pc = va_arg(arg, int8 *);
                    while (*pc)
                    {
                        uart_putchar((int8)(*pc));
                        pc++;
                    }
                }break;

                case 'p':// 以16进制形式输出指针
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,8);
                    uart_putbuff((uint8 *)vstr,8);

                }break;


                case '%':// 输出字符%
                {
                    uart_putchar('%');
                }break;

                default:break;
			}
		}
		else
		{
			uart_putchar((int8)(*format));
		}
		format++;
	}
	va_end(arg);
}
