//
// Created by claiff on 18.04.22.
//

#include "circle.hpp"

namespace drawer::figure
{
	static constexpr uint8_t MAX_SIZE_CIRCLE = 3;

	Circle::Circle( types::Vector const& position, uint8_t size,
					types::Color color )
			: mPosition( position )
			, mSize((size < MAX_SIZE_CIRCLE) ? size : MAX_SIZE_CIRCLE )
			, mColor( color )
	{

	}

	//
	//Public methods
	//

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
		//TODO FIX please it
		DrawUpCircle( led_matrix );
		DrawDownCircle( led_matrix );
	}

	void Circle::Move( types::Vector const& position )
	{
		mPosition += position;
	}

	types::OutSide Circle::IsFigureOut( device::LedMatrix const& led_matrix ) const
	{
		auto is_x_out = IsXOut( led_matrix );
		if( is_x_out != types::OutSide::NONE )
		{
			return is_x_out;
		}
		auto is_y_out = IsYOut( led_matrix );
		if( is_y_out != types::OutSide::NONE )
		{
			return is_y_out;
		}
		return types::OutSide::NONE;
	}

	void Circle::ResetPositionX()
	{
		mPosition.x = -mSize;
	}

	void Circle::ResetPositionY()
	{
		mPosition.y = -mSize;
	}

	//
	//Private methods
	//

	void Circle::DrawUpCircle( device::LedMatrix& led_matrix ) const
	{
		Pixel_t line_color{mColor.red, mColor.green, mColor.blue};
		effects::utils::Coordinate_t position{mPosition.x, mPosition.y};

		position.y -= mSize;
		for( uint8_t i = 0; i <= mSize; ++i )
		{
			led_matrix.FillHorizontalLine( position, line_color, 2 * i + 1 );
			led_matrix.ReDraw();
			position.y++;
			position.x--;
		}
	}

	void Circle::DrawDownCircle( device::LedMatrix& led_matrix ) const
	{
		Pixel_t line_color{mColor.red, mColor.green, mColor.blue};
		effects::utils::Coordinate_t position{mPosition.x, mPosition.y};

		position.x++;
		for( uint8_t i = mSize - 1; i >= 0; --i )
		{
			position.x++;
			led_matrix.FillHorizontalLine( position, line_color, 2 * i + 1 );
			led_matrix.ReDraw();
			position.y++;
		}
	}

	types::OutSide Circle::IsYOut( device::LedMatrix const& led_matrix ) const
	{
		if( mPosition.y + mSize <= 0 )
		{
			return types::OutSide::UP;
		}
		else if( mPosition.y + mSize > led_matrix.GetWidth())
		{
			return types::OutSide::DOWN;
		}
		return types::OutSide::NONE;
	}

	types::OutSide Circle::IsXOut( device::LedMatrix const& led_matrix ) const
	{
		if( mPosition.x + mSize <= 0 )
		{
			return types::OutSide::LEFT;
		}
		else if( mPosition.x + mSize > led_matrix.GetHeight())
		{
			return types::OutSide::RIGHT;
		}
		return types::OutSide::NONE;
	}
}