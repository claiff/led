//
// Created by claiff on 01.02.2022.
//

#pragma once

#include <cstdint>

namespace periphery
{
	class Adc
	{
	public:
		Adc();
		~Adc() = default;

		uint32_t GetValue() const;
	};
}

