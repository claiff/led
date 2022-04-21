//
// Created by claiff on 18.04.22.
//

#pragma once

#include "types/ifigure.hpp"
#include "device/led_matrix.hpp"
#include "utils/struct.hpp"

namespace drawer::figure
{
	class Circle
			: public types::IFigure
	{
	public:
		Circle( types::Vector const& position, uint8_t size,
				types::Color const& color );
		~Circle() override = default;

		void SetPosition( types::Vector const& position ) override;
		void SetColor( types::Color const& color ) override;
		void Draw( device::LedMatrix& led_matrix ) override;
		void Move( types::Vector const& position ) override;
		[[nodiscard]] types::OutSide IsFigureOut( device::LedMatrix const& led_matrix ) const override;
		void ResetPositionX() override;
		void ResetPositionY() override;
	private:
		[[nodiscard]] types::OutSide IsXOut( device::LedMatrix const& led_matrix ) const;
		[[nodiscard]] types::OutSide IsYOut( device::LedMatrix const& led_matrix ) const;

		types::Vector mPosition;
		uint8_t mSize;
		types::Color mColor;

		void DrawLines( device::LedMatrix& led_matrix, const Pixel_t& line_color,
						const effects::utils::Coordinate_t& position,
						uint8_t line ) const;
	};
}