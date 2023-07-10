/*
 * lvgl_all_in.c
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */
#include "lvgl_all_in.h"

lv_ui guider_ui;

void lvgl_wch_all_start(void){
    LVGL_TIM2_Init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    setup_ui(&guider_ui);
    events_init(&guider_ui);
}
