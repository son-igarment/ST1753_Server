/*
 * ST7735 LCD Driver - Header File
 * Author: Phạm Lê Ngọc Sơn
 * Date: 2023
 *
 * Header file for ST7735 LCD driver implementation.
 */

#ifndef GLCD_ST7735_H
#define GLCD_ST7735_H

/* LCD Pins
		RESET -----> PA7
		CS --------> PA3
		DC --------> PA6
*/

// Function prototypes
void ST7735_Init(void);
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg);
void ST7735_DrawString(uint16_t x, uint16_t y, char *string, uint16_t color, uint16_t bg);

#endif /* GLCD_ST7735_H */