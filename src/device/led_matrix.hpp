//
// Created by claiff on 27.01.2022.
//

#pragma once

#include "periphery/pwm.hpp"
#include "periphery/timer_irq.hpp"
#include "periphery/rcc_helper.hpp"

namespace device
{
	class LedMatrix
	{
	public:
		LedMatrix( uint8_t count_row, uint8_t count_column, periphery::RccHelper& rcc);
		~LedMatrix();

		void ReDraw();

	private:
		void BuildPwm( periphery::RccHelper& rcc );
		void FillMatrix( Pixel_t const& color );

		uint8_t mWidth;
		uint8_t mHeight;
		periphery::PWM* mPwm;
		periphery::TimerIRQ* mTimerIrq;

	};
}

