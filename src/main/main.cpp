#include "periphery/rcc_helper.hpp"
#include "drawer/builder/cyclic.hpp"
#include "drawer/effects/random_figure.hpp"

void FillEffects( drawer::effects::utils::Registrator& registrator );

int main()
{
	static constexpr uint16_t TIME_SWITCH_MS = 200;

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
	auto random_figure = new drawer::effects::RandomFigure{};
	registrator.Add(random_figure);
}

