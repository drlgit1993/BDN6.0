/*
 * gpio.c
 *
 *  Created on: 2021��6��9��
 *      Author: DRL-XSZ
 */
#include "gpio.h"



void bsp_gpio_init(void)
{
	IfxPort_setPinMode(&MODULE_P22, 1, IfxPort_Mode_outputPushPullGeneral);/*B_PPS_OUT*/
}


