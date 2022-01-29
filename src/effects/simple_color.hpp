//
// Created by claiff on 29.01.2022.
//

#pragma once

#include "types/ieffect.hpp"
#include "utils/struct.hpp"

namespace effect
{
	class SimpleColor
			: public types::IEffect
	{
	public:
		explicit SimpleColor( Pixel_t const& color );
		~SimpleColor() = default;

		void Draw() const override;
	private:
		Pixel_t mColor{};
	};

}
