/*
 * spi.c
 *
 *  Created on: 2021Äê6ÔÂ11ÈÕ
 *      Author: DRL-XSZ
 */
#include "spi.h"

#define QSPI0_MASTER_Dev                &MODULE_QSPI0
#define QSPI2_MASTER_Dev                &MODULE_QSPI2
#define QSPI3_SLAVE_Dev                 &MODULE_QSPI3

#define QSPI0_MASTER_TX_BUFF_MAX           (32)
#define QSPI0_MASTER_RX_BUFF_MAX           (32)

#define QSPI2_MASTER_TX_BUFF_MAX           (32)
#define QSPI2_MASTER_RX_BUFF_MAX           (32)

#define QSPI3_SLAVE_TX_BUFF_MAX            (32)
#define QSPI3_SLAVE_RX_BUFF_MAX            (32)

#define QSPI0_MASTER_CHANNEL_BAUDRATE     1000000         /* Master channel baud rate                                     */
#define QSPI2_MASTER_CHANNEL_BAUDRATE     1000000         /* Master channel baud rate                                     */

/* Interrupt Service Routine priorities for Master and Slave SPI communication */


IfxQspi_SpiMaster         QSPI0_MASTER_Handle;            /* QSPI0 Master handle            */
IfxQspi_SpiMaster_Channel QSPI0_MASTER_Channel_Handle;    /* QSPI0 Master Channel handle    */

IfxQspi_SpiMaster         QSPI2_MASTER_Handle;            /* QSPI2 Master handle            */
IfxQspi_SpiMaster_Channel QSPI2_MASTER_Channel_Handle;    /* QSPI2 Master Channel handle    */

IfxQspi_SpiSlave          QSPI3_Slave_Handle;             /* QSPI3 Slave handle             */

uint8 QSPI0_MASTER_TX_buff[QSPI0_MASTER_TX_BUFF_MAX];
uint8 QSPI0_MASTER_RX_buff[QSPI0_MASTER_RX_BUFF_MAX];

uint8 QSPI2_MASTER_TX_buff[QSPI2_MASTER_TX_BUFF_MAX];
uint8 QSPI2_MASTER_RX_buff[QSPI2_MASTER_RX_BUFF_MAX];

uint8 QSPI3_Slave_TX_buff[QSPI3_SLAVE_TX_BUFF_MAX];
uint8 QSPI3_Slave_RX_buff[QSPI3_SLAVE_RX_BUFF_MAX];


IFX_INTERRUPT(QSPI0_Master_TX_IRQHandler, 0, QSPI0_MASTER_TX_ISR_PRIORITY);    /* SPI0 Master ISR for transmit data*/
IFX_INTERRUPT(QSPI0_Master_RX_IRQHandler, 0, QSPI0_MASTER_RX_ISR_PRIORITY);    /* SPI0 Master ISR for receive data*/
IFX_INTERRUPT(QSPI0_Master_ER_IRQHandler, 0, QSPI0_MASTER_ER_ISR_PRIORITY);    /* SPI0 Master ISR for error*/

IFX_INTERRUPT(QSPI2_Master_TX_IRQHandler, 0, QSPI2_MASTER_TX_ISR_PRIORITY);    /* SPI2 Master ISR for transmit data*/
IFX_INTERRUPT(QSPI2_Master_RX_IRQHandler, 0, QSPI2_MASTER_RX_ISR_PRIORITY);    /* SPI2 Master ISR for receive data*/
IFX_INTERRUPT(QSPI2_Master_ER_IRQHandler, 0, QSPI2_MASTER_ER_ISR_PRIORITY);    /* SPI2 Master ISR for error*/

IFX_INTERRUPT(QSPI3_Slave_TX_IRQHandler, 0, QSPI3_SLAVE_TX_ISR_PRIORITY);    /* SPI3 Slave ISR for transmit data*/
IFX_INTERRUPT(QSPI3_Slave_RX_IRQHandler, 0, QSPI3_SLAVE_RX_ISR_PRIORITY);    /* SPI3 Slave ISR for receive data*/
IFX_INTERRUPT(QSPI3_Slave_ER_IRQHandler, 0, QSPI3_SLAVE_ER_ISR_PRIORITY);    /* SPI3 Slave ISR for error*/

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
void QSPI3_Slave_TX_IRQHandler(void)
{
    IfxQspi_SpiSlave_isrTransmit(&QSPI3_Slave_Handle);
}

