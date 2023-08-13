/*
 * util.h
 *
 *  Created on: Jun 19, 2023
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_UTIL_H_
#define USER_HUANSIC_UTIL_H_

#include "huansic_types.h"

#define HUAN_DefaultMapping 0xFFFFFFFF
#define HUAN_NoMapping 0x00

#define HUAN_US_TIMER TIM10

void huansic_us_Init(void);

void huansic_us_delay(uint32_t duration);

float huansic_us_get(void);

uint8_t huansic_I2C_write(HUAN_I2CM_TypeDef *twi, uint8_t deviceAddr, uint8_t registerAddr,
		uint8_t *txBuffer, uint8_t len);

uint8_t huansic_I2C_read(HUAN_I2CM_TypeDef *twi, uint8_t deviceAddr, uint8_t registerAddr,
		uint8_t *rxBuffer, uint8_t len);

uint32_t huansic_findRemap_servo(Servo_TypeDef *servo);

uint32_t huansic_findRemap_motor(Motor_TypeDef *motor);

uint32_t huansic_findRemap_edge(Edge_TypeDef *edge);

uint32_t huansic_findRemap_encoder(Encoder_TypeDef *encoder);

uint32_t huansic_getAPB2_fromGPIO(GPIO_TypeDef *gpio);

uint32_t huansic_getAPB1_fromTIM(TIM_TypeDef *tim);

uint32_t huansic_getAPB2_fromTIM(TIM_TypeDef *tim);

uint32_t huansic_getAPB1_fromUART(USART_TypeDef *usart);

uint32_t huansic_getAPB2_fromUART(USART_TypeDef *usart);

uint32_t huansic_getAPB1_fromSPI(SPI_TypeDef *spi);

uint32_t huansic_getAPB2_fromSPI(SPI_TypeDef *spi);

uint32_t huansic_getAPB1_fromI2C(I2C_TypeDef *twi);

IRQn_Type huansic_getIRQ_fromUART(USART_TypeDef *usart);

IRQn_Type huansic_getIRQ_fromTIM(TIM_TypeDef *tim);

#endif /* USER_HUANSIC_UTIL_H_ */
