/*

    EXTERNAL_INTERRUPT.c

*/

#include "EXTERNAL_INTERRUPT.h"

volatile uint8_t PIN_Activo = 7; // Valor para imprimir STOP

void Extern_Interrupt_Init(void){
    /*  CONFIGURACION DE PERIFERICOS  */
    RCC -> APB2PCENR |= RCC_IOPCEN | RCC_AFIOEN; // Se habilita el reloj del puerto C y Funcion alternativa (Interrupcion)

    /*  CONFIGURACION DE LOS PINES DEL PUERTO C  */
    GPIOC -> CFGLR &= ~(GPIO_CFGLR_MODE0 | GPIO_CFGLR_CNF0 | 
                        GPIO_CFGLR_MODE1 | GPIO_CFGLR_CNF1 |
                        GPIO_CFGLR_MODE2 | GPIO_CFGLR_CNF2 |
                        GPIO_CFGLR_MODE3 | GPIO_CFGLR_CNF3 |
                        GPIO_CFGLR_MODE4 | GPIO_CFGLR_CNF4 |
                        GPIO_CFGLR_MODE5 | GPIO_CFGLR_CNF5); // Borra configuraciones iniciales
    
    GPIOC -> CFGLR |= GPIO_CFGLR_CNF0_1 | GPIO_CFGLR_CNF1_1 | GPIO_CFGLR_CNF2_1 | 
                      GPIO_CFGLR_CNF3_1 | GPIO_CFGLR_CNF4_1 | GPIO_CFGLR_CNF5_1; // PC0 a PC5 como entrada en modo Pull-Down por defecto

    GPIOC -> OUTDR |= GPIO_OUTDR_ODR0 | GPIO_OUTDR_ODR1 | GPIO_OUTDR_ODR2 |
                      GPIO_OUTDR_ODR3 | GPIO_OUTDR_ODR4 | GPIO_OUTDR_ODR5; // PC0 a PC5 como entrada en modo Pull-Down por defecto
                      
    /*  CONFIGURACION DE PINES DE INTERRUPCION EXTERNA  */
    EXTI -> INTENR |= EXTI_INTENR_MR0 | EXTI_INTENR_MR1 | EXTI_INTENR_MR2 |
                      EXTI_INTENR_MR3 | EXTI_INTENR_MR4 | EXTI_INTENR_MR5; // Se habilita la interrupcion para el pin PC0 a PC5

    EXTI -> FTENR |= EXTI_FTENR_TR0 | EXTI_FTENR_TR1 | EXTI_FTENR_TR2 |
                     EXTI_FTENR_TR3 | EXTI_FTENR_TR4 | EXTI_FTENR_TR5; // Se ajusta la captura por flanco de bajada

    AFIO -> EXTICR |= AFIO_EXTICR1_EXTI0_PC | AFIO_EXTICR1_EXTI1_PC | AFIO_EXTICR1_EXTI2_PC |
                      AFIO_EXTICR1_EXTI3_PC | AFIO_EXTICR1_EXTI4_PC | AFIO_EXTICR1_EXTI5_PC; // Se habilita la interrupcion externa en PC0 a PC5
    
    PFIC -> IENR[0] = (1<<EXTI7_0_IRQn); // Se habilita la peticion de interrupcion externa de 0 a 7 independientemente del puerto A, C o D
}

void EXTI7_0_IRQHandler(void){
    /*  DETERMINA SI LA INTERRUPCION FUE EN PC0  */
    if (EXTI -> INTFR & EXTI_INTF_INTF0) {
        if (!(GPIOC -> INDR & GPIO_INDR_IDR0)){
            while (!(GPIOC -> INDR & GPIO_INDR_IDR0));
        }
        PIN_Activo = 0;
        EXTI -> INTFR = EXTI_INTF_INTF0;
    }
    
    /*  DETERMINA SI LA INTERRUPCION FUE EN PC1  */
    else if (EXTI -> INTFR & EXTI_INTF_INTF1) {
        if (!(GPIOC -> INDR & GPIO_INDR_IDR1)){
            while (!(GPIOC -> INDR & GPIO_INDR_IDR1));
        }
        PIN_Activo = 1;
        EXTI -> INTFR = EXTI_INTF_INTF1;
    }

    /*  DETERMINA SI LA INTERRUPCION FUE EN PC2  */
    else if (EXTI -> INTFR & EXTI_INTF_INTF2) {
        if (!(GPIOC -> INDR & GPIO_INDR_IDR2)){
            while (!(GPIOC -> INDR & GPIO_INDR_IDR2));
        }
        PIN_Activo = 2;
        EXTI -> INTFR = EXTI_INTF_INTF2;
    }

    /*  DETERMINA SI LA INTERRUPCION FUE EN PC3  */
    else if (EXTI -> INTFR & EXTI_INTF_INTF3) {
        if (!(GPIOC -> INDR & GPIO_INDR_IDR3)){
            while (!(GPIOC -> INDR & GPIO_INDR_IDR3));
        }
        PIN_Activo = 3;
        EXTI -> INTFR = EXTI_INTF_INTF3;
    }

    /*  DETERMINA SI LA INTERRUPCION FUE EN PC4  */
    else if (EXTI -> INTFR & EXTI_INTF_INTF4) {
        if (!(GPIOC -> INDR & GPIO_INDR_IDR4)){
            while (!(GPIOC -> INDR & GPIO_INDR_IDR4));
        }
        PIN_Activo = 4;
        EXTI -> INTFR = EXTI_INTF_INTF4;
    }

    /*  DETERMINA SI LA INTERRUPCION FUE EN PC5  */
    else if (EXTI -> INTFR & EXTI_INTF_INTF5) {
        if (!(GPIOC -> INDR & GPIO_INDR_IDR5)){
            while (!(GPIOC -> INDR & GPIO_INDR_IDR5));
        }
        PIN_Activo = 5;
        EXTI -> INTFR = EXTI_INTF_INTF5;
    }
}