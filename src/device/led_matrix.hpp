//
// Created by claiff on 27.01.2022.
//

#pragma once

#include "periphery/pwm.hpp"

namespace device
{
	class LedMatrix
	{
	public:
		LedMatrix( uint8_t count_row, uint8_t count_column, periphery::PWM const& pwm);
		~LedMatrix() = default;

	private:
		uint8_t mWidth;
		uint8_t mHeight;
		periphery::PWM mPwm;
		void FillMatrix( Pixel_t color );
	};
}

