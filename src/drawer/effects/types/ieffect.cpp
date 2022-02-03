//
// Created by claiff on 03.02.2022.
//

#include "ieffect.hpp"

namespace drawer::effects::types
{

	types::IEffect::IEffect()
			: mBrightness{0x10}
	{

	}

	void types::IEffect::SetBrightness( uint8_t value )
	{
		mBrightness = value;
	}
}