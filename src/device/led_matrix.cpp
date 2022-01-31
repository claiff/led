//
// Created by claiff on 27.01.2022.
//

#include "led_matrix.hpp"
#include "utils/struct.hpp"


static const Pixel_t DEFAULT_PIXEL = {0x10, 0x10, 0x10};

namespace device
{
	LedMatrix::LedMatrix( uint8_t count_row, uint8_t count_column, periphery::RccHelper& rcc )
			: mWidth( count_row )
			, mHeight( count_column )
	{
		BuildPwm( rcc );
		FillMatrix( DEFAULT_PIXEL );
	}

	LedMatrix::~LedMatrix()
	{
		//FIXME Нужно удалять pwm и irq, но отваливается в дальнейшем
	}

	void LedMatrix::ReDraw()
	{
		mPwm->StartPWM();
	}

	void LedMatrix::FillMatrix( Pixel_t const& color )
	{
		for( auto i = 0; i < mWidth * mHeight; ++i )
		{
			mPwm->SetPixel( i, color );
		}
	}

	void LedMatrix::FillMatrix( Pixel_t const& color, uint8_t brightness )
	{
		Pixel_t brightned_color{};

		brightned_color.red = (color.red * brightness) >> 8;
		brightned_color.green = (color.green * brightness) >> 8;
		brightned_color.blue = (color.blue * brightness) >> 8;

		FillMatrix(brightned_color);
	}

//
// Private methods
//

	void LedMatrix::BuildPwm( periphery::RccHelper& rcc )
	{
		uint16_t size = mWidth * mHeight;
		mPwm = new periphery::PWM{rcc, size};
		mTimerIrq = new periphery::TimerIRQ{mPwm};
	}
}
