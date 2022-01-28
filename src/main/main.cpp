#include "periphery/rcc_helper.hpp"
#include "periphery/pwm.hpp"
#include "periphery/timer_irq.hpp"

int main( )
{
	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	periphery::PWM pwm{rcc, 1};
	periphery::TimerIRQ timer_irq{pwm};

	pwm.StartPWM();
	while(1)
	{

	}
	return 0;
}
