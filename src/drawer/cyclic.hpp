//
// Created by claiff on 30.01.2022.
//

#pragma once

#include "drawer/effects/utils/registrator.hpp"
#include "device/led_matrix.hpp"
#include "drawer/effects/utils/timer_policy.hpp"

namespace drawer
{
	class Cyclic
	{
	public:
		Cyclic( device::LedMatrix const& led_matrix,
				effects::utils::Registrator < effects::types::IEffect > const& effects,
				effects::utils::TimerPolicy const& timer );
		~Cyclic() = default;

		void Draw();

	private:
		device::LedMatrix mLedMatrix;
		effects::utils::Registrator < effects::types::IEffect > mEffects;
		effects::utils::TimerPolicy mTimer;
	};

}
