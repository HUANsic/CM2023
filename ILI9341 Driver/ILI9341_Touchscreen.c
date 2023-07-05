//-----------------------------------
//	ILI9341 Touchscreen library for WCH
//-----------------------------------
//
//	Very simple Touchscreen library for ILI9341.
//	Extremly basic reading of position. No runtime calibration, No prediction, basic noise removal. Simple but stupid.
//	Basic hardcoded calibration values saved in .h file
//
//	Library is written for STM32 HAL library and supports STM32CUBEMX. To use the library with Cube software
//	you need to tick the box that generates peripheral initialization code in their own respective .c and .h file
//
//
//-----------------------------------
//	How to use this library
//-----------------------------------
//
//	-If using MCUs other than STM32F7 you will have to change the #include "stm32f7xx_hal.h" in the ILI9341_Touchscreen.h to your respective .h file
//	-define GPIO inputs and outputs then map the Pins and Ports inside the ILI9341_Touchscreen.h
//	-Library does not require any initialization calls apart from GPIO initialization. Initialize GPIOs before calling library functions!
//
//		Touchpad GPIO defines
//			Outputs:
//				CLK
//				MOSI
//				CS
//
//			Inputs:
//				IRQ
//				MISO
//
//
//	-Touchpad library bitbangs SPI interface and only requires basic GPIOs.
//	-Setting GPIOs as FREQ_VERY_HIGH Recommended
//
//	-Warning! Library is written for "ILI9341_Set_Rotation(SCREEN_VERTICAL_1)"	(See ILI9341_STM32_Driver for information about function)
//	-If using different layout you will have to Re-Map X and Y coordinates of the Screen
//
//
//	-NO_OF_POSITION_SAMPLES makes location output less noisy but increases reading time. Increase and decrease to your liking
//
//----------EXAMPLE------------------
/*
if(TP_Touchpad_Pressed())
	{
		uint16_t x_pos = 0;
		uint16_t y_pos = 0;

		uint16_t position_array[2];
		if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK)
		{
		x_pos = position_array[0];
		y_pos = position_array[1];
		}
	}
*/
//-----------------------------------

#include "ILI9341_Touchscreen.h"

// Internal Touchpad command, do not call directly
uint16_t TP_Read(void)
{
	uint8_t i = 16;
	uint16_t value = 0;

	while (i > 0x00)
	{
		value <<= 1;

		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);

		if (GPIO_ReadInputDataBit(TP_MISO_PORT, TP_MISO_PIN) != 0)
		{
			value++;
		}

		i--;
	};

	return value;
}

// Internal Touchpad command, do not call directly
void TP_Write(uint8_t value)
{
	uint8_t i = 0x08;

	GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);

	while (i > 0)
	{
		if ((value & 0x80) != 0x00)
		{
			GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_SET);
		}
		else
		{
			GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_RESET);
		}

		value <<= 1;
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);
		i--;
	};
}

// Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2])
{
	GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
	GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_SET);
	GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_SET);

	uint32_t avg_x, avg_y = 0;
	uint16_t rawx, rawy = 0;
	uint32_t calculating_x, calculating_y = 0;

	uint32_t samples = NO_OF_POSITION_SAMPLES;
	uint32_t counted_samples = 0;

	GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_RESET);

	while ((samples > 0) && (GPIO_ReadInputDataBit(TP_IRQ_PORT, TP_IRQ_PIN) == 0))
	{
		TP_Write(CMD_RDY);

		rawy = TP_Read();
		avg_y += rawy;
		calculating_y += rawy;

		TP_Write(CMD_RDX);
		rawx = TP_Read();
		avg_x += rawx;
		calculating_x += rawx;
		samples--;
		counted_samples++;
	};

	GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_SET);

	if ((counted_samples == NO_OF_POSITION_SAMPLES) && (GPIO_ReadInputDataBit(TP_IRQ_PORT, TP_IRQ_PIN) == 0))
	{

		calculating_x /= counted_samples;
		calculating_y /= counted_samples;

		rawx = calculating_x;
		rawy = calculating_y;

		rawx *= -1;
		rawy *= -1;

		// CONVERTING 16bit Value to Screen coordinates
		// 65535/273 = 240!
		// 65535/204 = 320!
		Coordinates[0] = ((240 - (rawx / X_TRANSLATION)) - X_OFFSET) * X_MAGNITUDE;
		Coordinates[1] = ((rawy / Y_TRANSLATION) - Y_OFFSET) * Y_MAGNITUDE;

		return TOUCHPAD_DATA_OK;
	}
	else
	{
		Coordinates[0] = 0;
		Coordinates[1] = 0;
		return TOUCHPAD_DATA_NOISY;
	}
}

// Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void)
{
	if (GPIO_ReadInputDataBit(TP_IRQ_PORT, TP_IRQ_PIN) == 0)
	{
		return TOUCHPAD_PRESSED;
	}
	else
	{
		return TOUCHPAD_NOT_PRESSED;
	}
}
