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

	drawer::figure::Circle circle{{2, -2}, 3,
								  {0x00, 100, 0x00}};
	circle.Draw( led_matrix );
	led_matrix.ReDraw();
	volatile auto result = circle.IsFigureOut();

	circle.Move({0,5});
	led_matrix.FillMatrix( blue );
	circle.Draw(led_matrix);
	led_matrix.ReDraw();

	led_matrix.FillMatrix( blue );
	circle.ResetPositionY();
	circle.Draw(led_matrix);
	led_matrix.ReDraw();

	result = circle.IsFigureOut();

	led_matrix.FillMatrix( blue );
	circle.Move({0,1});
	circle.Draw(led_matrix);
	led_matrix.ReDraw();
	while( true )
	{
	}
}

