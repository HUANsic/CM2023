/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

void events_init(lv_ui *ui)
{
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
