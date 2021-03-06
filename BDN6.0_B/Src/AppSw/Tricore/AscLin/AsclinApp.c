#include "AsclinApp.h"


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
void bsp_UART1_init(void)
{
	/* disable interrupts */ //??????????CUP????????????????????interruptState????????
	IfxCpu_disableInterrupts();

    /* create module config */
    IfxAsclin_Asc_Config UART1_Config;   //????????ascConfig??????????????????asc????
    IfxAsclin_Asc_initModuleConfig(&UART1_Config, &MODULE_ASCLIN1); //????????ASCLIN1??????????????????asc??????

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
	/* disable interrupts */ //??????????CUP????????????????????interruptState????????
	IfxCpu_disableInterrupts();

    /* create module config */
    IfxAsclin_Asc_Config UART2_Config;   //????????ascConfig??????????????????asc????
    IfxAsclin_Asc_initModuleConfig(&UART2_Config, &MODULE_ASCLIN2); //????????ASCLIN1??????????????????asc??????

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


    /* pin configuration */ //????????
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
    IfxAsclin_Asc_Config UART3_Config;   //????????ascConfig??????????????????asc????
    IfxAsclin_Asc_initModuleConfig(&UART3_Config, &MODULE_ASCLIN3); //????????ASCLIN1??????????????????asc??????

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


    /* pin configuration */ //????????
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
uint8 UART1_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART1) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART1);
	}
	return 0;
}
boolean UART1_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART1,data,cnt,TIME_INFINITE);
}
uint8 UART2_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART2) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART2);
	}
	return 0;
}
boolean UART2_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART2,data,cnt,TIME_INFINITE);
}
uint8 UART3_Read_Data(void)
{
	if(IfxAsclin_Asc_getReadCount(&UART3) >0)
	{
		return IfxAsclin_Asc_blockingRead(&UART3);
	}
	return 0;
}
boolean UART3_Write_Data(uint8 *data,Ifx_SizeT *cnt)
{
	return IfxAsclin_Asc_write(&UART3,data,cnt,TIME_INFINITE);
}
void UART3_test(void)
{
	sint16 cnt=0;

	uint8 *data=(uint8 *)UART3.rx->buffer;
	if(uart3_flag)
	{
		cnt = UART3.rx->endIndex;
		uart3_flag=0;
		IfxAsclin_Asc_write(&UART3,data,&cnt,TIME_INFINITE);
	}
}

void sendUARTMessage(char * msg, Ifx_SizeT count)
{
    IfxAsclin_Asc_write(&UART3, msg, &count, TIME_INFINITE);            /* Transfer of data                         */
}
