//
// Created by claiff on 27.01.2022.
//

#include "pwm.hpp"
#include "utils/timings_converter.hpp"

static constexpr uint16_t DEFAULT_DELAY = 50;

namespace periphery
{
	//
	//Constructors/destructors
	//

	PWM::PWM( RccHelper& rcc, uint16_t count_elements )
	{
		static constexpr uint8_t DELAY_ELEMENT = 1;

		InitTimings( count_elements + DELAY_ELEMENT );
		InitPWMTimer( rcc );
		InitDMA( rcc );
	}

	PWM::PWM( PWM const& other )
	{
		mTimings = other.mTimings;
	}

	PWM& PWM::operator=( const PWM& other )
	{
		auto other_timings = other.mTimings;
		mTimings.reserve( other_timings.size());
		std::copy( other_timings.begin(), other_timings.end(), std::back_inserter( mTimings ));

		return *this;
	}

	PWM& PWM::operator=( PWM* other )
	{
		auto other_timings = other->mTimings;
		mTimings.reserve( other_timings.size());
		std::copy( other_timings.begin(), other_timings.end(), std::back_inserter( mTimings ));

		return *this;
	}

	PWM::~PWM()
	{
		mTimings.clear();
		std::destroy( mTimings.begin(), mTimings.end());
		mTimings.resize( 0 );
		mTimings.reserve( 0 );
	}

	//
	//Public methods
	//

	void PWM::StartPWM()
	{
		DMA1_Channel2->CNDTR = GetTimingsSize();
		DMA1_Channel2->CCR |= DMA_CCR_EN;
		TIM1->CR1 |= TIM_CR1_CEN;
	}

	void PWM::StopPWM()
	{
		DMA1_Channel2->CCR &= ~DMA_CCR_EN;
		TIM1->CR1 &= ~TIM_CR1_CEN;
	}

	void PWM::SetDelay( uint8_t time_us )
	{
		//FIXME Maybe need check time_us
		TIM2->ARR = time_us;
	}

	void PWM::SetPixel( uint16_t number_pixel, utils::Color const& pixel )
	{
		if( number_pixel > mTimings.size() )
		{
			return;
		}
		auto data = utils::TimingsConverter::Convert( pixel );
		mTimings[number_pixel] = data;
	}

	//
	//Private methods
	//

	void PWM::InitPWMTimer( RccHelper& rcc )
	{
		SetupGPIO( rcc );
		rcc.SetTimer(TIM1);

		TIM1->ARR = 0x0E;
		TIM1->PSC = 0x05;
		TIM1->CCMR1 |= TIM_CCMR1_IC1PSC_1;
		TIM1->CCMR1 |= TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1;
		TIM1->BDTR |= TIM_BDTR_BKP;
		TIM1->DIER |= TIM_DIER_CC1DE;
		TIM1->CCER |= TIM_CCER_CC1E;
		TIM1->BDTR |= TIM_BDTR_MOE;
	}

	void PWM::SetupGPIO( RccHelper& rcc )
	{
		rcc.SetGPIO(GPIOA);

		GPIOA->CRH &= ~(GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1 | GPIO_CRH_CNF8_0);
		GPIOA->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_CNF8_1);
	}

	void PWM::InitDMA( RccHelper& rcc )
	{
		rcc.SetDMA(DMA1);
		DMA1_Channel2->CCR |= DMA_CCR_TCIE;
		DMA1_Channel2->CCR |= DMA_CCR_DIR;
		DMA1_Channel2->CCR |= DMA_CCR_MINC;
		DMA1_Channel2->CCR |= DMA_CCR_PSIZE_0;
		DMA1_Channel2->CCR |= DMA_CCR_PL_0;

		auto address_par = ( uint32_t ) &TIM1->CCR1;
		auto address_mar = ( uint32_t ) &mTimings[0];

		DMA1_Channel2->CPAR = address_par;
		DMA1_Channel2->CMAR = address_mar;

		NVIC_EnableIRQ( DMA1_Channel2_IRQn );
	}

	uint16_t PWM::GetTimingsSize() const
	{
		return mTimings.size() * sizeof( TimingColorFull_t );
	}

	void PWM::InitTimings( uint16_t count_elements )
	{
		mTimings.reserve( count_elements );
		mTimings.resize( count_elements );
		auto default_timing = GetDefaultTiming();
		std::fill_n( mTimings.begin(), mTimings.size() - 1, default_timing );
	}

	TimingColorFull_t PWM::GetDefaultTiming() const
	{
		TimingColorFull_t result;
		Timing_Part_t temp_part;

		for( auto& bit: temp_part.bit )
		{
			bit = TOH;
		}
		result.blue = temp_part;
		result.green = temp_part;
		result.red = temp_part;

		return result;
	}

	void PWM::DmaFullTransmitEvent()
	{
		if((DMA1->ISR & DMA_ISR_TCIF2) != DMA_ISR_TCIF2)
		{
			return;
		}
		TIM1->CR1 &= ~TIM_CR1_CEN;
		DMA1_Channel2->CCR &= ~DMA_CCR_EN;
		DMA1->IFCR |= DMA_IFCR_CTCIF2 | DMA_IFCR_CHTIF2;
		//TIM2->CR1 |= TIM_CR1_CEN;
		TIM1->CCR1 = 0;
		TIM1->CNT = 0;
		TIM1->SR = 0;
	}


}