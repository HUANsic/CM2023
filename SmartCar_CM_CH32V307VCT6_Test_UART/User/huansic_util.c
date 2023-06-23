/*
 * util.c
 *
 *  Created on: Jun 19, 2023
 *      Author: ZonghuanWu
 */

#include <huansic_util.h>

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

// 			[TIMx][Option][CHx]
/*
 *
 uint8_t huansic_remap_tim_table[][][] = {
 // TIM1
 {
 { 1, 	PAx | Px8, 	PAx | Px9, 	PAx | Px10, PAx | Px11}, 	// option 1
 { 2, 	PAx | Px8, 	PAx | Px9, 	PAx | Px10, PAx | Px11}, 	// option 2
 { 3,	PEx | Px9, 	PEx | Px11, PEx | Px13, PEx | Px14}, 	// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM2
 {
 { 1, 	PAx | Px0, 	PAx | Px1, 	PAx | Px2, 	PAx | Px3}, 	// option 1
 { 4,	PAx | Px15,	PBx | Px3, 	PAx | Px2, 	PAx | Px3}, 	// option 2
 { 5,	PAx | Px0, 	PAx | Px1, 	PBx | Px10, PBx | Px11}, 	// option 3
 { 6,	PAx | Px15,	PBx | Px3, 	PBx | Px10, PBx | Px11} 	// option 4
 },
 // TIM3
 {
 { 1,	PAx | Px6, 	PAx | Px7, 	PBx | Px0, 	PBx | Px1}, 	// option 1
 { 7,	PBx | Px4, 	PBx | Px5, 	PBx | Px0, 	PBx | Px1}, 	// option 2
 { 8,	PCx | Px6, 	PCx | Px7, 	PCx | Px8, 	PCx | Px9}, 	// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM4
 {
 { 1,	PBx | Px6,	PBx | Px7, 	PBx | Px8, 	PBx | Px9}, 	// option 1
 { 9,	PDx | Px12,	PDx | Px13,	PDx | Px14,	PDx | Px15}, 	// option 2
 { 0,	0,			0,			0,			0}, 			// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM5
 {
 { 1,	PAx | Px0, 	PAx | Px1, 	PAx | Px2, 	PAx | Px3}, 	// option 1
 { 0,	0,			0,			0,			0}, 			// option 2
 { 0,	0,			0,			0,			0}, 			// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM6 (no output)
 {
 { 0,	0,			0,			0,			0}, 			// option 1
 { 0,	0,			0,			0,			0}, 			// option 2
 { 0,	0,			0,			0,			0}, 			// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM7 (no output)
 {
 { 0,	0,			0,			0,			0}, 			// option 1
 { 0,	0,			0,			0,			0}, 			// option 2
 { 0,	0,			0,			0,			0}, 			// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM8
 {
 { 1,	PCx | Px6, 	PCx | Px7, 	PCx | Px8, 	PCx | Px9}, 	// option 1
 { 10,	PBx | Px6, 	PBx | Px7, 	PBx | Px8, 	PCx | Px13}, 	// option 2
 { 0,	0,			0,			0,			0}, 			// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM9
 {
 { 1,	PAx | Px2, 	PAx | Px3, 	PAx | Px4, 	PCx | Px4}, 	// option 1
 { 11,	PAx | Px2, 	PAx | Px3, 	PAx | Px4, 	PCx | Px14}, 	// option 2
 { 12,	PDx | Px9,	PDx | Px11,	PDx | Px13,	PDx | Px15}, 	// option 3
 { 0,	0,			0,			0,			0}	 			// option 4
 },
 // TIM10
 {
 { 1,	PBx | Px8,	PBx | Px9,	PCx | Px3,	PCx | Px11}, 	// option 1
 { 13,	PBx | Px3,	PBx | Px4,	PBx | Px5,	PCx | Px15}, 	// option 2
 { 14,	PDx | Px1,	PDx | Px3,	PDx | Px5,	PDx | Px7}, 	// option 3
 { 0,	0,			0,			0,			0} 				// option 4
 }
 };
 *
 */
