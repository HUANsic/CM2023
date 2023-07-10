/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	bool screen_del;
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
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif