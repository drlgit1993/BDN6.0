/*
 * stm_systick.h
 *
 *  Created on: 2021年6月18日
 *      Author: DRL-XSZ
 */

#ifndef SRC_APPSW_TRICORE_STM_SYSTICK_STM_SYSTICK_H_
#define SRC_APPSW_TRICORE_STM_SYSTICK_STM_SYSTICK_H_



typedef enum  // ö��STMģ���
{
    STM0,
	STM1,
}STMN_enum;


void systick_delay(STMN_enum stmn, uint32 time);
void systick_start(STMN_enum stmn);
uint32 systick_getval(STMN_enum stmn);

//------------------------------------以下宏定义用于延时------------------------------------
#define delay_ms(time)	systick_delay(STM0, time*1000000)   //设置延时时间  单位ms
#define delay_us(time)	systick_delay(STM0, time*1000)      //设置延时时间  单位us
#define delay_ns(time)	systick_delay(STM0, time)   		//设置延时时间  单位ns

#define systick_delay_ms(stmn, time)	systick_delay(stmn, time*1000000)   //设置延时时间  单位ms
#define systick_delay_us(stmn, time)	systick_delay(stmn, time*1000)      //设置延时时间  单位us
#define systick_delay_ns(stmn, time)	systick_delay(stmn, time)   		//设置延时时间  单位ns

//------------------------------------以下宏定义用于获取当前时间------------------------------------
#define systick_getval_ms(stmn)         systick_getval(stmn)/100000         //获取当前计时时间  单位ms
#define systick_getval_us(stmn)         systick_getval(stmn)/100            //获取当前计时时间  单位us
#define systick_getval_ns(stmn)         systick_getval(stmn)*10    			//获取当前计时时间  单位ns


#endif /* SRC_APPSW_TRICORE_STM_SYSTICK_STM_SYSTICK_H_ */
