//
// Created by claiff on 27.01.2022.
//

#include "led_matrix.hpp"
#include "utils/struct.hpp"


static const Pixel_t DEFAULT_PIXEL = {0x05, 0x00, 0x00};

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

		FillMatrix( brightned_color );
	}

	void LedMatrix::FillRectangle( drawer::effects::utils::Rectangle const& rectangle, Pixel_t const& color )
	{
		auto position_x = rectangle.mPosition.x;
		auto position_y = rectangle.mPosition.y;
		auto width = rectangle.mSize.x;
		auto height = rectangle.mSize.y;

		for(uint8_t count_line = 0; count_line < width ; ++count_line)
		{
			uint8_t x = position_x + count_line;
			DrawVerticalLine( {x, position_y}, height, color );
		}
	}

	uint8_t LedMatrix::GetWidth() const
	{
		return mWidth;
	}

	uint8_t LedMatrix::GetHeight() const
	{
		return mHeight;
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

	void
	LedMatrix::DrawVerticalLine( drawer::effects::utils::Coordinate_t position, uint8_t height, Pixel_t const& color )
	{
		//FIXME Refactor
		auto position_x = position.x;
		auto position_y = position.y;

		if((position_x % 2) == 0 )
		{
			auto number_led = GetHeight() * position_x + position_y;
			for( auto y = 0; y < height; ++y )
			{
				mPwm->SetPixel( number_led + y, color );
			}
		}
		else
		{
			auto number_led = position_x  * GetHeight();
			number_led += (GetHeight() - position_y) - 1;
			for( auto y = 0; y < height; ++y )
			{
				mPwm->SetPixel( number_led - y, color );
			}
		}
		mPwm->StartPWM();
	}


}
