# Copyright 2023 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=320,h=240)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(320*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 320
disp_drv.ver_res = 240
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)
        
def ta_zh_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.keyboard_set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.keyboard_set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)



# create screen
screen = lv.obj()
screen.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_default
style_screen_main_main_default = lv.style_t()
style_screen_main_main_default.init()
style_screen_main_main_default.set_bg_color(lv.color_make(0x00,0x00,0x00))
style_screen_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_main_default.set_bg_opa(255)

# add style for screen
screen.add_style(style_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_1
screen_label_1 = lv.label(screen)
screen_label_1.set_pos(int(8.5),int(4))
screen_label_1.set_size(92,32)
screen_label_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_1.set_text("System Clock")
screen_label_1.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_1_main_main_default
style_screen_label_1_main_main_default = lv.style_t()
style_screen_label_1_main_main_default.init()
style_screen_label_1_main_main_default.set_radius(0)
style_screen_label_1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_1_main_main_default.set_bg_opa(0)
style_screen_label_1_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_1_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_label_1_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_1_main_main_default.set_text_letter_space(1)
style_screen_label_1_main_main_default.set_text_line_space(0)
style_screen_label_1_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_label_1_main_main_default.set_pad_left(0)
style_screen_label_1_main_main_default.set_pad_right(0)
style_screen_label_1_main_main_default.set_pad_top(8)
style_screen_label_1_main_main_default.set_pad_bottom(0)

# add style for screen_label_1
screen_label_1.add_style(style_screen_label_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_sysclock_label
screen_sysclock_label = lv.label(screen)
screen_sysclock_label.set_pos(int(8),int(36))
screen_sysclock_label.set_size(112,38)
screen_sysclock_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_sysclock_label.set_text("144 MHz")
screen_sysclock_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_sysclock_label_main_main_default
style_screen_sysclock_label_main_main_default = lv.style_t()
style_screen_sysclock_label_main_main_default.init()
style_screen_sysclock_label_main_main_default.set_radius(0)
style_screen_sysclock_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_sysclock_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_sysclock_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_sysclock_label_main_main_default.set_bg_opa(0)
style_screen_sysclock_label_main_main_default.set_text_color(lv.color_make(0x9e,0x2e,0xe3))
try:
    style_screen_sysclock_label_main_main_default.set_text_font(lv.font_Alatsi_Regular_25)
except AttributeError:
    try:
        style_screen_sysclock_label_main_main_default.set_text_font(lv.font_montserrat_25)
    except AttributeError:
        style_screen_sysclock_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_sysclock_label_main_main_default.set_text_letter_space(2)
style_screen_sysclock_label_main_main_default.set_text_line_space(0)
style_screen_sysclock_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_sysclock_label_main_main_default.set_pad_left(0)
style_screen_sysclock_label_main_main_default.set_pad_right(0)
style_screen_sysclock_label_main_main_default.set_pad_top(8)
style_screen_sysclock_label_main_main_default.set_pad_bottom(0)

# add style for screen_sysclock_label
screen_sysclock_label.add_style(style_screen_sysclock_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_4
screen_label_4 = lv.label(screen)
screen_label_4.set_pos(int(8.5),int(74))
screen_label_4.set_size(92,32)
screen_label_4.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_4.set_text("PID Goal")
screen_label_4.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_4_main_main_default
style_screen_label_4_main_main_default = lv.style_t()
style_screen_label_4_main_main_default.init()
style_screen_label_4_main_main_default.set_radius(0)
style_screen_label_4_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_4_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_4_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_4_main_main_default.set_bg_opa(0)
style_screen_label_4_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_4_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_label_4_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_label_4_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_4_main_main_default.set_text_letter_space(1)
style_screen_label_4_main_main_default.set_text_line_space(0)
style_screen_label_4_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_label_4_main_main_default.set_pad_left(0)
style_screen_label_4_main_main_default.set_pad_right(0)
style_screen_label_4_main_main_default.set_pad_top(8)
style_screen_label_4_main_main_default.set_pad_bottom(0)

# add style for screen_label_4
screen_label_4.add_style(style_screen_label_4_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_pidgoal_label
screen_pidgoal_label = lv.label(screen)
screen_pidgoal_label.set_pos(int(8),int(104))
screen_pidgoal_label.set_size(112,38)
screen_pidgoal_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_pidgoal_label.set_text("3.0 m/s")
screen_pidgoal_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_pidgoal_label_main_main_default
style_screen_pidgoal_label_main_main_default = lv.style_t()
style_screen_pidgoal_label_main_main_default.init()
style_screen_pidgoal_label_main_main_default.set_radius(0)
style_screen_pidgoal_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pidgoal_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pidgoal_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_pidgoal_label_main_main_default.set_bg_opa(0)
style_screen_pidgoal_label_main_main_default.set_text_color(lv.color_make(0x37,0xb7,0xeb))
try:
    style_screen_pidgoal_label_main_main_default.set_text_font(lv.font_Alatsi_Regular_25)
except AttributeError:
    try:
        style_screen_pidgoal_label_main_main_default.set_text_font(lv.font_montserrat_25)
    except AttributeError:
        style_screen_pidgoal_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_pidgoal_label_main_main_default.set_text_letter_space(2)
style_screen_pidgoal_label_main_main_default.set_text_line_space(0)
style_screen_pidgoal_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_pidgoal_label_main_main_default.set_pad_left(0)
style_screen_pidgoal_label_main_main_default.set_pad_right(0)
style_screen_pidgoal_label_main_main_default.set_pad_top(8)
style_screen_pidgoal_label_main_main_default.set_pad_bottom(0)

# add style for screen_pidgoal_label
screen_pidgoal_label.add_style(style_screen_pidgoal_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_5
screen_label_5 = lv.label(screen)
screen_label_5.set_pos(int(8),int(141))
screen_label_5.set_size(101,32)
screen_label_5.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_5.set_text("State Machine")
screen_label_5.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_5_main_main_default
style_screen_label_5_main_main_default = lv.style_t()
style_screen_label_5_main_main_default.init()
style_screen_label_5_main_main_default.set_radius(0)
style_screen_label_5_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_5_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_5_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_5_main_main_default.set_bg_opa(0)
style_screen_label_5_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_5_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_label_5_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_label_5_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_5_main_main_default.set_text_letter_space(1)
style_screen_label_5_main_main_default.set_text_line_space(0)
style_screen_label_5_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_label_5_main_main_default.set_pad_left(0)
style_screen_label_5_main_main_default.set_pad_right(0)
style_screen_label_5_main_main_default.set_pad_top(8)
style_screen_label_5_main_main_default.set_pad_bottom(0)

# add style for screen_label_5
screen_label_5.add_style(style_screen_label_5_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_statemachine_label
screen_statemachine_label = lv.label(screen)
screen_statemachine_label.set_pos(int(8),int(174))
screen_statemachine_label.set_size(112,57)
screen_statemachine_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_statemachine_label.set_text("Roundabout")
screen_statemachine_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_statemachine_label_main_main_default
style_screen_statemachine_label_main_main_default = lv.style_t()
style_screen_statemachine_label_main_main_default.init()
style_screen_statemachine_label_main_main_default.set_radius(0)
style_screen_statemachine_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_statemachine_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_statemachine_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_statemachine_label_main_main_default.set_bg_opa(0)
style_screen_statemachine_label_main_main_default.set_text_color(lv.color_make(0xbd,0x22,0x64))
try:
    style_screen_statemachine_label_main_main_default.set_text_font(lv.font_Alatsi_Regular_25)
except AttributeError:
    try:
        style_screen_statemachine_label_main_main_default.set_text_font(lv.font_montserrat_25)
    except AttributeError:
        style_screen_statemachine_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_statemachine_label_main_main_default.set_text_letter_space(2)
style_screen_statemachine_label_main_main_default.set_text_line_space(0)
style_screen_statemachine_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_statemachine_label_main_main_default.set_pad_left(0)
style_screen_statemachine_label_main_main_default.set_pad_right(0)
style_screen_statemachine_label_main_main_default.set_pad_top(8)
style_screen_statemachine_label_main_main_default.set_pad_bottom(0)

# add style for screen_statemachine_label
screen_statemachine_label.add_style(style_screen_statemachine_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_go_btn
screen_go_btn = lv.btn(screen)
screen_go_btn.set_pos(int(142),int(188))
screen_go_btn.set_size(170,43)
screen_go_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_go_btn_label = lv.label(screen_go_btn)
screen_go_btn_label.set_text("GO")
screen_go_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_go_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_go_btn_main_main_default
style_screen_go_btn_main_main_default = lv.style_t()
style_screen_go_btn_main_main_default.init()
style_screen_go_btn_main_main_default.set_radius(5)
style_screen_go_btn_main_main_default.set_bg_color(lv.color_make(0x22,0xbd,0x2b))
style_screen_go_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_go_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_go_btn_main_main_default.set_bg_opa(255)
style_screen_go_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_go_btn_main_main_default.set_border_width(0)
style_screen_go_btn_main_main_default.set_border_opa(255)
style_screen_go_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_go_btn_main_main_default.set_text_font(lv.font_Alatsi_Regular_25)
except AttributeError:
    try:
        style_screen_go_btn_main_main_default.set_text_font(lv.font_montserrat_25)
    except AttributeError:
        style_screen_go_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_go_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_go_btn
screen_go_btn.add_style(style_screen_go_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_pid_adjust_sw
screen_pid_adjust_sw = lv.switch(screen)
screen_pid_adjust_sw.set_pos(int(272),int(10))
screen_pid_adjust_sw.set_size(40,20)
screen_pid_adjust_sw.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_pid_adjust_sw_main_main_default
style_screen_pid_adjust_sw_main_main_default = lv.style_t()
style_screen_pid_adjust_sw_main_main_default.init()
style_screen_pid_adjust_sw_main_main_default.set_radius(10)
style_screen_pid_adjust_sw_main_main_default.set_bg_color(lv.color_make(0x29,0x24,0x24))
style_screen_pid_adjust_sw_main_main_default.set_bg_grad_color(lv.color_make(0xe6,0xe2,0xe6))
style_screen_pid_adjust_sw_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_pid_adjust_sw_main_main_default.set_bg_opa(255)
style_screen_pid_adjust_sw_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pid_adjust_sw_main_main_default.set_border_width(0)
style_screen_pid_adjust_sw_main_main_default.set_border_opa(255)

# add style for screen_pid_adjust_sw
screen_pid_adjust_sw.add_style(style_screen_pid_adjust_sw_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_pid_adjust_sw_main_indicator_checked
style_screen_pid_adjust_sw_main_indicator_checked = lv.style_t()
style_screen_pid_adjust_sw_main_indicator_checked.init()
style_screen_pid_adjust_sw_main_indicator_checked.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pid_adjust_sw_main_indicator_checked.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pid_adjust_sw_main_indicator_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_pid_adjust_sw_main_indicator_checked.set_bg_opa(255)
style_screen_pid_adjust_sw_main_indicator_checked.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pid_adjust_sw_main_indicator_checked.set_border_width(0)
style_screen_pid_adjust_sw_main_indicator_checked.set_border_opa(255)

# add style for screen_pid_adjust_sw
screen_pid_adjust_sw.add_style(style_screen_pid_adjust_sw_main_indicator_checked, lv.PART.INDICATOR|lv.STATE.CHECKED)

# create style style_screen_pid_adjust_sw_main_knob_default
style_screen_pid_adjust_sw_main_knob_default = lv.style_t()
style_screen_pid_adjust_sw_main_knob_default.init()
style_screen_pid_adjust_sw_main_knob_default.set_radius(100)
style_screen_pid_adjust_sw_main_knob_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_pid_adjust_sw_main_knob_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_pid_adjust_sw_main_knob_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_pid_adjust_sw_main_knob_default.set_bg_opa(255)
style_screen_pid_adjust_sw_main_knob_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_pid_adjust_sw_main_knob_default.set_border_width(0)
style_screen_pid_adjust_sw_main_knob_default.set_border_opa(255)

# add style for screen_pid_adjust_sw
screen_pid_adjust_sw.add_style(style_screen_pid_adjust_sw_main_knob_default, lv.PART.KNOB|lv.STATE.DEFAULT)


# create screen_step_list
screen_step_list = lv.dropdown(screen)
screen_step_list.set_pos(int(197),int(37))
screen_step_list.set_size(111,30)
screen_step_list.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_step_list.set_options("0.001\n0.01\n0.1\n1")

screen_step_list_list = screen_step_list.get_list()
# create style style_screen_step_list_extra_list_selected_checked
style_screen_step_list_extra_list_selected_checked = lv.style_t()
style_screen_step_list_extra_list_selected_checked.init()
style_screen_step_list_extra_list_selected_checked.set_radius(3)
style_screen_step_list_extra_list_selected_checked.set_bg_color(lv.color_make(0x00,0xa1,0xb5))
style_screen_step_list_extra_list_selected_checked.set_bg_grad_color(lv.color_make(0x00,0xa1,0xb5))
style_screen_step_list_extra_list_selected_checked.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_step_list_extra_list_selected_checked.set_bg_opa(255)
style_screen_step_list_extra_list_selected_checked.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_screen_step_list_extra_list_selected_checked.set_border_width(1)
style_screen_step_list_extra_list_selected_checked.set_border_opa(255)
style_screen_step_list_extra_list_selected_checked.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_step_list_extra_list_selected_checked.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        style_screen_step_list_extra_list_selected_checked.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_step_list_extra_list_selected_checked.set_text_font(lv.font_montserrat_16)

# add style for screen_step_list_list
screen_step_list_list.add_style(style_screen_step_list_extra_list_selected_checked, lv.PART.SELECTED|lv.STATE.CHECKED)

# create style style_screen_step_list_extra_list_main_default
style_screen_step_list_extra_list_main_default = lv.style_t()
style_screen_step_list_extra_list_main_default.init()
style_screen_step_list_extra_list_main_default.set_radius(3)
style_screen_step_list_extra_list_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_step_list_extra_list_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_step_list_extra_list_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_step_list_extra_list_main_default.set_bg_opa(255)
style_screen_step_list_extra_list_main_default.set_border_color(lv.color_make(0xe1,0xe6,0xee))
style_screen_step_list_extra_list_main_default.set_border_width(1)
style_screen_step_list_extra_list_main_default.set_border_opa(255)
style_screen_step_list_extra_list_main_default.set_text_color(lv.color_make(0x0D,0x30,0x55))
try:
    style_screen_step_list_extra_list_main_default.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        style_screen_step_list_extra_list_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_step_list_extra_list_main_default.set_text_font(lv.font_montserrat_16)
style_screen_step_list_extra_list_main_default.set_max_height(90)

# add style for screen_step_list_list
screen_step_list_list.add_style(style_screen_step_list_extra_list_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_step_list_extra_list_scrollbar_default
style_screen_step_list_extra_list_scrollbar_default = lv.style_t()
style_screen_step_list_extra_list_scrollbar_default.init()
style_screen_step_list_extra_list_scrollbar_default.set_radius(3)
style_screen_step_list_extra_list_scrollbar_default.set_bg_color(lv.color_make(0x00,0xff,0x00))
style_screen_step_list_extra_list_scrollbar_default.set_bg_opa(255)

# add style for screen_step_list_list
screen_step_list_list.add_style(style_screen_step_list_extra_list_scrollbar_default, lv.PART.SCROLLBAR|lv.STATE.DEFAULT)

# create style style_screen_step_list_main_main_default
style_screen_step_list_main_main_default = lv.style_t()
style_screen_step_list_main_main_default.init()
style_screen_step_list_main_main_default.set_radius(3)
style_screen_step_list_main_main_default.set_bg_color(lv.color_make(0x31,0x31,0x31))
style_screen_step_list_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_step_list_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_step_list_main_main_default.set_bg_opa(255)
style_screen_step_list_main_main_default.set_border_color(lv.color_make(0x61,0x4b,0x4b))
style_screen_step_list_main_main_default.set_border_width(1)
style_screen_step_list_main_main_default.set_border_opa(255)
style_screen_step_list_main_main_default.set_text_color(lv.color_make(0xf7,0xf8,0xf9))
try:
    style_screen_step_list_main_main_default.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        style_screen_step_list_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_step_list_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_step_list_main_main_default.set_pad_left(6)
style_screen_step_list_main_main_default.set_pad_right(6)
style_screen_step_list_main_main_default.set_pad_top(8)

# add style for screen_step_list
screen_step_list.add_style(style_screen_step_list_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_6
screen_label_6 = lv.label(screen)
screen_label_6.set_pos(int(142),int(4))
screen_label_6.set_size(123,32)
screen_label_6.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_6.set_text("PID Minor Adjust")
screen_label_6.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_6_main_main_default
style_screen_label_6_main_main_default = lv.style_t()
style_screen_label_6_main_main_default.init()
style_screen_label_6_main_main_default.set_radius(0)
style_screen_label_6_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_6_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_6_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_6_main_main_default.set_bg_opa(0)
style_screen_label_6_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_6_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_label_6_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_label_6_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_6_main_main_default.set_text_letter_space(1)
style_screen_label_6_main_main_default.set_text_line_space(0)
style_screen_label_6_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_label_6_main_main_default.set_pad_left(0)
style_screen_label_6_main_main_default.set_pad_right(0)
style_screen_label_6_main_main_default.set_pad_top(8)
style_screen_label_6_main_main_default.set_pad_bottom(0)

# add style for screen_label_6
screen_label_6.add_style(style_screen_label_6_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_label_7
screen_label_7 = lv.label(screen)
screen_label_7.set_pos(int(142),int(36))
screen_label_7.set_size(47,32)
screen_label_7.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_label_7.set_text("Step")
screen_label_7.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_label_7_main_main_default
style_screen_label_7_main_main_default = lv.style_t()
style_screen_label_7_main_main_default.init()
style_screen_label_7_main_main_default.set_radius(0)
style_screen_label_7_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_7_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_label_7_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_label_7_main_main_default.set_bg_opa(0)
style_screen_label_7_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_label_7_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_label_7_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_label_7_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_label_7_main_main_default.set_text_letter_space(1)
style_screen_label_7_main_main_default.set_text_line_space(0)
style_screen_label_7_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_label_7_main_main_default.set_pad_left(0)
style_screen_label_7_main_main_default.set_pad_right(0)
style_screen_label_7_main_main_default.set_pad_top(8)
style_screen_label_7_main_main_default.set_pad_bottom(0)

# add style for screen_label_7
screen_label_7.add_style(style_screen_label_7_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_kp_label
screen_kp_label = lv.label(screen)
screen_kp_label.set_pos(int(140),int(80))
screen_kp_label.set_size(93,32)
screen_kp_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_kp_label.set_text("Kp=0.0")
screen_kp_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_kp_label_main_main_default
style_screen_kp_label_main_main_default = lv.style_t()
style_screen_kp_label_main_main_default.init()
style_screen_kp_label_main_main_default.set_radius(0)
style_screen_kp_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kp_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kp_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_kp_label_main_main_default.set_bg_opa(0)
style_screen_kp_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_kp_label_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_kp_label_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_kp_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_kp_label_main_main_default.set_text_letter_space(1)
style_screen_kp_label_main_main_default.set_text_line_space(0)
style_screen_kp_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_kp_label_main_main_default.set_pad_left(0)
style_screen_kp_label_main_main_default.set_pad_right(0)
style_screen_kp_label_main_main_default.set_pad_top(8)
style_screen_kp_label_main_main_default.set_pad_bottom(0)

# add style for screen_kp_label
screen_kp_label.add_style(style_screen_kp_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_kp_plus_btn
screen_kp_plus_btn = lv.btn(screen)
screen_kp_plus_btn.set_pos(int(244),int(82.5))
screen_kp_plus_btn.set_size(27,27)
screen_kp_plus_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_kp_plus_btn_label = lv.label(screen_kp_plus_btn)
screen_kp_plus_btn_label.set_text("+")
screen_kp_plus_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_kp_plus_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_kp_plus_btn_main_main_default
style_screen_kp_plus_btn_main_main_default = lv.style_t()
style_screen_kp_plus_btn_main_main_default.init()
style_screen_kp_plus_btn_main_main_default.set_radius(5)
style_screen_kp_plus_btn_main_main_default.set_bg_color(lv.color_make(0x31,0x37,0x3c))
style_screen_kp_plus_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kp_plus_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_kp_plus_btn_main_main_default.set_bg_opa(255)
style_screen_kp_plus_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kp_plus_btn_main_main_default.set_border_width(0)
style_screen_kp_plus_btn_main_main_default.set_border_opa(255)
style_screen_kp_plus_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_kp_plus_btn_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_kp_plus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_kp_plus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_kp_plus_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_kp_plus_btn
screen_kp_plus_btn.add_style(style_screen_kp_plus_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_kp_minus_btn
screen_kp_minus_btn = lv.btn(screen)
screen_kp_minus_btn.set_pos(int(281),int(82.5))
screen_kp_minus_btn.set_size(27,27)
screen_kp_minus_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_kp_minus_btn_label = lv.label(screen_kp_minus_btn)
screen_kp_minus_btn_label.set_text("-")
screen_kp_minus_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_kp_minus_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_kp_minus_btn_main_main_default
style_screen_kp_minus_btn_main_main_default = lv.style_t()
style_screen_kp_minus_btn_main_main_default.init()
style_screen_kp_minus_btn_main_main_default.set_radius(5)
style_screen_kp_minus_btn_main_main_default.set_bg_color(lv.color_make(0x31,0x37,0x3c))
style_screen_kp_minus_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kp_minus_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_kp_minus_btn_main_main_default.set_bg_opa(255)
style_screen_kp_minus_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kp_minus_btn_main_main_default.set_border_width(0)
style_screen_kp_minus_btn_main_main_default.set_border_opa(255)
style_screen_kp_minus_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_kp_minus_btn_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_kp_minus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_kp_minus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_kp_minus_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_kp_minus_btn
screen_kp_minus_btn.add_style(style_screen_kp_minus_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_ki_minus_btn
screen_ki_minus_btn = lv.btn(screen)
screen_ki_minus_btn.set_pos(int(281),int(113.5))
screen_ki_minus_btn.set_size(27,27)
screen_ki_minus_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_ki_minus_btn_label = lv.label(screen_ki_minus_btn)
screen_ki_minus_btn_label.set_text("-")
screen_ki_minus_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_ki_minus_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_ki_minus_btn_main_main_default
style_screen_ki_minus_btn_main_main_default = lv.style_t()
style_screen_ki_minus_btn_main_main_default.init()
style_screen_ki_minus_btn_main_main_default.set_radius(5)
style_screen_ki_minus_btn_main_main_default.set_bg_color(lv.color_make(0x31,0x37,0x3c))
style_screen_ki_minus_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_ki_minus_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_ki_minus_btn_main_main_default.set_bg_opa(255)
style_screen_ki_minus_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_ki_minus_btn_main_main_default.set_border_width(0)
style_screen_ki_minus_btn_main_main_default.set_border_opa(255)
style_screen_ki_minus_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_ki_minus_btn_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_ki_minus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_ki_minus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_ki_minus_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_ki_minus_btn
screen_ki_minus_btn.add_style(style_screen_ki_minus_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_ki_plus_btn
screen_ki_plus_btn = lv.btn(screen)
screen_ki_plus_btn.set_pos(int(244),int(113.5))
screen_ki_plus_btn.set_size(27,27)
screen_ki_plus_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_ki_plus_btn_label = lv.label(screen_ki_plus_btn)
screen_ki_plus_btn_label.set_text("+")
screen_ki_plus_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_ki_plus_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_ki_plus_btn_main_main_default
style_screen_ki_plus_btn_main_main_default = lv.style_t()
style_screen_ki_plus_btn_main_main_default.init()
style_screen_ki_plus_btn_main_main_default.set_radius(5)
style_screen_ki_plus_btn_main_main_default.set_bg_color(lv.color_make(0x31,0x37,0x3c))
style_screen_ki_plus_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_ki_plus_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_ki_plus_btn_main_main_default.set_bg_opa(255)
style_screen_ki_plus_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_ki_plus_btn_main_main_default.set_border_width(0)
style_screen_ki_plus_btn_main_main_default.set_border_opa(255)
style_screen_ki_plus_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_ki_plus_btn_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_ki_plus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_ki_plus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_ki_plus_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_ki_plus_btn
screen_ki_plus_btn.add_style(style_screen_ki_plus_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_kd_label
screen_kd_label = lv.label(screen)
screen_kd_label.set_pos(int(140),int(142))
screen_kd_label.set_size(93,32)
screen_kd_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_kd_label.set_text("Kd=0.0")
screen_kd_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_kd_label_main_main_default
style_screen_kd_label_main_main_default = lv.style_t()
style_screen_kd_label_main_main_default.init()
style_screen_kd_label_main_main_default.set_radius(0)
style_screen_kd_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kd_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kd_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_kd_label_main_main_default.set_bg_opa(0)
style_screen_kd_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_kd_label_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_kd_label_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_kd_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_kd_label_main_main_default.set_text_letter_space(1)
style_screen_kd_label_main_main_default.set_text_line_space(0)
style_screen_kd_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_kd_label_main_main_default.set_pad_left(0)
style_screen_kd_label_main_main_default.set_pad_right(0)
style_screen_kd_label_main_main_default.set_pad_top(8)
style_screen_kd_label_main_main_default.set_pad_bottom(0)

# add style for screen_kd_label
screen_kd_label.add_style(style_screen_kd_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_kd_minus_btn
screen_kd_minus_btn = lv.btn(screen)
screen_kd_minus_btn.set_pos(int(281),int(144.5))
screen_kd_minus_btn.set_size(27,27)
screen_kd_minus_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_kd_minus_btn_label = lv.label(screen_kd_minus_btn)
screen_kd_minus_btn_label.set_text("-")
screen_kd_minus_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_kd_minus_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_kd_minus_btn_main_main_default
style_screen_kd_minus_btn_main_main_default = lv.style_t()
style_screen_kd_minus_btn_main_main_default.init()
style_screen_kd_minus_btn_main_main_default.set_radius(5)
style_screen_kd_minus_btn_main_main_default.set_bg_color(lv.color_make(0x31,0x37,0x3c))
style_screen_kd_minus_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kd_minus_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_kd_minus_btn_main_main_default.set_bg_opa(255)
style_screen_kd_minus_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kd_minus_btn_main_main_default.set_border_width(0)
style_screen_kd_minus_btn_main_main_default.set_border_opa(255)
style_screen_kd_minus_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_kd_minus_btn_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_kd_minus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_kd_minus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_kd_minus_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_kd_minus_btn
screen_kd_minus_btn.add_style(style_screen_kd_minus_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_kd_plus_btn
screen_kd_plus_btn = lv.btn(screen)
screen_kd_plus_btn.set_pos(int(244),int(144.5))
screen_kd_plus_btn.set_size(27,27)
screen_kd_plus_btn.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_kd_plus_btn_label = lv.label(screen_kd_plus_btn)
screen_kd_plus_btn_label.set_text("+")
screen_kd_plus_btn.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_kd_plus_btn_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_kd_plus_btn_main_main_default
style_screen_kd_plus_btn_main_main_default = lv.style_t()
style_screen_kd_plus_btn_main_main_default.init()
style_screen_kd_plus_btn_main_main_default.set_radius(5)
style_screen_kd_plus_btn_main_main_default.set_bg_color(lv.color_make(0x31,0x37,0x3c))
style_screen_kd_plus_btn_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kd_plus_btn_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_kd_plus_btn_main_main_default.set_bg_opa(255)
style_screen_kd_plus_btn_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_kd_plus_btn_main_main_default.set_border_width(0)
style_screen_kd_plus_btn_main_main_default.set_border_opa(255)
style_screen_kd_plus_btn_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_kd_plus_btn_main_main_default.set_text_font(lv.font_montserratMedium_16)
except AttributeError:
    try:
        style_screen_kd_plus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
    except AttributeError:
        style_screen_kd_plus_btn_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_kd_plus_btn_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_kd_plus_btn
screen_kd_plus_btn.add_style(style_screen_kd_plus_btn_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_ki_label
screen_ki_label = lv.label(screen)
screen_ki_label.set_pos(int(140),int(111))
screen_ki_label.set_size(93,32)
screen_ki_label.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_ki_label.set_text("Ki =0.0")
screen_ki_label.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_ki_label_main_main_default
style_screen_ki_label_main_main_default = lv.style_t()
style_screen_ki_label_main_main_default.init()
style_screen_ki_label_main_main_default.set_radius(0)
style_screen_ki_label_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_ki_label_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_ki_label_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_ki_label_main_main_default.set_bg_opa(0)
style_screen_ki_label_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_ki_label_main_main_default.set_text_font(lv.font_Alatsi_Regular_14)
except AttributeError:
    try:
        style_screen_ki_label_main_main_default.set_text_font(lv.font_montserrat_14)
    except AttributeError:
        style_screen_ki_label_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_ki_label_main_main_default.set_text_letter_space(1)
style_screen_ki_label_main_main_default.set_text_line_space(0)
style_screen_ki_label_main_main_default.set_text_align(lv.TEXT_ALIGN.LEFT)
style_screen_ki_label_main_main_default.set_pad_left(0)
style_screen_ki_label_main_main_default.set_pad_right(0)
style_screen_ki_label_main_main_default.set_pad_top(8)
style_screen_ki_label_main_main_default.set_pad_bottom(0)

# add style for screen_ki_label
screen_ki_label.add_style(style_screen_ki_label_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


# create screen_msgbox_1
screen_msgbox_1 = lv.msgbox(screen, "Belonging to", "Tsinghua M.O.U.S.E. Team", [""], True)

screen_msgbox_1_title = screen_msgbox_1.get_title()
# create style style_screen_msgbox_1_extra_title_main_default
style_screen_msgbox_1_extra_title_main_default = lv.style_t()
style_screen_msgbox_1_extra_title_main_default.init()
style_screen_msgbox_1_extra_title_main_default.set_text_color(lv.color_make(0x4e,0x4e,0x4e))
try:
    style_screen_msgbox_1_extra_title_main_default.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        style_screen_msgbox_1_extra_title_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_msgbox_1_extra_title_main_default.set_text_font(lv.font_montserrat_16)
style_screen_msgbox_1_extra_title_main_default.set_text_letter_space(0)
style_screen_msgbox_1_extra_title_main_default.set_text_line_space(30)

# add style for screen_msgbox_1_title
screen_msgbox_1_title.add_style(style_screen_msgbox_1_extra_title_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_msgbox_1_content = screen_msgbox_1.get_text()
# create style style_screen_msgbox_1_extra_content_main_default
style_screen_msgbox_1_extra_content_main_default = lv.style_t()
style_screen_msgbox_1_extra_content_main_default.init()
style_screen_msgbox_1_extra_content_main_default.set_text_color(lv.color_make(0x4e,0x4e,0x4e))
try:
    style_screen_msgbox_1_extra_content_main_default.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        style_screen_msgbox_1_extra_content_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_screen_msgbox_1_extra_content_main_default.set_text_font(lv.font_montserrat_16)
style_screen_msgbox_1_extra_content_main_default.set_text_letter_space(0)
style_screen_msgbox_1_extra_content_main_default.set_text_line_space(10)

# add style for screen_msgbox_1_content
screen_msgbox_1_content.add_style(style_screen_msgbox_1_extra_content_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)


screen_msgbox_1.set_pos(int(43),int(76))
screen_msgbox_1.set_size(235,88)
screen_msgbox_1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_msgbox_1_main_main_default
style_screen_msgbox_1_main_main_default = lv.style_t()
style_screen_msgbox_1_main_main_default.init()
style_screen_msgbox_1_main_main_default.set_radius(4)
style_screen_msgbox_1_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_msgbox_1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_msgbox_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_msgbox_1_main_main_default.set_bg_opa(255)
style_screen_msgbox_1_main_main_default.set_border_color(lv.color_make(0xff,0xff,0xff))
style_screen_msgbox_1_main_main_default.set_border_width(0)
style_screen_msgbox_1_main_main_default.set_border_opa(100)

# add style for screen_msgbox_1
screen_msgbox_1.add_style(style_screen_msgbox_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)














# content from custom.py

# Load the default screen
lv.scr_load(screen)

while SDL.check():
    time.sleep_ms(5)
