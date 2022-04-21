//
// Created by claiff on 02.02.2022.
//

#pragma once

#include "drawer/effects/random_rectangle.hpp"

namespace drawer::effects::decorator
{
	class FillRandomFigure
			: public RandomRectangle
	{
	public:
		explicit FillRandomFigure( ::utils::Color const& background_color );
		~FillRandomFigure() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		::utils::Color mBackgroundColor;
	};
}
