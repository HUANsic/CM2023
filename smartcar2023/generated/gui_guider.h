/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *g_kb_screen;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_label_speed;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_label_pidgoal;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_label_stepcounter;
	lv_obj_t *screen_label_7;
	lv_obj_t *screen_sw_pid;
	lv_obj_t *screen_btn_go;
	lv_obj_t *screen_btn_go_label;
	lv_obj_t *screen_label_8;
	lv_obj_t *screen_btn_add;
	lv_obj_t *screen_btn_add_label;
	lv_obj_t *screen_adjstep_list;
	lv_obj_t *screen_label_9;
	lv_obj_t *screen_btn_sub;
	lv_obj_t *screen_btn_sub_label;
	lv_obj_t *screen_btn_next;
	lv_obj_t *screen_btn_next_label;
	lv_obj_t *screen_sw_disarm;
	lv_obj_t *screen_label_10;
	lv_obj_t *screen_btn_save;
	lv_obj_t *screen_btn_save_label;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen(lv_ui *ui);

LV_FONT_DECLARE(lv_font_Alatsi_Regular_14)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_25)


#ifdef __cplusplus
}
#endif
#endif
