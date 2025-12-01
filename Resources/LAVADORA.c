/*

    LAVADORA.c

*/

#include "LAVADORA.h"

void Lavadora_Formato(uint16_t Tiempo){
    uint8_t Hora[3] = {(Tiempo/3600)/10+'0', (Tiempo/3600)%10+'0',':'};
    uint8_t Min[3] = {((Tiempo%3600)/60)/10+'0', ((Tiempo%3600)/60)%10+'0',':'};
    uint8_t Seg[2] ={((Tiempo%3600)%60)/10+'0', ((Tiempo%3600)%60)%10+'0'};
    
    /* IMPRIME EL TIEMPO EN HORAS */
    OLED_Print_Str(38, 40, (const char*) Hora);
    OLED_Print_Str(56, 40, (const char*) Min);
    OLED_Print_Str(74, 40, (const char*) Seg);
}

void Lavadora_Init(void){
    OLED_Cuadrado(0, 0, 127, 63);
    OLED_Cuadrado(1, 1, 125, 61);
    OLED_Print_Str(10, 16, "INTERFAZ LAVADORA");
    OLED_Print_Str(10, 32, "   VERSION 1.0");
    OLED_Print_Str(70, 48, "UGB_DEV");
    OLED_Print_Buffer();
    Delay_Ms(5000);
    OLED_Clear();
    OLED_Print_Buffer();
    
    /*  CONFIGURACION DE PERIFERICOS  */
    RCC -> APB2PCENR |= RCC_IOPDEN; // Se habilita el reloj del puerto C y Funcion alternativa (Interrupcion)

    /*  CONFIGURACION DE LOS PINES DEL PUERTO C  */
    GPIOD -> CFGLR &= ~(GPIO_CFGLR_MODE3 | GPIO_CFGLR_CNF3 ); // Borra configuraciones iniciales
    GPIOD -> CFGLR |= GPIO_CFGLR_MODE3;
}