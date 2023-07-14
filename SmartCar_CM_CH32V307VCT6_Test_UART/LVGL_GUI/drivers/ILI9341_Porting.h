/*
 * ILI9341_Porting.h
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */

#ifndef LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#define LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#include "debug.h"

/* ����CH32V307ƽ̨ʵ�ֵĴ���  */
void LVGL_TIM2_Init(void);
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void WCH_ILI9341_SPI_FullDuplex_Init(void);
void WCH_ILI9341_GPIO_FullDuplex_Init(void);
/* �ϴ��ٶ� */
void ui_display_speed(float data);
/* �ϴ�PIDĿ��ֵ */
void ui_display_pid_goal(float data);
/* �ϴ���ǰ״̬ */
void ui_display_step_counter(uint8_t* data);

//#define NOT_PORTED
#ifdef NOT_PORTED
#warning You have not implement two functions and two pinters which receives the command from the ui.
#warning You should call ui_display_speed,ui_display_pid_goal and ui_display_step_counter in your code.
#warning You also need to enable `Use wchprintfloat` in C/C++ Build/GNC Risc-V Cross C Linker
#endif
/* TODO:��Ҫʵ�ֵĺ�������include "ILI9341_Porting.h"����ɾ����ͷ�ļ���Ӧ��c�ļ��к�����  */
/* ���� */
void ui_cmd_go(void);
/* ����ͣ�� */
void ui_cmd_stop(void);

/* TODO:��Ҫ�����ָ�롣  */
extern float* ui_Kp;
extern float* ui_Ki;
extern float* ui_Kd;

#endif /* LVGL_GUI_DRIVERS_ILI9341_PORTING_H_ */
