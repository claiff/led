//
// Created by claiff on 29.01.2022.
//

#pragma once

#include "drawer/effects/types/ieffect.hpp"

namespace drawer::effects
{
	class SimpleColor
			: public types::IEffect
	{
	public:
		explicit SimpleColor( ::utils::Color const& color );
		~SimpleColor() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	protected:
		::utils::Color mColor{};
	};
}
