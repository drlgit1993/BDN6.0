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
#define USR_UART1_TX_DMA  (0)
#define USR_UART1_RX_DMA  (1)
#define USR_UART2_TX_DMA  (0)
#define USR_UART2_RX_DMA  (1)
#define USR_UART3_TX_DMA  (0)
#define USR_UART3_RX_DMA  (1)

#define UART0_BAUDRATE                    (230400)
#define UART1_BAUDRATE                    (230400)
#define UART2_BAUDRATE                    (230400)
#define UART3_BAUDRATE                    (230400)


IFX_EXTERN void bsp_UART0_init(void);
IFX_EXTERN void UART0_Read_Data(unsigned char *dest,unsigned short *rlen);
IFX_EXTERN void UART0_Write_Data_DMA(uint8 *data,uint16 cnt);

IFX_EXTERN void bsp_UART1_init(void);
IFX_EXTERN void UART1_Read_Data(unsigned char *dest,unsigned short *rlen);
IFX_EXTERN void UART1_Write_Data_DMA(uint8 *data,uint16 cnt);

IFX_EXTERN void bsp_UART2_init(void);
IFX_EXTERN void UART2_Read_Data(unsigned char *dest,unsigned short *rlen);
IFX_EXTERN void UART2_Write_Data_DMA(uint8 *data,uint16 cnt);

IFX_EXTERN void bsp_UART3_init(void);
IFX_EXTERN void UART3_Read_Data(unsigned char *dest,unsigned short *rlen);
IFX_EXTERN void UART3_Write_Data_DMA(uint8 *data,uint16 cnt);

IFX_EXTERN void uart0_printf( char *format, ...);
IFX_EXTERN void uart1_printf( char *format, ...);
IFX_EXTERN void uart2_printf( char *format, ...);
IFX_EXTERN void uart3_printf( char *format, ...);

void uart0_dma_test(void);
void uart1_dma_test(void);
void uart2_dma_test(void);
void uart3_dma_test(void);

#endif /* 0_APPSW_TRICORE_MAIN_ASCLIN_APP_H_ */
