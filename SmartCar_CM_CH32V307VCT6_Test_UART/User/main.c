/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

 */

#include "huansic_FullFunction_lib.h"

/* Global typedef */

/* Global define */

/* Global Variable */
extern Edge_TypeDef edgeboard;
extern Motor_TypeDef motor;
extern Servo_TypeDef servo;
extern Encoder_TypeDef encoder;
extern LED_TypeDef led1, led2, led3, led4;
extern PID_TypeDef pid_controller;

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();

	huansic_Initialize();
	huansic_Motor_Set(&motor, 0);
	huansic_Motor_Enable(&motor);
	huansic_Servo_Set(&servo, 0);

	uint16_t i = 0;
//	uint8_t j = 0;
	while(1) {
/*
		for(; i < 40; i++) {
			Delay_Ms(10);
			huansic_Servo_Set(&servo, i);
		}
		huansic_LED_Set(&led1, (j = !j));
		for(; i > -40; i--) {
			Delay_Ms(10);
			huansic_Servo_Set(&servo, i);
		}
*/

//		huansic_Edgboard_Send(&edgeboard, '!');
		huansic_LED_Set(&led1, (i = !i));
		Delay_Ms(500);
	}
}

