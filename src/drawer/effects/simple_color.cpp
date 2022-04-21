//
// Created by claiff on 29.01.2022.
//

#include "simple_color.hpp"


namespace drawer::effects
{
	//
	//Constructor
	//

	SimpleColor::SimpleColor( ::utils::Color const& color )
			: mColor( color )
	{

	}

	//
	//Public methods
	//

	void SimpleColor::Draw( device::LedMatrix& led_matrix ) const
	{
		led_matrix.FillMatrix(mColor, mBrightness);
		led_matrix.ReDraw();
	}

}