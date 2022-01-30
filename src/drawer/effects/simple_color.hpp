//
// Created by claiff on 29.01.2022.
//

#pragma once

#include "drawer/effects/types/ieffect.hpp"
#include "utils/struct.hpp"

namespace drawer::effects
{
	class SimpleColor
			: public types::IEffect
	{
	public:
		explicit SimpleColor( Pixel_t const& color );
		~SimpleColor() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		Pixel_t mColor{};
	};
}
