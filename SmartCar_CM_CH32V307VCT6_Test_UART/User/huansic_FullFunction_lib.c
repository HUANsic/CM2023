/*
 * huansic_FullFunction_lib.c
 *
 *  Created on: Apr 1, 2023
 *      Author: abcde
 */

#include "huansic_FullFunction_lib.h"
#include "lvgl_all_in.h"

#define KP_ADDRESS	0x10
#define KI_ADDRESS	0x20
#define KD_ADDRESS	0x30

void TIM9_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));		// PID timer
void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));		// Encoder timer
void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));		// Edgeboard
//void EXTI9_5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));		// Touch screen

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
Screen_TypeDef screen;
EEPROM_TypeDef eeprom;

void huansic_Initialize(void) {
	uint32_t edgemap, motormap, servomap, encodermap;

	// set up port mappings
	edgeboard.uart = USART3;
	edgeboard.txport = GPIOB;
	edgeboard.txpin = GPIO_Pin_10;
	edgeboard.rxport = GPIOB;
	edgeboard.rxpin = GPIO_Pin_11;
	motor.timer = TIM1;
	motor.channelN = TIM_Channel_1;
	motor.portN = GPIOA;
	motor.pinN = GPIO_Pin_8;
	motor.channelP = TIM_Channel_2;
	motor.portP = GPIOA;
	motor.pinP = GPIO_Pin_9;
	motor.portEn = GPIOA;
	motor.pinEn = GPIO_Pin_10;
	servo.timer = TIM8;
	servo.channel = TIM_Channel_4;
	servo.port = GPIOC;
	servo.pin = GPIO_Pin_9;
	servo.offset = 2;
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
	screen.int_port = GPIOD;
	screen.int_pin = GPIO_Pin_5;

	// set up PID
	pid_controller.timer = TIM9;
	pid_controller.kp = 30;
	pid_controller.ki = 0.4;
	pid_controller.kd = 5;
	pid_controller.goal = 0;

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
	if (edgemap && (edgemap != 0xFFFFFFFF)) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(edgemap, ENABLE);
	}
	if (motormap && (motormap != 0xFFFFFFFF)) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(motormap, ENABLE);
	}
	if (servomap && (servomap != 0xFFFFFFFF)) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(servomap, ENABLE);
	}
	if (encodermap && (encodermap != 0xFFFFFFFF)) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(encodermap, ENABLE);
	}

	// TODO complete this part
	huansic_Screen_Init(&screen);

	// initialize edgeboard interface
	huansic_Edgeboard_Init(&edgeboard);

	// initialize motor
	huansic_Motor_Init(&motor);

	// initialize servo
	huansic_Servo_Init(&servo);

	// initialize encoder
	huansic_Encoder_Init(&encoder);

	// initialize the LEDs
	huansic_LED_Init(&led1);
	huansic_LED_Init(&led2);
	huansic_LED_Init(&led3);
	huansic_LED_Init(&led4);

	// initialize PID timer
	huansic_Motor_PID_Init(&pid_controller);
}

