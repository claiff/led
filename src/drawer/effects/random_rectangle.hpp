//
// Created by claiff on 01.02.2022.
//

#pragma once

#include "drawer/effects/types/ieffect.hpp"
#include "periphery/adc.hpp"
#include "utils/color.hpp"

namespace drawer::effects
{
	class RandomRectangle
			: public types::IEffect
	{
	public:
		RandomRectangle() = default;
		~RandomRectangle() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;

	private:
		[[nodiscard]] utils::Rectangle GetRandomRectangle() const;
		[[nodiscard]] ::utils::Color GetRandomColor() const;
		void RestrictRectangle( device::LedMatrix const& led_matrix, utils::Rectangle& rectangle ) const;
		void RestrictColor( ::utils::Color& color, uint8_t max_color ) const;
		[[nodiscard]] uint16_t RestrictPartColor( float part_color, uint8_t max_color ) const;

		periphery::Adc mAdc;

	};
}