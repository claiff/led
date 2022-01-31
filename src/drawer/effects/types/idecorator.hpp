//
// Created by claiff on 31.01.2022.
//

#pragma once

#include "ieffect.hpp"

namespace drawer::effects::types
{
	class IDecorator
			: public IEffect
	{
	public:
		explicit IDecorator( IEffectPtr effect );
		~IDecorator() override;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		IEffectPtr mEffect;
	};
}