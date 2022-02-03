#include "periphery/rcc_helper.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/decorator/smoth_transition.hpp"
#include "drawer/effects/simple_color.hpp"
#include "drawer/effects/utils/timer_policy.hpp"
#include <memory>

void FillEffects( drawer::effects::utils::Registrator& registrator );

drawer::effects::types::IEffectPtr GetColorEffect( Pixel_t const& color );

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
	registrator.Add( GetColorEffect( {0x0A, 0x00, 0x00} ) );
	registrator.Add( GetColorEffect( {0x00, 0x0A, 0x00} ) );
	registrator.Add( GetColorEffect( {0x00, 0x00, 0x0A} ) );
}

drawer::effects::types::IEffectPtr GetColorEffect( Pixel_t const& color )
{
	drawer::effects::utils::TimerPolicy timer_policy_main{500};
	drawer::effects::utils::TimerPolicy timer_policy_trans{20};

	auto smooth_transition = new drawer::effects::decorator::SmoothTransition{timer_policy_main, timer_policy_trans};
	auto simple_color = std::make_shared <drawer::effects::SimpleColor>(color);
	smooth_transition->Apply(simple_color);
	return smooth_transition;
}

