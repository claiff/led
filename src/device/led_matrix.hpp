//
// Created by claiff on 27.01.2022.
//

#pragma once



#include "specific/stm32f103xb.h"
#include "periphery/rcc_helper.hpp"



namespace device
{
	class LedMatrix
	{
	public:
		LedMatrix( uint8_t count_row, uint8_t count_column);
		~LedMatrix();

	private:


	};
}

