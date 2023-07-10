/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "ILI9341_Porting.h"
#include "gui_guider.h"

static uint8_t is_running=0;
static lv_ui *ui;
void events_init(lv_ui *xui)
{
    ui=xui;
}

static void screen_sw_pid_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{

	}
		break;
	default:
		break;
	}
}

static void screen_btn_go_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t* btn=lv_event_get_target(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
        if(!is_running){
            if(lv_obj_has_state(ui->screen_sw_disarm, LV_STATE_CHECKED)){
                ui_cmd_go();
                lv_obj_set_style_bg_color(btn, lv_color_make(0x9e, 0x2a, 0x2a), LV_PART_MAIN|LV_STATE_DEFAULT);
                lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x8e, 0x2a, 0x2a), LV_PART_MAIN|LV_STATE_FOCUSED);
                lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x7e, 0x2a, 0x2a), LV_PART_MAIN|LV_STATE_PRESSED);
                lv_label_set_text(ui->screen_btn_go_label, "STOP");
                is_running=1;
            }
            else{
                lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Error", "You must DISARM before you go.", NULL, true);
                lv_obj_center(mbox1);
            }
        }else{
            ui_cmd_stop();
            lv_obj_set_style_bg_color(btn, lv_color_make(0x0d, 0x9d, 0x0e), LV_PART_MAIN|LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x2e, 0x53, 0x2a), LV_PART_MAIN|LV_STATE_FOCUSED);
            lv_obj_set_style_bg_color(ui->screen_btn_go, lv_color_make(0x70, 0xd7, 0x66), LV_PART_MAIN|LV_STATE_PRESSED);
            lv_label_set_text(ui->screen_btn_go_label, "GO");
            is_running=0;
            lv_obj_clear_state(ui->screen_sw_disarm, LV_STATE_CHECKED);
        }

	}
		break;
	default:
		break;
	}
}

static void screen_btn_add_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
	}
		break;
	default:
		break;
	}
}

static void screen_adjstep_list_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
	}
		break;
	default:
		break;
	}
}

static void screen_btn_sub_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
	}
		break;
	default:
		break;
	}
}

static void screen_btn_next_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
	}
		break;
	default:
		break;
	}
}

static void screen_sw_disarm_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_sw_pid, screen_sw_pid_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_btn_go, screen_btn_go_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_btn_add, screen_btn_add_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_adjstep_list, screen_adjstep_list_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_btn_sub, screen_btn_sub_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_btn_next, screen_btn_next_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_sw_disarm, screen_sw_disarm_event_handler, LV_EVENT_ALL, ui);
}
