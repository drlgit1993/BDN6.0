/*
 * spi.h
 *
 *  Created on: 2021Äê6ÔÂ11ÈÕ
 *      Author: DRL-XSZ
 */

#ifndef APPSW_TRICORE_SPI_SPI_H_
#define APPSW_TRICORE_SPI_SPI_H_

#include "Ifx_Types.h"
#include "IfxQspi_SpiMaster.h"
#include "IfxQspi_SpiSlave.h"
#include "isr.h"

IFX_EXTERN void bsp_QSPI_Init(void);

IFX_EXTERN void QSPI0_Master_Write_Data(uint8 *src,Ifx_SizeT len);
IFX_EXTERN void QSPI0_Master_Read_Data(uint8 *dest,Ifx_SizeT len);

IFX_EXTERN void QSPI2_Master_Write_Data(uint8 *src,Ifx_SizeT len);
IFX_EXTERN void QSPI2_Master_Read_Data(uint8 *dest,Ifx_SizeT len);

IFX_EXTERN void QSPI3_Slave_Read_Data(uint8 *dest,Ifx_SizeT len);

#endif /* APPSW_TRICORE_SPI_SPI_H_ */
