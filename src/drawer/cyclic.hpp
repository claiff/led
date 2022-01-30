//
// Created by claiff on 30.01.2022.
//

#pragma once

#include "effects/registrator.hpp"
#include "device/led_matrix.hpp"
#include "effects/timer_policy.hpp"

namespace drawer
{
	class Cyclic
	{
	public:
		Cyclic( device::LedMatrix const& led_matrix, effects::Registrator const& effects, effects::TimerPolicy const& timer);
		~Cyclic() = default;

		void Draw();

	private:
		device::LedMatrix mLedMatrix;
		effects::Registrator mEffects;
		effects::TimerPolicy mTimer;
	};

}
