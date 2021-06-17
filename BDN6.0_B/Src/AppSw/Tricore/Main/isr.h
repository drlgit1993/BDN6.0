/*
 * isr.h
 *
 *  Created on: 2021Äê6ÔÂ10ÈÕ
 *      Author: DRL-XSZ
 */

#ifndef APPSW_TRICORE_MAIN_ISR_H_
#define APPSW_TRICORE_MAIN_ISR_H_

#include "IfxQspi_SpiMaster.h"
#include "IfxQspi_SpiSlave.h"



#define PPS_TX_ISR_PRIORITY                (1)
#define GNSS_PPS_ISR_PRIORITY              (2)

#define UART1_TX_ISR_PRIORITY              (3)
#define UART1_RX_ISR_PRIORITY              (4)
#define UART1_ER_ISR_PRIORITY              (5)

#define UART2_TX_ISR_PRIORITY              (6)
#define UART2_RX_ISR_PRIORITY              (7)
#define UART2_ER_ISR_PRIORITY              (8)

#define UART3_TX_ISR_PRIORITY              (9)
#define UART3_RX_ISR_PRIORITY              (10)
#define UART3_ER_ISR_PRIORITY              (11)

#define QSPI0_MASTER_TX_ISR_PRIORITY       (12)
#define QSPI0_MASTER_RX_ISR_PRIORITY       (13)
#define QSPI0_MASTER_ER_ISR_PRIORITY       (14)

#define QSPI2_MASTER_TX_ISR_PRIORITY       (15)
#define QSPI2_MASTER_RX_ISR_PRIORITY       (16)
#define QSPI2_MASTER_ER_ISR_PRIORITY       (17)

#define QSPI3_SLAVE_TX_ISR_PRIORITY        (18)
#define QSPI3_SLAVE_RX_ISR_PRIORITY        (19)
#define QSPI3_SLAVE_ER_ISR_PRIORITY        (20)

#define CCU6_ISR_PRIORITY           (21)                      /* Define the GPT12 Timer interrupt priority            */

#endif /* APPSW_TRICORE_MAIN_ISR_H_ */
