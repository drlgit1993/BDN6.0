/**
 * \file Cpu0_Main.c
 * \brief System initialisation and main program implementation.
 *
 * \version iLLD_Demos_1_0_0_11_0
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include <uart/uart.h>
#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
#include "Scu\Std\IfxScuWdt.h"

#include "IfxPort.h"
#include "IfxStm.h"
#include "spi.h"
#include "gpio.h"
#include "stm_systick.h"

/******************************************************************************/
/*------------------------Inline Function Prototypes--------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/
/*
 * watchdog timeout=(0xFFFF - WD_REL_VAL)/(Fspb/WDTSCON1.IRx)=(0xFFFF - WD_REL_VAL)/(100MHz/16384)
 * the value 16384 is a constant ,defined by IRx of register WDTSCON1.
*/
#define WD_REL_VAL   (0xE828) /*1s*/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
IfxCpu_syncEvent g_cpuSyncEvent = 0;

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

/** \brief Main entry point after CPU boot-up.
 *
 *  It initialise the system and enter the endless loop that handles the demo
 */
int core0_main(void)
{
	IfxCpu_enableInterrupts();

	//IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    bsp_UART0_init();
    bsp_UART1_init();
    bsp_UART2_init();
    bsp_UART3_init();
    uart0_printf("UART0:%d,%d,%d,%d\r\n",g_AppCpu0.info.pllFreq,g_AppCpu0.info.cpuFreq,g_AppCpu0.info.sysFreq,g_AppCpu0.info.stmFreq);

    bsp_QSPI_Init();

    //   bsp_gpio_init();


    //IfxScuWdt_enableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_changeCpuWatchdogReload(IfxScuWdt_getCpuWatchdogPassword(), WD_REL_VAL); /* Set CPU0WD timer to ~1.3 sec */
    //IfxScuWdt_serviceCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());               /* Service the CPU0WDT          */

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);


    while(1)
    {
    	 uart0_dma_test();
    	 uart1_dma_test();
    	 uart2_dma_test();
    	 uart3_dma_test();
    	 IfxScuWdt_serviceCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    }

    return 0;
}



/** \} */
