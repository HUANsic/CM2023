/*
 * huansic_FullFunction_lib.h
 *
 *  Created on: Apr 1, 2023
 *      Author: abcde
 */

#ifndef USER_HUANSIC_FULLFUNCTION_LIB_H_
#define USER_HUANSIC_FULLFUNCTION_LIB_H_

#include "debug.h"
#include "huansic_types.h"
#include "huansic_util.h"

void huansic_Initialize(void);

void huansic_Edgeboard_Init(Edge_TypeDef *edgeboard);

void huansic_Edgeboard_Send(Edge_TypeDef *edgeboard, char ch);

void huansic_Edgeboard_SendString(Edge_TypeDef *edgeboard, char *str, uint8_t len);

void huansic_Edgeboard_Interpret(Edge_TypeDef *edgeboard);

void huansic_Edgeboard_IRQ(Edge_TypeDef *edgeboard, uint8_t msg);

void huansic_Motor_Init(Motor_TypeDef *motor);

void huansic_Motor_Set(Motor_TypeDef *motor, int16_t power);

void huansic_Motor_Enable(Motor_TypeDef *motor);

void huansic_Motor_Disable(Motor_TypeDef *motor);

void huansic_Motor_PID_Init(PID_TypeDef *pid_controller);

void huansic_Motor_PID_SetGoal(PID_TypeDef *pid_controller, int16_t goal);

void huansic_Motor_PID_IRQ(PID_TypeDef *pid_controller);

void huansic_Servo_Init(Servo_TypeDef *servo);

void huansic_Servo_Set(Servo_TypeDef *servo, int16_t angle);

void huansic_Encoder_Init(Encoder_TypeDef *encoder);

uint16_t huansic_Encoder_GetValue(Encoder_TypeDef *encoder);

float huansic_Encoder_GetFullValue(Encoder_TypeDef *encoder);

void huansic_LED_Init(LED_TypeDef *led);

void huansic_LED_Set(LED_TypeDef *led, uint8_t state);

uint8_t huansic_LED_Get(LED_TypeDef *led);

void huansic_Screen_Init(Screen_TypeDef *screen);

void huansic_TouchScreen_IRQ(void);


#endif /* USER_HUANSIC_FULLFUNCTION_LIB_H_ */
