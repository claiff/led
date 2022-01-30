//
// Created by claiff on 27.01.2022.
//

#include "led_matrix.hpp"
#include "utils/struct.hpp"


static const Pixel_t DEFAULT_PIXEL = {0xFF, 0xFF, 0xFF};

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
		delete mPwm;
		delete mTimerIrq;
	}

	void LedMatrix::ReDraw()
	{
		mPwm->StartPWM();
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

	void LedMatrix::FillMatrix( Pixel_t const& color )
	{
		for( auto i = 0; i < mWidth * mHeight; ++i )
		{
			mPwm->SetPixel( i, color );
		}
	}

}
