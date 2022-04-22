//
// Created by claiff on 28.01.2022.
//

#pragma once

#include "color.hpp"

namespace utils
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

	class TimingsConverter
	{
	public:
		TimingsConverter() = default;
		~TimingsConverter() = default;

		static TimingColorFull_t Convert( Color const& color );
		static utils::TimingColorFull_t GetDefaultTiming();

	private:
		static Timing_Part_t ConvertPart( uint8_t color_part );
	};
}
