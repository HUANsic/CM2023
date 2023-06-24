#ifndef ILI9341_H_
#define ILI9341_H_
#ifndef uint8_t
#define uint8_t unsigned char
#endif

#ifndef uint16_t
#define uint16_t unsigned short
#endif

#ifndef uint32_t
#define uint32_t unsigned int
#endif

#ifndef uint64_t
#define uint64_t unsigned long long
#endif

#define ILI9341_SCREEN_HEIGHT 240
#define ILI9341_SCREEN_WIDTH 320

// SPI INSTANCE
#define WSPI_INSTANCE SPI1

// CHIP SELECT PIN AND PORT, STANDARD GPIO
#define LCD_CS_PORT GPIOC
#define LCD_CS_PIN CS_Pin

// DATA COMMAND PIN AND PORT, STANDARD GPIO
#define LCD_DC_PORT GPIOC
#define LCD_DC_PIN DC_Pin

// RESET PIN AND PORT, STANDARD GPIO
#define LCD_RST_PORT GPIOC
#define LCD_RST_PIN RST_Pin

#define BURST_MAX_SIZE 500

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

/* TODO: 需要外部实现的函数*/
/*TODO: 实现SPI全双工初始化，参数如下：
Direction:SPI_Direction_2Lines_FullDuplex
SPI_Mode:SPI_Mode_Master
SPI_DataSize:SPI_DataSize_8b
SPI_CPOL:SPI_CPOL_Low
SPI_CPHA:SPI_CPHA_1Edge
SPI_NSS:SPI_NSS_Soft
SPI_FirstBit:SPI_FirstBit_LSB
SPI_CRCPolynomial:7
*/
void WCH_ILI9341_SPI_FullDuplex_Init(void);
/*TODO: 实现GPIO初始化，参考实现如下：
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
使能引脚需要另外指定
*/
void WCH_ILI9341_GPIO_FullDuplex_Init(void);
/*延时函数*/
void Delay_Ms(uint32_t n);
/*For debug use*/
void SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data);

#endif