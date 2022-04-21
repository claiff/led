//
// Created by claiff on 19.04.22.
//

#include "up_down_figures.hpp"

namespace drawer
{
	UpDownFigures::UpDownFigures( figure::types::Color const& background,
								  device::LedMatrix const& led_matrix,
								  effects::utils::Registrator < EffectType > const& registrator )
			: mBackground( background )
			, mLedMatrix( led_matrix )
			, mRegistrator( registrator )
	{
		auto registrator_size = mRegistrator.Size();
		mState.reserve( registrator_size );
		mState.resize( registrator_size, State::NOT_SET_TIME );
		Pixel_t color{mBackground.red, mBackground.green, mBackground.blue};
		mLedMatrix.FillMatrix( color );
		mLedMatrix.ReDraw();
	}

	void UpDownFigures::ReDraw()
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

	void UpDownFigures::SetDelayState( EffectType& effect, State& state )
	{
		effect.delay.SetTime();
		state = State::DELAY;
	}

	void UpDownFigures::ApplyDelay( EffectType& effect, State& state )
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
		auto& figure = effect.figure;
		if( IsFigureOnBottom( figure ))
		{
			figure->ResetPositionY();
		}
		else
		{
			MoveFigure( figure );
		}

		duration_policy.SetTime();
	}

	bool UpDownFigures::IsFigureOnBottom( const figure::types::IFigure* figure ) const
	{
		return figure->IsFigureOut( mLedMatrix ) == figure::types::OutSide::DOWN;
	}

	void UpDownFigures::MoveFigure( figure::types::IFigurePtr const& figure )
	{
		static const figure::types::Vector DEFAULT_SPEED = {0, 1};

		figure->Move( DEFAULT_SPEED );
		Pixel_t color{mBackground.red, mBackground.green, mBackground.blue};
		mLedMatrix.FillMatrix( color );
		figure->Draw( mLedMatrix );
		mLedMatrix.ReDraw();
	}
}