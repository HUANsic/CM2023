/*
 * ILI9341_Porting.h
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */

#ifndef LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#define LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#include "debug.h"

/* TODO: 需要外部实现的函数*/
void LVGL_TIM2_Init(void);//在main函数中初始化
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
/*TODO: 实现SPI全双工初始化，参数如下：
Direction:SPI_Direction_2Lines_FullDuplex
SPI_Mode:SPI_Mode_Master
SPI_DataSize:SPI_DataSize_8b
SPI_CPOL:SPI_CPOL_Low
SPI_CPHA:SPI_CPHA_1Edge
SPI_NSS:SPI_NSS_Soft
SPI_FirstBit:SPI_FirstBit_MSB
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

#endif /* LVGL_GUI_DRIVERS_ILI9341_PORTING_H_ */
