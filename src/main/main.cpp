#include "periphery/rcc_helper.hpp"

#include "drawer/figure/circle.hpp"

#include "drawer/up_down_figures.hpp"
#include "drawer/effects/utils/registrator.hpp"

using Registrator_t = drawer::effects::utils::Registrator < drawer::UpDownFigures::EffectType >;

Registrator_t GetRegistrator();
drawer::UpDownFigures::EffectType GetEffect( uint16_t time_delay, uint16_t time_duration );

int main()
{
	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	Pixel_t red = {0x10, 0x00, 0x00};
	Pixel_t green = {0x00, 0x10, 0x00};
	Pixel_t blue = {0x00, 0x00, 0x10};

	auto led_matrix = device::LedMatrix{16, 16, rcc};
	led_matrix.FillMatrix( blue );
	led_matrix.ReDraw();

	auto registrator = GetRegistrator();
	drawer::UpDownFigures up_down{led_matrix, registrator};

	while( true )
	{
		up_down.ReDraw();
	}
}

Registrator_t GetRegistrator()
{
	Registrator_t result;
	auto effect = GetEffect( 500, 500 );
	result.Add( effect );
	return result;
}

drawer::UpDownFigures::EffectType GetEffect( uint16_t time_delay, uint16_t time_duration )
{
	using namespace drawer::effects::utils;

	auto circle = new drawer::figure::Circle{{5, 5}, 1, {0x00, 0x10, 0x00}};

	TimerPolicy delay{time_delay};
	TimerPolicy duration{time_duration};
	return {delay, duration, circle};
}

