//
// Created by claiff on 18.04.22.
//

#include "circle.hpp"

namespace drawer::figure
{
	static constexpr uint8_t MAX_SIZE_CIRCLE = 3;

	Circle::Circle( types::Vector const& position, uint8_t size,
					types::Color const& color )
			: mPosition( position )
			, mSize((size < MAX_SIZE_CIRCLE) ? size : MAX_SIZE_CIRCLE )
			, mColor( color )
	{

	}

	void Circle::SetPosition( types::Vector const& position )
	{
		mPosition = position;
	}

	void Circle::SetColor( types::Color const& color )
	{
		mColor = color;
	}

	void Circle::Draw( device::LedMatrix& led_matrix )
	{
		int8_t init_width = 2 * (mSize - 1) + 1;
		Pixel_t line_color{mColor.red, mColor.green, mColor.blue};
		effects::utils::Coordinate_t position{mPosition.x, mPosition.y};
		//TODO FIX please it
		for( uint8_t i = 0; i < mSize; ++i )
		{
			DrawLines( led_matrix, line_color, position, i );
		}
		led_matrix.ReDraw();
	}

	void Circle::DrawLines( device::LedMatrix& led_matrix, const Pixel_t& line_color,
							const effects::utils::Coordinate_t& position, uint8_t line ) const
	{
		for( uint8_t j = 0; j < mSize - line; ++j )
		{
			led_matrix.DrawPixel( position.x - j, position.y + line, line_color );
			led_matrix.DrawPixel( position.x + j, position.y + line, line_color );

			led_matrix.DrawPixel( position.x - j, position.y - line, line_color );
			led_matrix.DrawPixel( position.x + j, position.y - line, line_color );
		}
	}

	void Circle::Move( types::Vector const& position )
	{
		mPosition += position;
	}

	bool Circle::IsFigureOut() const
	{
		return IsXOut() && IsYOut();
	}

	bool Circle::IsYOut() const
	{
		return mPosition.y + mSize <= 0;
	}

	bool Circle::IsXOut() const
	{
		return mPosition.x + mSize <= 0;
	}

	void Circle::ResetPositionX()
	{
		mPosition.x = -mSize;
	}

	void Circle::ResetPositionY()
	{
		mPosition.y = -mSize;
	}
}