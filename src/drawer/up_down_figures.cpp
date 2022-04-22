//
// Created by claiff on 19.04.22.
//

#include "up_down_figures.hpp"

namespace drawer
{
	UpDownFigures::UpDownFigures( utils::Color const& background,
								  device::LedMatrix const& led_matrix,
								  effects::utils::Registrator < EffectType > const& registrator )
			: mBackground( background )
			, mLedMatrix( led_matrix )
			, mRegistrator( registrator )
			, mRedrawLed{60}
	{
		InitStates();

		mRedrawLed.SetTime();
	}

	//
	//Public methods
	//

	void UpDownFigures::ReDraw()
	{
		ApplyOnState();
		ApplyRedrawLed();
	}

	//
	//Private methods
	//

	void UpDownFigures::InitStates()
	{
		auto registrator_size = mRegistrator.Size();
		mState.reserve( registrator_size );
		mState.resize( registrator_size, State::NOT_SET_TIME );
	}

	void UpDownFigures::ApplyOnState()
	{
		for( auto i = 0; i < mRegistrator.Size(); ++i )
		{
			auto& effect = mRegistrator.Get();
			switch( mState[i] )
			{
				case State::NOT_SET_TIME:
					SetDelayState( effect, mState[i] );
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

	void UpDownFigures::ApplyRedrawLed()
	{
		if( mRedrawLed.IsSwitch())
		{
			mLedMatrix.ReDraw();
			mRedrawLed.SetTime();
		}
	}

	void UpDownFigures::SetDelayState( EffectType& effect, State& state ) const
	{
		effect.delay.SetTime();
		state = State::DELAY;
	}

	void UpDownFigures::ApplyDelay( EffectType& effect, State& state ) const
	{
		if( !effect.delay.IsSwitch())
		{
			return;
		}
		SetDurationState( effect, state );
	}

	void UpDownFigures::SetDurationState( EffectType& effect, State& state ) const
	{
		state = State::DURATION;
		effect.duration.SetTime();
	}

	void UpDownFigures::ApplyDuration( EffectType& effect, State& state )
	{
		auto& duration_policy = effect.duration;
		if( !duration_policy.IsSwitch())
		{
			return;
		}
		ApplyFigure( effect );

		duration_policy.SetTime();
	}

	void UpDownFigures::ApplyFigure(  UpDownFigures::EffectType const& effect )
	{
		auto& figure = effect.figure;
		IsFigureOnBottom( figure ) ? figure->ResetPositionY() : MoveFigure( figure );
	}

	bool UpDownFigures::IsFigureOnBottom( const figure::types::IFigure* figure ) const
	{
		return figure->IsFigureOut( mLedMatrix ) == figure::types::OutSide::DOWN;
	}

	void UpDownFigures::MoveFigure( figure::types::IFigurePtr const& figure )
	{
		static const utils::Vector DEFAULT_SPEED = {0, 1};

		figure->Move( DEFAULT_SPEED );
		ReDrawFigures();
	}

	void UpDownFigures::ReDrawFigures()
	{
		mLedMatrix.FillMatrix( mBackground );

		for( auto it = mRegistrator.Begin(); it < mRegistrator.End(); ++it )
		{
			(*it).figure->Draw( mLedMatrix );
		}
	}
}