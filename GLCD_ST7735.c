/*
 * ST7735 LCD Driver - Implementation File
 * Author: Phạm Lê Ngọc Sơn
 * Date: 2023
 *
 * Implementation file for ST7735 LCD driver.
 */

#include "TM4C123.h"
#include "GLCD_ST7735.h"

// ST7735 LCD controller commands
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define ST7735_BLACK   0x0000
#define ST7735_BLUE    0x001F
#define ST7735_RED     0xF800
#define ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0
#define ST7735_WHITE   0xFFFF

// External declarations from main.c
extern void SSIWrite(unsigned char);
extern void timer0_delayMs(uint32_t);

// Function to write a command to the LCD
static void ST7735_WriteCommand(uint8_t cmd) {
    // Set DC pin low for command
    GPIOA->DATA &= ~(0x40);  // PA6 low
    SSIWrite(cmd);
}

// Function to write data to the LCD
static void ST7735_WriteData(uint8_t data) {
    // Set DC pin high for data
    GPIOA->DATA |= (0x40);   // PA6 high
    SSIWrite(data);
}

// Initialize the ST7735 LCD
void ST7735_Init(void) {
    // Initialize GPIO for control pins
    SYSCTL->RCGCGPIO |= (0x1);       // Enable Port A
    GPIOA->DIR |= (0xC8);            // Set PA3, PA6, PA7 as outputs
    GPIOA->DEN |= (0xC8);            // Enable digital functions on PA3, PA6, PA7
    
    // Reset the display
    GPIOA->DATA |= (0x80);           // PA7 high
    timer0_delayMs(10);
    GPIOA->DATA &= ~(0x80);          // PA7 low
    timer0_delayMs(10);
    GPIOA->DATA |= (0x80);           // PA7 high
    timer0_delayMs(10);
    
    // Initialize display
    ST7735_WriteCommand(ST7735_SWRESET);
    timer0_delayMs(150);
    
    ST7735_WriteCommand(ST7735_SLPOUT);
    timer0_delayMs(500);
    
    ST7735_WriteCommand(ST7735_FRMCTR1);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2C);
    ST7735_WriteData(0x2D);
    
    ST7735_WriteCommand(ST7735_FRMCTR2);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2C);
    ST7735_WriteData(0x2D);
    
    ST7735_WriteCommand(ST7735_FRMCTR3);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2C);
    ST7735_WriteData(0x2D);
    ST7735_WriteData(0x01);
    ST7735_WriteData(0x2C);
    ST7735_WriteData(0x2D);
    
    ST7735_WriteCommand(ST7735_INVCTR);
    ST7735_WriteData(0x07);
    
    ST7735_WriteCommand(ST7735_PWCTR1);
    ST7735_WriteData(0xA2);
    ST7735_WriteData(0x02);
    ST7735_WriteData(0x84);
    
    ST7735_WriteCommand(ST7735_PWCTR2);
    ST7735_WriteData(0xC5);
    
    ST7735_WriteCommand(ST7735_PWCTR3);
    ST7735_WriteData(0x0A);
    ST7735_WriteData(0x00);
    
    ST7735_WriteCommand(ST7735_PWCTR4);
    ST7735_WriteData(0x8A);
    ST7735_WriteData(0x2A);
    
    ST7735_WriteCommand(ST7735_PWCTR5);
    ST7735_WriteData(0x8A);
    ST7735_WriteData(0xEE);
    
    ST7735_WriteCommand(ST7735_VMCTR1);
    ST7735_WriteData(0x0E);
    
    ST7735_WriteCommand(ST7735_INVOFF);
    
    ST7735_WriteCommand(ST7735_MADCTL);
    ST7735_WriteData(0xC8);
    
    ST7735_WriteCommand(ST7735_COLMOD);
    ST7735_WriteData(0x05);
    
    ST7735_WriteCommand(ST7735_DISPON);
    timer0_delayMs(100);
}

// Draw a single pixel
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    // Set the x and y coordinates
    ST7735_WriteCommand(ST7735_CASET);
    ST7735_WriteData(0x00);
    ST7735_WriteData(x);
    ST7735_WriteData(0x00);
    ST7735_WriteData(x);
    
    ST7735_WriteCommand(ST7735_RASET);
    ST7735_WriteData(0x00);
    ST7735_WriteData(y);
    ST7735_WriteData(0x00);
    ST7735_WriteData(y);
    
    // Write the pixel color
    ST7735_WriteCommand(ST7735_RAMWR);
    ST7735_WriteData(color >> 8);
    ST7735_WriteData(color & 0xFF);
}

// Fill the entire screen with a single color
void ST7735_FillScreen(uint16_t color) {
    uint16_t i, j;
    
    ST7735_WriteCommand(ST7735_CASET);
    ST7735_WriteData(0x00);
    ST7735_WriteData(0x00);
    ST7735_WriteData(0x00);
    ST7735_WriteData(0x7F);
    
    ST7735_WriteCommand(ST7735_RASET);
    ST7735_WriteData(0x00);
    ST7735_WriteData(0x00);
    ST7735_WriteData(0x00);
    ST7735_WriteData(0x9F);
    
    ST7735_WriteCommand(ST7735_RAMWR);
    
    for (i = 0; i < 128; i++) {
        for (j = 0; j < 160; j++) {
            ST7735_WriteData(color >> 8);
            ST7735_WriteData(color & 0xFF);
        }
    }
}

// Basic character drawing functions - placeholder for now
void ST7735_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bg) {
    // TODO: Implement character drawing
}

void ST7735_DrawString(uint16_t x, uint16_t y, char *string, uint16_t color, uint16_t bg) {
    // TODO: Implement string drawing
}
