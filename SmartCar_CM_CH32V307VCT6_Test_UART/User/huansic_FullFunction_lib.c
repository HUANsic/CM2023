/*
 * huansic_FullFunction_lib.c
 *
 *  Created on: Apr 1, 2023
 *      Author: abcde
 */

#include "huansic_FullFunction_lib.h"

const uint16_t EDGE_CMD_RESET_LED = 0x3FF8;
const uint16_t EDGE_CMD_SET_LED = 0x3FFC;
const uint16_t EDGE_CMD_ENABLE = 0x3F80;
const uint16_t EDGE_CMD_DISABLE = 0x3F00;

Edge_TypeDef edgeboard;
Motor_TypeDef motor;
Servo_TypeDef servo;
Encoder_TypeDef encoder;
LED_TypeDef led1, led2, led3, led4;

PID_TypeDef pid_controller;

void huansic_Initialize(void) {
	uint32_t edgemap, motormap, servomap, encodermap;

	// initialize clocks
	huansic_Clocks_Init();

	// set up port mappings
	edgeboard.uart = USART3;
	edgeboard.txport = GPIOB;
	edgeboard.txpin = GPIO_Pin_10;
	edgeboard.rxport = GPIOB;
	edgeboard.rxpin = GPIO_Pin_11;
	motor.timer = TIM1;
	motor.channelP = TIM_Channel_1;
	motor.portP = GPIOA;
	motor.pinP = GPIO_Pin_8;
	motor.channelN = TIM_Channel_2;
	motor.portN = GPIOA;
	motor.pinN = GPIO_Pin_9;
	servo.timer = TIM8;
	servo.channel = TIM_Channel_4;
	servo.port = GPIOC;
	servo.pin = GPIO_Pin_9;
	encoder.counter = TIM3;
	encoder.Aport = GPIOC;
	encoder.Apin = GPIO_Pin_6;
	encoder.Bport = GPIOC;
	encoder.Bpin = GPIO_Pin_7;
	led1.port = GPIOE;
	led1.pin = GPIO_Pin_7;
	led2.port = GPIOE;
	led2.pin = GPIO_Pin_8;
	led3.port = GPIOE;
	led3.pin = GPIO_Pin_9;
	led4.port = GPIOE;
	led4.pin = GPIO_Pin_10;

	// set up PID
	pid_controller.timer = TIM9;
	pid_controller.kp = 0.000;
	pid_controller.ki = 0.000;
	pid_controller.kd = 0.000;
	pid_controller.dt = 0.050;

	// check port availability
	edgemap = huansic_findRemap_edge(&edgeboard);
	motormap = huansic_findRemap_motor(&motor);
	servomap = huansic_findRemap_servo(&servo);
	encodermap = huansic_findRemap_encoder(&encoder);
	if (edgemap == HUAN_NoMapping || motormap == HUAN_NoMapping || servomap == HUAN_NoMapping
			|| encodermap == HUAN_NoMapping) {
		while(1) {
			Delay_Ms(1000);
		}
	}

	// remap any if needed
	GPIO_PinRemapConfig(edgemap, ENABLE);
	GPIO_PinRemapConfig(motormap, ENABLE);
	GPIO_PinRemapConfig(servomap, ENABLE);
	GPIO_PinRemapConfig(encodermap, ENABLE);

	// initialize edgeboard interface
	huansic_Edgeboard_Init(&edgeboard);

	// initialize motor
	huansic_Motor_Init(&motor);

	// initialize servo
	huansic_Servo_Init(&servo);

	// initialize encoder
	huansic_Encoder_Init(&encoder);

	// initialize the LEDs
	huansic_LED_Init();

	// initialize PID timer
	huansic_Motor_PID_Init();
}

