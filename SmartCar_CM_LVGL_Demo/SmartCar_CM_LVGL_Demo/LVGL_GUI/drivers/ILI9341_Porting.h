/*
 * ILI9341_Porting.h
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */

#ifndef LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#define LVGL_GUI_DRIVERS_ILI9341_PORTING_H_
#include "debug.h"

extern float ui_Kp;
extern float ui_Ki;
extern float ui_Kd;

/* ����CH32V307ƽ̨ʵ�ֵĴ���  */
void LVGL_TIM2_Init(void);
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void WCH_ILI9341_SPI_FullDuplex_Init(void);
void WCH_ILI9341_GPIO_FullDuplex_Init(void);

#define NOT_PORTED
#ifdef NOT_PORTED
#warning You have not ported two functions which receives the command from the ui.
#endif
/* TODO:��Ҫʵ�ֵĺ�������include "ILI9341_Porting.h"����ɾ����ͷ�ļ���Ӧ��c�ļ��к�����  */
/* ���� */
void ui_cmd_go(void);
/* ����ͣ�� */
void ui_cmd_stop(void);
/* ����Kp */
void ui_display_Kp(float data);
/* ����Ki */
void ui_display_Ki(float data);
/* ����Kd */
void ui_display_Kd(float data);
/* �����ٶ� */
void ui_display_speed(float data);
/* ����PIDĿ��ֵ */
void ui_display_pid_goal(float data);
/* ���µ�ǰ״̬ */
void ui_display_step_counter(uint8_t* data);

#endif /* LVGL_GUI_DRIVERS_ILI9341_PORTING_H_ */
