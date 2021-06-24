/*
 * spi.c
 *
 *  Created on: 2021��6��11��
 *      Author: DRL-XSZ
 */
#include "spi.h"


#define QSPI0_MASTER_Dev                   (&MODULE_QSPI0)
#define QSPI2_MASTER_Dev                   (&MODULE_QSPI2)
#define QSPI3_MASTER_Dev                   (&MODULE_QSPI3)

#define QSPI0_CHANNEL_NUM                  (2)

#define QSPI0_MASTER_TX_BUFF_MAX           (32)
#define QSPI0_MASTER_RX_BUFF_MAX           (32)

#define QSPI2_MASTER_TX_BUFF_MAX           (32)
#define QSPI2_MASTER_RX_BUFF_MAX           (32)

#define QSPI3_MASTER_TX_BUFF_MAX           (32)
#define QSPI3_MASTER_RX_BUFF_MAX           (32)

#define QSPI0_MASTER_CHANNEL_BAUDRATE      (1000000)
#define QSPI2_MASTER_CHANNEL_BAUDRATE      (1000000)
#define QSPI3_MASTER_CHANNEL_BAUDRATE      (1000000)


IfxQspi_SpiMaster         QSPI0_MASTER_Handle;
IfxQspi_SpiMaster_Channel QSPI0_MASTER_Channel_Handle[QSPI0_CHANNEL_NUM];

IfxQspi_SpiMaster         QSPI2_MASTER_Handle;
IfxQspi_SpiMaster_Channel QSPI2_MASTER_Channel_Handle;

IfxQspi_SpiMaster         QSPI3_MASTER_Handle;
IfxQspi_SpiMaster_Channel QSPI3_MASTER_Channel_Handle;

uint8 QSPI0_MASTER_TX_buff[QSPI0_MASTER_TX_BUFF_MAX];
uint8 QSPI0_MASTER_RX_buff[QSPI0_MASTER_RX_BUFF_MAX];

uint8 QSPI2_MASTER_TX_buff[QSPI2_MASTER_TX_BUFF_MAX];
uint8 QSPI2_MASTER_RX_buff[QSPI2_MASTER_RX_BUFF_MAX];

uint8 QSPI3_MASTER_TX_buff[QSPI3_MASTER_TX_BUFF_MAX];
uint8 QSPI3_MASTER_RX_buff[QSPI3_MASTER_RX_BUFF_MAX];

const IfxQspi_SpiMaster_Pins qspi0MasterPins =
{
    &IfxQspi0_SCLK_P20_11_OUT, IfxPort_OutputMode_pushPull,
    &IfxQspi0_MTSR_P20_14_OUT, IfxPort_OutputMode_pushPull,
    &IfxQspi0_MRSTA_P20_12_IN, IfxPort_InputMode_pullDown,
    IfxPort_PadDriver_cmosAutomotiveSpeed3
};
const IfxQspi_SpiMaster_Output qspi0MasterSelect[QSPI0_CHANNEL_NUM] =
{
	{
        &IfxQspi0_SLSO2_P20_13_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    },

	{
		 &IfxQspi0_SLSO6_P20_10_OUT, IfxPort_OutputMode_pushPull,
		 IfxPort_PadDriver_cmosAutomotiveSpeed1
	}
};

const IfxQspi_SpiMaster_Pins qspi2MasterPins =
{
    &IfxQspi2_SCLK_P15_6_OUT, IfxPort_OutputMode_pushPull,
    &IfxQspi2_MTSR_P15_5_OUT, IfxPort_OutputMode_pushPull,
    &IfxQspi2_MRSTA_P15_4_IN, IfxPort_InputMode_pullDown,
    IfxPort_PadDriver_cmosAutomotiveSpeed3
};
const IfxQspi_SpiMaster_Output qspi2MasterSelect =
{
        &IfxQspi2_SLSO5_P15_1_OUT, IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
};

