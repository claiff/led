//
// Created by claiff on 27.01.2022.
//

#pragma once

#include "periphery/pwm.hpp"
#include "periphery/timer_irq.hpp"
#include "periphery/rcc_helper.hpp"
#include "drawer/effects/utils/figures.hpp"

namespace device
{
	class LedMatrix
	{
	public:
		LedMatrix( uint8_t count_row, uint8_t count_column, periphery::RccHelper& rcc );
		~LedMatrix();

		void ReDraw();
		void FillMatrix( utils::Color const& color );
		void FillMatrix( utils::Color const& color, uint8_t brightness );

		void FillRectangle( drawer::effects::utils::Rectangle const& rectangle, utils::Color const& color,
							uint8_t brightness );
		void FillCircle( drawer::effects::utils::Circle const& circle, utils::Color const& color );

		void DrawPixel( int8_t x, int8_t y, utils::Color const& color );

		[[nodiscard]] uint8_t GetWidth() const;
		[[nodiscard]] uint8_t GetHeight() const;

		void FillHorizontalLine( utils::Vector position, const utils::Color& line_color,
								 uint8_t width );
		void FillOnBrightHorizontalLine( utils::Vector position, const utils::Color& line_color,
										 uint8_t width );

	private:
		void BuildPwm( periphery::RccHelper& rcc );
		void DrawVerticalLine( utils::Vector position, uint8_t height, utils::Color const& color );
		[[nodiscard]] utils::Color OnBrightColor( utils::Color const& color, uint8_t brightness ) const;

		uint8_t mWidth;
		uint8_t mHeight;
		periphery::PWM* mPwm;
		periphery::TimerIRQ* mTimerIrq;


	};
}

