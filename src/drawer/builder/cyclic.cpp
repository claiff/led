//
// Created by claiff on 31.01.2022.
//

#include "cyclic.hpp"
#include "drawer/effects/utils/timer_policy.hpp"

namespace drawer::builder
{
	drawer::Cyclic Cyclic::Build( effects::utils::Registrator< effects::types::IEffect* > const& registrator, periphery::RccHelper& rcc, uint16_t time_ms )
	{
		static constexpr uint8_t WIDTH = 16;
		static constexpr uint8_t HEIGHT = 16;

		auto led_matrix = device::LedMatrix{HEIGHT, WIDTH, rcc};
		auto policy = effects::utils::TimerPolicy{time_ms};

		return {led_matrix, registrator, policy};
	}

}