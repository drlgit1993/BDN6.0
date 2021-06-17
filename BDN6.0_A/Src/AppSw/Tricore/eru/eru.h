/*
 * eru.h
 *
 *  Created on: 2021��6��15��
 *      Author: DRL-XSZ
 */

#ifndef APPSW_TRICORE_ERU_ERU_H_
#define APPSW_TRICORE_ERU_ERU_H_


#include "ifxscueru.h"
#include "isr.h"
#include "Bsp.h"



typedef enum
{
	GPIO_MODE_IT_RISING,
	GPIO_MODE_IT_FALLING,
	GPIO_MODE_IT_RISING_FALLING,
}GPIO_MODE_IT;

typedef struct
{
	IfxScu_Req_In *reqpin;
	IfxSrc_Tos    typOfService;
	Ifx_Priority  priority;
	GPIO_MODE_IT IT;
	IfxScuEru_InputNodePointer triggerSelect;
	IfxScuEru_OutputChannel outputChannel;
}eru_cfg_t;

typedef enum
{
    /*ERS0 ��ѡP15.4,P10.7*/
	ERU_CH0_REQ4_P10_7   = 0*3,
	ERU_CH0_REQ0_P15_4,

	/*ERS1��ѡP14.3,P10.8*/
	ERU_CH1_REQ5_P10_8   = 1*3,
	ERU_CH1_REQ10_P14_3,

	/*ERS2��ѡP10.2,P02.1,P00.4*/
	ERU_CH2_REQ7_P00_4   = 2*3,
	ERU_CH2_REQ14_P02_1,
	ERU_CH2_REQ2_P10_2,

	/*ERS3��ѡP10.3,P14.1,P02.0*/
	ERU_CH3_REQ6_P02_0   = 3*3,
	ERU_CH3_REQ3_P10_3,
	ERU_CH3_REQ15_P14_1,

	/*ERS4��ѡp33.7,p15.5*/
	ERU_CH4_REQ13_P15_5  = 4*3,
	ERU_CH4_REQ8_P33_7,

	/*ERS5��ѡP15.8,*/
	ERU_CH5_REQ1_P15_8   = 5*3,

	/*ERS6��ѡP20.0,P11.10*/
	ERU_CH6_REQ12_P11_10 = 6*3,
	ERU_CH6_REQ9_P20_0,

	/*ERS7��ѡP20.9,P15.1*/
	ERU_CH7_REQ16_P15_1  = 7*3,
	ERU_CH7_REQ11_P20_9,
}ERU_PIN_enum;


IFX_EXTERN void bsp_eru_init(void);

#endif /* APPSW_TRICORE_ERU_ERU_H_ */
