/*
 * timer.c
 *
 *  Created on: 2021Äê6ÔÂ15ÈÕ
 *      Author: DRL-XSZ
 */


#include "timer.h"


/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

#define CCU6_TIMER_FREQ         97656                                       /* Timer module frequency in Hz         */
#define CCU6_ISR_FREQ           2                                           /* ISR frequency in Hz                  */
#define CCU6_TIMER_PERIOD       (CCU6_TIMER_FREQ / CCU6_ISR_FREQ) - 1       /* Timer module period in ticks         */

IfxCcu6_Timer g_timer;

/*********************************************************************************************************************/
/*--------------------------------------------Function Implementations-----------------------------------------------*/
/*********************************************************************************************************************/
/* Macro defining the Interrupt Service Routine */
IFX_INTERRUPT(Timer_IRQHandler, 0, CCU6_ISR_PRIORITY);

void Timer_IRQHandler(void)
{


}

/* Function to initialize the GPT12 and start the timer */
void bsp_Timer_Init(void)
{
	IfxCcu6_Timer_Config timerConfig;                   /* Structure for timer configuration                        */
	    IfxCcu6_Timer_initModuleConfig(&timerConfig, &MODULE_CCU60); /* Initialize the timer module structure with default values*/

	    /* The Serial Peripheral Bus has a default Frequency of Fcc6 = 100000000 Hz = 100 MHz
	     * Possible frequencies for the CCU6 timer are:
	     *       - 100000000 Hz = 100 MHz   (Fcc6)
	     *       - 50000000 Hz  = 50 MHz    (Fcc6/2)
	     *       - 25000000 Hz  = 25 MHz    (Fcc6/4)
	     *       - 12500000 Hz  = 12.5 MHz  (Fcc6/8)
	     *       - 6250000 Hz   = 6.25 MHz  (Fcc6/16)
	     *       - 3125000 Hz   ~ 3 MHz     (Fcc6/32)
	     *       - 1562500 Hz   ~ 1.5 MHz   (Fcc6/64)
	     *       - 781250 Hz    ~ 780 KHz   (Fcc6/128)
	     *       - 390625 Hz    ~ 390 KHz   (Fcc6/256)
	     *       - 195312.5 Hz  ~ 200 KHz   (Fcc6/512)
	     *       - 97656.25 Hz  ~ 100 KHz   (Fcc6/1024)
	     *       - 48828.12 Hz  ~ 50 KHz    (Fcc6/2048)
	     *       - 24414.06 Hz  ~ 25 KHz    (Fcc6/4096)
	     *       - 12207.03 Hz  ~ 12.5 KHz  (Fcc6/8192)
	     *       - 6103.51 Hz   ~ 6 KHz     (Fcc6/16384)
	     *       - 3051.75 Hz   ~ 3 KHz     (Fcc6/32768)
	     */
	    timerConfig.base.t12Frequency = CCU6_TIMER_FREQ;                /* Configure the frequency of the timer module */
	    timerConfig.base.t12Period = CCU6_TIMER_PERIOD;                 /* Configure the period of the timer (16-bit)  */
	    timerConfig.timer = IfxCcu6_TimerId_t12;                        /* Select the timer to be started              */
	    timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t12PeriodMatch; /* Set interrupt source                */
	    timerConfig.interrupt1.priority = CCU6_ISR_PRIORITY;       /* Set the priority of the ISR                 */
	    timerConfig.interrupt1.typeOfService = IfxSrc_Tos_cpu0;         /* Set the type of service for the interrupt   */
	    timerConfig.trigger.t13InSyncWithT12 = FALSE;                   /* Configure timers synchronization            */

	    IfxCcu6_Timer_initModule(&g_timer, &timerConfig);               /* Initialize the CCU6 module                  */

	    IfxCcu6_Timer_start(&g_timer);                                  /* Start the timer                             */
}

