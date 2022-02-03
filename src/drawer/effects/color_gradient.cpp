//
// Created by claiff on 31.01.2022.
//

#include "color_gradient.hpp"

static constexpr uint8_t DEFAULT_COUNT_TRANSITIONS = 16;

namespace drawer::effects
{
	ColorGradient::ColorGradient( Pixel_t const& pixel_start, Pixel_t const& pixel_end, GradientStyle gradient_style )
			: mPixelStart( pixel_start )
			, mPixelEnd( pixel_end )
			, mGradientStyle( gradient_style )
	{

	}

	void ColorGradient::Draw( device::LedMatrix& led_matrix ) const
	{
		if( mGradientStyle == GradientStyle::Horizontal )
		{
			auto width = led_matrix.GetWidth();
			auto height = led_matrix.GetHeight();
			auto count_transitions = DEFAULT_COUNT_TRANSITIONS > width ? width : DEFAULT_COUNT_TRANSITIONS;

			auto color_mixer = GetColorMixer( count_transitions );

			uint8_t step_width_rectangle = width / count_transitions;
			auto start_color = mPixelStart;

			for( auto color_number = 0; color_number < count_transitions; ++color_number )
			{
				uint8_t x = color_number * step_width_rectangle;
				drawer::effects::utils::Rectangle rectangle = {x, 0, step_width_rectangle, height};
				led_matrix.FillRectangle( rectangle, start_color, mBrightness );
				MixColor( start_color, color_mixer );
			}
		}
		led_matrix.ReDraw();
	}

	PixelMixer_t ColorGradient::GetColorMixer( uint8_t count_transitions ) const
	{
		PixelMixer_t result;

		result.red = (mPixelStart.red - mPixelEnd.red) / count_transitions;
		result.green = (mPixelStart.green - mPixelEnd.green) / count_transitions;
		result.blue = (mPixelStart.blue - mPixelEnd.blue) / count_transitions;
		return result;
	}

	void ColorGradient::MixColor( Pixel_t& color, PixelMixer_t const& mix_color ) const
	{
		color.red -= mix_color.red;
		color.green -= mix_color.green;
		color.blue -= mix_color.blue;
	}
}