//
// Created by claiff on 31.01.2022.
//

#pragma once

#include <cstdint>


namespace drawer::effects::utils
{
	struct Coordinate_t
	{
		uint8_t x;
		uint8_t y;
	};
	class Rectangle
	{
	public:
		Rectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
		~Rectangle() = default;

		Coordinate_t mPosition;
		Coordinate_t mSize;
	};
}