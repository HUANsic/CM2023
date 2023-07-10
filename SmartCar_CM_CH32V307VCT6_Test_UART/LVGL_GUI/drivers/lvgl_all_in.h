/*
 * lvgl_all_in.h
 *
 *  Created on: Jul 10, 2023
 *      Author: THUIRT
 */

#ifndef LVGL_GUI_DRIVERS_LVGL_ALL_IN_H_
#define LVGL_GUI_DRIVERS_LVGL_ALL_IN_H_
/* LCD & LVGL Driver Initialization*/
#include "debug.h"
#include "ILI9341.h"
#include "ILI9341_Touchscreen.h"
#include "ILI9341_WCH_Driver.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
/* END */

/* 使用LVGL_GUI库只需要包含本头文件在你的main.c中，并配置includePath。同时include进ILI9341_Porting.h，实现发车等指令。
 * ==============================================
Make sure you insert the followings to your include path
LVGL_GUI/drivers
LVGL_GUI/lvgl
LVGL_GUI/lvgl_app
LVGL_GUI/lvgl_app/guider_customer_fonts
LVGL_GUI/lvgl_app/guider_fonts
LVGL_GUI/lvgl_port
 * =========AND implement the followings=========
 * void ui_cmd_go(void);
*/

//All you need to do.
void lvgl_wch_all_start(void);

#endif /* LVGL_GUI_DRIVERS_LVGL_ALL_IN_H_ */
