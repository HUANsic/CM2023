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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "debug.h"
#include "ILI9341.h"
#include "ILI9341_Touchscreen.h"
#include "ILI9341_WCH_Driver.h"
#include "ILI9341_GFX.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"

/* Global typedef */

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      WCH_ILI9341_SPI_FullDuplex_Init
 *
 * @brief   Declared in ILI9341.h
 *
 * @return  none
 */

void WCH_ILI9341_SPI_FullDuplex_Init(void){
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
    AFIO->PCFR1|=0x01<<28;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
//    GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);
//    AFIO->PCFR1|=0x01<<28;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI3, &SPI_InitStructure);

    SPI_Cmd(SPI3, ENABLE);
}

/*********************************************************************
 * @fn      WCH_ILI9341_GPIO_FullDuplex_Init
 *
 * @brief   Declared in ILI9341.h
 *
 * @return  none
 */

void WCH_ILI9341_GPIO_FullDuplex_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      GPIOE_Init
 *
 * @brief   Initialize GPIOE
 *
 * @return  none
 */

void GPIOE_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void GPIOD_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void LVGL_TIM2_Init(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};
    NVIC_InitTypeDef NVIC_InitStructure={0};
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitStructure.TIM_Period=9600-1;
    TIM_TimeBaseInitStructure.TIM_Prescaler=100-1;
    // 96MHz 10ms
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM2, ENABLE);
}

uint16_t cnt=0;
uint8_t led_flag=0;
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void){
    if(TIM_GetITStatus(TIM2, TIM_IT_Update)){
        lv_tick_inc(10);
        if(++cnt>=100){
            if(led_flag){
                led_flag=0;
                GPIO_WriteBit(GPIOE, GPIO_Pin_7, 1);
            }else{
                led_flag=1;
                GPIO_WriteBit(GPIOE, GPIO_Pin_7, 0);
            }
            cnt=0;
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void my_lv_port_init(void){
    lv_init();
    lv_port_disp_init();

    lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    lv_obj_set_size(spinner, 64, 64);
    lv_obj_align(spinner, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t* led_obj=lv_led_create(lv_scr_act());
    lv_obj_set_size(led_obj, 48, 24);
    lv_obj_align(led_obj, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* label_obj=lv_label_create(lv_scr_act());
    lv_obj_set_size(label_obj, 220, 30);
    lv_label_set_text(label_obj, "Hello LVGL FROM BD402");
    lv_obj_align(label_obj, LV_ALIGN_BOTTOM_MID, 20, 0);
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
    uint32_t frame=0;
    uint8_t frame_disp_buff[15];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	GPIOE_Init();
	LVGL_TIM2_Init();
	my_lv_port_init();
	while(1)
    {
	    lv_timer_handler();
	    Delay_Ms(5);
//	    memset(frame_disp_buff,0,15);
//	    sprintf(frame_disp_buff,"Frame: %lu",frame++);
//	    ILI9341_Draw_Text(frame_disp_buff, 10, 10, BLACK, 1, WHITE);
	}
}

#define MACRO_USB_SEND_BYTE(x)

void sendCMD_pid(int16_t goal){
	uint16_t sendVal;
	goal = (goal < -800) ? -800 : ((goal > 800) ? 800 : goal);
	goal += 800;
	sendVal = goal & 0x3F80;
	sendVal <<= 1;		// shift left one bit
	sendVal |= 0x8000;	// format MSb
	sendVal |= goal & 0x007F;
	MACRO_USB_SEND_BYTE(sendVal & 0x00FF);		// send low byte first
	MACRO_USB_SEND_BYTE((sendVal >> 8) & 0x00FF);	// then send high byte
}

void sendCMD_motor(int16_t goal){
	uint16_t sendVal;
	goal = (goal < -200) ? -200 : ((goal > 200) ? 200 : goal);
	goal += 800;
	goal += 0x800;
	sendVal = goal & 0x3F80;
	sendVal <<= 1;		// shift left one bit
	sendVal |= 0x8000;	// format MSb
	sendVal |= goal & 0x007F;
	MACRO_USB_SEND_BYTE(sendVal & 0x00FF);		// send low byte first
	MACRO_USB_SEND_BYTE((sendVal >> 8) & 0x00FF);	// then send high byte
}

void sendCMD_servo(int16_t angle){
	uint16_t sendVal;
	angle = (angle < -30) ? -30 : ((angle > 30) ? 30 : angle);
	angle += 3940;
	sendVal = angle & 0x3F80;
	sendVal <<= 1;		// shift left one bit
	sendVal |= 0x8000;	// format MSb
	sendVal |= goal & 0x007F;
	MACRO_USB_SEND_BYTE(sendVal & 0x00FF);		// send low byte first
	MACRO_USB_SEND_BYTE((sendVal >> 8) & 0x00FF);	// then send high byte
}

void sendCMD_disableMotor(){
	uint16_t sendVal = 0xFF00;
	MACRO_USB_SEND_BYTE(sendVal & 0x00FF);		// send low byte first
	MACRO_USB_SEND_BYTE((sendVal >> 8) & 0x00FF);	// then send high byte
}

void sendCMD_enableMotor(){
	uint16_t sendVal = 0xFF40;
	MACRO_USB_SEND_BYTE(sendVal & 0x00FF);		// send low byte first
	MACRO_USB_SEND_BYTE((sendVal >> 8) & 0x00FF);	// then send high byte
}

void sendCMD_setLED(uint8_t index, uint8_t status){		// 0 <= index <= 3
	uint16_t sendVal = 0xFF78 | (status ? 0x04 : 0) | index;
	MACRO_USB_SEND_BYTE(sendVal & 0x00FF);		// send low byte first
	MACRO_USB_SEND_BYTE((sendVal >> 8) & 0x00FF);	// then send high byte
}
