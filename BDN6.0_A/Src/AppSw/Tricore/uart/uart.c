#include <stdarg.h>
#include <string.h>
#include <uart/uart.h>

#define __uart_Dma_ChannelIncrementCircular(size)         IfxDma_ChannelIncrementCircular_##size
#define uart_Dma_ChannelIncrementCircular(size)           __uart_Dma_ChannelIncrementCircular(size)

/***********************************************UART0***********************************************************/
#define UART0_TX_BUFFER_SIZE 64
#define UART0_RX_BUFFER_SIZE 64

static uint8 UART0_TxBuffer[UART0_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 UART0_RxBuffer[UART0_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

static IfxAsclin_Asc UART0;
static uint16 uart0_cnt_head = 0;
static uint16 uart0_cnt_tail = 0;

#if (USR_UART0_RX_DMA==1)
#define UART0_DMA_RX_BUFFER_SIZE                           1024

static IfxDma_Dma_Channel uart0_rx_Dma_Channel;
static uint8 UART0_DMA_RxBuffer[UART0_DMA_RX_BUFFER_SIZE]  IFX_ALIGN(UART0_DMA_RX_BUFFER_SIZE);
#endif

#if (USR_UART0_TX_DMA==1)
#define UART0_DMA_TX_BUFFER_SIZE                           1024
static IfxDma_Dma_Channel uart0_tx_Dma_Channel;
static uint8 UART0_DMA_TxBuffer[UART0_DMA_TX_BUFFER_SIZE]  IFX_ALIGN(4);
#endif

IFX_INTERRUPT(UART0_Tx_IRQHandler, 0, UART0_TX_ISR_PRIORITY);
void UART0_Tx_IRQHandler(void)
{
	 IfxAsclin_Asc_isrTransmit(&UART0);
}
#if(USR_UART0_TX_DMA==1)
IFX_INTERRUPT(UART0_DMA_Tx_IRQHandler, 0, UART0_TX_DMA_ISR_PRIORITY);
void UART0_DMA_Tx_IRQHandler(void)
{
	 //IfxDma_disableChannelTransaction(&MODULE_DMA,uart0_tx_Dma_Channel.channelId);
	 IfxDma_clearChannelInterrupt(&MODULE_DMA,uart0_tx_Dma_Channel.channelId);
}
#endif
IFX_INTERRUPT(UART0_DMA_Rx_IRQHandler, 0, UART0_RX_DMA_ISR_PRIORITY);
void UART0_DMA_Rx_IRQHandler(void)
{
	IfxCpu_enableInterrupts();
	uart0_cnt_tail = UART0_DMA_RX_BUFFER_SIZE - uart0_rx_Dma_Channel.channel->CHCSR.B.TCOUNT;
}
IFX_INTERRUPT(UART0_ER_IRQHandler, 0, UART0_ER_ISR_PRIORITY);
void UART0_ER_IRQHandler(void)
{
    IfxAsclin_Asc_isrError(&UART0);
}
/***************************************************************************************************************/

/***********************************************UART1***********************************************************/

#define UART1_TX_BUFFER_SIZE 64
#define UART1_RX_BUFFER_SIZE 64

static uint8 UART1_TxBuffer[UART1_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 UART1_RxBuffer[UART1_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


static IfxAsclin_Asc UART1;
static uint16 uart1_cnt_head = 0;
static uint16 uart1_cnt_tail = 0;

#if (USR_UART1_RX_DMA==1)
#define UART1_DMA_RX_BUFFER_SIZE                           1024

static IfxDma_Dma_Channel uart1_rx_Dma_Channel;
static uint8 UART1_DMA_RxBuffer[UART1_DMA_RX_BUFFER_SIZE]  IFX_ALIGN(UART1_DMA_RX_BUFFER_SIZE);
#endif

#if (USR_UART1_TX_DMA==1)
#define UART1_DMA_TX_BUFFER_SIZE                           1024
static IfxDma_Dma_Channel uart1_tx_Dma_Channel;
static uint8 UART1_DMA_TxBuffer[UART1_DMA_TX_BUFFER_SIZE]  IFX_ALIGN(4);
#endif

IFX_INTERRUPT(UART1_Tx_IRQHandler, 0, UART1_TX_ISR_PRIORITY);
void UART1_Tx_IRQHandler(void)
{
	 IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&UART1);
}
IFX_INTERRUPT(UART1_DMA_Rx_IRQHandler, 0, UART1_RX_DMA_ISR_PRIORITY);
void UART1_DMA_Rx_IRQHandler(void)
{
	 IfxCpu_enableInterrupts();
	 uart1_cnt_tail = UART1_DMA_RX_BUFFER_SIZE - uart1_rx_Dma_Channel.channel->CHCSR.B.TCOUNT;
}
IFX_INTERRUPT(UART1_ER_IRQHandler, 0, UART1_ER_ISR_PRIORITY);
void UART1_ER_IRQHandler(void)
{
	 IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&UART1);
}
/***************************************************************************************************************/

/***********************************************UART2***********************************************************/

#define UART2_TX_BUFFER_SIZE 64
#define UART2_RX_BUFFER_SIZE 64

static uint8 UART2_TxBuffer[UART2_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 UART2_RxBuffer[UART2_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

static IfxAsclin_Asc UART2;
static uint16 uart2_cnt_head = 0;
static uint16 uart2_cnt_tail = 0;

#if (USR_UART2_RX_DMA==1)
#define UART2_DMA_RX_BUFFER_SIZE                           1024

static IfxDma_Dma_Channel uart2_rx_Dma_Channel;
static uint8 UART2_DMA_RxBuffer[UART1_DMA_RX_BUFFER_SIZE]  IFX_ALIGN(UART2_DMA_RX_BUFFER_SIZE);
#endif

#if (USR_UART2_TX_DMA==1)
#define UART2_DMA_TX_BUFFER_SIZE                           1024
static IfxDma_Dma_Channel uart2_tx_Dma_Channel;
static uint8 UART2_DMA_TxBuffer[UART2_DMA_TX_BUFFER_SIZE]  IFX_ALIGN(4);
#endif

IFX_INTERRUPT(UART2_Tx_IRQHandler, 0, UART2_TX_ISR_PRIORITY);
void UART2_Tx_IRQHandler(void)
{
	 IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&UART2);
}
IFX_INTERRUPT(UART2_DMA_Rx_IRQHandler, 0, UART2_RX_DMA_ISR_PRIORITY);
void UART2_DMA_Rx_IRQHandler(void)
{
	IfxCpu_enableInterrupts();
    uart2_cnt_tail = UART2_DMA_RX_BUFFER_SIZE - uart2_rx_Dma_Channel.channel->CHCSR.B.TCOUNT;
}
IFX_INTERRUPT(UART2_ER_IRQHandler, 0, UART2_ER_ISR_PRIORITY);
void UART2_ER_IRQHandler(void)
{
	 IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&UART2);
}
/***************************************************************************************************************/

/***********************************************UART3***********************************************************/
#define UART3_TX_BUFFER_SIZE 64
#define UART3_RX_BUFFER_SIZE 64

static uint8 UART3_TxBuffer[UART3_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 UART3_RxBuffer[UART3_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

static IfxAsclin_Asc UART3;
static uint16 uart3_cnt_head = 0;
static uint16 uart3_cnt_tail = 0;

#if (USR_UART3_RX_DMA==1)
#define UART3_DMA_RX_BUFFER_SIZE                           1024

static IfxDma_Dma_Channel uart3_rx_Dma_Channel;
static uint8 UART3_DMA_RxBuffer[UART3_DMA_RX_BUFFER_SIZE]  IFX_ALIGN(UART3_DMA_RX_BUFFER_SIZE);
#endif

#if (USR_UART3_TX_DMA==1)
#define UART3_DMA_TX_BUFFER_SIZE                           1024
static IfxDma_Dma_Channel uart3_tx_Dma_Channel;
static uint8 UART3_DMA_TxBuffer[UART3_DMA_TX_BUFFER_SIZE]  IFX_ALIGN(4);
#endif

IFX_INTERRUPT(UART3_Tx_IRQHandler, 0, UART3_TX_ISR_PRIORITY);
void UART3_Tx_IRQHandler(void)
{
    IfxAsclin_Asc_isrTransmit(&UART3);
}
#if(USR_UART3_TX_DMA==1)
IFX_INTERRUPT(UART3_DMA_Tx_IRQHandler, 0, UART3_TX_DMA_ISR_PRIORITY);
void UART3_DMA_Tx_IRQHandler(void)
{
	 IfxDma_disableChannelTransaction(&MODULE_DMA,uart3_tx_Dma_Channel.channelId);
	 IfxDma_clearChannelInterrupt(&MODULE_DMA,uart3_tx_Dma_Channel.channelId);
}
#endif
#if(USR_UART3_RX_DMA==1)
IFX_INTERRUPT(UART3_DMA_Rx_IRQHandler, 0, UART3_RX_DMA_ISR_PRIORITY);
void UART3_DMA_Rx_IRQHandler(void)
{
	IfxCpu_enableInterrupts();
	uart3_cnt_tail = UART3_DMA_RX_BUFFER_SIZE - uart3_rx_Dma_Channel.channel->CHCSR.B.TCOUNT;
}
#endif
IFX_INTERRUPT(UART3_ER_IRQHandler, 0, UART3_ER_ISR_PRIORITY);
void UART3_ER_IRQHandler(void)
{
	 IfxCpu_enableInterrupts();
    IfxAsclin_Asc_isrError(&UART3);
}
/***************************************************************************************************************/


#if (USR_UART0_RX_DMA==1)
static void bsp_usart0_rx_dma_init(void)
{
   IfxDma_Dma uart0_rx_dma;
   uart0_rx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart0_rx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART0_RX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART0.asclin->RXDATA.U;
   channel_cfg.destinationAddress = (uint32)&UART0_DMA_RxBuffer;
   channel_cfg.transferCount = UART0_DMA_RX_BUFFER_SIZE;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_oneTransferPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = TRUE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = uart_Dma_ChannelIncrementCircular(UART0_DMA_RX_BUFFER_SIZE);
   channel_cfg.sourceCircularBufferEnabled = TRUE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = TRUE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_transferCountDecremented;
   channel_cfg.channelInterruptPriority = UART0_RX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart0_rx_Dma_Channel, &channel_cfg);
}
void UART0_Read_Data(unsigned char *dest,unsigned short *rlen)
{
	uint16 len=0;

	if(uart0_cnt_head == uart0_cnt_tail)
	{
		*rlen=0;
	    return ;
	}

	if(uart0_cnt_tail > uart0_cnt_head)
	{
		  len=uart0_cnt_tail-uart0_cnt_head;
		  memcpy(dest,UART0_DMA_RxBuffer + uart0_cnt_head,len);
	}
	else
	{
		 len=UART0_DMA_RX_BUFFER_SIZE-uart0_cnt_head;
		  memcpy(dest,UART0_DMA_RxBuffer + uart0_cnt_head,len);

		  memcpy(dest+len,UART0_DMA_RxBuffer,uart0_cnt_tail);
		  len += uart0_cnt_tail;
	}
	uart0_cnt_head=uart0_cnt_tail;
	*rlen=len;
}
#endif

#if (USR_UART0_TX_DMA==1)
static void bsp_usart0_tx_dma_init(void)
{
   IfxDma_Dma uart0_tx_dma;
   uart0_tx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart0_tx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART0_TX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART0_DMA_TxBuffer;
   channel_cfg.destinationAddress = (uint32) &UART0.asclin->TXDATA.U;
   channel_cfg.transferCount = 0;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_single;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = FALSE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.sourceCircularBufferEnabled = FALSE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = FALSE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_thresholdLimitMatch;
   channel_cfg.channelInterruptPriority = UART0_TX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart0_tx_Dma_Channel, &channel_cfg);
}
void UART0_Write_Data_DMA(uint8 *data,uint16 cnt)
{
	memcpy(UART0_DMA_TxBuffer,data,cnt);
	Ifx_DMA_CH *ch=uart0_tx_Dma_Channel.channel;
	ch->SADR.U = (uint32) &UART0_DMA_TxBuffer;
	ch->CHCFGR.B.TREL = cnt;

	IfxDma_enableChannelTransaction(&MODULE_DMA,uart0_tx_Dma_Channel.channelId);
	MODULE_ASCLIN0.FLAGSSET.B.TFLS=1;
}
#endif
void bsp_UART0_init(void)
{
	volatile Ifx_SRC_SRCR *src;
    IfxAsclin_Asc_Config UART0_Config;
    IfxAsclin_Asc_initModuleConfig(&UART0_Config, &MODULE_ASCLIN0);

    UART0_Config.baudrate.prescaler    = 4;
    UART0_Config.baudrate.baudrate     = UART1_BAUDRATE;
    UART0_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    // ISR priorities and interrupt target
    UART0_Config.interrupt.txPriority = UART0_TX_ISR_PRIORITY;
    UART0_Config.interrupt.rxPriority = UART0_RX_ISR_PRIORITY;
    UART0_Config.interrupt.erPriority = UART0_ER_ISR_PRIORITY;
    UART0_Config.interrupt.typeOfService =  IfxSrc_Tos_cpu0;

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

    IfxAsclin_Asc_initModule(&UART0, &UART0_Config);

#if (USR_UART0_RX_DMA==1)
	src = IfxAsclin_getSrcPointerRx(UART0_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART0_RX_ISR_PRIORITY);

	IfxAsclin_enableRxFifoFillLevelFlag(UART0_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart0_rx_dma_init();
#endif

#if (USR_UART0_TX_DMA==1)
	src = IfxAsclin_getSrcPointerTx(UART0_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART0_TX_ISR_PRIORITY);

	IfxAsclin_enableTxFifoFillLevelFlag(UART0_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart0_tx_dma_init();
#endif
}


#if (USR_UART1_RX_DMA==1)
static void bsp_usart1_rx_dma_init(void)
{
   IfxDma_Dma uart1_rx_dma;
   uart1_rx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart1_rx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART1_RX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART1.asclin->RXDATA.U;
   channel_cfg.destinationAddress = (uint32)&UART1_DMA_RxBuffer;
   channel_cfg.transferCount = UART1_DMA_RX_BUFFER_SIZE;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_oneTransferPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = TRUE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = uart_Dma_ChannelIncrementCircular(UART1_DMA_RX_BUFFER_SIZE);
   channel_cfg.sourceCircularBufferEnabled = TRUE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = TRUE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_transferCountDecremented;
   channel_cfg.channelInterruptPriority = UART1_RX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart1_rx_Dma_Channel, &channel_cfg);
}
void UART1_Read_Data(unsigned char *dest,unsigned short *rlen)
{
	uint16 len=0;

	if(uart1_cnt_head == uart1_cnt_tail)
	{
		*rlen=0;
	    return ;
	}

	if(uart1_cnt_tail > uart1_cnt_head)
	{
		  len=uart1_cnt_tail-uart1_cnt_head;
		  memcpy(dest,UART1_DMA_RxBuffer + uart1_cnt_head,len);
	}
	else
	{
		 len=UART1_DMA_RX_BUFFER_SIZE-uart1_cnt_head;
		  memcpy(dest,UART1_DMA_RxBuffer + uart1_cnt_head,len);

		  memcpy(dest+len,UART1_DMA_RxBuffer,uart1_cnt_tail);
		  len += uart1_cnt_tail;
	}
	uart1_cnt_head=uart1_cnt_tail;
	*rlen=len;
}
#endif

#if (USR_UART1_TX_DMA==1)
static void bsp_usart1_tx_dma_init(void)
{
   IfxDma_Dma uart1_tx_dma;
   uart1_tx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart1_tx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART1_TX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART1_DMA_TxBuffer;
   channel_cfg.destinationAddress = (uint32) &UART1.asclin->TXDATA.U;
   channel_cfg.transferCount = 0;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_single;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = FALSE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.sourceCircularBufferEnabled = FALSE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = FALSE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_thresholdLimitMatch;
   channel_cfg.channelInterruptPriority = UART1_TX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart1_tx_Dma_Channel, &channel_cfg);
}
void UART1_Write_Data_DMA(uint8 *data,uint16 cnt)
{
	memcpy(UART1_DMA_TxBuffer,data,cnt);
	Ifx_DMA_CH *ch=uart1_tx_Dma_Channel.channel;
	ch->SADR.U = (uint32) &UART1_DMA_TxBuffer;
	ch->CHCFGR.B.TREL = cnt;

	IfxDma_enableChannelTransaction(&MODULE_DMA,uart1_tx_Dma_Channel.channelId);
	MODULE_ASCLIN1.FLAGSSET.B.TFLS=1;
}
#endif
void bsp_UART1_init(void)
{
	volatile Ifx_SRC_SRCR *src;

    IfxAsclin_Asc_Config UART1_Config;
    IfxAsclin_Asc_initModuleConfig(&UART1_Config, &MODULE_ASCLIN1);

    UART1_Config.baudrate.prescaler    = 4;
    UART1_Config.baudrate.baudrate     = UART1_BAUDRATE;
    UART1_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    UART1_Config.interrupt.txPriority = UART1_TX_ISR_PRIORITY;
    UART1_Config.interrupt.rxPriority = UART1_RX_ISR_PRIORITY;
    UART1_Config.interrupt.erPriority = UART1_ER_ISR_PRIORITY;
    UART1_Config.interrupt.typeOfService =   IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    UART1_Config.txBuffer = &UART1_TxBuffer;
    UART1_Config.txBufferSize = UART1_TX_BUFFER_SIZE;

    UART1_Config.rxBuffer = &UART1_RxBuffer;
    UART1_Config.rxBufferSize = UART1_RX_BUFFER_SIZE;

    const IfxAsclin_Asc_Pins pins =
    {
        NULL,                     IfxPort_InputMode_pullUp,
        &IfxAsclin1_RXF_P33_13_IN, IfxPort_InputMode_pullUp,
        NULL,                     IfxPort_OutputMode_pushPull,
        &IfxAsclin1_TX_P33_12_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };

    UART1_Config.pins = &pins;

    IfxAsclin_Asc_initModule(&UART1, &UART1_Config);

    IfxCpu_enableInterrupts();

#if (USR_UART1_RX_DMA==1)
	src = IfxAsclin_getSrcPointerRx(UART1_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART1_RX_ISR_PRIORITY);

	IfxAsclin_enableRxFifoFillLevelFlag(UART1_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart1_rx_dma_init();
#endif

#if (USR_UART1_TX_DMA==1)
	src = IfxAsclin_getSrcPointerTx(UART1_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART1_TX_ISR_PRIORITY);

	IfxAsclin_enableTxFifoFillLevelFlag(UART1_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart1_tx_dma_init();
#endif
}


#if (USR_UART2_RX_DMA==1)
static void bsp_usart2_rx_dma_init(void)
{
   IfxDma_Dma uart2_rx_dma;
   uart2_rx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart2_rx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART2_RX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART2.asclin->RXDATA.U;
   channel_cfg.destinationAddress = (uint32)&UART2_DMA_RxBuffer;
   channel_cfg.transferCount = UART2_DMA_RX_BUFFER_SIZE;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_oneTransferPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = TRUE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = uart_Dma_ChannelIncrementCircular(UART2_DMA_RX_BUFFER_SIZE);
   channel_cfg.sourceCircularBufferEnabled = TRUE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = TRUE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_transferCountDecremented;
   channel_cfg.channelInterruptPriority = UART2_RX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart2_rx_Dma_Channel, &channel_cfg);
}
void UART2_Read_Data(unsigned char *dest,unsigned short *rlen)
{
	uint16 len=0;

	if(uart2_cnt_head == uart2_cnt_tail)
	{
		*rlen=0;
	    return ;
	}

	if(uart2_cnt_tail > uart2_cnt_head)
	{
		  len=uart2_cnt_tail-uart2_cnt_head;
		  memcpy(dest,UART2_DMA_RxBuffer + uart2_cnt_head,len);
	}
	else
	{
		 len=UART2_DMA_RX_BUFFER_SIZE-uart2_cnt_head;
		  memcpy(dest,UART2_DMA_RxBuffer + uart2_cnt_head,len);

		  memcpy(dest+len,UART2_DMA_RxBuffer,uart2_cnt_tail);
		  len += uart2_cnt_tail;
	}
	uart2_cnt_head=uart2_cnt_tail;
	*rlen=len;
}
#endif

#if (USR_UART2_TX_DMA==1)
static void bsp_usart2_tx_dma_init(void)
{
   IfxDma_Dma uart2_tx_dma;
   uart2_tx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart2_tx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART2_TX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART2_DMA_TxBuffer;
   channel_cfg.destinationAddress = (uint32) &UART2.asclin->TXDATA.U;
   channel_cfg.transferCount = 0;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_single;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = FALSE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.sourceCircularBufferEnabled = FALSE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = FALSE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_thresholdLimitMatch;
   channel_cfg.channelInterruptPriority = UART2_TX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart2_tx_Dma_Channel, &channel_cfg);
}
void UART2_Write_Data_DMA(uint8 *data,uint16 cnt)
{
	memcpy(UART2_DMA_TxBuffer,data,cnt);
	Ifx_DMA_CH *ch=uart2_tx_Dma_Channel.channel;
	ch->SADR.U = (uint32) &UART2_DMA_TxBuffer;
	ch->CHCFGR.B.TREL = cnt;

	IfxDma_enableChannelTransaction(&MODULE_DMA,uart2_tx_Dma_Channel.channelId);
	MODULE_ASCLIN2.FLAGSSET.B.TFLS=1;
}
#endif
void bsp_UART2_init(void)
{
	volatile Ifx_SRC_SRCR *src;

    IfxAsclin_Asc_Config UART2_Config;
    IfxAsclin_Asc_initModuleConfig(&UART2_Config, &MODULE_ASCLIN2);

    UART2_Config.baudrate.prescaler    = 4;
    UART2_Config.baudrate.baudrate     = UART2_BAUDRATE;
    UART2_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    UART2_Config.interrupt.txPriority = UART2_TX_ISR_PRIORITY;
    UART2_Config.interrupt.rxPriority = UART2_RX_ISR_PRIORITY;
    UART2_Config.interrupt.erPriority = UART2_ER_ISR_PRIORITY;
    UART2_Config.interrupt.typeOfService =   IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    UART2_Config.txBuffer = &UART2_TxBuffer;
    UART2_Config.txBufferSize = UART2_TX_BUFFER_SIZE;

    UART2_Config.rxBuffer = &UART2_RxBuffer;
    UART2_Config.rxBufferSize = UART2_RX_BUFFER_SIZE;

    const IfxAsclin_Asc_Pins pins = {
        NULL,                     IfxPort_InputMode_pullUp,
        &IfxAsclin2_RXE_P33_8_IN, IfxPort_InputMode_pullUp,
        NULL,                     IfxPort_OutputMode_pushPull,
        &IfxAsclin2_TX_P33_9_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    UART2_Config.pins = &pins;

    IfxAsclin_Asc_initModule(&UART2, &UART2_Config);

#if (USR_UART2_RX_DMA==1)
	src = IfxAsclin_getSrcPointerRx(UART2_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART2_RX_ISR_PRIORITY);

	IfxAsclin_enableRxFifoFillLevelFlag(UART2_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart2_rx_dma_init();
#endif

#if (USR_UART2_TX_DMA==1)
	src = IfxAsclin_getSrcPointerTx(UART2_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART2_TX_ISR_PRIORITY);

	IfxAsclin_enableTxFifoFillLevelFlag(UART2_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart2_tx_dma_init();
#endif
}


#if (USR_UART3_RX_DMA==1)
static void bsp_usart3_rx_dma_init(void)
{
   /* Initialize module */
   IfxDma_Dma uart3_rx_dma;
   uart3_rx_dma.dma = &MODULE_DMA;

   /* Initial configuration for all channels */
   IfxDma_Dma_ChannelConfig cfg;
   IfxDma_Dma_initChannelConfig(&cfg, &uart3_rx_dma);

   cfg.channelId = (IfxDma_ChannelId) UART3_RX_ISR_PRIORITY;
   cfg.sourceAddress = (uint32) &UART3.asclin->RXDATA.U;
   cfg.destinationAddress = (uint32)&UART3_DMA_RxBuffer;
   cfg.transferCount = UART3_DMA_RX_BUFFER_SIZE;
   cfg.blockMode = IfxDma_ChannelMove_1;
   cfg.requestMode = IfxDma_ChannelRequestMode_oneTransferPerRequest;
   cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
   cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   cfg.hardwareRequestEnabled = TRUE;
   cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   cfg.destinationAddressCircularRange = uart_Dma_ChannelIncrementCircular(UART3_DMA_RX_BUFFER_SIZE);
   cfg.sourceCircularBufferEnabled = TRUE;
   cfg.destinationCircularBufferEnabled = TRUE;
   cfg.channelInterruptEnabled = TRUE;
   cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_transferCountDecremented;
   cfg.channelInterruptPriority = UART3_RX_DMA_ISR_PRIORITY;
   cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart3_rx_Dma_Channel, &cfg);
}
void UART3_Read_Data(unsigned char *dest, unsigned short *rlen)
{
	uint16 len=0;

	if(uart3_cnt_head == uart3_cnt_tail)
	{
		*rlen=0;
	    return ;
	}

	if(uart3_cnt_tail > uart3_cnt_head)
	{
		  len=uart3_cnt_tail-uart3_cnt_head;
		  memcpy(dest,UART3_DMA_RxBuffer + uart3_cnt_head,len);
	}
	else
	{
		 len=UART3_DMA_RX_BUFFER_SIZE-uart3_cnt_head;
		  memcpy(dest,UART3_DMA_RxBuffer + uart3_cnt_head,len);

		  memcpy(dest+len,UART3_DMA_RxBuffer,uart3_cnt_tail);
		  len += uart3_cnt_tail;
	}
	uart3_cnt_head=uart3_cnt_tail;
	*rlen=len;
}
#endif

#if (USR_UART3_TX_DMA==1)
static void bsp_usart3_tx_dma_init(void)
{
   IfxDma_Dma uart3_tx_dma;
   uart3_tx_dma.dma = &MODULE_DMA;

   IfxDma_Dma_ChannelConfig channel_cfg;
   IfxDma_Dma_initChannelConfig(&channel_cfg, &uart3_tx_dma);

   channel_cfg.channelId = (IfxDma_ChannelId) UART3_TX_ISR_PRIORITY;
   channel_cfg.sourceAddress = (uint32) &UART3_DMA_TxBuffer;
   channel_cfg.destinationAddress = (uint32) &UART3.asclin->TXDATA.U;
   channel_cfg.transferCount = 0;
   channel_cfg.blockMode = IfxDma_ChannelMove_1;
   channel_cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
   channel_cfg.operationMode = IfxDma_ChannelOperationMode_single;
   channel_cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
   channel_cfg.hardwareRequestEnabled = FALSE;
   channel_cfg.sourceAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.sourceAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.destinationAddressIncrementStep = IfxDma_ChannelIncrementStep_1;
   channel_cfg.destinationAddressIncrementDirection =IfxDma_ChannelIncrementDirection_positive;
   channel_cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
   channel_cfg.sourceCircularBufferEnabled = FALSE;
   channel_cfg.destinationCircularBufferEnabled = TRUE;
   channel_cfg.channelInterruptEnabled = FALSE;
   channel_cfg.channelInterruptControl =IfxDma_ChannelInterruptControl_thresholdLimitMatch;
   channel_cfg.channelInterruptPriority = UART3_TX_DMA_ISR_PRIORITY;
   channel_cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;

   IfxDma_Dma_initChannel(&uart3_tx_Dma_Channel, &channel_cfg);
}
void UART3_Write_Data_DMA(uint8 *data,uint16 cnt)
{
	memcpy(UART3_DMA_TxBuffer,data,cnt);
	Ifx_DMA_CH *ch=uart3_tx_Dma_Channel.channel;
	ch->SADR.U = (uint32) &UART3_DMA_TxBuffer;
	ch->CHCFGR.B.TREL = cnt;

	IfxDma_enableChannelTransaction(&MODULE_DMA,uart3_tx_Dma_Channel.channelId);
	MODULE_ASCLIN3.FLAGSSET.B.TFLS=1;
}
#endif
void bsp_UART3_init(void)
{
	volatile Ifx_SRC_SRCR *src;

    IfxAsclin_Asc_Config UART3_Config;
    IfxAsclin_Asc_initModuleConfig(&UART3_Config, &MODULE_ASCLIN3);

    UART3_Config.baudrate.prescaler    = 4;
    UART3_Config.baudrate.baudrate     = UART3_BAUDRATE;
    UART3_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;
    UART3_Config.interrupt.txPriority = UART3_TX_ISR_PRIORITY;
    UART3_Config.interrupt.rxPriority = UART3_RX_ISR_PRIORITY;
    UART3_Config.interrupt.erPriority = UART3_ER_ISR_PRIORITY;
    UART3_Config.interrupt.typeOfService =   IfxSrc_Tos_cpu0;

    UART3_Config.txBuffer = &UART3_TxBuffer;
    UART3_Config.txBufferSize = UART3_TX_BUFFER_SIZE;

    UART3_Config.rxBuffer = &UART3_RxBuffer;
    UART3_Config.rxBufferSize = UART3_RX_BUFFER_SIZE;

    const IfxAsclin_Asc_Pins pins = {
        NULL,                     IfxPort_InputMode_pullUp,
        &IfxAsclin3_RXE_P00_1_IN, IfxPort_InputMode_pullUp,
        NULL,                     IfxPort_OutputMode_pushPull,
        &IfxAsclin3_TX_P00_0_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    UART3_Config.pins = &pins;

    IfxAsclin_Asc_initModule(&UART3, &UART3_Config);

#if (USR_UART3_RX_DMA==1)
	src = IfxAsclin_getSrcPointerRx(UART3_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART3_RX_ISR_PRIORITY);

	IfxAsclin_enableRxFifoFillLevelFlag(UART3_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart3_rx_dma_init();
#endif

#if (USR_UART3_TX_DMA==1)
	src = IfxAsclin_getSrcPointerTx(UART3_Config.asclin);

	IfxSrc_init(src, IfxSrc_Tos_dma, UART3_TX_ISR_PRIORITY);

	IfxAsclin_enableTxFifoFillLevelFlag(UART3_Config.asclin, TRUE);
	IfxSrc_enable(src);
	bsp_usart3_tx_dma_init();
#endif

}

static uint8 number_conversion_ascii(uint32 dat, int8 *p, uint8 neg_type, uint8 radix)
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
            if(10 <= temp_data)
            {
            	temp_data += 'A'-10;
            }
            else
            {
            	temp_data += '0';
            }

            *p = temp_data;

            pos_dat = pos_dat/radix;
            valid_num++;

            if(!pos_dat) break;
            p++;
        }
    }
    return valid_num;
}
static void printf_reverse_order(int8 *d_buff, uint32 len)
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

static void uart0_putchar(uint8 dat)
{
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(&UART0, &dat, &count, TIME_INFINITE);
}
static void uart0_putbuff(uint8 *buff, uint32 len)
{
	Ifx_SizeT count = len;
    (void)IfxAsclin_Asc_write(&UART0, buff, &count, TIME_INFINITE);
}
void uart0_printf(char *format, ...)
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
                    uart0_putchar((int8)ch);

                }break;


                case 'd':
                case 'i':// 有符号十进制整数
                {
                    int8 vstr[33];
                    int32 ival = (int32)va_arg(arg, int32);
                    uint8 vlen = number_conversion_ascii((uint32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                   	   uart0_putchar('-');
                   	}
                    printf_reverse_order(vstr,vlen);
                    uart0_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'f':// 浮点数，输出小数点后六位  不能指定输出精度
                case 'F':// 浮点数，输出小数点后六位  不能指定输出精度
                {
                    int8 vstr[33];
                    double ival = (double)va_arg(arg, double);
                    uint8 vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                    	uart0_putchar('-');
                    }
                    printf_reverse_order(vstr,vlen);
                    uart0_putbuff((uint8 *)vstr,vlen);
                    uart0_putchar('.');

                    ival = ((double)ival - (int32)ival)*1000000;
                    vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
				      while(6>vlen)
                    {
                        vstr[vlen] = '0';
                        vlen++;
                    }
                    printf_reverse_order(vstr,vlen);
                    uart0_putbuff((uint8 *)vstr,vlen);
                    break;
                }

                case 'u':// 无符号十进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 10);
                    printf_reverse_order(vstr,vlen);
                    uart0_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'o':// 无符号八进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 8);
                    printf_reverse_order(vstr,vlen);
                    uart0_putbuff((uint8 *)vstr,vlen);

                }break;

                case 'x':// 无符号十六进制整数
                case 'X':// 无符号十六进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,vlen);
                    uart0_putbuff((uint8 *)vstr,vlen);
                }break;


                case 's':// 字符串
                {
                    int8 *pc = va_arg(arg, int8 *);
                    while (*pc)
                    {
                        uart0_putchar((int8)(*pc));
                        pc++;
                    }
                }break;

                case 'p':// 以16进制形式输出指针
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,8);
                    uart0_putbuff((uint8 *)vstr,8);

                }break;


                case '%':// 输出字符%
                {
                    uart0_putchar('%');
                }break;

                default:break;
			}
		}
		else
		{
			uart0_putchar((int8)(*format));
		}
		format++;
	}
	va_end(arg);
}

