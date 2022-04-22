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
		struct EffectType
		{
			effects::utils::TimerPolicy delay;
			effects::utils::TimerPolicy duration;
			figure::types::IFigurePtr figure;
		};
		using EffectType = struct EffectType;

		UpDownFigures( utils::Color const& background, device::LedMatrix const& led_matrix,
					   effects::utils::Registrator < EffectType > const& registrator );
		~UpDownFigures() override = default;

		void ReDraw() override;
	private:
		void SetDelayState( EffectType& effect, State& state ) const;
		void ApplyDelay( EffectType& effect, State& state ) const;
		void SetDurationState( EffectType& effect, State& state ) const;
		void ApplyDuration( EffectType& effect, State& state );
		void ApplyFigure( const EffectType& effect );
		bool IsFigureOnBottom( figure::types::IFigure const* figure ) const;
		void MoveFigure( figure::types::IFigurePtr const& figure );
		void ReDrawFigures();

		utils::Color mBackground;
		effects::utils::Registrator < EffectType > mRegistrator;
		std::vector < State > mState;
		device::LedMatrix mLedMatrix;
		effects::utils::TimerPolicy mRedrawLed;

		void ApplyOnState();
		void ApplyRedrawLed();
		void InitStates();
	};
}
