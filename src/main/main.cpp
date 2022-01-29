#include "periphery/rcc_helper.hpp"
#include "periphery/pwm.hpp"
#include "periphery/timer_irq.hpp"
#include "device/led_matrix.hpp"

static constexpr uint8_t WIDTH = 16;
static constexpr uint8_t HEIGHT = 16;

int main( )
{
	periphery::RccHelper rcc;
	rcc.SetMaxRcc();

	//FIXME Как то объединить
	periphery::PWM pwm{rcc, WIDTH * HEIGHT};
	periphery::TimerIRQ irq{pwm};
	device::LedMatrix led{HEIGHT,WIDTH, pwm};

	pwm.StartPWM();
	while(1)
	{

	}
	return 0;
}
