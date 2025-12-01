/*

    EXTERNAL_INTERRUPT.h

*/

#ifndef __EXTERNAL_INTERRUPT_H__
#define __EXTERNAL_INTERRUPT_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32v00x.h"
#include <stdbool.h>

/*  VARIABLES GLOBALES  */
extern volatile uint8_t PIN_Activo;

/*  PROTOTIPO DE FUNCION  */
void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void Extern_Interrupt_Init(void);

#ifdef __cplusplus
 }
#endif //__EXTERNAL_INTERRUPT_H__
#endif