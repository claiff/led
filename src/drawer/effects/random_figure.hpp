//
// Created by claiff on 01.02.2022.
//

#pragma once

#include "drawer/effects/types/ieffect.hpp"
#include "utils/struct.hpp"
#include "periphery/adc.hpp"

namespace drawer::effects
{
	enum class Figure
	{
		Rectangle,
		Circle
	};

	class RandomFigure
			: public types::IEffect
	{
	public:
		explicit RandomFigure( Pixel_t const& background_color );
		~RandomFigure() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;

	private:
		utils::Rectangle GetRandomRectangle() const;
		Pixel_t GetRandomColor() const;
		void RestrictRectangle( device::LedMatrix const& led_matrix, utils::Rectangle& rectangle ) const;

		void RestrictColor( Pixel_t& color, uint8_t max_color ) const;

		periphery::Adc mAdc;
		Pixel_t mBackgroundColor;
		uint16_t RestrictPartColor( float part_color, uint8_t max_color ) const;
	};
}