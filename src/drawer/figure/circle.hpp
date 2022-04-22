//
// Created by claiff on 18.04.22.
//

#pragma once

#include "types/ifigure.hpp"
#include "device/led_matrix.hpp"

namespace drawer::figure
{
	class Circle
			: public types::IFigure
	{
	public:
		Circle( utils::Vector const& position, uint8_t size,
				utils::Color const& color );
		~Circle() override = default;

		void SetPosition( utils::Vector const& position ) override;
		void SetColor( utils::Color const& color ) override;
		void Draw( device::LedMatrix& led_matrix ) override;
		void Move( utils::Vector const& position ) override;
		[[nodiscard]] types::OutSide IsFigureOut( device::LedMatrix const& led_matrix ) const override;
		void ResetPositionX() override;
		void ResetPositionY() override;
	private:
		[[nodiscard]] types::OutSide IsXOut( device::LedMatrix const& led_matrix ) const;
		[[nodiscard]] types::OutSide IsYOut( device::LedMatrix const& led_matrix ) const;

		utils::Vector mPosition;
		uint8_t mSize;
		utils::Color mColor;

		void DrawLines( device::LedMatrix& led_matrix, utils::Color const& line_color,
						utils::Vector const& position,
						uint8_t line ) const;
	};
}