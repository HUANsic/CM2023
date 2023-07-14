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
	GPIO_TypeDef *port;
	uint16_t channel;
	uint16_t pin;
	float offset;
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
	float overflow;
} Encoder_TypeDef;

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} LED_TypeDef;

typedef struct {
	TIM_TypeDef *timer;
	float kp, ki, kd;
	float goal, lastSpeed, last5Speed;
	float error, lastError, sError;
	float lastTick;
	uint8_t enabled;
} PID_TypeDef;

typedef struct {
	SPI_TypeDef *d_spi, *t_spi;
	GPIO_TypeDef *d_mosi_port, *d_miso_port, *d_cs_port, *d_sck_port;
	GPIO_TypeDef *t_mosi_port, *t_miso_port, *t_cs_port, *t_sck_port;
	GPIO_TypeDef *reset_port, *dc_port, *int_port;
	uint16_t d_mosi_pin, d_miso_pin, d_cs_pin, d_sck_pin;
	uint16_t t_mosi_pin, t_miso_pin, t_cs_pin, t_sck_pin;
	uint16_t reset_pin, dc_pin, int_pin;
} Screen_TypeDef;

#endif /* USER_HUANSIC_TYPES_H_ */