const IfxQspi_SpiMaster_Pins qspi3MasterPins =
{
    &IfxQspi3_SCLK_P02_7_OUT, IfxPort_OutputMode_pushPull,
    &IfxQspi3_MTSR_P02_6_OUT, IfxPort_OutputMode_pushPull,
    &IfxQspi3_MRSTA_P02_5_IN, IfxPort_InputMode_pullDown,
    IfxPort_PadDriver_cmosAutomotiveSpeed3
};
const IfxQspi_SpiMaster_Output qspi3MasterSelect =
{
     &IfxQspi3_SLSO0_P02_4_OUT, IfxPort_OutputMode_pushPull,
     IfxPort_PadDriver_cmosAutomotiveSpeed1
};

IFX_INTERRUPT(QSPI0_Master_TX_IRQHandler, 0, QSPI0_MASTER_TX_ISR_PRIORITY);    /* SPI0 Master ISR for transmit data*/
IFX_INTERRUPT(QSPI0_Master_RX_IRQHandler, 0, QSPI0_MASTER_RX_ISR_PRIORITY);    /* SPI0 Master ISR for receive data*/
IFX_INTERRUPT(QSPI0_Master_ER_IRQHandler, 0, QSPI0_MASTER_ER_ISR_PRIORITY);    /* SPI0 Master ISR for error*/

IFX_INTERRUPT(QSPI2_Master_TX_IRQHandler, 0, QSPI2_MASTER_TX_ISR_PRIORITY);    /* SPI2 Master ISR for transmit data*/
IFX_INTERRUPT(QSPI2_Master_RX_IRQHandler, 0, QSPI2_MASTER_RX_ISR_PRIORITY);    /* SPI2 Master ISR for receive data*/
IFX_INTERRUPT(QSPI2_Master_ER_IRQHandler, 0, QSPI2_MASTER_ER_ISR_PRIORITY);    /* SPI2 Master ISR for error*/

IFX_INTERRUPT(QSPI3_Master_TX_IRQHandler, 0, QSPI3_MASTER_TX_ISR_PRIORITY);    /* SPI3 Master ISR for transmit data*/
IFX_INTERRUPT(QSPI3_Master_RX_IRQHandler, 0, QSPI3_MASTER_RX_ISR_PRIORITY);    /* SPI3 Master ISR for receive data*/
IFX_INTERRUPT(QSPI3_Master_ER_IRQHandler, 0, QSPI3_MASTER_ER_ISR_PRIORITY);    /* SPI3 Master ISR for error*/

void QSPI0_Master_TX_IRQHandler(void)
{
    IfxQspi_SpiMaster_isrTransmit(&QSPI0_MASTER_Handle);
}
void QSPI0_Master_RX_IRQHandler(void)
{
    IfxQspi_SpiMaster_isrReceive(&QSPI0_MASTER_Handle);
}
void QSPI0_Master_ER_IRQHandler(void)
{
    IfxQspi_SpiMaster_isrError(&QSPI0_MASTER_Handle);
}
void QSPI2_Master_TX_IRQHandler(void)
{
    IfxQspi_SpiMaster_isrTransmit(&QSPI2_MASTER_Handle);
}
void QSPI2_Master_RX_IRQHandler(void)
{
    IfxQspi_SpiMaster_isrReceive(&QSPI2_MASTER_Handle);
}
void QSPI2_Master_ER_IRQHandler(void)
{
    IfxQspi_SpiMaster_isrError(&QSPI2_MASTER_Handle);
}
void QSPI3_Master_TX_IRQHandler(void)
{
	IfxQspi_SpiMaster_isrTransmit(&QSPI3_MASTER_Handle);
}
void QSPI3_Master_RX_IRQHandler(void)
{
	IfxQspi_SpiMaster_isrReceive(&QSPI3_MASTER_Handle);
}
void QSPI3_Master_ER_IRQHandler(void)
{
	IfxQspi_SpiMaster_isrError(&QSPI3_MASTER_Handle);
}

/* QSPI0 Master initialization
 * This function initializes the QSPI0 module in Master mode.
 * MISO:P20_12,MOSI;P20_14,CLK:P20_11,CS1:P20-13,CS2:P20_10,RST:P20_9
 */
