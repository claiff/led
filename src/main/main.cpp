#include "periphery/rcc_helper.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/decorator/smoth_transition.hpp"
#include "drawer/effects/decorator/fill_random_figure.hpp"
#include "drawer/effects/utils/timer_policy.hpp"
#include <memory>
#include "drawer/figure/circle.hpp"

void FillEffects( drawer::effects::utils::Registrator& registrator );

drawer::effects::types::IEffectPtr GetColorEffect( Pixel_t const& color_start, Pixel_t const& color_end );

int main()
{
	static constexpr uint16_t TIME_SWITCH_MS = 1000;

	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	Pixel_t red = {0x10, 0x00, 0x00};
	Pixel_t green = {0x00, 0x10, 0x00};
	Pixel_t blue = {0x00, 0x00, 0x10};

	auto led_matrix = device::LedMatrix{16, 16, rcc};
	led_matrix.FillMatrix( blue );
	led_matrix.ReDraw();

	drawer::figure::Circle circle{{5,    5},
								  {0x00, 100, 0x00}};
	circle.Draw(led_matrix);

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
	auto color_gradient = std::make_shared < drawer::effects::decorator::FillRandomFigure >( color_start );
	smooth_transition->Apply( color_gradient );
	return smooth_transition;
}