static void uart1_putchar(uint8 dat)
{
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(&UART1, &dat, &count, TIME_INFINITE);
}
static void uart1_putbuff(uint8 *buff, uint32 len)
{
	Ifx_SizeT count = len;
    (void)IfxAsclin_Asc_write(&UART1, buff, &count, TIME_INFINITE);
}
void uart1_printf(char *format, ...)
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
                    uart1_putchar((int8)ch);

                }break;


                case 'd':
                case 'i':// 有符号十进制整数
                {
                    int8 vstr[33];
                    int32 ival = (int32)va_arg(arg, int32);
                    uint8 vlen = number_conversion_ascii((uint32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                   	   uart1_putchar('-');
                   	}
                    printf_reverse_order(vstr,vlen);
                    uart1_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'f':// 浮点数，输出小数点后六位  不能指定输出精度
                case 'F':// 浮点数，输出小数点后六位  不能指定输出精度
                {
                    int8 vstr[33];
                    double ival = (double)va_arg(arg, double);
                    uint8 vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                    	uart1_putchar('-');
                    }
                    printf_reverse_order(vstr,vlen);
                    uart1_putbuff((uint8 *)vstr,vlen);
                    uart1_putchar('.');

                    ival = ((double)ival - (int32)ival)*1000000;
                    vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
				      while(6>vlen)
                    {
                        vstr[vlen] = '0';
                        vlen++;
                    }
                    printf_reverse_order(vstr,vlen);
                    uart1_putbuff((uint8 *)vstr,vlen);
                    break;
                }

                case 'u':// 无符号十进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 10);
                    printf_reverse_order(vstr,vlen);
                    uart1_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'o':// 无符号八进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 8);
                    printf_reverse_order(vstr,vlen);
                    uart1_putbuff((uint8 *)vstr,vlen);

                }break;

                case 'x':// 无符号十六进制整数
                case 'X':// 无符号十六进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,vlen);
                    uart1_putbuff((uint8 *)vstr,vlen);
                }break;


                case 's':// 字符串
                {
                    int8 *pc = va_arg(arg, int8 *);
                    while (*pc)
                    {
                        uart1_putchar((int8)(*pc));
                        pc++;
                    }
                }break;

                case 'p':// 以16进制形式输出指针
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,8);
                    uart1_putbuff((uint8 *)vstr,8);

                }break;


                case '%':// 输出字符%
                {
                    uart1_putchar('%');
                }break;

                default:break;
			}
		}
		else
		{
			uart1_putchar((int8)(*format));
		}
		format++;
	}
	va_end(arg);
}

