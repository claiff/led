#include "periphery/rcc_helper.hpp"
#include "drawer/effects/utils/registrator.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/decorator/smoth_transition.hpp"
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

	auto policy = drawer::effects::utils::TimerPolicy{TIME_SWITCH_MS};
	auto red_light = new drawer::effects::decorator::SmoothTransition{{0x0A, 0x00, 0x00}, policy};
	registrator.Add(red_light);

	auto green_light = new drawer::effects::decorator::SmoothTransition{{0x00, 0x0A, 0x00}, policy};
	registrator.Add(green_light);

	auto blue_light = new drawer::effects::decorator::SmoothTransition{{0x00, 0x00, 0x0A}, policy};
	registrator.Add(blue_light);
}

