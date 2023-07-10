/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

static lv_obj_t * g_kb_screen;
static void kb_screen_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
__attribute__((unused)) static void ta_screen_event_cb(lv_event_t *e)
{

	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	lv_obj_t *kb = lv_event_get_user_data(e);
	if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_move_foreground(kb);
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_move_background(kb);
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}

void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Create keyboard on screen
	g_kb_screen = lv_keyboard_create(ui->screen);
	lv_obj_add_event_cb(g_kb_screen, kb_screen_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(g_kb_screen, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(g_kb_screen, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->screen, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_1, 10, 10);
	lv_obj_set_size(ui->screen_label_1, 115, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_1, "Speed");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_1. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_1, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_1, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_label_speed
	ui->screen_label_speed = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_speed, 10, 42);
	lv_obj_set_size(ui->screen_label_speed, 109, 42);
	lv_obj_set_scrollbar_mode(ui->screen_label_speed, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_speed, "2.98 m/s");
	lv_label_set_long_mode(ui->screen_label_speed, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_speed. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_speed, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_speed, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_speed, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_speed, lv_color_make(0xa8, 0xb2, 0xf1), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_speed, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_speed, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_speed, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_speed, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_speed. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_speed, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_speed, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_speed, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_speed, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_speed, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_speed, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_speed, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_speed, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_speed, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_speed, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_speed, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_label_3
	ui->screen_label_3 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_3, 10, 85);
	lv_obj_set_size(ui->screen_label_3, 115, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_3, "PID Goal");
	lv_label_set_long_mode(ui->screen_label_3, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_3, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_3. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_3, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_3, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_3, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_3, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_3, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_3, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_label_pidgoal
	ui->screen_label_pidgoal = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_pidgoal, 10, 117);
	lv_obj_set_size(ui->screen_label_pidgoal, 109, 42);
	lv_obj_set_scrollbar_mode(ui->screen_label_pidgoal, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_pidgoal, "3.00 m/s");
	lv_label_set_long_mode(ui->screen_label_pidgoal, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_pidgoal. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_pidgoal, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_pidgoal, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_pidgoal, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_pidgoal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_pidgoal, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_pidgoal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_pidgoal, lv_color_make(0x83, 0xfd, 0x84), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_pidgoal, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_pidgoal, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_pidgoal, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_pidgoal, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_pidgoal. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_pidgoal, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_pidgoal, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_pidgoal, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_pidgoal, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_pidgoal, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_pidgoal, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_pidgoal, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_pidgoal, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_pidgoal, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_pidgoal, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_pidgoal, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_pidgoal, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_label_5
	ui->screen_label_5 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_5, 10, 159);
	lv_obj_set_size(ui->screen_label_5, 115, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_5, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_5, "Step Counter");
	lv_label_set_long_mode(ui->screen_label_5, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_5, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_5. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_5, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_5, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_5, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_5, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_5, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_5, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_label_stepcounter
	ui->screen_label_stepcounter = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_stepcounter, 10, 191);
	lv_obj_set_size(ui->screen_label_stepcounter, 109, 42);
	lv_obj_set_scrollbar_mode(ui->screen_label_stepcounter, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_stepcounter, "ROUND");
	lv_label_set_long_mode(ui->screen_label_stepcounter, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_stepcounter. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_stepcounter, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_stepcounter, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_stepcounter, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_stepcounter, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_stepcounter, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_stepcounter, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_stepcounter, lv_color_make(0xff, 0xcb, 0x80), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_stepcounter, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_stepcounter, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_stepcounter, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_stepcounter, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_stepcounter. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_stepcounter, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_stepcounter, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_stepcounter, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_stepcounter, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_stepcounter, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_stepcounter, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_stepcounter, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_stepcounter, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_stepcounter, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_stepcounter, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_stepcounter, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_stepcounter, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_label_7
	ui->screen_label_7 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_7, 137, 45);
	lv_obj_set_size(ui->screen_label_7, 123, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_7, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_7, "PID Minor Adjust");
	lv_label_set_long_mode(ui->screen_label_7, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_7, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_7. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_7, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_7, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_7, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_7, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_7, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_7, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_7, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_sw_pid
	ui->screen_sw_pid = lv_switch_create(ui->screen);
	lv_obj_set_pos(ui->screen_sw_pid, 267, 51);
	lv_obj_set_size(ui->screen_sw_pid, 40, 20);
	lv_obj_set_scrollbar_mode(ui->screen_sw_pid, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_sw_pid. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_sw_pid, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_sw_pid, lv_color_make(0x48, 0x48, 0x48), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_pid, lv_color_make(0xe6, 0xe2, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_pid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_sw_pid. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_sw_pid, 10, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_sw_pid, lv_color_make(0x33, 0x2a, 0x2a), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_pid, lv_color_make(0xe6, 0xe2, 0xe6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_pid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_sw_pid. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_sw_pid, 10, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_sw_pid, lv_color_make(0x3d, 0x07, 0x07), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_pid, lv_color_make(0xe6, 0xe2, 0xe6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_pid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_sw_pid, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_sw_pid, 255, LV_PART_MAIN|LV_STATE_DISABLED);

	//Set style for screen_sw_pid. Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED
	lv_obj_set_style_bg_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_pid, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_sw_pid, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_sw_pid, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_sw_pid, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Set style for screen_sw_pid. Part: LV_PART_KNOB, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_sw_pid, 100, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_sw_pid, lv_color_make(0xff, 0xff, 0xff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_pid, lv_color_make(0xff, 0xff, 0xff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_pid, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sw_pid, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_sw_pid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_sw_pid, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_sw_pid, 255, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_btn_go
	ui->screen_btn_go = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_btn_go, 138, 183);
	lv_obj_set_size(ui->screen_btn_go, 169, 50);
	lv_obj_set_scrollbar_mode(ui->screen_btn_go, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_btn_go. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_btn_go, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x0d, 0x9d, 0x0e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_go, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_go, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_go, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_go, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_btn_go. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_btn_go, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x2e, 0x53, 0x2a), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_go, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->screen_btn_go, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->screen_btn_go, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_btn_go. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->screen_btn_go, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x70, 0xd7, 0x66), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_go, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_btn_go, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_btn_go, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for screen_btn_go. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->screen_btn_go, 5, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_go, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_btn_go, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_btn_go, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for screen_btn_go. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_btn_go, 5, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_go, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_btn_go, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_btn_go, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_btn_go, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_btn_go, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_btn_go, &lv_font_Alatsi_Regular_25, LV_PART_MAIN|LV_STATE_DISABLED);
	ui->screen_btn_go_label = lv_label_create(ui->screen_btn_go);
	lv_label_set_text(ui->screen_btn_go_label, "GO");
	lv_obj_set_style_pad_all(ui->screen_btn_go, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_btn_go_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_label_8
	ui->screen_label_8 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_8, 137, 116);
	lv_obj_set_size(ui->screen_label_8, 123, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_8, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_8, "Kp=-0.000");
	lv_label_set_long_mode(ui->screen_label_8, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_8, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_8, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_8, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_8, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_8. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_8, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_8, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_8, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_8, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_8, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_8, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_8, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_8, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_btn_add
	ui->screen_btn_add = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_btn_add, 137, 152);
	lv_obj_set_size(ui->screen_btn_add, 75, 25);
	lv_obj_set_scrollbar_mode(ui->screen_btn_add, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_btn_add. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_btn_add, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_add, lv_color_make(0x34, 0x34, 0x34), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_add, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_add, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_add, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_add, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_btn_add. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_btn_add, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_btn_add, lv_color_make(0x35, 0x41, 0x4a), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_add, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->screen_btn_add, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->screen_btn_add, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_btn_add. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->screen_btn_add, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->screen_btn_add, lv_color_make(0x4f, 0x4f, 0x4f), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_add, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_btn_add, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_btn_add, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for screen_btn_add. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->screen_btn_add, 5, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_add, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_btn_add, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_btn_add, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for screen_btn_add. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_btn_add, 5, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_add, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_btn_add, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_btn_add, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_btn_add, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_btn_add, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_btn_add, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	ui->screen_btn_add_label = lv_label_create(ui->screen_btn_add);
	lv_label_set_text(ui->screen_btn_add_label, "ADD");
	lv_obj_set_style_pad_all(ui->screen_btn_add, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_btn_add_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_adjstep_list
	ui->screen_adjstep_list = lv_dropdown_create(ui->screen);
	lv_obj_set_pos(ui->screen_adjstep_list, 224, 81.5);
	lv_obj_set_size(ui->screen_adjstep_list, 83, 30);
	lv_obj_set_scrollbar_mode(ui->screen_adjstep_list, LV_SCROLLBAR_MODE_OFF);
	lv_dropdown_set_options(ui->screen_adjstep_list, "0.001\n0.01\n0.1\n1.0");

	//Set style for screen_adjstep_list. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_adjstep_list, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_adjstep_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_adjstep_list, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_adjstep_list, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_adjstep_list, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_adjstep_list, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_adjstep_list, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_adjstep_list, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_adjstep_list. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->screen_adjstep_list, 3, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_adjstep_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_color(ui->screen_adjstep_list, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_spread(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_adjstep_list, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_adjstep_list, 1, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_adjstep_list, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_adjstep_list, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_pad_left(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_pad_right(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_pad_top(ui->screen_adjstep_list, 8, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for screen_adjstep_list. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_adjstep_list, 3, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_adjstep_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_adjstep_list, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_adjstep_list, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_adjstep_list, 1, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->screen_adjstep_list, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->screen_adjstep_list, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_left(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_right(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_pad_top(ui->screen_adjstep_list, 8, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_adjstep_list. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_adjstep_list, 3, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_adjstep_list, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_adjstep_list, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_adjstep_list, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_adjstep_list, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_adjstep_list, lv_color_make(0xe1, 0xe6, 0xee), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_adjstep_list, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_adjstep_list, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_adjstep_list, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_adjstep_list, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_adjstep_list, 6, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_adjstep_list, 8, LV_PART_MAIN|LV_STATE_DISABLED);

	//Set style state: LV_STATE_CHECKED for style_screen_adjstep_list_extra_list_selected_checked
	static lv_style_t style_screen_adjstep_list_extra_list_selected_checked;
	ui_init_style(&style_screen_adjstep_list_extra_list_selected_checked);
	lv_style_set_radius(&style_screen_adjstep_list_extra_list_selected_checked, 3);
	lv_style_set_bg_color(&style_screen_adjstep_list_extra_list_selected_checked, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_adjstep_list_extra_list_selected_checked, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_screen_adjstep_list_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_adjstep_list_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_adjstep_list_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_adjstep_list_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_adjstep_list_extra_list_selected_checked, 255);
	lv_style_set_text_color(&style_screen_adjstep_list_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_screen_adjstep_list_extra_list_selected_checked, &lv_font_Alatsi_Regular_14);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_adjstep_list), &style_screen_adjstep_list_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Set style state: LV_STATE_DEFAULT for style_screen_adjstep_list_extra_list_main_default
	static lv_style_t style_screen_adjstep_list_extra_list_main_default;
	ui_init_style(&style_screen_adjstep_list_extra_list_main_default);
	lv_style_set_radius(&style_screen_adjstep_list_extra_list_main_default, 3);
	lv_style_set_bg_color(&style_screen_adjstep_list_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_adjstep_list_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_adjstep_list_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_adjstep_list_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_adjstep_list_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_screen_adjstep_list_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_adjstep_list_extra_list_main_default, 255);
	lv_style_set_text_color(&style_screen_adjstep_list_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_screen_adjstep_list_extra_list_main_default, &lv_font_Alatsi_Regular_14);
	lv_style_set_max_height(&style_screen_adjstep_list_extra_list_main_default, 90);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_adjstep_list), &style_screen_adjstep_list_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style state: LV_STATE_DEFAULT for style_screen_adjstep_list_extra_list_scrollbar_default
	static lv_style_t style_screen_adjstep_list_extra_list_scrollbar_default;
	ui_init_style(&style_screen_adjstep_list_extra_list_scrollbar_default);
	lv_style_set_radius(&style_screen_adjstep_list_extra_list_scrollbar_default, 3);
	lv_style_set_bg_color(&style_screen_adjstep_list_extra_list_scrollbar_default, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_opa(&style_screen_adjstep_list_extra_list_scrollbar_default, 255);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_adjstep_list), &style_screen_adjstep_list_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_label_9
	ui->screen_label_9 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_9, 137, 80.5);
	lv_obj_set_size(ui->screen_label_9, 75, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_9, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_9, "Adj. Step:");
	lv_label_set_long_mode(ui->screen_label_9, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_9, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_9, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_9, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_9, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_9. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_9, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_9, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_9, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_9, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_9, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_9, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_9, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_9, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_9, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes screen_btn_sub
	ui->screen_btn_sub = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_btn_sub, 232, 152);
	lv_obj_set_size(ui->screen_btn_sub, 75, 25);
	lv_obj_set_scrollbar_mode(ui->screen_btn_sub, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_btn_sub. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_btn_sub, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_sub, lv_color_make(0x34, 0x34, 0x34), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_sub, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_sub, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_sub, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_sub, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_btn_sub. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_btn_sub, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_btn_sub, lv_color_make(0x35, 0x41, 0x4a), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_sub, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->screen_btn_sub, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->screen_btn_sub, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_btn_sub. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->screen_btn_sub, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->screen_btn_sub, lv_color_make(0x4f, 0x4f, 0x4f), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_sub, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_btn_sub, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_btn_sub, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for screen_btn_sub. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->screen_btn_sub, 5, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_sub, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_btn_sub, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_btn_sub, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for screen_btn_sub. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_btn_sub, 5, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_sub, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_btn_sub, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_btn_sub, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_btn_sub, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_btn_sub, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_btn_sub, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	ui->screen_btn_sub_label = lv_label_create(ui->screen_btn_sub);
	lv_label_set_text(ui->screen_btn_sub_label, "SUB");
	lv_obj_set_style_pad_all(ui->screen_btn_sub, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_btn_sub_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_btn_next
	ui->screen_btn_next = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_btn_next, 237, 119.5);
	lv_obj_set_size(ui->screen_btn_next, 70, 25);
	lv_obj_set_scrollbar_mode(ui->screen_btn_next, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_btn_next. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_btn_next, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_next, lv_color_make(0x34, 0x34, 0x34), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_next, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_next, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_next, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_btn_next. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_btn_next, 5, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_btn_next, lv_color_make(0x35, 0x41, 0x4a), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_next, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->screen_btn_next, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_font(ui->screen_btn_next, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_btn_next. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
	lv_obj_set_style_radius(ui->screen_btn_next, 5, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->screen_btn_next, lv_color_make(0x4f, 0x4f, 0x4f), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_next, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_border_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_btn_next, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_btn_next, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_PRESSED);

	//Set style for screen_btn_next. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
	lv_obj_set_style_radius(ui->screen_btn_next, 5, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_next, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_btn_next, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_btn_next, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_CHECKED);

	//Set style for screen_btn_next. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_btn_next, 5, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_btn_next, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_btn_next, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_btn_next, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_btn_next, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	ui->screen_btn_next_label = lv_label_create(ui->screen_btn_next);
	lv_label_set_text(ui->screen_btn_next_label, "NEXT");
	lv_obj_set_style_pad_all(ui->screen_btn_next, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_btn_next_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_sw_disarm
	ui->screen_sw_disarm = lv_switch_create(ui->screen);
	lv_obj_set_pos(ui->screen_sw_disarm, 267, 16);
	lv_obj_set_size(ui->screen_sw_disarm, 40, 20);
	lv_obj_set_scrollbar_mode(ui->screen_sw_disarm, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_sw_disarm. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_sw_disarm, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_sw_disarm, lv_color_make(0x48, 0x48, 0x48), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_disarm, lv_color_make(0xe6, 0xe2, 0xe6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_disarm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_sw_disarm. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
	lv_obj_set_style_radius(ui->screen_sw_disarm, 10, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_sw_disarm, lv_color_make(0x33, 0x2a, 0x2a), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_disarm, lv_color_make(0xe6, 0xe2, 0xe6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_disarm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_width(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_spread(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_width(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Set style for screen_sw_disarm. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_sw_disarm, 10, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_sw_disarm, lv_color_make(0x3d, 0x07, 0x07), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_disarm, lv_color_make(0xe6, 0xe2, 0xe6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_disarm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_width(ui->screen_sw_disarm, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_border_opa(ui->screen_sw_disarm, 255, LV_PART_MAIN|LV_STATE_DISABLED);

	//Set style for screen_sw_disarm. Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED
	lv_obj_set_style_bg_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_disarm, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui->screen_sw_disarm, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_sw_disarm, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_opa(ui->screen_sw_disarm, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Set style for screen_sw_disarm. Part: LV_PART_KNOB, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_sw_disarm, 100, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_sw_disarm, lv_color_make(0xff, 0xff, 0xff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_sw_disarm, lv_color_make(0xff, 0xff, 0xff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_sw_disarm, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_sw_disarm, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_sw_disarm, lv_color_make(0x21, 0x95, 0xf6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_sw_disarm, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_sw_disarm, 255, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_label_10
	ui->screen_label_10 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_10, 137, 10);
	lv_obj_set_size(ui->screen_label_10, 123, 32);
	lv_obj_set_scrollbar_mode(ui->screen_label_10, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->screen_label_10, "DISARM");
	lv_label_set_long_mode(ui->screen_label_10, LV_LABEL_LONG_WRAP);

	//Set style for screen_label_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_radius(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_10, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_label_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_label_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_10, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_10, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_10, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Set style for screen_label_10. Part: LV_PART_MAIN, State: LV_STATE_DISABLED
	lv_obj_set_style_radius(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_color(ui->screen_label_10, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_color(ui->screen_label_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_grad_dir(ui->screen_label_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_bg_opa(ui->screen_label_10, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_width(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_color(ui->screen_label_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_opa(ui->screen_label_10, 255, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_spread(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_x(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_shadow_ofs_y(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_color(ui->screen_label_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_font(ui->screen_label_10, &lv_font_Alatsi_Regular_14, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_letter_space(ui->screen_label_10, 1, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_line_space(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_text_align(ui->screen_label_10, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_left(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_right(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_top(ui->screen_label_10, 8, LV_PART_MAIN|LV_STATE_DISABLED);
	lv_obj_set_style_pad_bottom(ui->screen_label_10, 0, LV_PART_MAIN|LV_STATE_DISABLED);

	//Init events for screen
	events_init_screen(ui);
}