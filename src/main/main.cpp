#include "periphery/rcc_helper.hpp"

#include "drawer/figure/circle.hpp"

#include "drawer/up_down_figures.hpp"
#include "drawer/effects/utils/registrator.hpp"

using Registrator_t = drawer::effects::utils::Registrator < drawer::UpDownFigures::EffectType >;

Registrator_t GetRegistrator();
drawer::UpDownFigures::EffectType
GetEffect( uint16_t time_delay, uint16_t time_duration, uint8_t size, utils::Color const& color, utils::Vector const& position );

int main()
{
	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	utils::Color red = {0x10, 0x00, 0x00};
	utils::Color green = {0x00, 0x10, 0x00};
	utils::Color blue = {0x00, 0x00, 0x10};

	auto led_matrix = device::LedMatrix{16, 16, rcc};

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
	utils::Color green = {0x00, 0x10, 0x00};
	utils::Color red = {0x10, 0x00, 0x00};

	//TODO Время умножено на 2
	auto effect = GetEffect( 300, 500, 3, green, {5, 0} );
	result.Add( effect );
	effect = GetEffect( 500, 50, 2, red, {9,0}  );
	result.Add( effect );
	effect = GetEffect( 500, 100, 1, red, {13,0}  );
	result.Add( effect );
	return result;
}

drawer::UpDownFigures::EffectType
GetEffect( uint16_t time_delay, uint16_t time_duration, uint8_t size, utils::Color const& color, utils::Vector const& position )
{
	using namespace drawer::effects::utils;

	auto circle = new drawer::figure::Circle{position, size, color};
	circle->ResetPositionY();

	TimerPolicy delay{time_delay};
	TimerPolicy duration{time_duration};

	return {delay, duration, circle};
}

