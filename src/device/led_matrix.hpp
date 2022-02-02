//
// Created by claiff on 27.01.2022.
//

#pragma once

#include "periphery/pwm.hpp"
#include "periphery/timer_irq.hpp"
#include "periphery/rcc_helper.hpp"
#include "drawer/effects/utils/rectangle.hpp"

namespace device
{
	class LedMatrix
	{
	public:
		LedMatrix( uint8_t count_row, uint8_t count_column, periphery::RccHelper& rcc );
		~LedMatrix();

		void ReDraw();
		void FillMatrix( Pixel_t const& color );
		void FillMatrix( Pixel_t const& color, uint8_t brightness );

		void FillRectangle( drawer::effects::utils::Rectangle const& rectangle, Pixel_t const& color );

		void DrawPixel( uint8_t x, uint8_t y, Pixel_t const& color );

		uint8_t GetWidth() const;
		uint8_t GetHeight() const;

	private:
		void BuildPwm( periphery::RccHelper& rcc );
		void DrawVerticalLine( drawer::effects::utils::Coordinate_t position, uint8_t height, Pixel_t const& color );

		uint8_t mWidth;
		uint8_t mHeight;
		periphery::PWM* mPwm;
		periphery::TimerIRQ* mTimerIrq;

	};
}

