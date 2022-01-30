#include "periphery/rcc_helper.hpp"
#include "drawer/effects/registrator.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/simple_color.hpp"

void FillEffects( drawer::effects::Registrator& registrator );

int main()
{
	static constexpr uint16_t TIME_SWITCH_MS = 1000;

	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	auto registrator_effects = drawer::effects::Registrator{};
	FillEffects( registrator_effects );

	auto cyclic_drawer = drawer::builder::Cyclic{}.Build( registrator_effects, rcc, TIME_SWITCH_MS );
	cyclic_drawer.Draw();

	while( true )
	{

	}
}

void FillEffects( drawer::effects::Registrator& registrator )
{
	auto red_light = new drawer::effects::SimpleColor{{0xFF, 0x00, 0x00}};
	registrator.Add(red_light);

	auto green_light = new drawer::effects::SimpleColor{{0x00, 0xFF, 0x00}};
	registrator.Add(green_light);

	auto blue_light = new drawer::effects::SimpleColor{{0x00, 0x00, 0xFF}};
	registrator.Add(blue_light);
}