static void uart2_putchar(uint8 dat)
{
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(&UART2, &dat, &count, TIME_INFINITE);
}
static void uart2_putbuff(uint8 *buff, uint32 len)
{
	Ifx_SizeT count = len;
    (void)IfxAsclin_Asc_write(&UART2, buff, &count, TIME_INFINITE);
}
void uart2_printf(char *format, ...)
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
                    uart2_putchar((int8)ch);

                }break;


                case 'd':
                case 'i':// 有符号十进制整数
                {
                    int8 vstr[33];
                    int32 ival = (int32)va_arg(arg, int32);
                    uint8 vlen = number_conversion_ascii((uint32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                   	   uart2_putchar('-');
                   	}
                    printf_reverse_order(vstr,vlen);
                    uart2_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'f':// 浮点数，输出小数点后六位  不能指定输出精度
                case 'F':// 浮点数，输出小数点后六位  不能指定输出精度
                {
                    int8 vstr[33];
                    double ival = (double)va_arg(arg, double);
                    uint8 vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                    	uart2_putchar('-');
                    }
                    printf_reverse_order(vstr,vlen);
                    uart2_putbuff((uint8 *)vstr,vlen);
                    uart2_putchar('.');

                    ival = ((double)ival - (int32)ival)*1000000;
                    vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
				      while(6>vlen)
                    {
                        vstr[vlen] = '0';
                        vlen++;
                    }
                    printf_reverse_order(vstr,vlen);
                    uart2_putbuff((uint8 *)vstr,vlen);
                    break;
                }

                case 'u':// 无符号十进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 10);
                    printf_reverse_order(vstr,vlen);
                    uart2_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'o':// 无符号八进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 8);
                    printf_reverse_order(vstr,vlen);
                    uart2_putbuff((uint8 *)vstr,vlen);

                }break;

                case 'x':// 无符号十六进制整数
                case 'X':// 无符号十六进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,vlen);
                    uart2_putbuff((uint8 *)vstr,vlen);
                }break;


                case 's':// 字符串
                {
                    int8 *pc = va_arg(arg, int8 *);
                    while (*pc)
                    {
                        uart2_putchar((int8)(*pc));
                        pc++;
                    }
                }break;

                case 'p':// 以16进制形式输出指针
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,8);
                    uart2_putbuff((uint8 *)vstr,8);

                }break;


                case '%':// 输出字符%
                {
                    uart2_putchar('%');
                }break;

                default:break;
			}
		}
		else
		{
			uart2_putchar((int8)(*format));
		}
		format++;
	}
	va_end(arg);
}

