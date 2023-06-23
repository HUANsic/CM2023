/*
 * huansic_FullFunction_lib.h
 *
 *  Created on: Apr 1, 2023
 *      Author: abcde
 */

#ifndef USER_HUANSIC_FULLFUNCTION_LIB_H_
#define USER_HUANSIC_FULLFUNCTION_LIB_H_

#include "debug.h"
#include <huansic_types.h>
#include <huansic_util.h>

void huansic_Initialize(void);

void huansic_Clocks_Init(void);

void huansic_Edgeboard_Init(void);

void huansic_Motor_Init(Motor_TypeDef *motor);

void huansic_Servo_Init(Servo_TypeDef *servo);

void huansic_Encoder_Init(void);

void huansic_LED_Init(void);


void huansic_Edgeboard_Interpret(void);

void huansic_Edgeboard_IRQ(void);


void huansic_Motor_PID_Init(void);

void huansic_Motor_Set(int16_t power);

void huansic_Motor_PID_IRQ(void);


void huansic_Servo_Set(int8_t angle);


uint16_t huansic_Encoder_GetValue(void);


void huansic_LED1_Set(uint8_t state);

void huansic_LED2_Set(uint8_t state);

void huansic_LED3_Set(uint8_t state);

void huansic_LED4_Set(uint8_t state);


#endif /* USER_HUANSIC_FULLFUNCTION_LIB_H_ */
