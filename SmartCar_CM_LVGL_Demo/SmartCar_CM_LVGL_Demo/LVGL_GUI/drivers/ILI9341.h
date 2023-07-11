#ifndef ILI9341_H_
#define ILI9341_H_
#include "ch32v30x.h"
#include "ILI9341_Porting.h"

#define ILI9341_SCREEN_HEIGHT 240
#define ILI9341_SCREEN_WIDTH 320

// SPI INSTANCE
#define WSPI_INSTANCE SPI3

// CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT GPIOD
#define LCD_CS_PIN GPIO_Pin_0

// DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT GPIOD
#define LCD_DC_PIN GPIO_Pin_2

// RESET PIN AND PORT, STANDARD GPIO
#define LCD_RST_PORT GPIOD
#define LCD_RST_PIN GPIO_Pin_1

#define LCD_BACKLIGHT_PORT GPIOD
#define LCD_BACKLIGHT_PIN GPIO_Pin_3

#define BURST_MAX_SIZE 512

#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

#define SCREEN_VERTICAL_1 0
#define SCREEN_HORIZONTAL_1 1
#define SCREEN_VERTICAL_2 2
#define SCREEN_HORIZONTAL_2 3

/*延时函数*/
void Delay_Ms(uint32_t n);
/*For debug use*/
void SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data);

#endif
