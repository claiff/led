//
// Created by claiff on 31.01.2022.
//

#include "figures.hpp"

namespace drawer::effects::utils
{

	Rectangle::Rectangle( uint8_t x, uint8_t y, uint8_t width, uint8_t height )
			: mPosition{x, y}
			, mSize{width, height}
	{

	}

	Rectangle::Rectangle( ::utils::Vector const& position, ::utils::Vector const& size )
			: mPosition( position )
			, mSize( size )
	{

	}

	Circle::Circle( ::utils::Vector const& position, uint8_t radius )
			: mPosition( position )
			, mRadius( radius )
	{

	}
}