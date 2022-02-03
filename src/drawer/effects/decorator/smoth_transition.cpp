//
// Created by claiff on 31.01.2022.
//

#include "smoth_transition.hpp"

static constexpr uint8_t COUNT_TRANSITIONS = 10;

namespace drawer::effects::decorator
{

	SmoothTransition::SmoothTransition( utils::TimerPolicy const& timer_main,
										utils::TimerPolicy const& timer_trans )
			: mTimerMain( timer_main )
			, mTimerTrans( timer_trans )
	{

	}

	void SmoothTransition::Draw( device::LedMatrix& led_matrix ) const
	{
		IncreaseBrightness( led_matrix );

		mBase->Draw(led_matrix);
		WaitColorProcessing( mTimerMain );

		DecreaseBrightness( led_matrix );
	}

	void SmoothTransition::IncreaseBrightness( device::LedMatrix& led_matrix ) const
	{
		static constexpr bool IS_NEED_INCREASE = true;
		static constexpr uint8_t MAX_BRIGHT_VALUE = 0xFF;
		static constexpr uint8_t START_BRIGHT_VALUE = 0x00;

		uint8_t brightness = START_BRIGHT_VALUE;
		auto step = (MAX_BRIGHT_VALUE - brightness) / COUNT_TRANSITIONS;

		ProcessBrightness( led_matrix, brightness, step, IS_NEED_INCREASE );
	}

	void SmoothTransition::DecreaseBrightness( device::LedMatrix& led_matrix ) const
	{
		static constexpr bool IS_NEED_INCREASE = false;
		static constexpr uint8_t MIN_BRIGHT_VALUE = 0x00;
		static constexpr uint8_t END_BRIGHT_VALUE = 0xFF;

		uint8_t brightness = END_BRIGHT_VALUE;
		auto step = (brightness - MIN_BRIGHT_VALUE) / COUNT_TRANSITIONS;

		ProcessBrightness( led_matrix, brightness, step, IS_NEED_INCREASE );
	}

	void SmoothTransition::ProcessBrightness( device::LedMatrix& led_matrix, uint8_t brightness, uint8_t step,
											  bool is_increase ) const
	{
		for( auto number_transition = 0; number_transition < COUNT_TRANSITIONS; ++number_transition )
		{
			WaitColorProcessing( mTimerTrans );
			mBase->SetBrightness(brightness);
			mBase->Draw(led_matrix);
			is_increase ? (brightness += step) : (brightness -= step);
			led_matrix.ReDraw();
		}
		//FIXME костыль при уменьшении яркости, яркость в 0 может не упасть
		if( brightness != 0 && !is_increase )
		{
			WaitColorProcessing( mTimerTrans );
			mBase->SetBrightness(0);
			mBase->Draw(led_matrix);
			led_matrix.ReDraw();
		}
	}

	void SmoothTransition::WaitColorProcessing( utils::TimerPolicy& timer ) const
	{
		timer.SetTime();
		while( !timer.IsSwitch());
	}
}