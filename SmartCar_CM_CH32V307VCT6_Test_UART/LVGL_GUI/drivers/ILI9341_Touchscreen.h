#ifndef TOUCH_H
#define TOUCH_H

#include "ILI9341.h"

#define TP_CLK_PORT GPIOB
#define TP_CLK_PIN GPIO_Pin_3

#define TP_CS_PORT GPIOD
#define TP_CS_PIN GPIO_Pin_4

#define TP_MISO_PORT GPIOB
#define TP_MISO_PIN GPIO_Pin_4

#define TP_MOSI_PORT GPIOB
#define TP_MOSI_PIN GPIO_Pin_5

#define TP_IRQ_PORT GPIOD
#define TP_IRQ_PIN GPIO_Pin_5

#define CMD_RDY 0X90
#define CMD_RDX 0XD0

// RETURN VALUES FOR TP_Touchpad_Pressed
#define TOUCHPAD_NOT_PRESSED 0
#define TOUCHPAD_PRESSED 1

// RETURN VALUES FOR TP_Read_Coordinates
#define TOUCHPAD_DATA_OK 1
#define TOUCHPAD_DATA_NOISY 0

// HARDCODED CALIBRATION, CHANGE IF REQUIRED
#define X_OFFSET 13
#define Y_OFFSET 15
#define X_MAGNITUDE 1.16
#define Y_MAGNITUDE 1.16

// CONVERTING 16bit Value to Screen coordinates
//  65535/273 = 240!
//  65535/204 = 320!
#define X_TRANSLATION 273
#define Y_TRANSLATION 204

// In order to increase accuracy of location reads library samples
// NO_OF_POSITION_SAMPLES numbers of locations and averages them
// If library runs too slow decrease NO_OF_POSITION_SAMPLES, but
// expect inreasingly noisy or incorrect locations returned

#define NO_OF_POSITION_SAMPLES 1000

// Internal Touchpad command, do not call directly
uint16_t TP_Read(void);

// Internal Touchpad command, do not call directly
void TP_Write(uint8_t value);

// Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2]);

// Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void);

#endif
