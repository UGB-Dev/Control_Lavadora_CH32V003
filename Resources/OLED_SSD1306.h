/*

    OLED_SSD1306.h

*/

#ifndef __OLED_SSD1306_H__
#define __OLED_SSD1306_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32v00x.h"
#include "I2C_SOFTWARE.h"
#include <stdlib.h>

#define Width 128
#define Height 64

extern const uint8_t Config_OLED[];
extern const uint8_t OLED_FONT[];
extern uint8_t Buffer[];

void Dato_(void);
void Comando_(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Print_Pixel(int16_t Pos_x, int16_t Pos_y);
void OLED_Print_Buffer(void);
void OLED_Linea(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1 );
void OLED_Cuadrado(uint8_t X0, uint8_t Y0, uint8_t LadoX, uint8_t LadoY);
void OLED_Print_Str(uint8_t xpos, uint8_t ypos,const char* DATA);
void OLED_Print_Char(uint8_t xpos, uint8_t ypos, char DATA);

#ifdef __cplusplus
 }
#endif //__OLED_SSD1306_H__
#endif