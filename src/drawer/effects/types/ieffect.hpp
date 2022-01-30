//
// Created by claiff on 29.01.2022.
//

#pragma once

#include "device/led_matrix.hpp"

namespace drawer::effects::types
{
	class IEffect
	{
	public:
		virtual ~IEffect() = default;

		virtual void Draw( device::LedMatrix& led_matrix ) const = 0;
	};

	using IEffectPtr = IEffect*;
}