void huansic_Clocks_Init(void) {
	// disable peripheral clocks
	uint32_t rcc_apb1pcenr = RCC->APB1PCENR;
	RCC->APB1PCENR = 0;
	uint32_t rcc_apb2pcenr = RCC->APB2PCENR;
	RCC->APB2PCENR = 0;

	// make sure HSI is on
	if (!(RCC->CTLR & (1 << 1))) {	// HSIRDY
		RCC->CTLR |= (1 << 0);		// HSION(1)
		while(!(RCC->CTLR & (1 << 1)));
	}

	// switch to HSI for now
	RCC->CFGR0 &= ~(0x03L << 0);	// SW(00)

	// if PLL is on, turn it off
	if (RCC->CTLR & (1 << 25)) {		// PLLRDY
		RCC->CTLR &= ~(1 << 24);	// PLLON(0)
		while(RCC->CTLR & (1 << 25));
	}

	// enable HSE
	RCC->CTLR |= (1 << 16);		// HSEON

	// configure the path before the system clock MUX
	RCC->CFGR2 |= (1 << 16);		// PREDIV1SRC (HSE)
	RCC->CFGR2 &= ~(0x0FL << 0);	// PREDIV1 (/1)
	RCC->CFGR0 |= (1 << 16);		// PLLSRC (HSE)
	RCC->CFGR0 |= (0x0F << 18);		// PLLMUL (x18)

	// wait for HSE to stabilize
	while(!(RCC->CTLR & (1 << 17)));
	// HSERDY

	// enable PLL
	RCC->CTLR |= (1 << 24);		// PLLON(1)

	// wait for PLL to stabilize
	while(!(RCC->CTLR & (1 << 25)));
	// PLLRDY

	// configure the path before peripheral clocks
	// AHB prescaler (/1)
	RCC->CFGR0 &= ~(0x0FL << 4);		// HPRE(0)
	// APB1 prescaler (/1)
	RCC->CFGR0 &= ~(0x07L << 8);		// PPRE1(0)
	// APB1 prescaler (/1)
	RCC->CFGR0 &= ~(0x07L << 11);		// PPRE2(0)
	// USB prescaler (/3)
	RCC->CFGR0 = (RCC->CFGR0 & ~(0x03L << 22)) | (1 << 23);

	// switch the system clock source to PLL
	RCC->CFGR0 = (RCC->CFGR0 & (~(0x03L << 0))) | (0x02 << 0);		// SW (10)

	// enable peripheral clocks
	RCC->APB1PCENR = rcc_apb1pcenr;
	RCC->APB2PCENR = rcc_apb2pcenr;
}

