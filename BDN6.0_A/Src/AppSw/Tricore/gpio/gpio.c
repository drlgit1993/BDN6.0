/*
 * gpio.c
 *
 *  Created on: 2021��6��9��
 *      Author: DRL-XSZ
 */
#include "gpio.h"



void bsp_gpio_init(void)
{
	IfxPort_setPinMode(&MODULE_P33, 4, IfxPort_Mode_outputPushPullGeneral);/*A2_GNSS_RST*/
	IfxPort_setPinMode(&MODULE_P33, 5, IfxPort_Mode_outputPushPullGeneral);/*A1_GNSS_RST*/
	IfxPort_setPinMode(&MODULE_P22, 1, IfxPort_Mode_outputPushPullGeneral);/*A_PPS_OUT*/
	IfxPort_setPinMode(&MODULE_P22, 2, IfxPort_Mode_outputPushPullGeneral);/*A_PPS_TX*/
}


