/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#define LV_USE_MSGBOX 1
#include <stdio.h>
float step;
float ui_Kp=0;
unsigned char ui_go_status=0;
unsigned char ui_pid_adjust_enabled=0;
#include <string.h>
unsigned char ui_step_buffer[16];
float step=0.001;
float step;

void events_init(lv_ui *ui)
{
}

static void screen_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if(!ui_pid_adjust_enabled){
		    static const char * btns[] ={"Close", ""};//创建按钮字符
		    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning",
		  "You must enable the adjust switch before you do adjust.", btns, true);
		    lv_obj_center(mbox1);
		}else{
		  ui_Kp+=step;
		  unsigned char text[16];
		  memset(text,0,sizeof(text));
		  sprintf(text,"Kp=%.3f",ui_Kp);
		  //lv_label_set_text()
		}
	}
		break;
	default:
		break;
	}
}

static void screen_go_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if(!ui_go_status){
		  ui_go_status=1;
		  lv_obj_set_style_bg_color(guider_ui.screen_go_btn,lv_color_make(0xdb, 0x11, 0x11), LV_PART_MAIN|LV_STATE_DEFAULT);
		  lv_label_set_text(guider_ui.screen_go_btn_label, "STOP");
		}else{
		  ui_go_status=0;
		  lv_obj_set_style_bg_color(guider_ui.screen_go_btn,lv_color_make(0x22, 0xbd, 0x2b), LV_PART_MAIN|LV_STATE_DEFAULT);
		  lv_label_set_text(guider_ui.screen_go_btn_label, "GO");
		}
	}
		break;
	default:
		break;
	}
}

static void screen_pid_adjust_sw_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if(lv_obj_has_state(guider_ui.screen_pid_adjust_sw, LV_STATE_CHECKED)){
		  ui_pid_adjust_enabled=1;
		}else{
		  ui_pid_adjust_enabled=0;
		}
	}
		break;
	default:
		break;
	}
}

static void screen_step_list_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if(!ui_pid_adjust_enabled){
		    static const char * btns[] ={"Close", ""};//创建按钮字符
		    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning",
		  "You must enable the adjust switch before you do adjust.", btns, true);
		    lv_obj_center(mbox1);
		}else{
		  lv_obj_t * obj = lv_event_get_target(e);
		  memset(ui_step_buffer,0,sizeof(ui_step_buffer));
		  lv_dropdown_get_selected_str(obj, ui_step_buffer, sizeof(ui_step_buffer));
		  if(!strcmp(ui_step_buffer,"0.001")){
		    step=0.001;
		  }else if(!strcmp(ui_step_buffer,"0.01")){
		    step=0.01;
		  }
		  else if(!strcmp(ui_step_buffer,"0.1")){
		    step=0.1;
		  }
		  else if(!strcmp(ui_step_buffer,"1")){
		    step=1;
		  }
		}
	}
		break;
	default:
		break;
	}
}

static void screen_kp_plus_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if(!ui_pid_adjust_enabled){
		    static const char * btns[] ={"Close", ""};//创建按钮字符
		    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning",
		  "You must enable the adjust switch before you do adjust.", btns, true);
		    lv_obj_center(mbox1);
		}else{
		  ui_Kp+=step;
		  unsigned char buf[16];
		  memset(buf,0,sizeof(buf));
		  sprintf(buf,"Kp=%.3f",ui_Kp);
		  lv_label_set_text(guider_ui.screen_kp_label,buf);
		}
	}
		break;
	default:
		break;
	}
}

static void screen_kp_minus_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if(!ui_pid_adjust_enabled){
		    static const char * btns[] ={"Close", ""};//创建按钮字符
		    lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning",
		  "You must enable the adjust switch before you do adjust.", btns, true);
		    lv_obj_center(mbox1);
		}else{
		  ui_Kp-=step;
		}
	}
		break;
	default:
		break;
	}
}

static void screen_ki_minus_btn_event_handler(lv_event_t *e)
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

static void screen_ki_plus_btn_event_handler(lv_event_t *e)
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

static void screen_kd_minus_btn_event_handler(lv_event_t *e)
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

static void screen_kd_plus_btn_event_handler(lv_event_t *e)
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

void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_go_btn, screen_go_btn_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_pid_adjust_sw, screen_pid_adjust_sw_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_step_list, screen_step_list_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_kp_plus_btn, screen_kp_plus_btn_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_kp_minus_btn, screen_kp_minus_btn_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_ki_minus_btn, screen_ki_minus_btn_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_ki_plus_btn, screen_ki_plus_btn_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_kd_minus_btn, screen_kd_minus_btn_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_kd_plus_btn, screen_kd_plus_btn_event_handler, LV_EVENT_ALL, ui);
}
