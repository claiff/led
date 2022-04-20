//
// Created by claiff on 31.01.2022.
//
#pragma once

#include "drawer/cyclic.hpp"
#include "drawer/effects/utils/registrator.hpp"

namespace drawer::builder
{
	class Cyclic
	{
	public:
		Cyclic() = default;
		~Cyclic() = default;

		drawer::Cyclic
		Build( effects::utils::Registrator < effects::types::IEffect > const& registrator, periphery::RccHelper& rcc,
			   uint16_t time_ms );
	};

}
