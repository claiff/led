//
// Created by claiff on 27.01.2022.
//

#include "led_matrix.hpp"
#include "utils/struct.hpp"

static const Pixel_t DEFAULT_PIXEL = {0xFF, 0xFF, 0xFF};

namespace device
{
	LedMatrix::LedMatrix( uint8_t count_row, uint8_t count_column, periphery::PWM const& pwm )
			: mWidth( count_row )
			, mHeight( count_column )
			, mPwm( pwm )
	{
		FillMatrix( DEFAULT_PIXEL );
	}

	void LedMatrix::FillMatrix( Pixel_t color )
	{
		for( auto i = 0; i < mWidth * mHeight; ++i )
		{
			mPwm.SetPixel( i, color );
		}
	}
//
// Private methods
//

}
