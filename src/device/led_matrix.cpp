//
// Created by claiff on 27.01.2022.
//

#include <cmath>

#include "led_matrix.hpp"
#include "utils/struct.hpp"

//TODO Нужно сохранять цвет фона, для очистки его
//TODO Нужно уметь заливать не только цвета но и градиент

namespace device
{
	LedMatrix::LedMatrix( uint8_t count_row, uint8_t count_column, periphery::RccHelper& rcc )
			: mWidth( count_row )
			, mHeight( count_column )
	{
		BuildPwm( rcc );
	}

	LedMatrix::~LedMatrix()
	{
		//FIXME Нужно удалять pwm и irq, но отваливается в дальнейшем
	}

	void LedMatrix::ReDraw()
	{
		mPwm->StartPWM();
	}

	void LedMatrix::FillMatrix( utils::Color const& color )
	{
		for( auto i = 0; i < mWidth * mHeight; ++i )
		{
			mPwm->SetPixel( i, color );
		}
	}

	void LedMatrix::FillMatrix( utils::Color const& color, uint8_t brightness )
	{
		utils::Color brightned_color{};

		brightned_color = OnBrightColor( color, brightness );

		FillMatrix( brightned_color );
	}

	void LedMatrix::FillRectangle( drawer::effects::utils::Rectangle const& rectangle, utils::Color const& color,
								   uint8_t brightness )
	{
		auto position_x = rectangle.mPosition.x;
		auto position_y = rectangle.mPosition.y;
		auto width = rectangle.mSize.x;
		auto height = rectangle.mSize.y;
		auto brightned_color = OnBrightColor( color, brightness );

		for( uint8_t count_line = 0; count_line < width; ++count_line )
		{
			int8_t x = position_x + count_line;
			DrawVerticalLine( {x, position_y}, height, brightned_color );
		}
		mPwm->StartPWM();
	}

	void LedMatrix::FillCircle( drawer::effects::utils::Circle const& circle,  utils::Color const& color )
	{
		uint8_t start_x = 4;
		uint8_t start_y = 4;

		auto radius = static_cast<int8_t> (circle.mRadius);
		for( uint8_t x = 0; x < radius; ++x )
		{
			auto y = sqrt( radius * radius - x * x );
			uint8_t y_round = round( y );

			int8_t y_bottom = start_y - y_round;
			int8_t height = y_round * 2;
			int8_t x_ready = x + start_x;
			int8_t x_ready2 = start_x - x;

			DrawVerticalLine( {x_ready, y_bottom}, height, color );
			DrawVerticalLine( {x_ready2, y_bottom}, height, color );
		}

		mPwm->StartPWM();
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

	utils::Color LedMatrix::OnBrightColor( utils::Color const& color, uint8_t brightness ) const
	{
		utils::Color result;
		result.red = (color.red * brightness) >> 8;
		result.green = (color.green * brightness) >> 8;
		result.blue = (color.blue * brightness) >> 8;

		return result;
	}

	void LedMatrix::BuildPwm( periphery::RccHelper& rcc )
	{
		uint16_t size = mWidth * mHeight;
		mPwm = new periphery::PWM{rcc, size};
		mTimerIrq = new periphery::TimerIRQ{mPwm};
	}

	void
	LedMatrix::DrawVerticalLine( utils::Vector position, uint8_t height, utils::Color const& color )
	{
		auto position_x = position.x;
		auto position_y = position.y;

		for( auto y = 0; y < height; ++y )
		{
			DrawPixel( position_x, position_y + y, color );
		}

	}

	void LedMatrix::DrawPixel( int8_t x, int8_t y, utils::Color const& color )
	{
		//FIXME Refactor
		uint16_t number_led = 0;
		if( x < 0 || y < 0 || x >= mWidth || y >= mHeight )
		{
			return;
		}

		if((x % 2) == 0 )
		{
			number_led = x * GetHeight() + y;
		}
		else
		{
			number_led = (x + 1) * GetHeight() - y - 1;
		}
		mPwm->SetPixel( number_led, color );
	}

	void LedMatrix::FillHorizontalLine( utils::Vector position, utils::Color const& line_color,
										uint8_t width )
	{
		auto position_x = position.x;
		auto position_y = position.y;

		for( uint8_t x = 0; x < width; ++x )
		{
			DrawPixel( position_x + x, position_y, line_color );
		}
	}

	void
	LedMatrix::FillOnBrightHorizontalLine( utils::Vector position, utils::Color const& line_color,
										   uint8_t width )
	{
		static constexpr int BRIGHTNESS = 40;

		auto position_x = position.x;
		auto position_y = position.y;
		auto bright_color = OnBrightColor( line_color, BRIGHTNESS );

//		if( position_x != 0 )
//		{
//			DrawPixel( position_x - 1, position_y, bright_color);
//		}

		for( auto x = 0; x < width; ++x )
		{
			DrawPixel( position_x + x, position_y, line_color );
		}
		auto full_width = position_x + width;
//		if( full_width != mWidth )
//		{
//			DrawPixel( full_width, position_y, bright_color );
//		}
	}
}
