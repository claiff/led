#include "periphery/rcc_helper.hpp"
#include "device/led_matrix.hpp"

int main()
{
	static constexpr uint8_t WIDTH = 16;
	static constexpr uint8_t HEIGHT = 16;

	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	auto led_matrix = device::LedMatrix{HEIGHT, WIDTH, rcc};

	led_matrix.ReDraw();
	while( 1 )
	{

	}
}
