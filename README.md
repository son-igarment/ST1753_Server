# ST1753_Server - ST7735 LCD Driver

## Overview
This project implements a driver for the ST7735 LCD display using the TM4C123 microcontroller. Created by Phạm Lê Ngọc Sơn, this project provides a simple interface for communicating with the ST7735 LCD display via SPI.

## Hardware Connections
The project uses the following pin connections:
- **SPI Interface:**
  - PD0 = SSI1Clk (Clock)
  - PD3 = SSI1Tx (Data)
  - PF2 = DC (Data/Command selection pin)
- **LCD Pins:**
  - RESET -----> PA7
  - CS --------> PA3
  - DC --------> PA6

## Project Structure
- `main.c`: Main implementation file containing SPI initialization and communication functions
- `GLCD_ST7735.h`: Header file with LCD pin definitions
- `GLCD_ST7735.c`: Implementation file for LCD-specific functions (currently empty)
- `ST7753_driver.uvprojx`: Keil MDK project file
- `ST7753_driver.uvoptx`: Keil MDK options file
- `RTE/`: Run-Time Environment files for device configuration

## Functionality
The current implementation includes:
1. SSI (SPI) initialization for communication with the LCD
2. Basic timer delay functionality
3. Data transmission via SPI

## How to Use
1. Open the project in Keil MDK using the ST7753_driver.uvprojx file
2. Build the project
3. Flash the compiled code to a TM4C123 microcontroller
4. Connect the ST7735 LCD according to the pin definitions

## Development Status
This project is currently in development. The basic SPI communication is implemented, but the complete LCD driver functionality is still being developed.

## Future Improvements
- Complete implementation of the GLCD_ST7735.c file with drawing functions
- Add support for text rendering
- Add support for image display
- Implement additional graphical primitives (circles, rectangles, etc.)

## License
Copyright © 2023 Phạm Lê Ngọc Sơn. All rights reserved.