void QSPI3_Slave_RX_IRQHandler(void)
{
    IfxQspi_SpiSlave_isrReceive(&QSPI3_Slave_Handle);
}

void QSPI3_Slave_ER_IRQHandler(void)
{
    IfxQspi_SpiSlave_isrError(&QSPI3_Slave_Handle);
}

/* QSPI0 Master initialization
 * This function initializes the QSPI0 module in Master mode.
 * MISO:P20_12,MOSI;P20_14,CLK:P20_11,CS1:P20-13,CS2:P20_10,RST:P20_9
 */
static void bsp_QSPI0_Master_Init(void)
{
    IfxQspi_SpiMaster_Config Qspi0MasterConfig;                           /* Define a Master configuration            */

    IfxQspi_SpiMaster_ChannelConfig Qspi0MasterChannelConfig;             /* Define a Master Channel configuration    */

    IfxQspi_SpiMaster_initModuleConfig(&Qspi0MasterConfig, QSPI0_MASTER_Dev); /* Initialize it with default values        */

    Qspi0MasterConfig.base.mode = SpiIf_Mode_master;                      /* Configure the mode                       */

    /* Select the port pins for communication£¬ */
    const IfxQspi_SpiMaster_Pins qspi0MasterPins =
    {
        &IfxQspi0_SCLK_P20_11_OUT, IfxPort_OutputMode_pushPull,          /* SCLK Pin                       (CLK)     */
        &IfxQspi0_MTSR_P20_14_OUT, IfxPort_OutputMode_pushPull,          /* MasterTransmitSlaveReceive pin (MOSI)    */
        &IfxQspi0_MRSTA_P20_12_IN, IfxPort_InputMode_pullDown,           /* MasterReceiveSlaveTransmit pin (MISO)    */
        IfxPort_PadDriver_cmosAutomotiveSpeed3                          /* Pad driver mode                          */
    };
    Qspi0MasterConfig.pins = &qspi0MasterPins;                            /* Assign the Master's port pins            */

    /* Set the ISR priorities and the service provider */
    Qspi0MasterConfig.base.txPriority = QSPI0_MASTER_TX_ISR_PRIORITY;
    Qspi0MasterConfig.base.rxPriority = QSPI0_MASTER_RX_ISR_PRIORITY;
    Qspi0MasterConfig.base.erPriority = QSPI0_MASTER_ER_ISR_PRIORITY;
    Qspi0MasterConfig.base.isrProvider = IfxSrc_Tos_cpu0;

    /* Initialize the QSPI0 Master module */
    IfxQspi_SpiMaster_initModule(&QSPI0_MASTER_Handle, &Qspi0MasterConfig);

    /* Initialize the configuration with default values */
    IfxQspi_SpiMaster_initChannelConfig(&Qspi0MasterChannelConfig, &QSPI0_MASTER_Handle);

    Qspi0MasterChannelConfig.base.baudrate = QSPI0_MASTER_CHANNEL_BAUDRATE;     /* Set SCLK frequency to 1 MHz              */

    /* Select the port pin for the Chip Select signal */
    const IfxQspi_SpiMaster_Output qspi0SlaveSelect = {                 /* QSPI2 Master selects the QSPI3 Slave     */
            &IfxQspi0_SLSO2_P20_13_OUT, IfxPort_OutputMode_pushPull,         /* Slave Select port pin (CS)               */
            IfxPort_PadDriver_cmosAutomotiveSpeed1                          /* Pad driver mode                          */
    };
    Qspi0MasterChannelConfig.sls.output = qspi0SlaveSelect;

    /* Initialize the QSPI Master channel */
    IfxQspi_SpiMaster_initChannel(&QSPI0_MASTER_Channel_Handle, &Qspi0MasterChannelConfig);

    IfxPort_setPinMode(&MODULE_P20, 10, IfxPort_Mode_outputPushPullGeneral);/*CS2*/
    IfxPort_setPinMode(&MODULE_P20, 9, IfxPort_Mode_outputPushPullGeneral);/*RST*/
}
/* QSPI Master SW buffer initialization
 * This function initializes SW buffers the Master uses.
 */
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
    IfxQspi_SpiMaster_Config Qspi2MasterConfig;                           /* Define a Master configuration            */
    IfxQspi_SpiMaster_ChannelConfig Qspi2MasterChannelConfig;             /* Define a Master Channel configuration    */

    IfxQspi_SpiMaster_initModuleConfig(&Qspi2MasterConfig, QSPI2_MASTER_Dev); /* Initialize it with default values        */

    Qspi2MasterConfig.base.mode = SpiIf_Mode_master;                      /* Configure the mode                       */

    /* Select the port pins for communication */
    const IfxQspi_SpiMaster_Pins qspi2MasterPins =
    {
        &IfxQspi2_SCLK_P15_6_OUT, IfxPort_OutputMode_pushPull,          /* SCLK Pin                       (CLK)     */
        &IfxQspi2_MTSR_P15_5_OUT, IfxPort_OutputMode_pushPull,          /* MasterTransmitSlaveReceive pin (MOSI)    */
        &IfxQspi2_MRSTA_P15_4_IN, IfxPort_InputMode_pullDown,           /* MasterReceiveSlaveTransmit pin (MISO)    */
        IfxPort_PadDriver_cmosAutomotiveSpeed3                          /* Pad driver mode                          */
    };
    Qspi2MasterConfig.pins = &qspi2MasterPins;                            /* Assign the Master's port pins            */

    /* Set the ISR priorities and the service provider */
    Qspi2MasterConfig.base.txPriority = QSPI2_MASTER_TX_ISR_PRIORITY;
    Qspi2MasterConfig.base.rxPriority = QSPI2_MASTER_RX_ISR_PRIORITY;
    Qspi2MasterConfig.base.erPriority = QSPI2_MASTER_ER_ISR_PRIORITY;
    Qspi2MasterConfig.base.isrProvider = IfxSrc_Tos_cpu0;

    /* Initialize the QSPI0 Master module */
    IfxQspi_SpiMaster_initModule(&QSPI2_MASTER_Handle, &Qspi2MasterConfig);

    /* Initialize the configuration with default values */
    IfxQspi_SpiMaster_initChannelConfig(&Qspi2MasterChannelConfig, &QSPI2_MASTER_Handle);

    Qspi2MasterChannelConfig.base.baudrate = QSPI2_MASTER_CHANNEL_BAUDRATE;     /* Set SCLK frequency to 1 MHz              */

    /* Select the port pin for the Chip Select signal */
    const IfxQspi_SpiMaster_Output qspi2SlaveSelect = {                 /* QSPI2 Master selects the QSPI3 Slave     */
            &IfxQspi2_SLSO5_P15_1_OUT, IfxPort_OutputMode_pushPull,         /* Slave Select port pin (CS)               */
            IfxPort_PadDriver_cmosAutomotiveSpeed1                          /* Pad driver mode                          */
    };
    Qspi2MasterChannelConfig.sls.output = qspi2SlaveSelect;

    /* Initialize the QSPI Master channel */
    IfxQspi_SpiMaster_initChannel(&QSPI0_MASTER_Channel_Handle, &Qspi2MasterChannelConfig);

    IfxPort_setPinMode(&MODULE_P15, 2, IfxPort_Mode_outputPushPullGeneral);/*RST*/
    IfxPort_setPinMode(&MODULE_P15, 3, IfxPort_Mode_outputPushPullGeneral);/*WP*/
    IfxPort_setPinMode(&MODULE_P15, 7, IfxPort_Mode_outputPushPullGeneral);/*HOLD*/
}
/* QSPI2 Master SW buffer initialization
 * This function initializes SW buffers the Master uses.
 */
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
/* QSPI3 Slave initialization
 * This function initializes the QSPI3 module in Slave mode.
 * MOSI:P02_6,MISO:P02_5,CLK:P02_7,CS:P02_4
 */
