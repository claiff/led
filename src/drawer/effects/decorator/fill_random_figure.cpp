//
// Created by claiff on 02.02.2022.
//

#include "fill_random_figure.hpp"

namespace drawer::effects::decorator
{

	FillRandomFigure::FillRandomFigure( const Pixel_t& background_color )
			: mBackgroundColor( background_color )
	{

	}

	void FillRandomFigure::Draw( device::LedMatrix& led_matrix ) const
	{
		led_matrix.FillMatrix( mBackgroundColor );

		RandomFigure::Draw( led_matrix );
	}
}