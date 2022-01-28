//
// Created by claiff on 28.01.2022.
//

#pragma once

#include "pwm.hpp"


namespace periphery
{
	class TimerIRQ
	{
	public:
		explicit TimerIRQ( periphery::PWM const& pwm);
		~TimerIRQ() = default;

		PWM GetPwm() const;
		static TimerIRQ* GetInstance();
	private:
		PWM mPwm;
		static TimerIRQ *mInstance;
	};

}
