//
// Created by claiff on 31.01.2022.
//

#pragma once

#include "utils/vector.hpp"

namespace drawer::effects::utils
{
	class Rectangle
	{
	public:
		Rectangle( uint8_t x, uint8_t y, uint8_t width, uint8_t height );
		Rectangle( ::utils::Vector const& position, ::utils::Vector const& size );
		~Rectangle() = default;

		::utils::Vector mPosition;
		::utils::Vector mSize;
	};

	class Circle
	{
	public:
		Circle( ::utils::Vector const& position, uint8_t radius );
		~Circle() = default;

		::utils::Vector mPosition;
		uint8_t mRadius;
	};
}