//
// Created by claiff on 19.04.22.
//

#include "up_down_figures.hpp"

namespace drawer
{
	UpDownFigures::UpDownFigures( effects::utils::Registrator < EffectType > const& registrator )
			: mRegistrator( registrator )
	{
		auto registrator_size = mRegistrator.Size();
		mState.reserve( registrator_size );
		mState.resize( registrator_size, State::NOT_SET_TIME );

	}

	void UpDownFigures::ReDraw()
	{
		for( auto i = 0; i < mRegistrator.Size(); ++i )
		{
			auto effect = mRegistrator.Get();
			switch( mState[i] )
			{
				case State::NOT_SET_TIME:
					SetTimer( effect, mState[i] );
					break;
				case State::DELAY:
					ApplyDelay( effect, mState[i] );
					break;
				case State::DURATION:
					ApplyDuration( effect, mState[i] );
					break;
				default:
					continue;
			}
		}
	}

	void UpDownFigures::SetTimer( EffectType* effect, State& state )
	{
		effect->delay.SetTime();
		state = State::DELAY;
	}

	void UpDownFigures::ApplyDelay( EffectType* effect, State& state )
	{
		if( !effect->delay.IsSwitch())
		{
			return;
		}
		state = State::DURATION;
	}

	void UpDownFigures::ApplyDuration( EffectType* effect, State& state )
	{
		if( !effect->duration.IsSwitch())
		{
			return;
		}
		effect->figure->Move( {0, effect->speed} );
	}
}