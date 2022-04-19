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
		explicit Circle( types::Position const& position, uint8_t size,
						 types::Color const& color );
		~Circle() override = default;

		void SetPosition( types::Position const& position ) override;
		void SetColor( types::Color const& color ) override;
		void Draw( device::LedMatrix& led_matrix ) override;
	private:
		types::Position mPosition;
		uint8_t mSize;
		types::Color mColor;
	};
}