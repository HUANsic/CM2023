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
	lv_obj_t *screen_sysclock_label;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_pidgoal_label;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_statemachine_label;
	lv_obj_t *screen_go_btn;
	lv_obj_t *screen_go_btn_label;
	lv_obj_t *screen_pid_adjust_sw;
	lv_obj_t *screen_step_list;
	lv_obj_t *screen_label_6;
	lv_obj_t *screen_label_7;
	lv_obj_t *screen_kp_label;
	lv_obj_t *screen_kp_plus_btn;
	lv_obj_t *screen_kp_plus_btn_label;
	lv_obj_t *screen_kp_minus_btn;
	lv_obj_t *screen_kp_minus_btn_label;
	lv_obj_t *screen_ki_minus_btn;
	lv_obj_t *screen_ki_minus_btn_label;
	lv_obj_t *screen_ki_plus_btn;
	lv_obj_t *screen_ki_plus_btn_label;
	lv_obj_t *screen_kd_label;
	lv_obj_t *screen_kd_minus_btn;
	lv_obj_t *screen_kd_minus_btn_label;
	lv_obj_t *screen_kd_plus_btn;
	lv_obj_t *screen_kd_plus_btn_label;
	lv_obj_t *screen_ki_label;
	lv_obj_t *screen_msgbox_1;
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