static void uart3_putchar(uint8 dat)
{
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(&UART3, &dat, &count, TIME_INFINITE);
}
static void uart3_putbuff(uint8 *buff, uint32 len)
{
	Ifx_SizeT count = len;
    (void)IfxAsclin_Asc_write(&UART3, buff, &count, TIME_INFINITE);
}
void uart3_printf(char *format, ...)
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
                    uart3_putchar((int8)ch);

                }break;


                case 'd':
                case 'i':// 有符号十进制整数
                {
                    int8 vstr[33];
                    int32 ival = (int32)va_arg(arg, int32);
                    uint8 vlen = number_conversion_ascii((uint32)ival, vstr, 1, 10);
                    if(ival<0)
                    	{
                    	   uart3_putchar('-');
                    	}
                    printf_reverse_order(vstr,vlen);
                    uart3_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'f':// 浮点数，输出小数点后六位  不能指定输出精度
                case 'F':// 浮点数，输出小数点后六位  不能指定输出精度
                {
                    int8 vstr[33];
                    double ival = (double)va_arg(arg, double);
                    uint8 vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
                    if(ival<0)
                    {
                    	uart3_putchar('-');
                    }
                    printf_reverse_order(vstr,vlen);
                    uart3_putbuff((uint8 *)vstr,vlen);
                    uart3_putchar('.');

                    ival = ((double)ival - (int32)ival)*1000000;
                    vlen = number_conversion_ascii((uint32)(int32)ival, vstr, 1, 10);
				      while(6>vlen)
                    {
                        vstr[vlen] = '0';
                        vlen++;
                    }
                    printf_reverse_order(vstr,vlen);
                    uart3_putbuff((uint8 *)vstr,vlen);
                    break;
                }

                case 'u':// 无符号十进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 10);
                    printf_reverse_order(vstr,vlen);
                    uart3_putbuff((uint8 *)vstr,vlen);
                }break;

                case 'o':// 无符号八进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 8);
                    printf_reverse_order(vstr,vlen);
                    uart3_putbuff((uint8 *)vstr,vlen);

                }break;

                case 'x':// 无符号十六进制整数
                case 'X':// 无符号十六进制整数
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    uint8 vlen = number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,vlen);
                    uart3_putbuff((uint8 *)vstr,vlen);
                }break;


                case 's':// 字符串
                {
                    int8 *pc = va_arg(arg, int8 *);
                    while (*pc)
                    {
                        uart3_putchar((int8)(*pc));
                        pc++;
                    }
                }break;

                case 'p':// 以16进制形式输出指针
                {
                    int8 vstr[33];
                    uint32 ival = (uint32)va_arg(arg, uint32);
                    number_conversion_ascii(ival, vstr, 0, 16);
                    printf_reverse_order(vstr,8);
                    uart3_putbuff((uint8 *)vstr,8);

                }break;


                case '%':// 输出字符%
                {
                    uart3_putchar('%');
                }break;

                default:break;
			}
		}
		else
		{
			uart3_putchar((int8)(*format));
		}
		format++;
	}
	va_end(arg);
}

