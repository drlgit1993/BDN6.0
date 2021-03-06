/*
 * isr.h
 *
 *  Created on: 2021��6��10��
 *      Author: DRL-XSZ
 */

#ifndef APPSW_TRICORE_MAIN_ISR_H_
#define APPSW_TRICORE_MAIN_ISR_H_

#include "IfxQspi_SpiMaster.h"
#include "IfxQspi_SpiSlave.h"


#define PPS_TX_ISR_PRIORITY                (1)
#define GNSS_PPS_ISR_PRIORITY              (2)

#define UART0_TX_ISR_PRIORITY              (3)
#define UART0_RX_ISR_PRIORITY              (4)
#define UART0_ER_ISR_PRIORITY              (5)
#define UART0_RX_DMA_ISR_PRIORITY          (6)
#define UART0_TX_DMA_ISR_PRIORITY          (7)

#define UART1_TX_ISR_PRIORITY              (8)
#define UART1_RX_ISR_PRIORITY              (9)
#define UART1_ER_ISR_PRIORITY              (10)
#define UART1_RX_DMA_ISR_PRIORITY          (11)
#define UART1_TX_DMA_ISR_PRIORITY          (12)


#define UART2_TX_ISR_PRIORITY              (13)
#define UART2_RX_ISR_PRIORITY              (14)
#define UART2_ER_ISR_PRIORITY              (15)
#define UART2_RX_DMA_ISR_PRIORITY          (16)
#define UART2_TX_DMA_ISR_PRIORITY          (17)


#define UART3_TX_ISR_PRIORITY              (18)
#define UART3_RX_ISR_PRIORITY              (19)
#define UART3_ER_ISR_PRIORITY              (20)
#define UART3_RX_DMA_ISR_PRIORITY          (21)
#define UART3_TX_DMA_ISR_PRIORITY          (22)


#define QSPI0_MASTER_TX_ISR_PRIORITY       (23)
#define QSPI0_MASTER_RX_ISR_PRIORITY       (24)
#define QSPI0_MASTER_ER_ISR_PRIORITY       (25)

#define QSPI2_MASTER_TX_ISR_PRIORITY       (26)
#define QSPI2_MASTER_RX_ISR_PRIORITY       (27)
#define QSPI2_MASTER_ER_ISR_PRIORITY       (28)

#define QSPI3_MASTER_TX_ISR_PRIORITY        (29)
#define QSPI3_MASTER_RX_ISR_PRIORITY        (30)
#define QSPI3_MASTER_ER_ISR_PRIORITY        (31)


#define CCU6_ISR_PRIORITY                  (26)                      /* Define the GPT12 Timer interrupt priority            */

#endif /* APPSW_TRICORE_MAIN_ISR_H_ */
