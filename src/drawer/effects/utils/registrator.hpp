//
// Created by claiff on 30.01.2022.
//

#pragma once

#include <vector>

#include "drawer/effects/types/ieffect.hpp"

namespace drawer::effects::utils
{
	class Registrator
	{
	public:
		Registrator();
		~Registrator();

		void Add( types::IEffectPtr const& effect );
		types::IEffectPtr Get();

	private:
		std::vector < types::IEffectPtr > mEffects;
		uint8_t mPosition;
	};

}
