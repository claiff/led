//
// Created by claiff on 27.01.2022.
//

#pragma once

#include <vector>

#include "rcc_helper.hpp"
#include "utils/color.hpp"
#include "utils/timings_converter.hpp"

namespace periphery
{
	class PWM
	{
	public:
		PWM( RccHelper& rcc, uint16_t count_element );
		PWM( PWM const& other );
		PWM& operator=(PWM const& other);
		PWM& operator=(PWM* other);
		~PWM();

		void StartPWM();
		void StopPWM();
		void SetDelay( uint8_t time_us );
		void SetPixel( uint16_t number_pixel, utils::Color const& color );
		void DmaFullTransmitEvent();
	private:
		void InitPWMTimer( RccHelper& rcc );
		void InitDMA( RccHelper& rcc );
		void SetupGPIO( RccHelper& rcc );
		void InitTimings( uint16_t count_elements );
		[[nodiscard]] uint16_t GetTimingsSize() const;

		std::vector < utils::TimingColorFull_t > mTimings;
	};

}