void huansic_Edgeboard_Init(Edge_TypeDef *edgeboard) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;
	IRQn_Type irq;

	// enable TX GPIO port
	temp32_2 |= huansic_getAPB2_fromGPIO(edgeboard->txport);
	// enable RX GPIO port
	temp32_2 |= huansic_getAPB2_fromGPIO(edgeboard->rxport);
	// enable UART and find interrupt vector
	temp32_1 |= huansic_getAPB1_fromUART(edgeboard->uart);
	temp32_2 |= huansic_getAPB2_fromUART(edgeboard->uart);
	irq = huansic_getIRQ_fromUART(edgeboard->uart);

	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// set up TX and RX GPIO
	GPIO_InitStructure.GPIO_Pin = edgeboard->txpin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(edgeboard->txport, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = edgeboard->rxpin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(edgeboard->rxport, &GPIO_InitStructure);

	// set up UART
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// apply changes
	USART_Init(edgeboard->uart, &USART_InitStructure);

	// enable receiving interrupt
	USART_ITConfig(edgeboard->uart, USART_IT_RXNE, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// 2nd highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start UART
	USART_Cmd(edgeboard->uart, ENABLE);
}

void huansic_Edgeboard_Interpret(Edge_TypeDef *edgeboard) {
	uint16_t utemp16;
	int16_t stemp16;
	int8_t stemp8;
	float tempf;

	utemp16 = ((uint16_t) edgeboard->highByte << 7) | ((uint16_t) (edgeboard->lowByte));

	if (utemp16 >= EDGE_CMD_RESET_LED) {		// 0x3FF8~0x3FFF is for controlling the LEDs
		utemp16 &= ~EDGE_CMD_RESET_LED;
		if (utemp16 == 0x00) {
			huansic_LED_Set(&led1, 0);
		} else if (utemp16 == 0x01) {
			huansic_LED_Set(&led2, 0);
		} else if (utemp16 == 0x02) {
			huansic_LED_Set(&led3, 0);
		} else if (utemp16 == 0x03) {
			huansic_LED_Set(&led4, 0);
		} else if (utemp16 == 0x04) {
			huansic_LED_Set(&led1, 1);
		} else if (utemp16 == 0x05) {
			huansic_LED_Set(&led2, 1);
		} else if (utemp16 == 0x06) {
			huansic_LED_Set(&led3, 1);
		} else if (utemp16 == 0x07) {
			huansic_LED_Set(&led4, 1);
		}
	} else if (utemp16 >= EDGE_CMD_ENABLE) {		// 0x3F80~0x3FF7 enables motor output
		huansic_Motor_Enable(&motor);
	} else if (utemp16 >= EDGE_CMD_DISABLE) {		// 0x3F00~0x3F7F disables motor output
		huansic_Motor_Disable(&motor);
	} else if (utemp16 >= 0x1000) {		// 0x1000~0x3EFF
		// reserved
	} else if (utemp16 >= 0x0FD0) {		// 4040; 0x0FD0~0x0FFF
		stemp8 = (utemp16 << 4);	// keep 4 lowest bits as 2's complement
		stemp8 >>= 4;				// shift with sign
		if (utemp16 & 0x0030 == 0x0010) {		// modify kp
			pid_controller.kp += stemp8;
		} else if (utemp16 & 0x0030 == 0x0020) {	// modify ki
			pid_controller.ki += stemp8;
		} else if (utemp16 & 0x0030 == 0x0030) {	// modify kd
			pid_controller.kd += stemp8;
		} else {
			// reserved (should not happen)
		}
	} else if (utemp16 > 0x0FC8) {		// 0x0FC8~0x0FCF
		// reserved
	} else if (utemp16 >= 0x0F00) {		// 3840; 0x0F00~0x0FC8
		// 3840~4040 sets the servo angle
		stemp8 = utemp16 - 3940;
		huansic_Servo_Set(&servo, stemp8);
	} else if (utemp16 > 0x0E40) {		// 3648; 0x0E41~0x0EFF
		// reserved
	} else if (utemp16 >= 0x0800) {		// 2048; 0x0800~0x0E40
		stemp16 = utemp16 - 0x0800;
		stemp16 -= 800;
		//huansic_Motor_Set(&motor, stemp16);
	} else if (utemp16 > 0x0640) {		// 1600; 0x0641~0x07FF
		// reserved
	} else {							// 0x0000~0x0640
		tempf = utemp16;
		tempf -= 800;
		huansic_Motor_PID_SetGoal(&pid_controller, tempf);
	}
}

void huansic_Edgeboard_Send(Edge_TypeDef *edgeboard, char ch) {
	while(!(edgeboard->uart->STATR & USART_FLAG_TXE));
	USART_SendData(edgeboard->uart, ch);
	while(!(edgeboard->uart->STATR & USART_FLAG_TC));
}

void huansic_Edgeboard_SendString(Edge_TypeDef *edgeboard, char *str, uint8_t len) {
	uint8_t i;
	for (i = 0; i < len; i++) {
		while(!(edgeboard->uart->STATR & (1 << 7)));
		// wait for TXE to be set
		USART_SendData(edgeboard->uart, str[i]);
	}
	while(!(edgeboard->uart->STATR & (1 << 6)));
	// wait for TC to be set
}

void huansic_Edgeboard_IRQ(Edge_TypeDef *edgeboard, uint8_t msg) {
	uint32_t tick = SysTick->CNT;
	edgeboard->lastReceivedInterval = tick - edgeboard->lastReceived;
	edgeboard->lastReceived = tick;
	if (msg & 0x80) {
		edgeboard->highByte = msg & 0x7F;		// clear the highest byte
	} else {
		edgeboard->lowByte = msg;
		huansic_Edgeboard_Interpret(edgeboard);	// interpret the message every time a lower byte is received
	}
}

void huansic_Motor_Init(Motor_TypeDef *motor) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;

	// enable GPIO ports
	temp32_2 |= huansic_getAPB2_fromGPIO(motor->portP);
	temp32_2 |= huansic_getAPB2_fromGPIO(motor->portN);
	temp32_2 |= huansic_getAPB2_fromGPIO(motor->portEn);
	// enable PWM timer
	temp32_1 |= huansic_getAPB1_fromTIM(motor->timer);
	temp32_2 |= huansic_getAPB2_fromTIM(motor->timer);
	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// positive output pin configuration
	GPIO_InitStructure.GPIO_Pin = motor->pinP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->portP, &GPIO_InitStructure);

	// negative output pin configuration
	GPIO_InitStructure.GPIO_Pin = motor->pinN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->portN, &GPIO_InitStructure);

	// enable pin configuration
	GPIO_InitStructure.GPIO_Pin = motor->pinEn;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(motor->portEn, &GPIO_InitStructure);

	// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 800 - 1;		// period (50us)(20kHz)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 9 - 1;	// prescaler
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(motor->timer, &TIM_TimeBaseInitStructure);

	// set up channel
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// apply changes to positive channel
	switch (motor->channelP) {
	case TIM_Channel_1:
		TIM_OC1Init(motor->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(motor->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(motor->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(motor->timer, &TIM_OCInitStructure);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// apply changes to negative channel
	switch (motor->channelN) {
	case TIM_Channel_1:
		TIM_OC1Init(motor->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(motor->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(motor->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(motor->timer, &TIM_OCInitStructure);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

	// enable auto reload for the positive channel
	switch (motor->channelP) {
	case TIM_Channel_1:
		TIM_OC1PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// enable auto reload for the negative channel
	switch (motor->channelN) {
	case TIM_Channel_1:
		TIM_OC1PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4PreloadConfig(motor->timer, TIM_OCPreload_Enable);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// then enable the overall auto reload function
	TIM_ARRPreloadConfig(motor->timer, ENABLE);

	// configure interrupt (disable any)
	TIM_ITConfig(motor->timer, TIM_IT_Update, DISABLE);

	// enable PWM outputs
	TIM_CtrlPWMOutputs(motor->timer, ENABLE);

	// start the timer
	TIM_Cmd(motor->timer, ENABLE);

	// disable driver for now
	huansic_Motor_Disable(motor);
}

void huansic_Motor_Set(Motor_TypeDef *motor, int16_t power) {
	uint16_t posPower, negPower;
// -800 to 800; 800 > period(799) means full on, different from 799
	power = (power < -800) ? -800 : ((power > 800) ? 800 : power);
	posPower = power < 0 ? 0 : power;
	negPower = power < 0 ? -power : 0;

// apply positive
	if (motor->channelP == TIM_Channel_1) {
		motor->timer->CH1CVR = posPower;
	} else if (motor->channelP == TIM_Channel_2) {
		motor->timer->CH2CVR = posPower;
	} else if (motor->channelP == TIM_Channel_3) {
		motor->timer->CH3CVR = posPower;
	} else if (motor->channelP == TIM_Channel_4) {
		motor->timer->CH4CVR = posPower;
	}
// apply negative
	if (motor->channelN == TIM_Channel_1) {
		motor->timer->CH1CVR = negPower;
	} else if (motor->channelN == TIM_Channel_2) {
		motor->timer->CH2CVR = negPower;
	} else if (motor->channelN == TIM_Channel_3) {
		motor->timer->CH3CVR = negPower;
	} else if (motor->channelN == TIM_Channel_4) {
		motor->timer->CH4CVR = negPower;
	}
}

void huansic_Motor_Enable(Motor_TypeDef *motor) {
	GPIO_WriteBit(motor->portEn, motor->pinEn, 1);
}

void huansic_Motor_Disable(Motor_TypeDef *motor) {
	GPIO_WriteBit(motor->portEn, motor->pinEn, 0);
}

void huansic_Motor_PID_Init(PID_TypeDef *pid_controller) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;
	IRQn_Type irq;

	// enable timer
	temp32_1 |= huansic_getAPB1_fromTIM(pid_controller->timer);
	temp32_2 |= huansic_getAPB2_fromTIM(pid_controller->timer);
	irq = huansic_getIRQ_fromTIM(pid_controller->timer);
	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 200 - 1;	// period (200ticks/cycle*100us/tick=20ms/cycle)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 14400 - 1;	// prescaler (1/144MHz*14400=100us/tick)
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// apply changes
	TIM_TimeBaseInit(pid_controller->timer, &TIM_TimeBaseInitStructure);

	// configure interrupt (enable update)
	TIM_ITConfig(pid_controller->timer, TIM_IT_Update, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// 2nd highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 2nd highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start the timer
	TIM_Cmd(pid_controller->timer, ENABLE);
}

void huansic_Motor_PID_SetGoal(PID_TypeDef *pid_controller, int16_t goal) {
	pid_controller->goal = (float) goal;
}

void huansic_Motor_PID_IRQ(PID_TypeDef *pid_controller) {
	float newTick = huansic_Encoder_GetFullValue(&encoder);
	float diffTick = newTick - pid_controller->lastTick;

	pid_controller->lastTick = newTick;

	pid_controller->lastSpeed = (float) diffTick;

	pid_controller->last5Speed = (4.0 * pid_controller->last5Speed + pid_controller->lastSpeed)
			/ 5.0;

	float error = pid_controller->goal - pid_controller->last5Speed;	// use running average

	// Derivative
	float dError = error - pid_controller->lastError;

	// Proportional
	pid_controller->lastError = error;

	// Integral
	pid_controller->sError += pid_controller->lastError;

	// calculate and constrain the duty cycle
	float foutput = pid_controller->kp * pid_controller->lastError
			+ pid_controller->ki * pid_controller->sError
			+ pid_controller->kd * dError;
	foutput /= 10000;
	foutput = foutput > 1.0 ? 1.0 : (foutput < -1.0 ? -1.0 : foutput);

	huansic_Motor_Set(&motor, (int16_t) (foutput * 300));
}

void huansic_Servo_Init(Servo_TypeDef *servo) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;

	// enable GPIO port
	temp32_2 |= huansic_getAPB2_fromGPIO(servo->port);
	// enable PWM timer
	temp32_1 |= huansic_getAPB1_fromTIM(servo->timer);
	temp32_2 |= huansic_getAPB2_fromTIM(servo->timer);
	// apply changes
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	// set GPIO pin mode to AF mode and set to proper speed level
	GPIO_InitStructure.GPIO_Pin = servo->pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// apply changes
	GPIO_Init(servo->port, &GPIO_InitStructure);

	// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 2000 - 1;	// period (20ms)
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;	// prescaler
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// apply changes
	TIM_TimeBaseInit(servo->timer, &TIM_TimeBaseInitStructure);

	// set up channel
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = (uint16_t) (servo->offset + 150) - 1;	// center (1.5ms+offset)
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	// apply changes
	switch (servo->channel) {
	case TIM_Channel_1:
		TIM_OC1Init(servo->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_2:
		TIM_OC2Init(servo->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_3:
		TIM_OC3Init(servo->timer, &TIM_OCInitStructure);
		break;
	case TIM_Channel_4:
		TIM_OC4Init(servo->timer, &TIM_OCInitStructure);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}

	// enable auto reload for the specific channel
	switch (servo->channel) {
	case TIM_Channel_1:
		TIM_OC1PreloadConfig(servo->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_2:
		TIM_OC2PreloadConfig(servo->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_3:
		TIM_OC3PreloadConfig(servo->timer, TIM_OCPreload_Enable);
		break;
	case TIM_Channel_4:
		TIM_OC4PreloadConfig(servo->timer, TIM_OCPreload_Enable);
		break;
	default:
		while(1) {
			Delay_Ms(1000);
		}
	}
	// then enable the overall auto reload function
	TIM_ARRPreloadConfig(servo->timer, ENABLE);

	// configure interrupt (disable any)
	TIM_ITConfig(servo->timer, TIM_IT_Update, DISABLE);

	// enable PWM outputs
	TIM_CtrlPWMOutputs(servo->timer, ENABLE);

	// start the timer
	TIM_Cmd(servo->timer, ENABLE);
}

void huansic_Servo_Set(Servo_TypeDef *servo, int16_t angle) {
	angle = (angle < -100) ? -100 : ((angle > 100) ? 100 : angle);
	angle += 150 - 1 + servo->offset;

	// apply output
	if (servo->channel == TIM_Channel_1) {
		servo->timer->CH1CVR = angle;
	} else if (servo->channel == TIM_Channel_2) {
		servo->timer->CH2CVR = angle;
	} else if (servo->channel == TIM_Channel_3) {
		servo->timer->CH3CVR = angle;
	} else if (servo->channel == TIM_Channel_4) {
		servo->timer->CH4CVR = angle;
	}
}

void huansic_Encoder_Init(Encoder_TypeDef *encoder) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };
	TIM_ICInitTypeDef TIM_ICInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
	uint32_t temp32_1 = 0, temp32_2 = 0;
	IRQn_Type irq;

	// enable input GPIO ports
	temp32_2 |= huansic_getAPB2_fromGPIO(encoder->Aport);
	temp32_2 |= huansic_getAPB2_fromGPIO(encoder->Bport);
	irq = huansic_getIRQ_fromTIM(encoder->counter);

	// enable PWM timer
	temp32_1 |= huansic_getAPB1_fromTIM(encoder->counter);
	temp32_2 |= huansic_getAPB2_fromTIM(encoder->counter);
	// apply changes
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);

	// A-input pin configuration
	GPIO_InitStructure.GPIO_Pin = encoder->Apin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(encoder->Aport, &GPIO_InitStructure);

	// B-input output pin configuration
	GPIO_InitStructure.GPIO_Pin = encoder->Bpin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(encoder->Bport, &GPIO_InitStructure);

	// set up timer basic properties
	TIM_TimeBaseInitStructure.TIM_Period = 65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(encoder->counter, &TIM_TimeBaseInitStructure);

	// set up encoder interface
	TIM_EncoderInterfaceConfig(encoder->counter, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,
	TIM_ICPolarity_Rising);

	// set up input polarity
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(encoder->counter, &TIM_ICInitStructure);

	// configure interrupt (enable update)
	TIM_ClearFlag(encoder->counter, TIM_FLAG_Update);
	TIM_ITConfig(encoder->counter, TIM_IT_Update, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	// highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start the timer
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(encoder->counter, ENABLE);
}

uint16_t huansic_Encoder_GetValue(Encoder_TypeDef *encoder) {
	return encoder->counter->CNT;
}

float huansic_Encoder_GetFullValue(Encoder_TypeDef *encoder) {
	float tempf = encoder->overflow;
	tempf *= 65536;
	tempf += encoder->counter->CNT;
	return tempf;
}

void huansic_LED_Init(LED_TypeDef *led) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };

	RCC_APB2PeriphClockCmd(huansic_getAPB2_fromGPIO(led->port), ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = led->pin;
	GPIO_Init(led->port, &GPIO_InitStructure);

	// turn off for now
	GPIO_WriteBit(led->port, led->pin, Bit_RESET);
}

void huansic_LED_Set(LED_TypeDef *led, uint8_t state) {
	GPIO_WriteBit(led->port, led->pin, state);
}

uint8_t huansic_LED_Get(LED_TypeDef *led) {
	return GPIO_ReadOutputDataBit(led->port, led->pin);
}

void huansic_Screen_Init(Screen_TypeDef *screen) {
	lvgl_wch_all_start();
}

void huansic_TouchScreen_IRQ(void) {
	// TODO complete touch screen IRQ
	uint8_t data[] = { 0x42, 0x06, 0x06, 0x00, 0xFF, 0x4D };
	huansic_Edgeboard_SendString(&edgeboard, data, 6);
}

#ifdef USE_SW_TWI
void huansic_EEPROM_init(EEPROM_TypeDef *eeprom) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	uint32_t temp32_2 = 0;

	temp32_2 |= huansic_getAPB2_fromGPIO(eeprom->twi->sda_port);
	temp32_2 |= huansic_getAPB2_fromGPIO(eeprom->twi->scl_port);
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = eeprom->twi->scl_pin;
	GPIO_Init(eeprom->twi->scl_port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = eeprom->twi->sda_pin;
	GPIO_Init(eeprom->twi->sda_port, &GPIO_InitStructure);
}

uint8_t huansic_EEPROM_readBytes(EEPROM_TypeDef *eeprom, uint16_t address, uint8_t *buffer,
		uint8_t len) {
	address &= 0x07FF;				// constrain it to 11 bits
	uint8_t phys_address = eeprom->address & (0x78);	// clear highest and 3 lowest bits
	phys_address |= address >> 8;		// OR with the highest 3 bits of address
	return huansic_I2C_read(eeprom->twi, phys_address, address & 0x0FF, buffer, len);
}

uint8_t huansic_EEPROM_writeBytes(EEPROM_TypeDef *eeprom, uint16_t address, uint8_t *buffer,
		uint8_t len) {
	address &= 0x07FF;				// constrain it to 11 bits
	uint8_t phys_address = eeprom->address & (0x78);	// clear highest and 3 lowest bits
	phys_address |= address >> 8;		// OR with the highest 3 bits of address
	return huansic_I2C_write(eeprom->twi, phys_address, address & 0x0FF, buffer, len);
}

void huansic_EEPROM_savePID(EEPROM_TypeDef *eeprom, PID_TypeDef *pid_controller) {
	union {
		float f;
		uint8_t u[4];
	} tempunion;

	tempunion.f = pid_controller->kp;
	huansic_EEPROM_writeBytes(eeprom, KP_ADDRESS, &tempunion.u[0], 4);
	tempunion.f = pid_controller->ki;
	huansic_EEPROM_writeBytes(eeprom, KI_ADDRESS, &tempunion.u[0], 4);
	tempunion.f = pid_controller->kd;
	huansic_EEPROM_writeBytes(eeprom, KD_ADDRESS, &tempunion.u[0], 4);
}

void huansic_EEPROM_loadPID(EEPROM_TypeDef *eeprom, PID_TypeDef *pid_controller) {
	union {
		float f;
		uint8_t u[4];
	} tempunion;

	huansic_EEPROM_readBytes(eeprom, KP_ADDRESS, &tempunion.u[0], 4);
	pid_controller->kp = tempunion.f;
	huansic_EEPROM_readBytes(eeprom, KI_ADDRESS, &tempunion.u[0], 4);
	pid_controller->ki = tempunion.f;
	huansic_EEPROM_readBytes(eeprom, KD_ADDRESS, &tempunion.u[0], 4);
	pid_controller->kd = tempunion.f;
}

#else
void huansic_EEPROM_init(EEPROM_TypeDef *eeprom) {
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	I2C_InitTypeDef I2C_InitTSturcture = {0};
	uint32_t temp32_1 = 0, temp32_2 = 0;

	temp32_1 |= huansic_getAPB1_fromI2C(eeprom->twi);
	temp32_2 |= huansic_getAPB2_fromGPIO(eeprom->sda_port);
	temp32_2 |= huansic_getAPB2_fromGPIO(eeprom->scl_port);
	RCC_APB2PeriphClockCmd(temp32_2, ENABLE);
	RCC_APB1PeriphClockCmd(temp32_1, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = eeprom->scl_pin;
	GPIO_Init(eeprom->scl_port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = eeprom->sda_pin;
	GPIO_Init(eeprom->sda_port, &GPIO_InitStructure);

	I2C_InitTSturcture.I2C_ClockSpeed = eeprom->baud;
	I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
	I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitTSturcture.I2C_OwnAddress1 = 0x00;
	I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
	I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(eeprom->twi, &I2C_InitTSturcture);

	I2C_Cmd(eeprom->twi, ENABLE);

	I2C_AcknowledgeConfig(eeprom->twi, ENABLE);
}
#endif

void TIM9_UP_IRQHandler(void) {
	TIM_ClearFlag(TIM9, TIM_FLAG_Update);
	huansic_Motor_PID_IRQ(&pid_controller);
	// TODO split task
	lv_timer_handler();
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update)) {
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		if (encoder.counter->CTLR1 & TIM_DIR) {
			encoder.overflow--;
		} else {
			encoder.overflow++;
		}
	}
//	if(encoder.counter->)
//	encoder.overflow
}

void USART3_IRQHandler(void) {
	if (USART_GetITStatus(USART3, USART_IT_ORE)) {
		USART_ReceiveData(USART3);
		USART_ReceiveData(USART3);
		USART_ClearFlag(USART3, USART_FLAG_ORE);
	} else if (USART_GetITStatus(USART3, USART_IT_RXNE)) {
		huansic_Edgeboard_IRQ(&edgeboard, USART_ReceiveData(USART3));
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
}

/*void EXTI9_5_IRQHandler(void) {
 if (EXTI_GetITStatus(EXTI_Line5)) {
 EXTI_ClearITPendingBit(EXTI_Line5); // Clear Flag
 huansic_TouchScreen_IRQ();
 }
 }*/

void ui_cmd_go(void) {
	uint8_t data[] = { 0x42, 0x06, 0x06, 0x00, 0xFF, 0x4D };
	uint8_t i;
	for (i = 0; i < 6; i++) {
		while(!(USART3->STATR & (1 << 7)));
		// wait for TXE to be set
		USART_SendData(USART3, data[i]);
	}
	while(!(USART3->STATR & (1 << 6)));
	// wait for TC to be set
}

void ui_cmd_stop(void) {
	huansic_Motor_PID_SetGoal(&pid_controller, 0);
}

void ui_cmd_pid_save(void) {
	huansic_EEPROM_savePID(&eeprom, &pid_controller);
}