static void bsp_QSPI3_Slave_Init(void)
{
    IfxQspi_SpiSlave_Config Qspi3SlaveConfig;                             /* Define the Slave configuration           */

    IfxQspi_SpiSlave_initModuleConfig(&Qspi3SlaveConfig, QSPI3_SLAVE_Dev);    /* Initialize it with default values        */

    /* Select the port pins for communication */
    const IfxQspi_SpiSlave_Pins qspi3SlavePins =
    {
        &IfxQspi3_SCLKA_P02_7_IN, IfxPort_InputMode_pullDown,           /* SCLK Pin                       (CLK)     */
        &IfxQspi3_MTSRA_P02_6_IN, IfxPort_InputMode_pullDown,           /* MasterTransmitSlaveReceive pin (MOSI)    */
        &IfxQspi3_MRST_P02_5_OUT, IfxPort_OutputMode_pushPull,          /* MasterReceiveSlaveTransmit pin (MISO)    */
        &IfxQspi3_SLSIA_P02_4_IN, IfxPort_InputMode_pullDown,           /* SlaveSelect Pin                (CS)      */
        IfxPort_PadDriver_cmosAutomotiveSpeed3                          /* Pad driver mode                          */
    };
    Qspi3SlaveConfig.pins = &qspi3SlavePins;                              /* Assign Slave port pins                   */

    /* Set the ISR priorities and the service provider */
    Qspi3SlaveConfig.base.txPriority = QSPI3_SLAVE_TX_ISR_PRIORITY;
    Qspi3SlaveConfig.base.rxPriority = QSPI3_SLAVE_RX_ISR_PRIORITY;
    Qspi3SlaveConfig.base.erPriority = QSPI3_SLAVE_ER_ISR_PRIORITY;
    Qspi3SlaveConfig.base.isrProvider = IfxSrc_Tos_cpu0;

    /* Initialize QSPI Slave module */
    IfxQspi_SpiSlave_initModule(&QSPI3_Slave_Handle, &Qspi3SlaveConfig);
}

