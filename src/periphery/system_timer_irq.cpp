//
// Created by claiff on 31.01.2022.
//

#include "system_timer_irq.hpp"

#include "specific/stm32f103xb.h"

namespace periphery
{
	static constexpr uint32_t DEFAULT_TIME = 0;
	SystemTimerIrq* SystemTimerIrq::mInstance = nullptr;
	uint32_t SystemTimerIrq::mTime = DEFAULT_TIME;

	SystemTimerIrq::SystemTimerIrq()
	{
		SysTick->LOAD = 72000000UL / 1000 - 1;
		SysTick->VAL = 72000000UL / 1000 - 1;
		SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
						SysTick_CTRL_TICKINT_Msk |
						SysTick_CTRL_ENABLE_Msk;
	}

	void SystemTimerIrq::SetTime( uint32_t time )
	{
		GetInstance()->mTime = time;
	}

	void SystemTimerIrq::IncrementTime()
	{
		GetInstance()->mTime++;
	}

	uint32_t SystemTimerIrq::GetTime()
	{
		return GetInstance()->mTime;
	}

	SystemTimerIrq::~SystemTimerIrq()
	{
		delete mInstance;
	}

	SystemTimerIrq* SystemTimerIrq::GetInstance()
	{
		if( !mInstance )
		{
			mInstance = new SystemTimerIrq();
		}
		return mInstance;
	}


	extern "C" void SysTick_Handler()
	{
		SystemTimerIrq::IncrementTime();
	}
}