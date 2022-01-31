//
// Created by claiff on 31.01.2022.
//

#include "idecorator.hpp"

namespace drawer::effects::types
{

	IDecorator::IDecorator( IEffectPtr effect )
			: mEffect( effect )
	{

	}

	IDecorator::~IDecorator()
	{
		delete mEffect;
	}

	void IDecorator::Draw( device::LedMatrix& led_matrix ) const
	{
		mEffect->Draw( led_matrix );
	}
}