/*
 * eru.c
 *
 *  Created on: 2021Äê6ÔÂ15ÈÕ
 *      Author: DRL-XSZ
 */

#include "eru.h"




IFX_INTERRUPT(PPS_TX_IRQHandler, 0, PPS_TX_ISR_PRIORITY);
void PPS_TX_IRQHandler(void)
{

}

IFX_INTERRUPT(GNSS_PPS_IRQHandler, 0, GNSS_PPS_ISR_PRIORITY);
void GNSS_PPS_IRQHandler(void)
{

}

static void eru_init(eru_cfg_t *cfg)
{
    boolean interrupt_state = disableInterrupts();
	volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)cfg->outputChannel % 4];

    IfxScuEru_initReqPin(cfg->reqpin, IfxPort_InputMode_pullUp);

    IfxScuEru_InputChannel inputChannel = (IfxScuEru_InputChannel)cfg->reqpin->channelId;

    switch(cfg->IT)
    {
    	case GPIO_MODE_IT_RISING:
    	{
    		IfxScuEru_disableFallingEdgeDetection(inputChannel);
    		IfxScuEru_enableRisingEdgeDetection(inputChannel);
    	}break;

    	case GPIO_MODE_IT_FALLING:
    	{
    		IfxScuEru_enableFallingEdgeDetection(inputChannel);
    		IfxScuEru_disableRisingEdgeDetection(inputChannel);
    	}break;

    	case GPIO_MODE_IT_RISING_FALLING:
    	{
    		IfxScuEru_enableFallingEdgeDetection(inputChannel);
    		IfxScuEru_enableRisingEdgeDetection(inputChannel);
    	}break;
    }

    IfxScuEru_enableTriggerPulse(inputChannel);
    IfxScuEru_connectTrigger(inputChannel, cfg->triggerSelect);

    IfxScuEru_setFlagPatternDetection(cfg->outputChannel, inputChannel, TRUE);
    IfxScuEru_enablePatternDetectionTrigger(cfg->outputChannel);
    IfxScuEru_setInterruptGatingPattern(cfg->outputChannel, IfxScuEru_InterruptGatingPattern_alwaysActive);

 	IfxSrc_init(src, cfg->typOfService,cfg->priority);
 	IfxSrc_enable(src);

    restoreInterrupts(interrupt_state);
}

void bsp_eru_init(void)
{
	eru_cfg_t cfg={0};

    cfg.priority=10;
    cfg.reqpin=&IfxScu_REQ14_P02_1_IN;
    cfg.IT=GPIO_MODE_IT_RISING_FALLING;
    cfg.triggerSelect=IfxScuEru_InputNodePointer_2;
    cfg.outputChannel= IfxScuEru_OutputChannel_2;
    cfg.typOfService=IfxSrc_Tos_cpu0;
	eru_init(&cfg);

	cfg.priority=11;
	cfg.reqpin=&IfxScu_REQ1_P15_8_IN;
	cfg.IT=GPIO_MODE_IT_RISING_FALLING;
	cfg.triggerSelect=IfxScuEru_InputNodePointer_5;
	cfg.outputChannel= IfxScuEru_OutputChannel_5;
	cfg.typOfService=IfxSrc_Tos_cpu0;
	eru_init(&cfg);
}
