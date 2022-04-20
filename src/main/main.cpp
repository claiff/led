#include "periphery/rcc_helper.hpp"

#include "drawer/figure/circle.hpp"


int main()
{
	static constexpr uint16_t TIME_SWITCH_MS = 1000;

	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	Pixel_t red = {0x10, 0x00, 0x00};
	Pixel_t green = {0x00, 0x10, 0x00};
	Pixel_t blue = {0x00, 0x00, 0x10};

	auto led_matrix = device::LedMatrix{16, 16, rcc};
	led_matrix.FillMatrix( blue );
	led_matrix.ReDraw();

	drawer::figure::Circle circle{{5, 5}, 2,
								  {0x00, 100, 0x00}};
	circle.Draw( led_matrix );

	while( true )
	{

	}
}

