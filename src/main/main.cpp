#include "periphery/rcc_helper.hpp"
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
	drawer::effects::utils::TimerPolicy timer_policy_main{500};

	drawer::effects::utils::TimerPolicy timer_policy_trans{20};

	auto smooth_color_red = new drawer::effects::decorator::SmoothTransition{{0x0A, 0x00, 0x00}, timer_policy_main,
																		 timer_policy_trans};

	auto smooth_color_green = new drawer::effects::decorator::SmoothTransition{{0x00, 0x0A, 0x00}, timer_policy_main,
																			 timer_policy_trans};

	auto smooth_color_blue = new drawer::effects::decorator::SmoothTransition{{0x00, 0x00, 0x0A}, timer_policy_main,
																			 timer_policy_trans};
	registrator.Add( smooth_color_red );
	registrator.Add( smooth_color_green );
	registrator.Add( smooth_color_blue );
}

