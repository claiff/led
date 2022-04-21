//
// Created by claiff on 28.01.2022.
//

#pragma once

#include "struct.hpp"
#include "color.hpp"
namespace utils
{
	class TimingsConverter
	{
	public:
		TimingsConverter() = default;
		~TimingsConverter() = default;

		static TimingColorFull_t Convert(Color const& color);

	private:
		static Timing_Part_t ConvertPart( uint8_t color_part);
	};
}
