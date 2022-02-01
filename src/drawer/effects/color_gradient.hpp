//
// Created by claiff on 31.01.2022.
//

#pragma once

#include "drawer/effects/types/ieffect.hpp"
#include "utils/struct.hpp"

namespace drawer::effects
{
	enum class GradientStyle
	{
		Horizontal,
		Vertical
	};

	struct PixelMixer
	{
		int16_t red;
		int16_t green;
		int16_t blue;
	};

	using PixelMixer_t = struct PixelMixer;

	class ColorGradient
			: public types::IEffect
	{
	public:
		ColorGradient( Pixel_t const& pixel_start, Pixel_t const& pixel_end, GradientStyle gradient_style );
		~ColorGradient() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		PixelMixer_t GetColorMixer( uint8_t count_transitions ) const;
		void MixColor( Pixel_t& color, PixelMixer_t const& mix_color ) const;

		Pixel_t mPixelStart{};
		Pixel_t mPixelEnd{};
		GradientStyle mGradientStyle;
	};

}