/* QSPI Slave SW buffer initialization
 * This function initializes the software buffers that are used by the Slave.
 */
static void QSPI3_Slave_Buff_Init(void)
{
	uint8 i=0;
    for (i = 0; i < QSPI3_SLAVE_TX_BUFF_MAX; i++)
    {
    	QSPI3_Slave_TX_buff[i] = 0;
    }

    for ( i= 0; i < QSPI3_SLAVE_RX_BUFF_MAX; i++)
	{
		QSPI3_Slave_RX_buff[i] = 0;
	}
}
void bsp_QSPI_Init(void)
{
	bsp_QSPI0_Master_Init();
	QSPI0_Master_Buff_Init();

	bsp_QSPI2_Master_Init();
	QSPI2_Master_Buff_Init();

	bsp_QSPI3_Slave_Init();
	QSPI3_Slave_Buff_Init();
}
void QSPI0_Master_Write_Data(uint8 *src,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI0_MASTER_Channel_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }
    IfxQspi_SpiMaster_exchange(&QSPI0_MASTER_Channel_Handle, src, NULL_PTR, len);
}
void QSPI0_Master_Read_Data(uint8 *dest,Ifx_SizeT len)
{
    while(IfxQspi_SpiMaster_getStatus(&QSPI0_MASTER_Channel_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }
    IfxQspi_SpiMaster_exchange(&QSPI0_MASTER_Channel_Handle, NULL_PTR, dest, len);
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
void QSPI3_Slave_Read_Data(uint8 *dest,Ifx_SizeT len)
{
    while(IfxQspi_SpiSlave_getStatus(&QSPI3_Slave_Handle) == SpiIf_Status_busy)
    {
    	/* Wait until the previous communication has finished, if any */
    }
    IfxQspi_SpiSlave_exchange(&QSPI3_Slave_Handle, NULL_PTR, dest, len);
}
