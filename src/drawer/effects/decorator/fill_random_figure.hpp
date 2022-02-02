//
// Created by claiff on 02.02.2022.
//

#pragma once

#include "drawer/effects/random_figure.hpp"

namespace drawer::effects::decorator
{
	class FillRandomFigure
			: public RandomFigure
	{
	public:
		explicit FillRandomFigure( Pixel_t const& background_color );
		~FillRandomFigure() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		Pixel_t mBackgroundColor;
	};
}
