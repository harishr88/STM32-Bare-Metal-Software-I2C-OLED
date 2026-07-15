# STM32 Bare Metal I2C Driver + SSD1306 OLED Display

## Overview
Complete bare metal I2C driver written from scratch on STM32F103 
Blue Pill — no HAL I2C functions used. Drives SSD1306 OLED display 
using manual bit-banging with full ACK detection and timeout handling.

## Why This Project Matters
Most engineers use HAL_I2C functions without understanding the 
underlying protocol. This project implements every I2C signal 
manually — start condition, stop condition, bit transmission, 
ACK/NACK detection — demonstrating deep protocol understanding.

## Hardware
- STM32F103C8T6 Blue Pill
- SSD1306 128x64 OLED Display (I2C)
- PA0 → SCL
- PA1 → SDA

## What Was Implemented From Scratch
- I2C Start condition (SDA low while SCL high)
- I2C Stop condition (SDA high while SCL high)  
- Byte transmission (MSB first, 8 bits)
- ACK detection with 100ms timeout
- BSRR register for atomic pin control
- SSD1306 initialization sequence
- Display clear function
- Character write at specific page/column

## Key Concepts Demonstrated
- Bare metal register manipulation (BSRR, IDR)
- I2C protocol implementation without library
- Timeout handling for robust communication
- Macro-based pin abstraction
- Open-drain GPIO configuration for I2C

## Tools
- STM32CubeIDE
- ST-Link V2
- STM32F103C8T6 Blue Pill

## Code Highlights
```c
// Atomic pin control using BSRR register
#define sclhigh() (GPIOA->BSRR = (1 << 0))
#define scllow()  (GPIOA->BSRR = (1 << 16))

// ACK detection with timeout
time = HAL_GetTick();
while(sdaread() && ((HAL_GetTick()-time) < 100));
if(sdaread()) timeout();
```

## Interview Talking Points
- "I implemented I2C from scratch using bit-banging on STM32"
- "Used BSRR register for atomic SCL/SDA control"  
- "Implemented ACK detection with timeout for robust error handling"
- "Wrote SSD1306 initialization sequence from datasheet"
