//
// Created by claiff on 01.02.2022.
//

#include "random_rectangle.hpp"
#include "utils/figures.hpp"


namespace drawer::effects
{
	void RandomRectangle::Draw( device::LedMatrix& led_matrix ) const
	{
		auto rectangle = GetRandomRectangle();
		auto color = GetRandomColor();

		RestrictRectangle( led_matrix, rectangle );
		RestrictColor( color, 0x35 );

		led_matrix.FillRectangle( rectangle, color, mBrightness );
	}

	utils::Rectangle RandomRectangle::GetRandomRectangle() const
	{
		::utils::Vector position{};
		::utils::Vector size{};

		auto adc_data = mAdc.GetValue();
		position.x = adc_data & 0x0F;
		position.y = (adc_data & 0xF0) >> 4;

		size.x = adc_data & 0xF00 >> 8;
		size.y = (adc_data & 0xF000) >> 12;

		return {position, size};
	}

	void RandomRectangle::RestrictRectangle( device::LedMatrix const& led_matrix, utils::Rectangle& rectangle ) const
	{
		auto max_width = led_matrix.GetWidth();
		auto max_height = led_matrix.GetHeight();

		if( rectangle.mSize.x == 0 )
		{
			rectangle.mSize.x++;
		}
		if( rectangle.mSize.y == 0 )
		{
			rectangle.mSize.y++;
		}

		if( rectangle.mPosition.x + rectangle.mSize.x >= max_width )
		{
			rectangle.mSize.x = max_width - rectangle.mPosition.x;
		}

		if( rectangle.mPosition.y + rectangle.mSize.y >= max_height )
		{
			rectangle.mSize.y = max_height - rectangle.mPosition.y;
		}
	}

	::utils::Color RandomRectangle::GetRandomColor() const
	{
		::utils::Color result{};

		auto adc_data = mAdc.GetValue();
		result.red = adc_data & 0xFF;
		result.green = (adc_data & 0xFF00) >> 8;
		result.blue = (adc_data & 0xFF0000) >> 16;

		return result;
	}

	void RandomRectangle::RestrictColor( ::utils::Color& color, uint8_t max_color ) const
	{
		if( color.red > max_color )
		{
			auto value = RestrictPartColor( color.red, max_color );
			color.red = value;
		}
		if( color.green > max_color )
		{
			auto value = RestrictPartColor( color.green, max_color );
			color.green = value;
		}
		if( color.blue > max_color )
		{
			auto value = RestrictPartColor( color.blue, max_color );
			color.blue = value;
		}
	}

	uint16_t RandomRectangle::RestrictPartColor( float part_color, uint8_t max_color ) const
	{
		float result = (part_color / 0xFF) * max_color;
		return static_cast<uint16_t>(result);
	}


}