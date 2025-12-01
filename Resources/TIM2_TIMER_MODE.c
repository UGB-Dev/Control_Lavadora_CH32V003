/*

    EXTERNAL_INTERRUPT.c

*/

#include "TIM2_TIMER_MODE.h"

int16_t Tiempo_Seg=0;

void TIM2_Timer_Mode_Init(void){
    RCC -> APB1PCENR |= RCC_TIM2EN; // Habilitacion del Timer 2

    /* CONFIGURACION DEL TIMER 2 */
    TIM2 -> PSC = (SystemCoreClock/1000) - 1 ; // Base de tiempo para el timer 2
    TIM2 -> ATRLR = VALUE_ATRLR(1) ; // Frecuencia de salida

    /* CONFIGURACION DE INTERRUPCION */
    PFIC -> IPRIOR[TIM2_IRQn] = 0xFF; // Prioridad de interrupcion alta para el timer 2

    /* ACTIVACION DEl CNT */
    TIM2 -> CTLR1 |= TIM_CEN; // Se habilita el contador CNT
}

void TIM2_Enable(void){
    RCC -> APB1PCENR |= RCC_TIM2EN; // Habilitacion del Timer 2

    /* CONFIGURACION DEL TIMER 2 */
    TIM2 -> DMAINTENR |= TIM_UIE; // Se habilita la interrupcion por actualizacion (CNT=0)
    
    /* CONFIGURACION DE INTERRUPCION */
    PFIC -> IENR[1] = 1 << (TIM2_IRQn-32); // Habilitacion de interrupcion general para el timer 2
    
}

void TIM2_Disable(void){
    RCC -> APB1PCENR &= ~RCC_TIM2EN; // Deshabilitacion del Timer 2
    TIM2 -> CNT = 1; // si es "0" el timer lo tomara como interrupcion
    TIM2 -> DMAINTENR &= ~TIM_UIE; // Se deshabilita la interrupcion por actualizacion (CNT=0)
    PFIC -> IENR[1] &= ~(1 << (TIM2_IRQn-32)); // Se deshabilita la interrupcion general para el timer 2
}

void TIM2_IRQHandler(){ // Rutina de interrupcion TIMER 2
    if (TIM2 -> INTFR & TIM_UIF){
        Tiempo_Seg--;
        TIM2 -> INTFR &= ~TIM_UIF; // Borra bandera de interrupcion
    }  
}