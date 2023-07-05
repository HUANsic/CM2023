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
 GPIO routine:
 PA0 push-pull output.

 */

#include "debug.h"

/* Global define */

typedef struct {
	TIM_TypeDef *timer;
	uint16_t channelP, channelN;
	GPIO_TypeDef *portP, *portN;
	uint16_t pinP, pinN;
} Motor_TypeDef;

/* Global Variable */

/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Toggle_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	u8 i = 0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
//	USART_Printf_Init(115200);
//	printf("SystemClk:%d\r\n", SystemCoreClock);
//	printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

//	printf("GPIO Toggle TEST\r\n");
	GPIO_Toggle_INIT();

	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;

	// enable positive GPIO port
	temp32_2 |= RCC_APB2Periph_GPIOA;
	temp32_2 |= RCC_APB2Periph_TIM1;

	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// positive output pin configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// negative output pin configuration
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 800 - 1;		// period (50us)(20kHz)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 9 - 1;	// prescaler
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	// set up channel
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 400;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// apply changes to channel
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	// enable auto reload for channel
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

	// then enable the overall auto reload function
	TIM_ARRPreloadConfig(TIM1, ENABLE);

	// configure interrupt (disable any)
	TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);

	// enable PWM outputs
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	// start the timer
	TIM_Cmd(TIM1, ENABLE);

	while(1)
	{
		Delay_Ms(250);
		GPIO_WriteBit(GPIOE, GPIO_Pin_7, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
		TIM1->CH1CVR = i ? 300 : 500;
		TIM1->CH2CVR = i ? 500 : 300;
	}
}
