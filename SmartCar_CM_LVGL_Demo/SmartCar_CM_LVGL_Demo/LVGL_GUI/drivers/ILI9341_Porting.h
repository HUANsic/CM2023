/*
 * ILI9341_Porting.h
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */

#ifndef LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#define LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#include "debug.h"

/* 已在CH32V307平台实现的代码  */
void LVGL_TIM2_Init(void);
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void WCH_ILI9341_SPI_FullDuplex_Init(void);
void WCH_ILI9341_GPIO_FullDuplex_Init(void);

#define NOT_PORTED
#ifdef NOT_PORTED
#warning You have not ported two functions which receives the command from the ui.
#endif
/* TODO:需要实现的函数。请include "ILI9341_Porting.h"，并删除本头文件对应的c文件中函数体  */
/* 发车 */
void ui_cmd_go(void);
/* 紧急停车 */
void ui_cmd_stop(void);

#endif /* LVGL_GUI_DRIVERS_ILI9341_PORTING_H_ */