uint8_t huansic_remap_tim_table[][][] = {
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
uint8_t huansic_remap_uart_table[][][] = {
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

uint32_t huansic_findRemap_servo(Servo_TypeDef *servo) {
	uint8_t timer, channel, portpin = 0, i;

	// find timer
	switch (servo->timer) {
	case TIM1:
		timer = 1;
		break;
	case TIM2:
		timer = 2;
		break;
	case TIM3:
		timer = 3;
		break;
	case TIM4:
		timer = 4;
		break;
	case TIM5:
		timer = 5;
		break;
	case TIM6:
		timer = 6;
		break;
	case TIM7:
		timer = 7;
		break;
	case TIM8:
		timer = 8;
		break;
	case TIM9:
		timer = 9;
		break;
	case TIM10:
		timer = 10;
		break;
	default:
		while(1) {
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
	switch (servo->port) {
	case GPIOA:
		portpin = PAx;
		break;
	case GPIOB:
		portpin = PBx;
		break;
	case GPIOC:
		portpin = PCx;
		break;
	case GPIOD:
		portpin = PDx;
		break;
	case GPIOE:
		portpin = PEx;
		break;
	default:
		while(1) {
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
	switch (motor->timer) {
	case TIM1:
		timer = 1;
		break;
	case TIM2:
		timer = 2;
		break;
	case TIM3:
		timer = 3;
		break;
	case TIM4:
		timer = 4;
		break;
	case TIM5:
		timer = 5;
		break;
	case TIM6:
		timer = 6;
		break;
	case TIM7:
		timer = 7;
		break;
	case TIM8:
		timer = 8;
		break;
	case TIM9:
		timer = 9;
		break;
	case TIM10:
		timer = 10;
		break;
	default:
		while(1) {
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
	// find port
	switch (motor->portP) {
	case GPIOA:
		portpinP = PAx;
		break;
	case GPIOB:
		portpinP = PBx;
		break;
	case GPIOC:
		portpinP = PCx;
		break;
	case GPIOD:
		portpinP = PDx;
		break;
	case GPIOE:
		portpinP = PEx;
		break;
	default:
		while(1) {
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
	switch (motor->portN) {
	case GPIOA:
		portpinN = PAx;
		break;
	case GPIOB:
		portpinN = PBx;
		break;
	case GPIOC:
		portpinN = PCx;
		break;
	case GPIOD:
		portpinN = PDx;
		break;
	case GPIOE:
		portpinN = PEx;
		break;
	default:
		while(1) {
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
	switch (edge->uart) {
	case USART1:
		uart = 1;
		break;
	case USART2:
		uart = 2;
		break;
	case USART3:
		uart = 3;
		break;
	case UART4:
		uart = 4;
		break;
	case UART5:
		uart = 5;
		break;
	case UART6:
		uart = 6;
		break;
	case UART7:
		uart = 7;
		break;
	case UART8:
		uart = 8;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find porttx
	switch (edge->txport) {
	case GPIOA:
		portpintx = PAx;
		break;
	case GPIOB:
		portpintx = PBx;
		break;
	case GPIOC:
		portpintx = PCx;
		break;
	case GPIOD:
		portpintx = PDx;
		break;
	case GPIOE:
		portpintx = PEx;
		break;
	default:
		while(1) {
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
	switch (edge->rxport) {
	case GPIOA:
		portpinrx = PAx;
		break;
	case GPIOB:
		portpinrx = PBx;
		break;
	case GPIOC:
		portpinrx = PCx;
		break;
	case GPIOD:
		portpinrx = PDx;
		break;
	case GPIOE:
		portpinrx = PEx;
		break;
	default:
		while(1) {
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
	switch (encoder->counter) {
	case TIM1:
		timer = 1;
		break;
	case TIM2:
		timer = 2;
		break;
	case TIM3:
		timer = 3;
		break;
	case TIM4:
		timer = 4;
		break;
	case TIM5:
		timer = 5;
		break;
	case TIM6:
		timer = 6;
		break;
	case TIM7:
		timer = 7;
		break;
	case TIM8:
		timer = 8;
		break;
	case TIM9:
		timer = 9;
		break;
	case TIM10:
		timer = 10;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find Aport
	switch (motor->portP) {
	case GPIOA:
		portpinA = PAx;
		break;
	case GPIOB:
		portpinA = PBx;
		break;
	case GPIOC:
		portpinA = PCx;
		break;
	case GPIOD:
		portpinA = PDx;
		break;
	case GPIOE:
		portpinA = PEx;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find Apin
	switch (motor->pinP) {
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
	switch (motor->portN) {
	case GPIOA:
		portpinB = PAx;
		break;
	case GPIOB:
		portpinB = PBx;
		break;
	case GPIOC:
		portpinB = PCx;
		break;
	case GPIOD:
		portpinB = PDx;
		break;
	case GPIOE:
		portpinB = PEx;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// find Bpin
	switch (motor->pinN) {
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


void huansic_Delay_Init(void){
	// TODO set up delay timer
}