void huansic_Edgeboard_Init(Edge_TypeDef *edgeboard) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;
	IRQn_Type irq;

	// enable TX GPIO port
	switch (edgeboard.txport) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// enable RX GPIO port
	switch (edgeboard.rxport) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// enable UART and find interrupt vector
	switch (edgeboard.uart) {
	case USART1:
		temp32_2 |= RCC_APB2Periph_USART1;
		irq = USART1_IRQn;
		break;
	case USART2:
		temp32_1 |= RCC_APB1Periph_USART2;
		irq = USART2_IRQn;
		break;
	case USART3:
		temp32_1 |= RCC_APB1Periph_USART3;
		irq = USART3_IRQn;
		break;
	case UART4:
		temp32_1 |= RCC_APB1Periph_UART4;
		irq = UART4_IRQn;
		break;
	case UART5:
		temp32_1 |= RCC_APB1Periph_UART5;
		irq = UART5_IRQn;
		break;
	case UART6:
		temp32_1 |= RCC_APB1Periph_UART6;
		irq = UART6_IRQn;
		break;
	case UART7:
		temp32_1 |= RCC_APB1Periph_UART7;
		irq = UART7_IRQn;
		break;
	case UART8:
		temp32_1 |= RCC_APB1Periph_UART8;
		irq = UART8_IRQn;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// set up TX and RX GPIO
	GPIO_InitStructure.GPIO_Pin = edgeboard.txpin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(edgeboard.txport, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = edgeboard.rxpin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(edgeboard.rxport, &GPIO_InitStructure);

	// set up UART
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// apply changes
	USART_Init(edgeboard.uart, &USART_InitStructure);

	// enable receiving interrupt
	USART_ITConfig(edgeboard.uart, USART_IT_RXNE, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start UART
	USART_Cmd(edgeboard.uart, ENABLE);
}

void huansic_Edgeboard_Interpret(void) {
	uint16_t utemp16;
	int16_t stemp16;
	int8_t stemp8;

	utemp16 = ((uint16_t) edgeboard.highByte << 7) | ((uint16_t) (edgeboard.lowByte));

	if (utemp16 >= EDGE_CMD_RESET_LED) {		// 0x3FF8~0x3FFF is for controlling the LEDs
		utemp16 &= ~EDGE_CMD_RESET_LED;
		if (utemp16 == 0x00) {
			huansic_LED1_Set(0);
		} else if (utemp16 == 0x01) {
			huansic_LED2_Set(0);
		} else if (utemp16 == 0x02) {
			huansic_LED3_Set(0);
		} else if (utemp16 == 0x03) {
			huansic_LED4_Set(0);
		} else if (utemp16 == 0x04) {
			huansic_LED1_Set(1);
		} else if (utemp16 == 0x05) {
			huansic_LED2_Set(1);
		} else if (utemp16 == 0x06) {
			huansic_LED3_Set(1);
		} else if (utemp16 == 0x07) {
			huansic_LED4_Set(1);
		}
	} else if (utemp16 >= EDGE_CMD_ENABLE) {		// 0x3F80~0x3FF8 enables PID output
		pid_controller.enabled = 1;
	} else if (utemp16 >= EDGE_CMD_DISABLE) {		// 0x3F00~0x3F80 disables PID output
		pid_controller.enabled = 0;
	} else if (utemp16 >= 2200) {
		// reserved
	} else if (utemp16 >= 2000) {		// 2000~2200 sets the servo angle
		stemp8 = utemp16 - 2100;
		huansic_Servo_Set(stemp8);
	} else if (utemp16 >= 1600) {
		// reserved
	} else {		// motor output is limited to below 1600 (-800 to 800)
		stemp16 = utemp16;
		stemp16 -= 800;
		huansic_Motor_PID_SetGoal(stemp16);
	}
}

void huansic_Edgeboard_IRQ(void) {
	uint8_t utemp8;
	utemp8 = (uint8_t) USART_ReceiveData(edgeboard.uart);
	if (utemp8 & 0x80) {
		edgeboard.highByte = utemp8 & 0x7F;		// clear the highest byte
	} else {
		edgeboard.lowByte = utemp8;
		huansic_Edgeboard_Interpret();	// interpret the message every time a lower byte is received
	}
}

void huansic_Motor_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;

// enable positive GPIO port
	switch (motor.portP) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// enable negative GPIO port
	switch (motor.portN) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// enable PWM timer
	switch (motor.timer) {
	case TIM1:
		temp32_2 |= RCC_APB2Periph_TIM1;
		break;
	case TIM2:
		temp32_1 |= RCC_APB1Periph_TIM2;
		break;
	case TIM3:
		temp32_1 |= RCC_APB1Periph_TIM3;
		break;
	case TIM4:
		temp32_1 |= RCC_APB1Periph_TIM4;
		break;
	case TIM5:
		temp32_1 |= RCC_APB1Periph_TIM5;
		break;
	case TIM6:
		temp32_1 |= RCC_APB1Periph_TIM6;
		break;
	case TIM7:
		temp32_1 |= RCC_APB1Periph_TIM7;
		break;
	case TIM8:
		temp32_2 |= RCC_APB2Periph_TIM8;
		break;
	case TIM9:
		temp32_2 |= RCC_APB2Periph_TIM9;
		break;
	case TIM10:
		temp32_2 |= RCC_APB2Periph_TIM10;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

// positive output pin configuration
	GPIO_InitStructure.GPIO_Pin = motor.pinP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor.portP, &GPIO_InitStructure);

// negative output pin configuration
	GPIO_InitStructure.GPIO_Pin = motor->pinN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor.portN, &GPIO_InitStructure);

// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 800 - 1;		// period (50us)(20kHz)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 9 - 1;	// prescaler
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(motor.timer, &TIM_TimeBaseInitStructure);

// set up channel
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// apply changes to positive channel
	switch (motor.channelP) {
	case TIM_Channel_1:
		TIM_OC1Init(motor.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(motor.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(motor.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(motor.timer, TIM_OCInitStructure);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// apply changes to negative channel
	switch (motor.channelN) {
	case TIM_Channel_1:
		TIM_OC1Init(motor.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(motor.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(motor.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(motor.timer, TIM_OCInitStructure);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

// enable auto reload for the positive channel
	switch (motor.channelP) {
	case TIM_Channel_1:
		TIM_OC1PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// enable auto reload for the negative channel
	switch (motor.channelN) {
	case TIM_Channel_1:
		TIM_OC1PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4PreloadConfig(motor.timer, TIM_OCPreload_Enable);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// then enable the overall auto reload function
	TIM_ARRPreloadConfig(motor.timer, ENABLE);

// configure interrupt (disable any)
	TIM_ITConfig(motor.timer, TIM_IT_Update, DISABLE);

// enable PWM outputs
	TIM_CtrlPWMOutputs(motor.timer, ENABLE);

// start the timer
	TIM_Cmd(motor.timer, ENABLE);
}

void huansic_Motor_Set(int16_t power) {
	uint16_t posPower, negPower;
// -800 to 800; 800 > period(799) means full on, different from 799
	power = (power < -800) ? -800 : ((power > 800) ? 800 : power);
	posPower = power < 0 ? 0 : power;
	negPower = power < 0 ? -power : 0;

// apply positive
	if (motor.channelP == TIM_Channel_1) {
		motor.timer->CH1CVR = posPower;
	} else if (motor.channelP == TIM_Channel_2) {
		motor.timer->CH2CVR = posPower;
	} else if (motor.channelP == TIM_Channel_3) {
		motor.timer->CH3CVR = posPower;
	} else if (motor.channelP == TIM_Channel_4) {
		motor.timer->CH4CVR = posPower;
	}
// apply negative
	if (motor.channelN == TIM_Channel_1) {
		motor.timer->CH1CVR = negPower;
	} else if (motor.channelN == TIM_Channel_2) {
		motor.timer->CH2CVR = negPower;
	} else if (motor.channelN == TIM_Channel_3) {
		motor.timer->CH3CVR = negPower;
	} else if (motor.channelN == TIM_Channel_4) {
		motor.timer->CH4CVR = negPower;
	}
}

void huansic_Motor_PID_Init(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;
	IRQn_Type irq;

// enable timer
	switch (pid_controller.timer) {
	case TIM1:
		temp32_2 |= RCC_APB2Periph_TIM1;
		irq = TIM1_UP_IRQn;
		break;
	case TIM2:
		temp32_1 |= RCC_APB1Periph_TIM2;
		irq = TIM2_IRQn;
		break;
	case TIM3:
		temp32_1 |= RCC_APB1Periph_TIM3;
		irq = TIM3_IRQn;
		break;
	case TIM4:
		temp32_1 |= RCC_APB1Periph_TIM4;
		irq = TIM4_IRQn;
		break;
	case TIM5:
		temp32_1 |= RCC_APB1Periph_TIM5;
		irq = TIM5_IRQn;
		break;
	case TIM6:
		temp32_1 |= RCC_APB1Periph_TIM6;
		irq = TIM6_IRQn;
		break;
	case TIM7:
		temp32_1 |= RCC_APB1Periph_TIM7;
		irq = TIM7_IRQn;
		break;
	case TIM8:
		temp32_2 |= RCC_APB2Periph_TIM8;
		irq = TIM8_UP_IRQn;
		break;
	case TIM9:
		temp32_2 |= RCC_APB2Periph_TIM9;
		irq = TIM9_UP_IRQn;
		break;
	case TIM10:
		temp32_2 |= RCC_APB2Periph_TIM10;
		irq = TIM10_UP_IRQn;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 2000 - 1;// period (2000ticks/cycle*10us/tick=20ms/cycle)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;	// prescaler (1/144MHz*1440=10us/tick)
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
// apply changes
	TIM_TimeBaseInit(pid_controller.timer, &TIM_TimeBaseInitStructure);

// configure interrupt (enable update)
	TIM_ITConfig(pid_controller.timer, TIM_IT_Update, ENABLE);

	// set up NVIC
    NVIC_InitStructure.NVIC_IRQChannel = irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // apply changes
    NVIC_Init(&NVIC_InitStructure);

// start the timer
	TIM_Cmd(pid_controller.timer, ENABLE);
}

void huansic_Motor_PID_SetGoal(int16_t goal) {
	pid_controller.goal = (float) goal;
}

void huansic_Motor_PID_IRQ(void) {
	// TODO complete PID calculation
}

void huansic_Servo_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;

// enable GPIO port
	switch (servo.port) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// enable PWM timer
	switch (servo.timer) {
	case TIM1:
		temp32_2 |= RCC_APB2Periph_TIM1;
		break;
	case TIM2:
		temp32_1 |= RCC_APB1Periph_TIM2;
		break;
	case TIM3:
		temp32_1 |= RCC_APB1Periph_TIM3;
		break;
	case TIM4:
		temp32_1 |= RCC_APB1Periph_TIM4;
		break;
	case TIM5:
		temp32_1 |= RCC_APB1Periph_TIM5;
		break;
	case TIM6:
		temp32_1 |= RCC_APB1Periph_TIM6;
		break;
	case TIM7:
		temp32_1 |= RCC_APB1Periph_TIM7;
		break;
	case TIM8:
		temp32_2 |= RCC_APB2Periph_TIM8;
		break;
	case TIM9:
		temp32_2 |= RCC_APB2Periph_TIM9;
		break;
	case TIM10:
		temp32_2 |= RCC_APB2Periph_TIM10;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

// set GPIO pin mode to AF mode and set to proper speed level
	GPIO_InitStructure.GPIO_Pin = servo.pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// apply changes
	GPIO_Init(servo.port, &GPIO_InitStructure);

// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 2000 - 1;	// period (20ms)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;	// prescaler
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
// apply changes
	TIM_TimeBaseInit(servo.timer, &TIM_TimeBaseInitStructure);

// set up channel
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 150 - 1;		// center (1.5ms)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
// apply changes
	switch (servo.channel) {
	case TIM_Channel_1:
		TIM_OC1Init(servo.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(servo.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(servo.timer, TIM_OCInitStructure);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(servo.timer, TIM_OCInitStructure);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

// enable auto reload for the specific channel
	switch (servo.channel) {
	case TIM_Channel_1:
		TIM_OC1PreloadConfig(servo.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2PreloadConfig(servo.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3PreloadConfig(servo.timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4PreloadConfig(servo.timer, TIM_OCPreload_Enable);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// then enable the overall auto reload function
	TIM_ARRPreloadConfig(servo.timer, ENABLE);

// configure interrupt (disable any)
	TIM_ITConfig(servo.timer, TIM_IT_Update, DISABLE);

// enable PWM outputs
	TIM_CtrlPWMOutputs(servo.timer, ENABLE);

// start the timer
	TIM_Cmd(servo.timer, ENABLE);
}

void huansic_Servo_Set(int8_t angle) {
	angle = (angle < -100) ? -100 : ((angle > 100) ? 100 : angle);
	angle += 150 - 1;

	// apply output
	if (servo.channel == TIM_Channel_1) {
		servo.timer->CH1CVR = angle;
	} else if (servo.channel == TIM_Channel_2) {
		servo.timer->CH2CVR = angle;
	} else if (servo.channel == TIM_Channel_3) {
		servo.timer->CH3CVR = angle;
	} else if (servo.channel == TIM_Channel_4) {
		servo.timer->CH4CVR = angle;
	}
}

void huansic_Encoder_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;

// enable A-input GPIO port
	switch (encoder.Aport) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// enable B-input GPIO port
	switch (encoder.Bport) {
	case GPIOA:
		temp32_2 |= RCC_APB2Periph_GPIOA;
		break;
	case GPIOB:
		temp32_2 |= RCC_APB2Periph_GPIOB;
		break;
	case GPIOC:
		temp32_2 |= RCC_APB2Periph_GPIOC;
		break;
	case GPIOD:
		temp32_2 |= RCC_APB2Periph_GPIOD;
		break;
	case GPIOE:
		temp32_2 |= RCC_APB2Periph_GPIOE;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// enable PWM timer
	switch (encoder.counter) {
	case TIM1:
		temp32_2 |= RCC_APB2Periph_TIM1;
		break;
	case TIM2:
		temp32_1 |= RCC_APB1Periph_TIM2;
		break;
	case TIM3:
		temp32_1 |= RCC_APB1Periph_TIM3;
		break;
	case TIM4:
		temp32_1 |= RCC_APB1Periph_TIM4;
		break;
	case TIM5:
		temp32_1 |= RCC_APB1Periph_TIM5;
		break;
	case TIM6:
		temp32_1 |= RCC_APB1Periph_TIM6;
		break;
	case TIM7:
		temp32_1 |= RCC_APB1Periph_TIM7;
		break;
	case TIM8:
		temp32_2 |= RCC_APB2Periph_TIM8;
		break;
	case TIM9:
		temp32_2 |= RCC_APB2Periph_TIM9;
		break;
	case TIM10:
		temp32_2 |= RCC_APB2Periph_TIM10;
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

// A-input pin configuration
	GPIO_InitStructure.GPIO_Pin = encoder.Apin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(encoder.Aport, &GPIO_InitStructure);

// B-input output pin configuration
	GPIO_InitStructure.GPIO_Pin = encoder.Bpin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(encoder.Bport, &GPIO_InitStructure);

// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(encoder.counter, &TIM_TimeBaseInitStructure);

// set up encoder interface
	TIM_EncoderInterfaceConfig(encoder.counter, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,
	TIM_ICPolarity_Rising);

// configure interrupt (disable any)
	TIM_ITConfig(encoder.counter, TIM_IT_Update, DISABLE);

// enable PWM outputs
	TIM_CtrlPWMOutputs(encoder.counter, ENABLE);

// start the timer
	TIM_Cmd(encoder.counter, ENABLE);
}

uint16_t huansic_Encoder_GetValue(void) {
	return encoder.counter->CNT;
}

void huansic_LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = led1.pin;
	GPIO_Init(led1.port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = led2.pin;
	GPIO_Init(led2.port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = led3.pin;
	GPIO_Init(led3.port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = led4.pin;
	GPIO_Init(led4.port, &GPIO_InitStructure);

// turn off for now
	GPIO_WriteBit(led1.port, led1.pin, Bit_RESET);
	GPIO_WriteBit(led2.port, led2.pin, Bit_RESET);
	GPIO_WriteBit(led3.port, led3.pin, Bit_RESET);
	GPIO_WriteBit(led4.port, led4.pin, Bit_RESET);
}

void huansic_LED1_Set(uint8_t state) {
	if (state)
		led1.port->BSHR = led1.pin;
	else
		led1.port->BCR = led1.pin;
}

void huansic_LED2_Set(uint8_t state) {
	if (state)
		led2.port->BSHR = led2.pin;
	else
		led2.port->BCR = led2.pin;
}

void huansic_LED3_Set(uint8_t state) {
	if (state)
		led3.port->BSHR = led3.pin;
	else
		led3.port->BCR = led3.pin;
}

void huansic_LED4_Set(uint8_t state) {
	if (state)
		led4.port->BSHR = led4.pin;
	else
		led4.port->BCR = led4.pin;
}

void huansic_TouchScreen_IRQ(void){
	// TODO complete touch screen IRQ
}
