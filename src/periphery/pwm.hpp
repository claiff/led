//
// Created by claiff on 27.01.2022.
//

#pragma once

#include <vector>

#include "rcc_helper.hpp"
#include "utils/struct.hpp"

namespace periphery
{
	class PWM
	{
	public:
		PWM( RccHelper& rcc, uint16_t count_element );
		~PWM();

		void StartPWM();
		void StopPWM();
		void SetDelay( uint8_t time_us );
		void SetPixel( uint16_t number_pixel, Pixel_t pixel );

		void DelayTimerEvent();

	private:
		void InitPWMTimer( RccHelper& rcc );
		void InitDMA( RccHelper& rcc );
		void InitRestartTimer( RccHelper& rcc );
		void SetupGPIO( RccHelper& rcc );
		void InitTimings( uint16_t count_elements );
		uint16_t GetTimingsSize() const;

		std::vector < TimingColorFull_t > mTimings;
		TimingColorFull_t GetDefaultTiming() const;
	};

}
