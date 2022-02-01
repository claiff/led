//
// Created by claiff on 31.01.2022.
//

#include "rectangle.hpp"

namespace drawer::effects::utils
{

	Rectangle::Rectangle( uint8_t x, uint8_t y, uint8_t width, uint8_t height )
			: mPosition{x, y}
			, mSize{width, height}
	{

	}
}