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
		IEffect();
		virtual ~IEffect() = default;

		virtual void Draw( device::LedMatrix& led_matrix ) const = 0;
		virtual void SetBrightness( uint8_t value );

	protected:
		uint8_t mBrightness;
	};

	using IEffectPtr = IEffect*;
}
