/*
 * util.c
 *
 *  Created on: Jun 19, 2023
 *      Author: ZonghuanWu
 */

#include "huansic_util.h"

#define PAx	0x10
#define PBx	0x20
#define PCx	0x30
#define PDx	0x40
#define PEx	0x50
#define Px0 0x00
#define Px1 0x01
#define Px2 0x02
#define Px3 0x03
#define Px4 0x04
#define Px5 0x05
#define Px6 0x06
#define Px7 0x07
#define Px8 0x08
#define Px9 0x09
#define Px10 0x0A
#define Px11 0x0B
#define Px12 0x0C
#define Px13 0x0D
#define Px14 0x0E
#define Px15 0x0F

uint32_t huansic_remap_tim_options[] = {
HUAN_NoMapping,				// 0
		HUAN_DefaultMapping,		// 1
		GPIO_PartialRemap_TIM1,		// 2
		GPIO_FullRemap_TIM1,		// 3
		GPIO_PartialRemap1_TIM2,	// 4
		GPIO_PartialRemap2_TIM2,	// 5
		GPIO_FullRemap_TIM2,		// 6
		GPIO_PartialRemap_TIM3,		// 7
		GPIO_FullRemap_TIM3,		// 8
		GPIO_Remap_TIM4,			// 9
		GPIO_Remap_TIM8,			// 10
		GPIO_PartialRemap_TIM9,		// 11
		GPIO_FullRemap_TIM9,		// 12
		GPIO_PartialRemap_TIM10,	// 13
		GPIO_FullRemap_TIM10		// 14
		};

uint32_t huansic_remap_uart_options[] = {
HUAN_NoMapping,				// 0
		HUAN_DefaultMapping,		// 1
		GPIO_Remap_USART1,			// 2
		GPIO_Remap_USART2,			// 3
		GPIO_PartialRemap_USART3,	// 4
		GPIO_PartialRemap1_USART3,	// 5
		GPIO_FullRemap_USART3,		// 6
		GPIO_PartialRemap_USART4,	// 7
		GPIO_FullRemap_USART4,		// 8
		GPIO_PartialRemap_USART5,	// 9
		GPIO_FullRemap_USART5,		// 10
		GPIO_PartialRemap_USART6,	// 11
		GPIO_FullRemap_USART6,		// 12
		GPIO_PartialRemap_USART7,	// 13
		GPIO_FullRemap_USART7,		// 14
		GPIO_PartialRemap_USART8,	// 15
		GPIO_FullRemap_USART8		// 16
		};

