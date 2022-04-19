//
// Created by claiff on 18.04.22.
//

#include "circle.hpp"

namespace drawer::figure
{

	Circle::Circle( types::Position const& position, uint8_t size,
					types::Color const& color )
			: mPosition( position )
			, mSize((size < 2) ? size : 2 )
			, mColor( color )
	{

	}

	void Circle::SetPosition( types::Position const& position )
	{
		mPosition = position;
	}

	void Circle::SetColor( types::Color const& color )
	{
		mColor = color;
	}

	void Circle::Draw( device::LedMatrix& led_matrix )
	{
		//TODO FIX please it
		effects::utils::Coordinate_t position{mPosition.x, mPosition.y};
		Pixel_t line_color{mColor.red, mColor.green, mColor.blue};

		position.y -= mSize;
		for( uint8_t i = 0; i <= mSize; ++i )
		{
			led_matrix.FillHorizontalLine( position, line_color, 2 * i + 1 );
			led_matrix.ReDraw();
			position.y++;
			position.x--;
		}
		position.x++;
		for( auto i = mSize - 1; i >= 0; --i )
		{
			position.x++;
			led_matrix.FillHorizontalLine( position, line_color, 2 * i + 1 );
			led_matrix.ReDraw();
			position.y++;
		}
	}
}