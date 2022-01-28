//
// Created by claiff on 28.01.2022.
//

#include "timer_irq.hpp"

namespace periphery
{
	TimerIRQ* TimerIRQ::mInstance = nullptr;

	periphery::TimerIRQ::TimerIRQ( periphery::PWM const& pwm )
			: mPwm( pwm )
	{
		mInstance = this;
	}

	PWM TimerIRQ::GetPwm() const
	{
		return mPwm;
	}

	TimerIRQ* TimerIRQ::GetInstance()
	{
		return mInstance;
	}

	extern "C" void DMA1_Channel2_IRQHandler()
	{
		if((DMA1->ISR & DMA_ISR_TCIF2) != DMA_ISR_TCIF2)
		{
			return;
		}
		TIM1->CR1 &= ~TIM_CR1_CEN;
		DMA1_Channel2->CCR &= ~DMA_CCR_EN;
		DMA1->IFCR |= DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2;
		TIM2->CR1 |= TIM_CR1_CEN;
		TIM1->CCR1 = 0;
		TIM1->CNT = 0;
		TIM1->SR = 0;
	}

	extern "C" void TIM2_IRQHandler()
	{
		TimerIRQ::GetInstance()->GetPwm().DelayTimerEvent();
	}
}
