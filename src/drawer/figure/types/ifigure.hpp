//
// Created by claiff on 18.04.22.
//

#pragma once

#include "device/led_matrix.hpp"
#include "utils/vector.hpp"

namespace drawer::figure::types
{
	enum class OutSide
	{
		NONE,
		RIGHT,
		DOWN,
		LEFT,
		UP
	};

	class IFigure
	{
	public:
		virtual ~IFigure() = default;

		virtual void SetPosition( utils::Vector const& position ) = 0;

		virtual void Move( utils::Vector const& position ) = 0;
		virtual void SetColor( utils::Color const& color ) = 0;
		virtual void Draw( device::LedMatrix& led_matrix ) = 0;
		virtual void ResetPositionX() = 0;
		virtual void ResetPositionY() = 0;
		[[nodiscard]] virtual OutSide IsFigureOut( device::LedMatrix const& led_matrix ) const = 0;
	};

	using IFigurePtr = IFigure*;
}