uint8_t huansic_remap_tim_table[][4][5] = {
		// 0 (leave empty)
		{
				{ 0, 0, 0, 0, 0 }, 			// option 1
				{ 0, 0, 0, 0, 0 }, 			// option 2
				{ 0, 0, 0, 0, 0 }, 			// option 3
				{ 0, 0, 0, 0, 0 }	 		// option 4
		},
		// TIM1
		{
				{ 1, PAx | Px8, PAx | Px9, PAx | Px10, PAx | Px11 }, 	// option 1
				{ 2, PAx | Px8, PAx | Px9, PAx | Px10, PAx | Px11 }, 	// option 2
				{ 3, PEx | Px9, PEx | Px11, PEx | Px13, PEx | Px14 }, 	// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM2
		{
				{ 1, PAx | Px0, PAx | Px1, PAx | Px2, PAx | Px3 }, 	// option 1
				{ 4, PAx | Px15, PBx | Px3, PAx | Px2, PAx | Px3 }, 	// option 2
				{ 5, PAx | Px0, PAx | Px1, PBx | Px10, PBx | Px11 }, 	// option 3
				{ 6, PAx | Px15, PBx | Px3, PBx | Px10, PBx | Px11 } 	// option 4
		},
		// TIM3
		{
				{ 1, PAx | Px6, PAx | Px7, PBx | Px0, PBx | Px1 }, 	// option 1
				{ 7, PBx | Px4, PBx | Px5, PBx | Px0, PBx | Px1 }, 	// option 2
				{ 8, PCx | Px6, PCx | Px7, PCx | Px8, PCx | Px9 }, 	// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM4
		{
				{ 1, PBx | Px6, PBx | Px7, PBx | Px8, PBx | Px9 }, 	// option 1
				{ 9, PDx | Px12, PDx | Px13, PDx | Px14, PDx | Px15 }, 	// option 2
				{ 0, 0, 0, 0, 0 }, 			// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM5
		{
				{ 1, PAx | Px0, PAx | Px1, PAx | Px2, PAx | Px3 }, 	// option 1
				{ 0, 0, 0, 0, 0 }, 			// option 2
				{ 0, 0, 0, 0, 0 }, 			// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM6 (no output)
		{
				{ 0, 0, 0, 0, 0 }, 			// option 1
				{ 0, 0, 0, 0, 0 }, 			// option 2
				{ 0, 0, 0, 0, 0 }, 			// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM7 (no output)
		{
				{ 0, 0, 0, 0, 0 }, 			// option 1
				{ 0, 0, 0, 0, 0 }, 			// option 2
				{ 0, 0, 0, 0, 0 }, 			// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM8
		{
				{ 1, PCx | Px6, PCx | Px7, PCx | Px8, PCx | Px9 }, 	// option 1
				{ 10, PBx | Px6, PBx | Px7, PBx | Px8, PCx | Px13 }, 	// option 2
				{ 0, 0, 0, 0, 0 }, 			// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM9
		{
				{ 1, PAx | Px2, PAx | Px3, PAx | Px4, PCx | Px4 }, 	// option 1
				{ 11, PAx | Px2, PAx | Px3, PAx | Px4, PCx | Px14 }, 	// option 2
				{ 12, PDx | Px9, PDx | Px11, PDx | Px13, PDx | Px15 }, 	// option 3
				{ 0, 0, 0, 0, 0 }	 			// option 4
		},
		// TIM10
		{
				{ 1, PBx | Px8, PBx | Px9, PCx | Px3, PCx | Px11 }, 	// option 1
				{ 13, PBx | Px3, PBx | Px4, PBx | Px5, PCx | Px15 }, 	// option 2
				{ 14, PDx | Px1, PDx | Px3, PDx | Px5, PDx | Px7 }, 	// option 3
				{ 0, 0, 0, 0, 0 } 				// option 4
		}
};

//						[UARTx][Option][TX|RX]
uint8_t huansic_remap_uart_table[][4][3] = {
		// 0 (leave empty)
		{
				{ 0, 0, 0 }, 			// option 1
				{ 0, 0, 0 }, 			// option 2
				{ 0, 0, 0 }, 			// option 3
				{ 0, 0, 0 }			// option 4
		},
		// UART1
		{
				{ 1, PAx | Px9, PAx | Px10 }, 	// option 1
				{ 2, PBx | Px6, PBx | Px7 },		// option 2
				{ 0, 0, 0 }, 						// option 3
				{ 0, 0, 0 }						// option 4
		},
		// UART2
		{
				{ 1, PAx | Px2, PAx | Px3 }, 	// option 1
				{ 3, PDx | Px5, PDx | Px6 }, 	// option 2
				{ 0, 0, 0 },						// option 3
				{ 0, 0, 0 }						// option 4
		},
		// UART3
		{
				{ 1, PBx | Px10, PBx | Px11 },	// option 1
				{ 4, PCx | Px10, PCx | Px11 },	// option 2
				{ 5, PAx | Px13, PAx | Px14 },	// option 3
				{ 6, PDx | Px8, PDx | Px9 }  // option 4
		},
		// UART4
		{
				{ 1, PCx | Px10, PCx | Px11 },	// option 1
				{ 7, PBx | Px8, PBx | Px9 },	// option 2
				{ 8, PEx | Px0, PEx | Px1 },	// option 3
				{ 0, 0, 0 }						// option 4
		},
		// UART5
		{
				{ 1, PCx | Px12, PDx | Px2 },	// option 1
				{ 9, PBx | Px4, PBx | Px5 }, 	// option 2
				{ 10, PEx | Px8, PEx | Px9 },	// option 3
				{ 0, 0, 0 }						// option 4
		},
		// UART6
		{
				{ 1, PCx | Px0, PCx | Px1 },	// option 1
				{ 11, PBx | Px8, PBx | Px9 },	// option 2
				{ 12, PEx | Px10, PEx | Px11 },	// option 3
				{ 0, 0, 0 }						// option 4
		},
		// UART7
		{
				{ 1, PCx | Px2, PCx | Px3 },	// option 1
				{ 13, PAx | Px6, PAx | Px7 },	// option 2
				{ 14, PEx | Px12, PEx | Px13 },	// option 3
				{ 0, 0, 0 }						// option 4
		},
		// UART8
		{
				{ 1, PCx | Px4, PCx | Px5 },	// option 1
				{ 15, PAx | Px14, PAx | Px15 }, 	// option 2
				{ 16, PEx | Px14, PEx | Px15 }, 	// option 3
				{ 0, 0, 0 }						// option 4
		}
};

uint32_t us_overflow;

void TIM10_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));		// us timer

void huansic_us_Init(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;
	IRQn_Type irq;

	// enable timer
	temp32_1 |= huansic_getAPB1_fromTIM(HUAN_US_TIMER);
	temp32_2 |= huansic_getAPB2_fromTIM(HUAN_US_TIMER);
	irq = huansic_getIRQ_fromTIM(HUAN_US_TIMER);
	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 65535;	// period
	TIM_TimeBaseInitStructure.TIM_Prescaler = 144 - 1;	// prescaler
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// apply changes
	TIM_TimeBaseInit(HUAN_US_TIMER, &TIM_TimeBaseInitStructure);

	// configure interrupt (enable update)
	TIM_ITConfig(HUAN_US_TIMER, TIM_IT_Update, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	// highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 2nd highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start the timer
	TIM_Cmd(HUAN_US_TIMER, ENABLE);

	us_overflow = 0;
}

void huansic_us_delay(uint32_t duration) {
	uint32_t startOVF = us_overflow, startUS = HUAN_US_TIMER->CNT;
	while(((us_overflow - startOVF) << 16) + HUAN_US_TIMER->CNT - startUS < duration) {
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");			// maybe chill a bit during waiting
	}
}

float huansic_us_get() {
	float result = us_overflow;
	result *= 65536;
	result += HUAN_US_TIMER->CNT;
	return result;
}

void TIM10_UP_IRQHandler(void) {
	us_overflow++;
	TIM_ClearFlag(TIM10, TIM_FLAG_Update);
}

uint32_t huansic_findRemap_servo(Servo_TypeDef *servo) {
	uint8_t timer, channel, portpin = 0, i;

	// find timer
	if (servo->timer == TIM1) {
		timer = 1;
	} else if (servo->timer == TIM2) {
		timer = 2;
	} else if (servo->timer == TIM3) {
		timer = 3;
	} else if (servo->timer == TIM4) {
		timer = 4;
	} else if (servo->timer == TIM5) {
		timer = 5;
	} else if (servo->timer == TIM6) {
		timer = 6;
	} else if (servo->timer == TIM7) {
		timer = 7;
	} else if (servo->timer == TIM8) {
		timer = 8;
	} else if (servo->timer == TIM9) {
		timer = 9;
	} else if (servo->timer == TIM10) {
		timer = 10;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find channel
	switch (servo->channel) {
	case TIM_Channel_1:
		channel = 1;
		break;
	case TIM_Channel_2:
		channel = 2;
		break;
	case TIM_Channel_3:
		channel = 3;
		break;
	case TIM_Channel_4:
		channel = 4;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find port
	if (servo->port == GPIOA) {
		portpin = PAx;
	} else if (servo->port == GPIOB) {
		portpin = PBx;
	} else if (servo->port == GPIOC) {
		portpin = PCx;
	} else if (servo->port == GPIOD) {
		portpin = PDx;
	} else if (servo->port == GPIOE) {
		portpin = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find pin
	switch (servo->pin) {
	case GPIO_Pin_0:
		portpin |= Px0;
		break;
	case GPIO_Pin_1:
		portpin |= Px1;
		break;
	case GPIO_Pin_2:
		portpin |= Px2;
		break;
	case GPIO_Pin_3:
		portpin |= Px3;
		break;
	case GPIO_Pin_4:
		portpin |= Px4;
		break;
	case GPIO_Pin_5:
		portpin |= Px5;
		break;
	case GPIO_Pin_6:
		portpin |= Px6;
		break;
	case GPIO_Pin_7:
		portpin |= Px7;
		break;
	case GPIO_Pin_8:
		portpin |= Px8;
		break;
	case GPIO_Pin_9:
		portpin |= Px9;
		break;
	case GPIO_Pin_10:
		portpin |= Px10;
		break;
	case GPIO_Pin_11:
		portpin |= Px11;
		break;
	case GPIO_Pin_12:
		portpin |= Px12;
		break;
	case GPIO_Pin_13:
		portpin |= Px13;
		break;
	case GPIO_Pin_14:
		portpin |= Px14;
		break;
	case GPIO_Pin_15:
		portpin |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

	for (i = 0; i < 4; i++) {
		if (huansic_remap_tim_table[timer][i][channel] == portpin)
			return huansic_remap_tim_options[huansic_remap_tim_table[timer][i][0]];
	}

	return HUAN_NoMapping;
}

uint32_t huansic_findRemap_motor(Motor_TypeDef *motor) {
	uint8_t timer, channelP, channelN, portpinP = 0, portpinN = 0, i;

	// find timer
	if (motor->timer == TIM1) {
		timer = 1;
	} else if (motor->timer == TIM2) {
		timer = 2;
	} else if (motor->timer == TIM3) {
		timer = 3;
	} else if (motor->timer == TIM4) {
		timer = 4;
	} else if (motor->timer == TIM5) {
		timer = 5;
	} else if (motor->timer == TIM6) {
		timer = 6;
	} else if (motor->timer == TIM7) {
		timer = 7;
	} else if (motor->timer == TIM8) {
		timer = 8;
	} else if (motor->timer == TIM9) {
		timer = 9;
	} else if (motor->timer == TIM10) {
		timer = 10;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find channelP
	switch (motor->channelP) {
	case TIM_Channel_1:
		channelP = 1;
		break;
	case TIM_Channel_2:
		channelP = 2;
		break;
	case TIM_Channel_3:
		channelP = 3;
		break;
	case TIM_Channel_4:
		channelP = 4;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find channelN
	switch (motor->channelN) {
	case TIM_Channel_1:
		channelN = 1;
		break;
	case TIM_Channel_2:
		channelN = 2;
		break;
	case TIM_Channel_3:
		channelN = 3;
		break;
	case TIM_Channel_4:
		channelN = 4;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find portP
	if (motor->portP == GPIOA) {
		portpinP = PAx;
	} else if (motor->portP == GPIOB) {
		portpinP = PBx;
	} else if (motor->portP == GPIOC) {
		portpinP = PCx;
	} else if (motor->portP == GPIOD) {
		portpinP = PDx;
	} else if (motor->portP == GPIOE) {
		portpinP = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find pinP
	switch (motor->pinP) {
	case GPIO_Pin_0:
		portpinP |= Px0;
		break;
	case GPIO_Pin_1:
		portpinP |= Px1;
		break;
	case GPIO_Pin_2:
		portpinP |= Px2;
		break;
	case GPIO_Pin_3:
		portpinP |= Px3;
		break;
	case GPIO_Pin_4:
		portpinP |= Px4;
		break;
	case GPIO_Pin_5:
		portpinP |= Px5;
		break;
	case GPIO_Pin_6:
		portpinP |= Px6;
		break;
	case GPIO_Pin_7:
		portpinP |= Px7;
		break;
	case GPIO_Pin_8:
		portpinP |= Px8;
		break;
	case GPIO_Pin_9:
		portpinP |= Px9;
		break;
	case GPIO_Pin_10:
		portpinP |= Px10;
		break;
	case GPIO_Pin_11:
		portpinP |= Px11;
		break;
	case GPIO_Pin_12:
		portpinP |= Px12;
		break;
	case GPIO_Pin_13:
		portpinP |= Px13;
		break;
	case GPIO_Pin_14:
		portpinP |= Px14;
		break;
	case GPIO_Pin_15:
		portpinP |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find portN
	if (motor->portN == GPIOA) {
		portpinN = PAx;
	} else if (motor->portN == GPIOB) {
		portpinN = PBx;
	} else if (motor->portN == GPIOC) {
		portpinN = PCx;
	} else if (motor->portN == GPIOD) {
		portpinN = PDx;
	} else if (motor->portN == GPIOE) {
		portpinN = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find pinN
	switch (motor->pinN) {
	case GPIO_Pin_0:
		portpinN |= Px0;
		break;
	case GPIO_Pin_1:
		portpinN |= Px1;
		break;
	case GPIO_Pin_2:
		portpinN |= Px2;
		break;
	case GPIO_Pin_3:
		portpinN |= Px3;
		break;
	case GPIO_Pin_4:
		portpinN |= Px4;
		break;
	case GPIO_Pin_5:
		portpinN |= Px5;
		break;
	case GPIO_Pin_6:
		portpinN |= Px6;
		break;
	case GPIO_Pin_7:
		portpinN |= Px7;
		break;
	case GPIO_Pin_8:
		portpinN |= Px8;
		break;
	case GPIO_Pin_9:
		portpinN |= Px9;
		break;
	case GPIO_Pin_10:
		portpinN |= Px10;
		break;
	case GPIO_Pin_11:
		portpinN |= Px11;
		break;
	case GPIO_Pin_12:
		portpinN |= Px12;
		break;
	case GPIO_Pin_13:
		portpinN |= Px13;
		break;
	case GPIO_Pin_14:
		portpinN |= Px14;
		break;
	case GPIO_Pin_15:
		portpinN |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

	for (i = 0; i < 4; i++) {
		if (huansic_remap_tim_table[timer][i][channelP] == portpinP
				&& huansic_remap_tim_table[timer][i][channelN] == portpinN)
			return huansic_remap_tim_options[huansic_remap_tim_table[timer][i][0]];
	}

	return HUAN_NoMapping;
}

uint32_t huansic_findRemap_edge(Edge_TypeDef *edge) {
	uint8_t uart, portpintx = 0, portpinrx = 0, i;

	// find uart
	if (edge->uart == USART1) {
		uart = 1;
	} else if (edge->uart == USART2) {
		uart = 2;
	} else if (edge->uart == USART3) {
		uart = 3;
	} else if (edge->uart == UART4) {
		uart = 4;
	} else if (edge->uart == UART5) {
		uart = 5;
	} else if (edge->uart == UART6) {
		uart = 6;
	} else if (edge->uart == UART7) {
		uart = 7;
	} else if (edge->uart == UART8) {
		uart = 8;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find porttx
	if (edge->txport == GPIOA) {
		portpintx = PAx;
	} else if (edge->txport == GPIOB) {
		portpintx = PBx;
	} else if (edge->txport == GPIOC) {
		portpintx = PCx;
	} else if (edge->txport == GPIOD) {
		portpintx = PDx;
	} else if (edge->txport == GPIOE) {
		portpintx = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find pintx
	switch (edge->txpin) {
	case GPIO_Pin_0:
		portpintx |= Px0;
		break;
	case GPIO_Pin_1:
		portpintx |= Px1;
		break;
	case GPIO_Pin_2:
		portpintx |= Px2;
		break;
	case GPIO_Pin_3:
		portpintx |= Px3;
		break;
	case GPIO_Pin_4:
		portpintx |= Px4;
		break;
	case GPIO_Pin_5:
		portpintx |= Px5;
		break;
	case GPIO_Pin_6:
		portpintx |= Px6;
		break;
	case GPIO_Pin_7:
		portpintx |= Px7;
		break;
	case GPIO_Pin_8:
		portpintx |= Px8;
		break;
	case GPIO_Pin_9:
		portpintx |= Px9;
		break;
	case GPIO_Pin_10:
		portpintx |= Px10;
		break;
	case GPIO_Pin_11:
		portpintx |= Px11;
		break;
	case GPIO_Pin_12:
		portpintx |= Px12;
		break;
	case GPIO_Pin_13:
		portpintx |= Px13;
		break;
	case GPIO_Pin_14:
		portpintx |= Px14;
		break;
	case GPIO_Pin_15:
		portpintx |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find portrx
	if (edge->rxport == GPIOA) {
		portpinrx = PAx;
	} else if (edge->rxport == GPIOB) {
		portpinrx = PBx;
	} else if (edge->rxport == GPIOC) {
		portpinrx = PCx;
	} else if (edge->rxport == GPIOD) {
		portpinrx = PDx;
	} else if (edge->rxport == GPIOE) {
		portpinrx = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find pinrx
	switch (edge->rxpin) {
	case GPIO_Pin_0:
		portpinrx |= Px0;
		break;
	case GPIO_Pin_1:
		portpinrx |= Px1;
		break;
	case GPIO_Pin_2:
		portpinrx |= Px2;
		break;
	case GPIO_Pin_3:
		portpinrx |= Px3;
		break;
	case GPIO_Pin_4:
		portpinrx |= Px4;
		break;
	case GPIO_Pin_5:
		portpinrx |= Px5;
		break;
	case GPIO_Pin_6:
		portpinrx |= Px6;
		break;
	case GPIO_Pin_7:
		portpinrx |= Px7;
		break;
	case GPIO_Pin_8:
		portpinrx |= Px8;
		break;
	case GPIO_Pin_9:
		portpinrx |= Px9;
		break;
	case GPIO_Pin_10:
		portpinrx |= Px10;
		break;
	case GPIO_Pin_11:
		portpinrx |= Px11;
		break;
	case GPIO_Pin_12:
		portpinrx |= Px12;
		break;
	case GPIO_Pin_13:
		portpinrx |= Px13;
		break;
	case GPIO_Pin_14:
		portpinrx |= Px14;
		break;
	case GPIO_Pin_15:
		portpinrx |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

	for (i = 0; i < 4; i++) {
		if (huansic_remap_uart_table[uart][i][1] == portpintx
				&& huansic_remap_uart_table[uart][i][2] == portpinrx)
			return huansic_remap_uart_options[huansic_remap_uart_table[uart][i][0]];
	}

	return HUAN_NoMapping;
}

uint32_t huansic_findRemap_encoder(Encoder_TypeDef *encoder) {
	uint8_t timer, portpinA = 0, portpinB = 0, i;

	// find timer
	if (encoder->counter == TIM1) {
		timer = 1;
	} else if (encoder->counter == TIM2) {
		timer = 2;
	} else if (encoder->counter == TIM3) {
		timer = 3;
	} else if (encoder->counter == TIM4) {
		timer = 4;
	} else if (encoder->counter == TIM5) {
		timer = 5;
	} else if (encoder->counter == TIM6) {
		timer = 6;
	} else if (encoder->counter == TIM7) {
		timer = 7;
	} else if (encoder->counter == TIM8) {
		timer = 8;
	} else if (encoder->counter == TIM9) {
		timer = 9;
	} else if (encoder->counter == TIM10) {
		timer = 10;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find Aport
	if (encoder->Aport == GPIOA) {
		portpinA = PAx;
	} else if (encoder->Aport == GPIOB) {
		portpinA = PBx;
	} else if (encoder->Aport == GPIOC) {
		portpinA = PCx;
	} else if (encoder->Aport == GPIOD) {
		portpinA = PDx;
	} else if (encoder->Aport == GPIOE) {
		portpinA = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find Apin
	switch (encoder->Apin) {
	case GPIO_Pin_0:
		portpinA |= Px0;
		break;
	case GPIO_Pin_1:
		portpinA |= Px1;
		break;
	case GPIO_Pin_2:
		portpinA |= Px2;
		break;
	case GPIO_Pin_3:
		portpinA |= Px3;
		break;
	case GPIO_Pin_4:
		portpinA |= Px4;
		break;
	case GPIO_Pin_5:
		portpinA |= Px5;
		break;
	case GPIO_Pin_6:
		portpinA |= Px6;
		break;
	case GPIO_Pin_7:
		portpinA |= Px7;
		break;
	case GPIO_Pin_8:
		portpinA |= Px8;
		break;
	case GPIO_Pin_9:
		portpinA |= Px9;
		break;
	case GPIO_Pin_10:
		portpinA |= Px10;
		break;
	case GPIO_Pin_11:
		portpinA |= Px11;
		break;
	case GPIO_Pin_12:
		portpinA |= Px12;
		break;
	case GPIO_Pin_13:
		portpinA |= Px13;
		break;
	case GPIO_Pin_14:
		portpinA |= Px14;
		break;
	case GPIO_Pin_15:
		portpinA |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find Bport
	if (encoder->Bport == GPIOA) {
		portpinB = PAx;
	} else if (encoder->Bport == GPIOB) {
		portpinB = PBx;
	} else if (encoder->Bport == GPIOC) {
		portpinB = PCx;
	} else if (encoder->Bport == GPIOD) {
		portpinB = PDx;
	} else if (encoder->Bport == GPIOE) {
		portpinB = PEx;
	} else {
		while (1) {
			Delay_Ms(1000);
		}
	}
	// find Bpin
	switch (encoder->Bpin) {
	case GPIO_Pin_0:
		portpinB |= Px0;
		break;
	case GPIO_Pin_1:
		portpinB |= Px1;
		break;
	case GPIO_Pin_2:
		portpinB |= Px2;
		break;
	case GPIO_Pin_3:
		portpinB |= Px3;
		break;
	case GPIO_Pin_4:
		portpinB |= Px4;
		break;
	case GPIO_Pin_5:
		portpinB |= Px5;
		break;
	case GPIO_Pin_6:
		portpinB |= Px6;
		break;
	case GPIO_Pin_7:
		portpinB |= Px7;
		break;
	case GPIO_Pin_8:
		portpinB |= Px8;
		break;
	case GPIO_Pin_9:
		portpinB |= Px9;
		break;
	case GPIO_Pin_10:
		portpinB |= Px10;
		break;
	case GPIO_Pin_11:
		portpinB |= Px11;
		break;
	case GPIO_Pin_12:
		portpinB |= Px12;
		break;
	case GPIO_Pin_13:
		portpinB |= Px13;
		break;
	case GPIO_Pin_14:
		portpinB |= Px14;
		break;
	case GPIO_Pin_15:
		portpinB |= Px15;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

	for (i = 0; i < 4; i++) {
		if (huansic_remap_tim_table[timer][i][1] == portpinA
				&& huansic_remap_tim_table[timer][i][2] == portpinB)
			return huansic_remap_tim_options[huansic_remap_tim_table[timer][i][0]];
	}

	return HUAN_NoMapping;
}

/*
 uint32_t huansic_findRemap_eeprom(EEPROM_TypeDef *eeprom) {
 if (eeprom->sda_port != GPIOB || eeprom->scl_port != GPIOB)
 return HUAN_NoMapping;
 if (eeprom->sda_pin == GPIO_Pin_7 && eeprom->scl_pin == GPIO_Pin_6)
 return HUAN_DefaultMapping;
 else if (eeprom->sda_pin == GPIO_Pin_11 && eeprom->scl_pin == GPIO_Pin_10)
 return HUAN_DefaultMapping;
 else if (eeprom->sda_pin == GPIO_Pin_9 && eeprom->scl_pin == GPIO_Pin_8)
 return GPIO_Remap_I2C1;
 else
 return HUAN_NoMapping;
 }
 */

uint32_t huansic_getAPB2_fromGPIO(GPIO_TypeDef *gpio) {
	if (gpio == GPIOA)
		return RCC_APB2Periph_GPIOA;
	else if (gpio == GPIOB)
		return RCC_APB2Periph_GPIOB;
	else if (gpio == GPIOC)
		return RCC_APB2Periph_GPIOC;
	else if (gpio == GPIOD)
		return RCC_APB2Periph_GPIOD;
	else if (gpio == GPIOE)
		return RCC_APB2Periph_GPIOE;
	else
		return 0;
}

uint32_t huansic_getAPB1_fromTIM(TIM_TypeDef *tim) {
	if (tim == TIM2)
		return RCC_APB1Periph_TIM2;
	else if (tim == TIM3)
		return RCC_APB1Periph_TIM3;
	else if (tim == TIM4)
		return RCC_APB1Periph_TIM4;
	else if (tim == TIM5)
		return RCC_APB1Periph_TIM5;
	else if (tim == TIM6)
		return RCC_APB1Periph_TIM6;
	else if (tim == TIM7)
		return RCC_APB1Periph_TIM7;
	else
		return 0;
}

uint32_t huansic_getAPB2_fromTIM(TIM_TypeDef *tim) {
	if (tim == TIM1)
		return RCC_APB2Periph_TIM1;
	else if (tim == TIM8)
		return RCC_APB2Periph_TIM8;
	else if (tim == TIM9)
		return RCC_APB2Periph_TIM9;
	else if (tim == TIM10)
		return RCC_APB2Periph_TIM10;
	else
		return 0;
}

uint32_t huansic_getAPB1_fromUART(USART_TypeDef *usart) {
	if (usart == USART2)
		return RCC_APB1Periph_USART2;
	else if (usart == USART3)
		return RCC_APB1Periph_USART3;
	else if (usart == UART4)
		return RCC_APB1Periph_UART4;
	else if (usart == UART5)
		return RCC_APB1Periph_UART5;
	else if (usart == UART6)
		return RCC_APB1Periph_UART6;
	else if (usart == UART7)
		return RCC_APB1Periph_UART7;
	else if (usart == UART8)
		return RCC_APB1Periph_UART8;
	else
		return 0;
}

uint32_t huansic_getAPB2_fromUART(USART_TypeDef *usart) {
	if (usart == USART1)
		return RCC_APB2Periph_USART1;
	else
		return 0;
}

uint32_t huansic_getAPB1_fromSPI(SPI_TypeDef *spi) {
	if (spi == SPI2)
		return RCC_APB1Periph_SPI2;
	else if (spi == SPI3)
		return RCC_APB1Periph_SPI3;
	else
		return 0;
}

uint32_t huansic_getAPB2_fromSPI(SPI_TypeDef *spi) {
	if (spi == SPI1)
		return RCC_APB2Periph_SPI1;
	else
		return 0;
}

uint32_t huansic_getAPB1_fromI2C(I2C_TypeDef *twi) {
	if (twi == I2C1)
		return RCC_APB1Periph_I2C1;
	else if (twi == I2C2)
		return RCC_APB1Periph_I2C2;
	else
		return 0;
}

IRQn_Type huansic_getIRQ_fromUART(USART_TypeDef *usart) {
	if (usart == USART1)
		return USART1_IRQn;
	else if (usart == USART2)
		return USART2_IRQn;
	else if (usart == USART3)
		return USART3_IRQn;
	else if (usart == UART4)
		return UART4_IRQn;
	else if (usart == UART5)
		return UART5_IRQn;
	else if (usart == UART6)
		return UART6_IRQn;
	else if (usart == UART7)
		return UART7_IRQn;
	else if (usart == UART8)
		return UART8_IRQn;
	else {
		while (1) {
			Delay_Ms(1000);
		}
	}
}

IRQn_Type huansic_getIRQ_fromTIM(TIM_TypeDef *tim) {
	if (tim == TIM1)
		return TIM1_UP_IRQn;
	else if (tim == TIM2)
		return TIM2_IRQn;
	else if (tim == TIM3)
		return TIM3_IRQn;
	else if (tim == TIM4)
		return TIM4_IRQn;
	else if (tim == TIM5)
		return TIM5_IRQn;
	else if (tim == TIM6)
		return TIM6_IRQn;
	else if (tim == TIM7)
		return TIM7_IRQn;
	else if (tim == TIM8)
		return TIM8_UP_IRQn;
	else if (tim == TIM9)
		return TIM9_UP_IRQn;
	else if (tim == TIM10)
		return TIM10_UP_IRQn;
	else {
		while (1) {
			Delay_Ms(1000);
		}
	}
}

#ifdef USE_SW_TWI

#define SDA_STATE(twi) GPIO_ReadInputDataBit(twi->sda_port, twi->sda_pin)
#define SCL_STATE(twi) GPIO_ReadInputDataBit(twi->scl_port, twi->scl_pin)
#define SDA_TO(twi, x) GPIO_WriteBit(twi->sda_port, twi->sda_pin, x)
#define SCL_TO(twi, x) GPIO_WriteBit(twi->scl_port, twi->sda_pin, x)
#define SDA_HIGH(twi) SDA_TO(twi, 1)
#define SDA_LOW(twi) SDA_TO(twi, 0)
#define SCL_HIGH(twi) SCL_TO(twi, 1)
#define SCL_LOW(twi) SCL_TO(twi, 0)

inline void huansic_I2C_start(HUAN_I2CM_TypeDef *twi) {
	if (!SDA_STATE(twi)) {
		SDA_HIGH(twi);
		huansic_us_delay(5);
	}
	SCL_HIGH(twi);
	huansic_us_delay(5);
	SDA_LOW(twi);
	huansic_us_delay(5);
	SCL_LOW(twi);
	huansic_us_delay(5);
}

inline void huansic_I2C_stop(HUAN_I2CM_TypeDef *twi) {
	// SCL should already be low
	SDA_LOW(twi);
	huansic_us_delay(5);
	SCL_HIGH(twi);
	huansic_us_delay(5);
	SDA_HIGH(twi);
	huansic_us_delay(5);
}

inline void huansic_I2C_sendBit(HUAN_I2CM_TypeDef *twi, uint8_t bit) {
	// SCL should already be low
	SDA_TO(twi, bit);
	huansic_us_delay(5);
	SCL_HIGH(twi);
	huansic_us_delay(5);
	SCL_LOW(twi);
	huansic_us_delay(5);
}

inline uint8_t huansic_I2C_readBit(HUAN_I2CM_TypeDef *twi) {
	uint8_t result;
	// SCL should already be low
	SDA_HIGH(twi);		// release
	huansic_us_delay(5);
	SCL_HIGH(twi);
	result = SDA_STATE(twi);		// read on rising edge
	huansic_us_delay(5);
	SCL_LOW(twi);
	huansic_us_delay(5);
	return result;
}

inline void huansic_I2C_Ack(HUAN_I2CM_TypeDef *twi) {
	huansic_I2C_sendBit(twi, 0);
}

inline void huansic_I2C_Nack(HUAN_I2CM_TypeDef *twi) {
	huansic_I2C_sendBit(twi, 1);
}

inline uint8_t huansic_I2C_getAck(HUAN_I2CM_TypeDef *twi) {
	return !huansic_I2C_readBit(twi);
}

inline uint8_t huansic_I2C_waitAck(HUAN_I2CM_TypeDef *twi, float timeout_us) {
	float startus = huansic_us_get();
	uint8_t result = 1;
	SDA_HIGH(twi);		// release
	huansic_us_delay(5);
	SCL_HIGH(twi);
	while(SDA_STATE(twi)) {		// wait until acknowledge or timeout
		if(huansic_us_get() - startus > timeout_us) {
			result = 0;
			break;
		}
	}
	huansic_us_delay(5);
	SCL_LOW(twi);
	huansic_us_delay(5);
	return result;
}

inline void huansic_I2C_sendByte(HUAN_I2CM_TypeDef *twi, uint8_t data) {
	uint8_t i;
	for (i = 0xF0; i; i >>= 1) {
		huansic_I2C_sendBit(twi, data & i ? 1 : 0);
	}
}

inline uint8_t huansic_I2C_readByte(HUAN_I2CM_TypeDef *twi) {
	uint8_t result = 0, i;
	for (i = 0; i < 8; i++) {
		result <<= 1;
		result |= huansic_I2C_readBit(twi);
	}
	return result;
}

uint8_t huansic_I2C_write(HUAN_I2CM_TypeDef *twi, uint8_t deviceAddr, uint8_t registerAddr,
		uint8_t *txBuffer, uint8_t len) {
	// start transaction
	huansic_I2C_start(twi);

	// call slave
	huansic_I2C_sendByte(twi, deviceAddr << 1);		// call slave and ask to write
	if (!huansic_I2C_waitAck(twi, 10000))			// wait 10ms for response
		return 0;

	// send register address
	huansic_I2C_sendByte(twi, registerAddr);
	huansic_I2C_waitAck(twi, 10000);				// should acknowledge fast enough

	// send data
	uint8_t counter = 0;
	while(len--) {
		huansic_I2C_sendByte(twi, *txBuffer);
		txBuffer++;
		if(!huansic_I2C_waitAck(twi, 10000))
		break;									// if it failed to send
		counter++;
	}

	// release line
	huansic_I2C_stop(twi);

	// return number of bytes sent
	return counter;
}

uint8_t huansic_I2C_read(HUAN_I2CM_TypeDef *twi, uint8_t deviceAddr, uint8_t registerAddr,
		uint8_t *rxBuffer, uint8_t len) {
	// start transaction
	huansic_I2C_start(twi);

	// call slave
	huansic_I2C_sendByte(twi, deviceAddr << 1);		// call slave and ask to write
	if (!huansic_I2C_waitAck(twi, 10000))			// wait 10ms for response
		return 0;

	// send register address
	huansic_I2C_sendByte(twi, registerAddr);
	huansic_I2C_waitAck(twi, 10000);				// should acknowledge fast enough

	// check if any data is required to be read
	if (len == 0) {
		// release line
		huansic_I2C_stop(twi);

		return 0;
	}

	// restart transaction
	huansic_I2C_start(twi);

	// call slave
	huansic_I2C_sendByte(twi, (deviceAddr << 1) | 0x01);		// call slave and ask to read
	if (!huansic_I2C_waitAck(twi, 10000))			// wait 10ms for response
		return 0;

	// receive data
	uint8_t counter = 0;
	len--;
	while(len--) {
		*rxBuffer = huansic_I2C_readByte(twi);
		rxBuffer++;
		huansic_I2C_Ack(twi);						// acknowledge for more data
		counter++;
	}
	*rxBuffer = huansic_I2C_readByte(twi);
	huansic_I2C_Nack(twi);							// NACK for no more data
	counter++;

	// release line
	huansic_I2C_stop(twi);

	// return the number of bytes received
	return counter;
}

#endif