static void bsp_QSPI0_Master_Init(void)
{
    IfxQspi_SpiMaster_Config Qspi0MasterConfig;
    IfxQspi_SpiMaster_ChannelConfig Qspi0MasterChannelConfig;

    IfxQspi_SpiMaster_initModuleConfig(&Qspi0MasterConfig, QSPI0_MASTER_Dev);

    Qspi0MasterConfig.base.mode = SpiIf_Mode_master;
    Qspi0MasterConfig.base.maximumBaudrate =10000000;


    Qspi0MasterConfig.base.txPriority = QSPI0_MASTER_TX_ISR_PRIORITY;
    Qspi0MasterConfig.base.rxPriority = QSPI0_MASTER_RX_ISR_PRIORITY;
    Qspi0MasterConfig.base.erPriority = QSPI0_MASTER_ER_ISR_PRIORITY;
    Qspi0MasterConfig.base.isrProvider = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());
    Qspi0MasterConfig.pins = &qspi0MasterPins;

    IfxQspi_SpiMaster_initModule(&QSPI0_MASTER_Handle, &Qspi0MasterConfig);

    IfxQspi_SpiMaster_initChannelConfig(&Qspi0MasterChannelConfig, &QSPI0_MASTER_Handle);
    Qspi0MasterChannelConfig.base.baudrate = QSPI0_MASTER_CHANNEL_BAUDRATE;
    Qspi0MasterChannelConfig.base.mode.csActiveLevel =  Ifx_ActiveState_low  ;
    Qspi0MasterChannelConfig.base.mode.csLeadDelay= SpiIf_SlsoTiming_4  ;
    Qspi0MasterChannelConfig.base.mode.csTrailDelay=SpiIf_SlsoTiming_4;
	Qspi0MasterChannelConfig.base.mode.dataWidth=8;
	Qspi0MasterChannelConfig.base.mode.dataHeading=SpiIf_DataHeading_msbFirst;
	Qspi0MasterChannelConfig.base.mode.clockPolarity=SpiIf_ClockPolarity_idleLow;
	Qspi0MasterChannelConfig.base.mode.shiftClock=SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
	Qspi0MasterChannelConfig.mode=IfxQspi_SpiMaster_Mode_short ;
	Qspi0MasterChannelConfig.channelBasedCs=IfxQspi_SpiMaster_ChannelBasedCs_enabled;
    Qspi0MasterChannelConfig.sls.output = qspi0MasterSelect[0];
    IfxQspi_SpiMaster_initChannel(&QSPI0_MASTER_Channel_Handle[0], &Qspi0MasterChannelConfig);


	Qspi0MasterChannelConfig.sls.output = qspi0MasterSelect[1];
	IfxQspi_SpiMaster_initChannel(&QSPI0_MASTER_Channel_Handle[1], &Qspi0MasterChannelConfig);

    IfxPort_setPinMode(&MODULE_P20, 9, IfxPort_Mode_outputPushPullGeneral);/*RST*/
    IfxPort_setPinHigh(&MODULE_P20, 9);
}
static void QSPI0_Master_Buff_Init(void)
{
	uint8 i = 0;
    for ( i = 0; i < QSPI0_MASTER_TX_BUFF_MAX; i++)
    {
    	QSPI0_MASTER_TX_buff[i] = 0;
    }

    for ( i = 0; i < QSPI0_MASTER_RX_BUFF_MAX; i++)
	{
		QSPI0_MASTER_RX_buff[i] = 0;
	}
}
/* QSPI2 Master initialization
 * This function initializes the QSPI2 module in Master mode.
 *CS:P15_1,RST:15_2,WP:15_3,MISO:15_4,MOSI:15_5,CLK:15_6,HOLD:15_7
 */
