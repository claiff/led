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
		explicit Circle( types::Vector const& position, uint8_t size,
						 types::Color color );
		~Circle() override = default;

		void SetPosition( types::Vector const& position ) override;
		void SetColor( types::Color const& color ) override;
		void Draw( device::LedMatrix& led_matrix ) override;
		void Move( const types::Vector& position ) override;
		[[nodiscard]] types::OutSide IsFigureOut( device::LedMatrix const& led_matrix ) const override;
		void ResetPositionX() override;
		void ResetPositionY() override;
	private:
		void DrawUpCircle( device::LedMatrix& led_matrix ) const;
		void DrawDownCircle( device::LedMatrix& led_matrix ) const;
		[[nodiscard]] types::OutSide IsXOut( device::LedMatrix const& led_matrix ) const;
		[[nodiscard]] types::OutSide IsYOut( device::LedMatrix const& led_matrix ) const;

		types::Vector mPosition;
		uint8_t mSize;
		types::Color mColor;

	};
}