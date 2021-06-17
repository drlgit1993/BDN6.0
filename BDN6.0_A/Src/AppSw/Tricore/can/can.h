/*
 * can.h
 *
 *  Created on: 2021Äê6ÔÂ16ÈÕ
 *      Author: DRL-XSZ
 */

#ifndef SRC_APPSW_TRICORE_CAN_CAN_H_
#define SRC_APPSW_TRICORE_CAN_CAN_H_

#include"IfxMultican_Can.h"

IFX_EXTERN void bsp_Can_Init(void);
IFX_EXTERN void CAN_ReceiveSingle(uint32 id, uint32 *p_high, uint32 *p_low);
IFX_EXTERN void CAN_SendSingle(uint32 id, uint32 high, uint32 low);

#endif /* SRC_APPSW_TRICORE_CAN_CAN_H_ */
