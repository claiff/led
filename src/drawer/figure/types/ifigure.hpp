//
// Created by claiff on 18.04.22.
//

#pragma once

#include <cstdint>

#include "device/led_matrix.hpp"

namespace drawer::figure::types
{
	struct Position
	{
		uint8_t x;
		uint8_t y;
	};
	using Position = struct Position;

	struct Color
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};
	using Color = struct Color;

	class IFigure
	{
	public:
		virtual ~IFigure() = default;

		virtual void SetPosition( Position const& position ) = 0;
		virtual void SetColor( Color const& color ) = 0;
		virtual void Draw( device::LedMatrix& led_matrix ) = 0;
	};

	using IFigurePtr = IFigure*;
}
