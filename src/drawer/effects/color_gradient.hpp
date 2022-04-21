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
		ColorGradient( ::utils::Color const& pixel_start, ::utils::Color const& pixel_end,
					   GradientStyle gradient_style );
		~ColorGradient() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		PixelMixer_t GetColorMixer( uint8_t count_transitions ) const;
		void MixColor( ::utils::Color& color, PixelMixer_t const& mix_color ) const;

		::utils::Color mPixelStart{};
		::utils::Color mPixelEnd{};
		GradientStyle mGradientStyle;
	};

}