static void bsp_QSPI2_Master_Init(void)
{
    IfxQspi_SpiMaster_Config Qspi2MasterConfig;
    IfxQspi_SpiMaster_ChannelConfig Qspi2MasterChannelConfig;

    IfxQspi_SpiMaster_initModuleConfig(&Qspi2MasterConfig, QSPI2_MASTER_Dev);

    Qspi2MasterConfig.base.mode = SpiIf_Mode_master;
    Qspi2MasterConfig.base.maximumBaudrate =10000000;

    Qspi2MasterConfig.base.txPriority = QSPI2_MASTER_TX_ISR_PRIORITY;
    Qspi2MasterConfig.base.rxPriority = QSPI2_MASTER_RX_ISR_PRIORITY;
    Qspi2MasterConfig.base.erPriority = QSPI2_MASTER_ER_ISR_PRIORITY;
    Qspi2MasterConfig.base.isrProvider = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());

    Qspi2MasterConfig.pins = &qspi2MasterPins;

    IfxQspi_SpiMaster_initModule(&QSPI2_MASTER_Handle, &Qspi2MasterConfig);

    IfxQspi_SpiMaster_initChannelConfig(&Qspi2MasterChannelConfig, &QSPI2_MASTER_Handle);
    Qspi2MasterChannelConfig.base.baudrate = QSPI2_MASTER_CHANNEL_BAUDRATE;
    Qspi2MasterChannelConfig.base.mode.csActiveLevel =  Ifx_ActiveState_low  ;
	Qspi2MasterChannelConfig.base.mode.csLeadDelay= SpiIf_SlsoTiming_4  ;
	Qspi2MasterChannelConfig.base.mode.csTrailDelay=SpiIf_SlsoTiming_4;
	Qspi2MasterChannelConfig.base.mode.dataWidth=8;
	Qspi2MasterChannelConfig.base.mode.dataHeading=SpiIf_DataHeading_msbFirst;
	Qspi2MasterChannelConfig.base.mode.clockPolarity=SpiIf_ClockPolarity_idleLow;
	Qspi2MasterChannelConfig.base.mode.shiftClock=SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
	Qspi2MasterChannelConfig.channelBasedCs=IfxQspi_SpiMaster_ChannelBasedCs_enabled;
    Qspi2MasterChannelConfig.mode=IfxQspi_SpiMaster_Mode_short ;
    Qspi2MasterChannelConfig.sls.output = qspi2MasterSelect;
    IfxQspi_SpiMaster_initChannel(&QSPI2_MASTER_Channel_Handle, &Qspi2MasterChannelConfig);

    IfxPort_setPinMode(&MODULE_P15, 2, IfxPort_Mode_outputPushPullGeneral);/*RST#*/
    IfxPort_setPinMode(&MODULE_P15, 3, IfxPort_Mode_outputPushPullGeneral);/*WP#*/
    IfxPort_setPinMode(&MODULE_P15, 7, IfxPort_Mode_outputPushPullGeneral);/*HOLD#*/

    IfxPort_setPinHigh(&MODULE_P15, 2);
    IfxPort_setPinHigh(&MODULE_P15, 3);
    IfxPort_setPinHigh(&MODULE_P15, 7);
}
static void QSPI2_Master_Buff_Init(void)
{
	uint8 i = 0;
    for ( i = 0; i < QSPI2_MASTER_TX_BUFF_MAX; i++)
    {
    	QSPI2_MASTER_TX_buff[i] = 0;
    }

    for ( i = 0; i < QSPI2_MASTER_RX_BUFF_MAX; i++)
	{
		QSPI2_MASTER_RX_buff[i] = 0;
	}
}
/* QSPI3 Master initialization
 * This function initializes the QSPI3 module in Master mode.
 *CS:P02_4,MISO:02_5,MOSI:02_6,CLK:02_7
 */
