//
// Created by claiff on 18.04.22.
//

#pragma once

#include <cstdint>

#include "device/led_matrix.hpp"

namespace drawer::figure::types
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

	using Vector = struct Vector;

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

		virtual void SetPosition( Vector const& position ) = 0;
		virtual void Move( Vector const& position ) = 0;
		virtual void SetColor( Color const& color ) = 0;
		virtual void Draw( device::LedMatrix& led_matrix ) = 0;
		virtual void ResetPositionX() = 0;
		virtual void ResetPositionY() = 0;
		[[nodiscard]] virtual bool IsFigureOut() const = 0;
	};

	using IFigurePtr = IFigure*;
}
