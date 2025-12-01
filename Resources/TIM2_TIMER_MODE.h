/*

    TIM2_TIMER_MODE.h

*/

#ifndef __TIM2_TIMER_MODE_H__
#define __TIM2_TIMER_MODE_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32v00x.h"

#define VALUE_ATRLR(x) (SystemCoreClock/(x*(TIM2 -> PSC +1)))

extern int16_t Tiempo_Seg;

void TIM2_IRQHandler() __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_Enable(void);
void TIM2_Disable(void);
void TIM2_Timer_Mode_Init(void);

#ifdef __cplusplus
 }
#endif //__TIM2_TIMER_MODE_H__
#endif