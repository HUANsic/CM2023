/*
 * huansic_types.h
 *
 *  Created on: Jun 19, 2023
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_TYPES_H_
#define USER_HUANSIC_TYPES_H_

#include "ch32v30x.h"

typedef enum {
	HUAN_LED_1 = 0,
	HUAN_LED_2,
	HUAN_LED_3,
	HUAN_LED_4,
	HUAN_LED_5,
	HUAN_LED_6
} LED_Index;

typedef struct {
	TIM_TypeDef* timer;
	uint16_t channel;
	GPIO_TypeDef *port;
	uint16_t pin;
} Servo_TypeDef;

typedef struct {
	TIM_TypeDef *timer;
	uint16_t channelP, channelN;
	GPIO_TypeDef *portP, *portN, *portEn;
	uint16_t pinP, pinN, pinEn;
} Motor_TypeDef;

typedef struct {
	USART_TypeDef *uart;
	GPIO_TypeDef *txport, *rxport;
	uint16_t txpin, rxpin;
	uint8_t highByte, lowByte;
} Edge_TypeDef;

typedef struct {
	TIM_TypeDef *counter;
	GPIO_TypeDef *Aport, *Bport;
	uint16_t Apin, Bpin;
	uint32_t overflow;
} Encoder_TypeDef;

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} LED_TypeDef;

typedef struct {
	TIM_TypeDef *timer;
	float kp, ki, kd, dt;
	float goal;
	float input;
	float error, lastError, dError, sError;
	uint8_t enabled;
} PID_TypeDef;

#endif /* USER_HUANSIC_TYPES_H_ */
