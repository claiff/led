//
// Created by claiff on 02.02.2022.
//

#pragma once

#include "drawer/effects/types/ieffect.hpp"

namespace drawer::effects
{
	class RandomCircle
			: public types::IEffect
	{
	public:
		RandomCircle() = default;
		~RandomCircle() override = default;

		virtual void Draw( device::LedMatrix& led_matrix ) const override;
	};
}