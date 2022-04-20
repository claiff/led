//
// Created by claiff on 19.04.22.
//

#pragma once

#include "effects/utils/registrator.hpp"
#include "effects/utils/timer_policy.hpp"
#include "figure/types/ifigure.hpp"
#include "types/idrawer.hpp"

namespace drawer
{
	struct EffectType
	{
		effects::utils::TimerPolicy delay;
		effects::utils::TimerPolicy duration;
		figure::types::IFigurePtr figure;
		uint8_t speed = 1;
	};
	using EffectType = struct EffectType;

	enum class State
	{
		NOT_SET_TIME,
		DELAY,
		DURATION
	};

	class UpDownFigures
			: public types::IDrawer
	{
	public:
		explicit UpDownFigures( effects::utils::Registrator < EffectType > const& registrator );
		~UpDownFigures() override = default;

		void ReDraw() override;
	private:
		void SetTimer( EffectType* effect, State& state );
		void ApplyDelay( EffectType* effect, State& state );
		void ApplyDuration( EffectType* effect, State& state );
		effects::utils::Registrator < EffectType > mRegistrator;
		std::vector < State > mState;
	};
}
