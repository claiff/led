//
// Created by claiff on 31.01.2022.
//

#include "cyclic.hpp"
#include "drawer/effects/timer_policy.hpp"

namespace drawer::builder
{
	drawer::Cyclic Cyclic::Build( effects::Registrator const& registrator, periphery::RccHelper& rcc, uint16_t time_ms )
	{
		static constexpr uint8_t WIDTH = 16;
		static constexpr uint8_t HEIGHT = 16;

		auto led_matrix = device::LedMatrix{HEIGHT, WIDTH, rcc};
		auto policy = effects::TimerPolicy{time_ms};

		return {led_matrix, registrator, policy};
	}

}