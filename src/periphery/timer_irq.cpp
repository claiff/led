//
// Created by claiff on 28.01.2022.
//

#include "timer_irq.hpp"

namespace periphery
{
	TimerIRQ* TimerIRQ::mInstance = nullptr;

	periphery::TimerIRQ::TimerIRQ( periphery::PWM* pwm )
			: mPwm( pwm )
	{
		mInstance = this;
	}

	PWM* TimerIRQ::GetPwm() const
	{
		return mPwm;
	}

	TimerIRQ* TimerIRQ::GetInstance()
	{
		return mInstance;
	}

	extern "C" void DMA1_Channel2_IRQHandler()
	{
		TimerIRQ::GetInstance()->GetPwm()->DmaFullTransmitEvent();
	}
}
