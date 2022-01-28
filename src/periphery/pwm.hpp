//
// Created by claiff on 27.01.2022.
//

#pragma once

#include <vector>

#include "rcc_helper.hpp"

namespace periphery
{
	struct TimingColorPart
	{
		uint8_t bit[8];
	};
	using Timing_Part_t = TimingColorPart;

	struct TimingColorFull
	{
		Timing_Part_t green;
		Timing_Part_t red;
		Timing_Part_t blue;
	};
	using TimingColorFull_t = TimingColorFull;

	struct Pixel
	{
		uint8_t green;
		uint8_t red;
		uint8_t blue;
	};
	typedef struct Pixel Pixel_t;


	class PWM
	{
	public:
		PWM( RccHelper& rcc, uint16_t count_element );
		~PWM();

		void StartPWM();
		void StopPWM();
		void SetDelay(uint8_t time_us);
		void SetPixel(uint16_t number_pixel, Pixel_t pixel);

		void DelayTimerEvent();

	private:
		void InitPWMTimer( RccHelper& rcc );
		void InitDMA( RccHelper& rcc );
		void InitRestartTimer(RccHelper& rcc);
		void SetupGPIO(RccHelper& rcc);
		void InitTimings( uint16_t count_elements );
		uint16_t GetTimingsSize() const;

		std::vector < TimingColorFull_t > mTimings;
		TimingColorFull_t GetDefaultTiming() const;
	};

}