uint8 uart_buff[1024]={0};
void uart0_dma_test(void)
{
	uint16 len=0;
	UART0_Read_Data(uart_buff,&len);
   if(len)
   {
	IfxAsclin_Asc_write(&UART0,uart_buff,(Ifx_SizeT*)&len,TIME_INFINITE);
   }
}
void uart1_dma_test(void)
{
#if(USR_UART1_RX_DMA==1)
	uint16 len=0;
	UART1_Read_Data(uart_buff,&len);
   if(len)
   {
	IfxAsclin_Asc_write(&UART1,uart_buff,(Ifx_SizeT*)&len,TIME_INFINITE);
   }
#endif
}
void uart2_dma_test(void)
{
#if(USR_UART2_RX_DMA==1)
	uint16 len=0;
	UART2_Read_Data(uart_buff,&len);
   if(len)
   {
	IfxAsclin_Asc_write(&UART2,uart_buff,(Ifx_SizeT*)&len,TIME_INFINITE);
   }
#endif
}
void uart3_dma_test(void)
{
#if(USR_UART3_RX_DMA==1)
	uint16 len=0;
	UART3_Read_Data(uart_buff,&len);
   if(len)
   {
	IfxAsclin_Asc_write(&UART3,uart_buff,(Ifx_SizeT*)&len,TIME_INFINITE);
   }
#endif
}