static void bsp_QSPI3_Master_Init(void)
{
    IfxQspi_SpiMaster_Config Qspi3MasterConfig;
    IfxQspi_SpiMaster_ChannelConfig Qspi3MasterChannelConfig;

    IfxQspi_SpiMaster_initModuleConfig(&Qspi3MasterConfig, QSPI2_MASTER_Dev);

    Qspi3MasterConfig.base.mode = SpiIf_Mode_master;
    Qspi3MasterConfig.base.maximumBaudrate =10000000;

    Qspi3MasterConfig.base.txPriority = QSPI3_MASTER_TX_ISR_PRIORITY;
    Qspi3MasterConfig.base.rxPriority = QSPI3_MASTER_RX_ISR_PRIORITY;
    Qspi3MasterConfig.base.erPriority = QSPI3_MASTER_ER_ISR_PRIORITY;
    Qspi3MasterConfig.base.isrProvider = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());;

    Qspi3MasterConfig.pins = &qspi3MasterPins;

    IfxQspi_SpiMaster_initModule(&QSPI3_MASTER_Handle, &Qspi3MasterConfig);

    IfxQspi_SpiMaster_initChannelConfig(&Qspi3MasterChannelConfig, &QSPI3_MASTER_Handle);

    Qspi3MasterChannelConfig.base.baudrate = QSPI3_MASTER_CHANNEL_BAUDRATE;
	Qspi3MasterChannelConfig.base.mode.csActiveLevel =  Ifx_ActiveState_low  ;
	Qspi3MasterChannelConfig.base.mode.csLeadDelay= SpiIf_SlsoTiming_4  ;
	Qspi3MasterChannelConfig.base.mode.csTrailDelay=SpiIf_SlsoTiming_4;
	Qspi3MasterChannelConfig.base.mode.dataWidth=8;
	Qspi3MasterChannelConfig.base.mode.dataHeading=SpiIf_DataHeading_msbFirst;
	Qspi3MasterChannelConfig.base.mode.clockPolarity=SpiIf_ClockPolarity_idleLow;
	Qspi3MasterChannelConfig.base.mode.shiftClock=SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge;
	Qspi3MasterChannelConfig.channelBasedCs=IfxQspi_SpiMaster_ChannelBasedCs_enabled;
	Qspi3MasterChannelConfig.mode=IfxQspi_SpiMaster_Mode_short ;
	Qspi3MasterChannelConfig.sls.output = qspi3MasterSelect;
	IfxQspi_SpiMaster_initChannel(&QSPI3_MASTER_Channel_Handle, &Qspi3MasterChannelConfig);
}
static void QSPI3_Master_Buff_Init(void)
{
	uint8 i = 0;
    for ( i = 0; i < QSPI3_MASTER_TX_BUFF_MAX; i++)
    {
    	QSPI3_MASTER_TX_buff[i] = 0;
    }

    for ( i = 0; i < QSPI3_MASTER_RX_BUFF_MAX; i++)
	{
		QSPI3_MASTER_RX_buff[i] = 0;
	}
}
void bsp_QSPI_Init(void)
{
	bsp_QSPI0_Master_Init();
	QSPI0_Master_Buff_Init();

	bsp_QSPI2_Master_Init();
	QSPI2_Master_Buff_Init();

	bsp_QSPI3_Master_Init();
	QSPI3_Master_Buff_Init();
}
void QSPI0_Master_Write_Data(uint8 chIdx,uint8 *src,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI0_MASTER_Channel_Handle[chIdx]) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }
    IfxQspi_SpiMaster_exchange(&QSPI0_MASTER_Channel_Handle[chIdx], src, NULL_PTR, len);
}
void QSPI0_Master_Read_Data(uint8 chIdx,uint8 *dest,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI0_MASTER_Channel_Handle[chIdx]) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }
    IfxQspi_SpiMaster_exchange(&QSPI0_MASTER_Channel_Handle[chIdx], NULL_PTR, dest, len);
}
void QSPI2_Master_Write_Data(uint8 *src,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI2_MASTER_Channel_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }

    IfxQspi_SpiMaster_exchange(&QSPI2_MASTER_Channel_Handle, src, NULL_PTR, len);
}
void QSPI2_Master_Read_Data(uint8 *dest,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI2_MASTER_Channel_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }

    IfxQspi_SpiMaster_exchange(&QSPI2_MASTER_Channel_Handle, NULL_PTR, dest, len);
}

void QSPI3_Master_Write_Data(uint8 *src,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI3_MASTER_Channel_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }

    IfxQspi_SpiMaster_exchange(&QSPI3_MASTER_Channel_Handle, src, NULL_PTR, len);
}
void QSPI3_Master_Read_Data(uint8 *dest,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI3_MASTER_Channel_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }

    IfxQspi_SpiMaster_exchange(&QSPI3_MASTER_Channel_Handle, NULL_PTR, dest, len);
}
