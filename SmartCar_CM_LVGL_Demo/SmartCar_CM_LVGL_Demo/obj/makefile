################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include LVGL_GUI/lvgl_port/subdir.mk
-include LVGL_GUI/lvgl_app/guider_fonts/subdir.mk
-include LVGL_GUI/lvgl_app/subdir.mk
-include LVGL_GUI/lvgl/src/widgets/subdir.mk
-include LVGL_GUI/lvgl/src/misc/subdir.mk
-include LVGL_GUI/lvgl/src/hal/subdir.mk
-include LVGL_GUI/lvgl/src/font/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/win/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/tileview/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/tabview/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/spinner/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/spinbox/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/span/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/msgbox/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/meter/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/menu/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/list/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/led/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/keyboard/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/imgbtn/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/colorwheel/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/chart/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/calendar/subdir.mk
-include LVGL_GUI/lvgl/src/extra/widgets/animimg/subdir.mk
-include LVGL_GUI/lvgl/src/extra/themes/mono/subdir.mk
-include LVGL_GUI/lvgl/src/extra/themes/default/subdir.mk
-include LVGL_GUI/lvgl/src/extra/themes/basic/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/snapshot/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/msg/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/monkey/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/imgfont/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/ime/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/gridnav/subdir.mk
-include LVGL_GUI/lvgl/src/extra/others/fragment/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/sjpg/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/rlottie/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/qrcode/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/png/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/gif/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/fsdrv/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/freetype/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/ffmpeg/subdir.mk
-include LVGL_GUI/lvgl/src/extra/libs/bmp/subdir.mk
-include LVGL_GUI/lvgl/src/extra/layouts/grid/subdir.mk
-include LVGL_GUI/lvgl/src/extra/layouts/flex/subdir.mk
-include LVGL_GUI/lvgl/src/extra/subdir.mk
-include LVGL_GUI/lvgl/src/draw/swm341_dma2d/subdir.mk
-include LVGL_GUI/lvgl/src/draw/sw/subdir.mk
-include LVGL_GUI/lvgl/src/draw/stm32_dma2d/subdir.mk
-include LVGL_GUI/lvgl/src/draw/sdl/subdir.mk
-include LVGL_GUI/lvgl/src/draw/renesas/subdir.mk
-include LVGL_GUI/lvgl/src/draw/nxp/vglite/subdir.mk
-include LVGL_GUI/lvgl/src/draw/nxp/pxp/subdir.mk
-include LVGL_GUI/lvgl/src/draw/arm2d/subdir.mk
-include LVGL_GUI/lvgl/src/draw/subdir.mk
-include LVGL_GUI/lvgl/src/core/subdir.mk
-include LVGL_GUI/drivers/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
SmartCar_CM_LVGL_Demo.hex \

SECONDARY_LIST += \
SmartCar_CM_LVGL_Demo.lst \

SECONDARY_SIZE += \
SmartCar_CM_LVGL_Demo.siz \


# All Target
all: SmartCar_CM_LVGL_Demo.elf secondary-outputs

# Tool invocations
SmartCar_CM_LVGL_Demo.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\CM2023\SmartCar_CM_LVGL_Demo\SmartCar_CM_LVGL_Demo\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"SmartCar_CM_LVGL_Demo.map" --specs=nano.specs --specs=nosys.specs  -o "SmartCar_CM_LVGL_Demo.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintfloat
	@	@
SmartCar_CM_LVGL_Demo.hex: SmartCar_CM_LVGL_Demo.elf
	@	riscv-none-embed-objcopy -O ihex "SmartCar_CM_LVGL_Demo.elf"  "SmartCar_CM_LVGL_Demo.hex"
	@	@
SmartCar_CM_LVGL_Demo.lst: SmartCar_CM_LVGL_Demo.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "SmartCar_CM_LVGL_Demo.elf" > "SmartCar_CM_LVGL_Demo.lst"
	@	@
SmartCar_CM_LVGL_Demo.siz: SmartCar_CM_LVGL_Demo.elf
	@	riscv-none-embed-size --format=berkeley "SmartCar_CM_LVGL_Demo.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) SmartCar_CM_LVGL_Demo.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
