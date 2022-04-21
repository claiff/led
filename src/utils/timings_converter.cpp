//
// Created by claiff on 28.01.2022.
//

#include "timings_converter.hpp"

namespace utils
{
	TimingColorFull_t utils::TimingsConverter::Convert( Color const& color )
	{
		TimingColorFull_t result;

		result.green = ConvertPart(color.green);
		result.red = ConvertPart(color.red);
		result.blue = ConvertPart(color.blue);
		return result;
	}

	Timing_Part_t TimingsConverter::ConvertPart( uint8_t color_part )
	{
		Timing_Part_t result;

		uint8_t size = sizeof( color_part ) * 8;
		for( uint8_t i = 0; i < size; ++i )
		{
			uint8_t state = (color_part >> (size - i - 1)) & 0x01;
			uint8_t convert_state = state ? T1H : TOH;
			result.bit[i]= convert_state;
		}
		return result;
	}
}