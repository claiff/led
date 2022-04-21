//
// Created by claiff on 21.04.22.
//

#pragma once

#include <cstdint>

namespace utils
{
	struct Vector
	{
		int8_t x;
		int8_t y;

		void operator+=( Vector const& other )
		{
			x += other.x;
			y += other.y;
		}
	};
}


