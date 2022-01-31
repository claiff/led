#include "periphery/rcc_helper.hpp"
#include "drawer/effects/utils/registrator.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/color_gradient.hpp"
#include "drawer/effects/utils/timer_policy.hpp"

void FillEffects( drawer::effects::utils::Registrator& registrator );

int main()
{
	static constexpr uint16_t TIME_SWITCH_MS = 1000;

	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	auto registrator_effects = drawer::effects::utils::Registrator{};
	FillEffects( registrator_effects );

	auto cyclic_drawer = drawer::builder::Cyclic{}.Build( registrator_effects, rcc, TIME_SWITCH_MS );
	cyclic_drawer.Draw();

	while( true )
	{

	}
}

void FillEffects( drawer::effects::utils::Registrator& registrator )
{
	static constexpr uint16_t TIME_SWITCH_MS = 30;

	auto red_light = new drawer::effects::ColorGradient{{0x20, 0x00, 0x20},{0x00, 0x20, 0x00}, drawer::effects::GradientStyle::Horizontal};
	registrator.Add(red_light);
}

