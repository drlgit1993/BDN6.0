#ifndef ASCLIN_APP_H
#define ASCLIN_APP_H


/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include <Asclin/Asc/IfxAsclin_Asc.h>
#include <Ifx_Types.h>
#include "Configuration.h"
#include <stdio.h>
#include "Bsp/Bsp.h"
#include "ConfigurationIsr.h"
#include "Cpu/Irq/IfxCpu_Irq.h"
#include "Port/Std/IfxPort.h"
#include <Stm/Std/IfxStm.h>
#include <Src/Std/IfxSrc.h>
#include "Cpu0_Main.h"
#include "Cpu/Irq/IfxCpu_Irq.h"
#include "ifxDma_reg.h"
#include "ifxDma_Dma.h"
#include "ifxSrc.h"
#include "isr.h"

#define USR_UART0_TX_DMA  (0)
#define USR_UART0_RX_DMA  (1)

IFX_EXTERN void bsp_UART0_init(void);
IFX_EXTERN void UART0_Read_Data(unsigned char *dest,unsigned short *rlen);
IFX_EXTERN void UART0_Write_Data_DMA(uint8 *data,uint16 cnt);

IFX_EXTERN void bsp_UART1_init(void);
IFX_EXTERN uint8 UART1_Read_Data(void);
IFX_EXTERN boolean UART1_Write_Data(uint8 *data,Ifx_SizeT *cnt);

IFX_EXTERN void bsp_UART2_init(void);
IFX_EXTERN uint8 UART2_Read_Data(void);
IFX_EXTERN boolean    UART3_Write_Data(uint8 *data,Ifx_SizeT *cnt);

IFX_EXTERN void bsp_UART3_init(void);
IFX_EXTERN uint8 UART3_Read_Data(void);
IFX_EXTERN boolean UART3_Write_Data(uint8 *data,Ifx_SizeT *cnt);


IFX_EXTERN void UART3_test(void);
IFX_EXTERN void sendUARTMessage(char * msg, Ifx_SizeT count);
IFX_EXTERN void uart0_printf(const int8 *format, ...);

void uart0_dma_callback(void);

#endif /* 0_APPSW_TRICORE_MAIN_ASCLIN_APP_H_ */
