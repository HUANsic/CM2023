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

/*********************************************************************
 * @fn      GPIO_PinRemapConfig
 *
 * @brief   Changes the mapping of the specified pin.
 *
 * @param	servo Initialization structure to check if current mapping is possible
 *
 * @return  GPIO_Remap - selects the pin to remap.
 *            GPIO_PartialRemap_TIM1 - TIM1 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM1 - TIM1 Full Alternate Function mapping
 *            GPIO_PartialRemap1_TIM2 - TIM2 Partial1 Alternate Function mapping
 *            GPIO_PartialRemap2_TIM2 - TIM2 Partial2 Alternate Function mapping
 *            GPIO_FullRemap_TIM2 - TIM2 Full Alternate Function mapping
 *            GPIO_PartialRemap_TIM3 - TIM3 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM3 - TIM3 Full Alternate Function mapping
 *            GPIO_Remap_TIM4 - TIM4 Alternate Function mapping
 *            GPIO_Remap_TIM8 - TIM8 Alternate Function mapping
 *            GPIO_PartialRemap_TIM9 - TIM9 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM9 - TIM9 Full Alternate Function mapping
 *            GPIO_PartialRemap_TIM10 - TIM10 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM10 - TIM10 Full Alternate Function mapping
 */
uint32_t huansic_findRemap_servo(Servo_TypeDef *servo);

uint32_t huansic_findRemap_motor(Motor_TypeDef *motor);

uint32_t huansic_findRemap_edge(Edge_TypeDef *edge);

uint32_t huansic_findRemap_encoder(Encoder_TypeDef *encoder);

uint32_t huansic_getAPB2_fromGPIO(GPIO_TypeDef *gpio);

uint32_t huansic_getAPB1_fromTIM(TIM_TypeDef *tim);

uint32_t huansic_getAPB2_fromTIM(TIM_TypeDef *tim);

uint32_t huansic_getAPB1_fromUART(USART_TypeDef *usart);

uint32_t huansic_getAPB2_fromUART(USART_TypeDef *usart);

IRQn_Type huansic_getIRQ_fromUART(USART_TypeDef *usart);

IRQn_Type huansic_getIRQ_fromTIM(TIM_TypeDef *tim);

/*********************************************************************
 * @fn      GPIO_PinRemapConfig
 *
 * @brief   Changes the mapping of the specified pin.
 *
 * @param	servo Initialization structure to check if current mapping is possible
 *
 * @return  GPIO_Remap - selects the pin to remap.
 *            GPIO_Remap_SPI1 - SPI1 Alternate Function mapping
 *            GPIO_Remap_I2C1 - I2C1 Alternate Function mapping
 *            GPIO_Remap_USART1 - USART1 Alternate Function mapping
 *            GPIO_Remap_USART2 - USART2 Alternate Function mapping
 *            GPIO_PartialRemap_USART3 - USART3 Partial Alternate Function mapping
 *            GPIO_PartialRemap1_USART3 - USART3 Partial1 Alternate Function mapping
 *            GPIO_FullRemap_USART3 - USART3 Full Alternate Function mapping
 *            GPIO_PartialRemap_TIM1 - TIM1 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM1 - TIM1 Full Alternate Function mapping
 *            GPIO_PartialRemap1_TIM2 - TIM2 Partial1 Alternate Function mapping
 *            GPIO_PartialRemap2_TIM2 - TIM2 Partial2 Alternate Function mapping
 *            GPIO_FullRemap_TIM2 - TIM2 Full Alternate Function mapping
 *            GPIO_PartialRemap_TIM3 - TIM3 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM3 - TIM3 Full Alternate Function mapping
 *            GPIO_Remap_TIM4 - TIM4 Alternate Function mapping
 *            GPIO_Remap1_CAN1 - CAN1 Alternate Function mapping
 *            GPIO_Remap2_CAN1 - CAN1 Alternate Function mapping
 *            GPIO_Remap_PD01 - PD01 Alternate Function mapping
 *            GPIO_Remap_ADC1_ETRGINJ - ADC1 External Trigger Injected Conversion remapping
 *            GPIO_Remap_ADC1_ETRGREG - ADC1 External Trigger Regular Conversion remapping
 *            GPIO_Remap_ADC2_ETRGINJ - ADC2 External Trigger Injected Conversion remapping
 *            GPIO_Remap_ADC2_ETRGREG - ADC2 External Trigger Regular Conversion remapping
 *            GPIO_Remap_ETH - Ethernet remapping
 *            GPIO_Remap_CAN2 - CAN2 remapping
 *            GPIO_Remap_MII_RMII_SEL - MII or RMII selection
 *            GPIO_Remap_SWJ_NoJTRST - Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST
 *            GPIO_Remap_SWJ_JTAGDisable - JTAG-DP Disabled and SW-DP Enabled
 *            GPIO_Remap_SWJ_Disable - Full SWJ Disabled (JTAG-DP + SW-DP)
 *            GPIO_Remap_TIM2ITR1_PTP_SOF - Ethernet PTP output or USB OTG SOF (Start of Frame) connected
 *        to TIM2 Internal Trigger 1 for calibration
 *            GPIO_Remap_TIM2ITR1_PTP_SOF - Ethernet PTP output or USB OTG SOF (Start of Frame)
 *            GPIO_Remap_TIM8 - TIM8 Alternate Function mapping
 *            GPIO_PartialRemap_TIM9 - TIM9 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM9 - TIM9 Full Alternate Function mapping
 *            GPIO_PartialRemap_TIM10 - TIM10 Partial Alternate Function mapping
 *            GPIO_FullRemap_TIM10 - TIM10 Full Alternate Function mapping
 *            GPIO_Remap_FSMC_NADV - FSMC_NADV Alternate Function mapping
 *            GPIO_PartialRemap_USART4 - USART4 Partial Alternate Function mapping
 *            GPIO_FullRemap_USART4 - USART4 Full Alternate Function mapping
 *            GPIO_PartialRemap_USART5 - USART5 Partial Alternate Function mapping
 *            GPIO_FullRemap_USART5 - USART5 Full Alternate Function mapping
 *            GPIO_PartialRemap_USART6 - USART6 Partial Alternate Function mapping
 *            GPIO_FullRemap_USART6 - USART6 Full Alternate Function mapping
 *            GPIO_PartialRemap_USART7 - USART7 Partial Alternate Function mapping
 *            GPIO_FullRemap_USART7 - USART7 Full Alternate Function mapping
 *            GPIO_PartialRemap_USART8 - USART8 Partial Alternate Function mapping
 *            GPIO_FullRemap_USART8 - USART8 Full Alternate Function mapping
 *            GPIO_Remap_USART1_HighBit - USART1 Alternate Function mapping high bit
 */

#endif /* USER_HUANSIC_UTIL_H_ */
