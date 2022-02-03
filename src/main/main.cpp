#include "periphery/rcc_helper.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/decorator/smoth_transition.hpp"
#include "drawer/effects/decorator/fill_random_figure.hpp"
#include "drawer/effects/utils/timer_policy.hpp"
#include <memory>

void FillEffects( drawer::effects::utils::Registrator& registrator );

drawer::effects::types::IEffectPtr GetColorEffect( Pixel_t const& color_start, Pixel_t const& color_end );

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
	Pixel_t red = {0x10, 0x00, 0x00};
	Pixel_t green = {0x00, 0x10, 0x00};
	Pixel_t blue = {0x00, 0x00, 0x10};

	registrator.Add( GetColorEffect( red, green ));
	//registrator.Add( GetColorEffect( green, blue ));
	//registrator.Add( GetColorEffect( blue, red ));
}

drawer::effects::types::IEffectPtr GetColorEffect( Pixel_t const& color_start, Pixel_t const& color_end )
{
	drawer::effects::utils::TimerPolicy timer_policy_main{500};
	drawer::effects::utils::TimerPolicy timer_policy_trans{20};

	auto smooth_transition = new drawer::effects::decorator::SmoothTransition{timer_policy_main, timer_policy_trans};
	auto color_gradient = std::make_shared < drawer::effects::decorator::FillRandomFigure >(color_start);
	smooth_transition->Apply( color_gradient );
	return smooth_transition;
}

