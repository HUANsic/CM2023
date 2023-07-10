/*
 * ILI9341_Porting.h
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */

#ifndef LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#define LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#include "debug.h"

/* TODO: ��Ҫ�ⲿʵ�ֵĺ���*/
void LVGL_TIM2_Init(void);//��main�����г�ʼ��
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
/*TODO: ʵ��SPIȫ˫����ʼ�����������£�
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
/*TODO: ʵ��GPIO��ʼ�����ο�ʵ�����£�
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
ʹ��������Ҫ����ָ��
*/
void WCH_ILI9341_GPIO_FullDuplex_Init(void);

#endif /* LVGL_GUI_DRIVERS_ILI9341_PORTING_H_ */
