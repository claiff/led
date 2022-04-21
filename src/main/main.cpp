#include "periphery/rcc_helper.hpp"

#include "drawer/figure/circle.hpp"

#include "drawer/up_down_figures.hpp"
#include "drawer/effects/utils/registrator.hpp"

using Registrator_t = drawer::effects::utils::Registrator < drawer::UpDownFigures::EffectType >;

Registrator_t GetRegistrator();
drawer::UpDownFigures::EffectType
GetEffect( uint16_t time_delay, uint16_t time_duration, uint8_t size, drawer::figure::types::Color const& color, drawer::figure::types::Vector const& position );

int main()
{
	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	Pixel_t red = {0x10, 0x00, 0x00};
	Pixel_t green = {0x00, 0x10, 0x00};
	Pixel_t blue = {0x00, 0x00, 0x10};

	auto led_matrix = device::LedMatrix{16, 16, rcc};
	//led_matrix.FillMatrix( blue );

	//led_matrix.ReDraw();

	auto registrator = GetRegistrator();
	drawer::UpDownFigures up_down{ {0x00, 0x00, 0x10}, led_matrix, registrator};

	while( true )
	{
		up_down.ReDraw();
	}
}

Registrator_t GetRegistrator()
{
	Registrator_t result;
	drawer::figure::types::Color blue = {0x00, 0x10, 0x00};
	drawer::figure::types::Color red = {0x10, 0x00, 0x00};
	//TODO Время умножено на 2
	auto effect = GetEffect( 500, 100, 3, blue, {5,0} );
	result.Add( effect );
	effect = GetEffect( 200, 100, 2, red, {9,0}  );
	result.Add( effect );
	return result;
}

drawer::UpDownFigures::EffectType
GetEffect( uint16_t time_delay, uint16_t time_duration, uint8_t size, drawer::figure::types::Color const& color, drawer::figure::types::Vector const& position )
{
	using namespace drawer::effects::utils;

	auto circle = new drawer::figure::Circle{position, size, color};
	circle->ResetPositionY();

	TimerPolicy delay{time_delay};
	TimerPolicy duration{time_duration};

	return {delay, duration, circle};
}

