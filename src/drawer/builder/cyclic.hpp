//
// Created by claiff on 31.01.2022.
//
#pragma once

#include "drawer/cyclic.hpp"
#include "drawer/effects/registrator.hpp"

namespace drawer::builder
{
	class Cyclic
	{
	public:
		Cyclic() = default;
		~Cyclic() = default;

		drawer::Cyclic Build( effects::Registrator const& registrator,periphery::RccHelper& rcc, uint16_t time_ms );
	};

}
