/*

    LAVADORA.h

*/

#ifndef __LAVADORA_H__
#define __LAVADORA_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32v00x.h"
#include "OLED_SSD1306.h"

#define Stop "STOP"
#define Pause "PAUSE"

#define PLAY 0
#define PAUSE 1
#define STOP 2
#define MIN_1 3
#define MIN_5 4
#define MIN_10 5
#define ON_MOTOR GPIOD -> BSHR = GPIO_BSHR_BS3
#define OFF_MOTOR GPIOD -> BSHR = GPIO_BSHR_BR3 

void Lavadora_Init(void);
void Lavadora_Formato(uint16_t Tiempo);

#ifdef __cplusplus
 }
#endif //__LAVADORA_H__
#endif