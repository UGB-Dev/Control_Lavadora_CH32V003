/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : UGB_Dev
 * Version            : V.1
 * Date               : 2025/11/20
 * Description        : Control de Lavadora.
 *********************************************************************************/
 /*
    Configuracion en archivo sytem_ch32v00x.c
 
    comentar esta linea -> #define SYSCLK_FREQ_48MHz_HSE   48000000
    descomentar esta linea -> #define SYSCLK_FREQ_24MHZ_HSI   HSI_VALUE

    El MCU CH32V003 trabajara a 24 MHz y los perifericos a 24 MHz
 */

#include "debug.h"
#include "EXTERNAL_INTERRUPT.h"
#include "I2C_SOFTWARE.h"
#include "OLED_SSD1306.h"
#include "TIM2_TIMER_MODE.h"
#include "LAVADORA.h"
#include "TIM1_PWM.h"

int main(void){
    Delay_Init();
    Extern_Interrupt_Init();
    TIM2_Timer_Mode_Init();
    PWM_Init(PWM_MODE1);
    PWM_Set(2000, 50, 100000); // Generador de 2 KHz para el sonido 
    PWM_Disable(); // Salida desactivada
    I2C_SOFT_Init(100000); // I2C a 100 kb/s

    OLED_Init();
    Lavadora_Init();

    uint8_t Flag_Tecla=0, N_Veces_Tecla=0;;
    uint8_t Time_Stop_Alarm = 0, Flag_Stop=0, ON_OFF_Alarm=0, N_Veces=0;
    
    while(1){
        OLED_Clear();
        OLED_Cuadrado(0, 0, 127, 63);
        OLED_Cuadrado(1, 1, 125, 61);
        OLED_Print_Str(26, 8,  "CENTRIFUGADO");
        OLED_Print_Str(26, 24, "   TIEMPO:");

        switch (PIN_Activo) {
            case PLAY: // PLAY = 0
                TIM2_Enable();
                ON_MOTOR;
                PIN_Activo = 6;
                Flag_Stop = 1;
                Flag_Tecla = 1;
                Lavadora_Formato(Tiempo_Seg);
                break;

            case PAUSE: // PAUSE = 1
                OFF_MOTOR;
                TIM2_Disable();
                Flag_Tecla = 1;
                PIN_Activo = 8;
                Lavadora_Formato(Tiempo_Seg);
                break;

            case STOP: // STOP = 2
                Flag_Tecla = 1;
                PIN_Activo = 6;
                Tiempo_Seg = 0;
                break;
            
            case MIN_1: // MIN_1 = 3
                OFF_MOTOR;
                Flag_Tecla = 1;
                TIM2_Disable();
                Tiempo_Seg += 60; 
                PIN_Activo = 6;
                break;

            case MIN_5: // MIN_5 = 4
                OFF_MOTOR;
                Flag_Tecla = 1;
                TIM2_Disable();
                Tiempo_Seg += 300; 
                PIN_Activo = 6;
                break;

            case MIN_10: // MIN_10 = 5
                OFF_MOTOR;
                Flag_Tecla = 1;
                TIM2_Disable();
                Tiempo_Seg += 600; 
                PIN_Activo = 6;
                break;
            
            case 6:
                if (Tiempo_Seg < 1) {
                    OFF_MOTOR;
                    TIM2_Disable();
                    OLED_Print_Str(50, 40, Stop);
                    OLED_Print_Buffer();
                    PIN_Activo = 7;
                    Tiempo_Seg = 0; 
                }
                else{
                    Lavadora_Formato(Tiempo_Seg);
                }
                break;

            case 7:
                OLED_Print_Str(50, 40, Stop);
                break;
            
            case 8:
                OLED_Print_Str(50, 40, Pause);
                break;
        }
        
        OLED_Print_Buffer();

        /* ACTIVACION DE SONIDO EN STOP */
        if (Tiempo_Seg == 0  && Flag_Stop == 1) {
            Time_Stop_Alarm++;
        }

        if (Time_Stop_Alarm == 3) { // 10us*(1024 bytes)*10 bits* 3 cuentas = 300 ms
            Time_Stop_Alarm = 0;
            N_Veces++;
            if (ON_OFF_Alarm == 0) {
                ON_OFF_Alarm = 1;
                PWM_Enable();
            }
            else {
                ON_OFF_Alarm = 0;
                PWM_Disable();
            }
        }

        if (N_Veces > 9) {
            N_Veces = 0;
            Flag_Stop = 0;
        }

        /* ACTIVACION DE SONIDO DE TECLAS */
        if (N_Veces_Tecla == 1) {
            PWM_Disable();
            N_Veces_Tecla=0;
        }

        if (Flag_Tecla == 1) {
            Flag_Tecla = 0;
            PWM_Enable();
            N_Veces_Tecla = 1;
        }
    }
}
