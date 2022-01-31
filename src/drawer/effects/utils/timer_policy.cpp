//
// Created by claiff on 31.01.2022.
//

#include "timer_policy.hpp"
#include "periphery/system_timer_irq.hpp"

namespace drawer::effects::utils
{
	TimerPolicy::TimerPolicy( uint16_t time_ms )
			: mTimerMs( time_ms )
	{

	}

	void TimerPolicy::SetTime()
	{
		mBeginTime = periphery::SystemTimerIrq::GetTime();
	}

	bool TimerPolicy::IsSwitch() const
	{
		auto current_time = periphery::SystemTimerIrq::GetTime();
		return current_time >= mBeginTime + mTimerMs;
	}
}