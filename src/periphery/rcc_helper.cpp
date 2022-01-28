//
// Created by claiff on 27.01.2022.
//

#include "rcc_helper.hpp"

namespace periphery
{

	//
	//Public methods
	//

	void RccHelper::SetMaxRcc()
	{
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		RCC->APB1ENR |=RCC_APB1ENR_PWREN;

		if( !InitHSE())
		{
			//TODO Error
		}
		if( !InitPLL())
		{
			//TODO Error
		}
		InitSW();
	}

	void RccHelper::SetTimer( TIM_TypeDef* tim )
	{
		if( tim == TIM1)
		{
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		}
		if( tim == TIM2)
		{
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		}
	}

	void RccHelper::SetGPIO( GPIO_TypeDef* gpio )
	{
		if(gpio == GPIOA)
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		}
	}

	void RccHelper::SetDMA( DMA_TypeDef* dma )
	{
		if(dma == DMA1)
		{
			RCC->AHBENR |= RCC_AHBENR_DMA1EN;
		}
	}

	//
	//Private methods
	//

	bool RccHelper::InitHSE()
	{
		FLASH->ACR = FLASH_ACR_LATENCY_2;
		RCC->CR |= RCC_CR_HSEON;

		if( !CheckRegister( &RCC->CR, RCC_CR_HSERDY))
		{
			return false;
		}

		RCC->CFGR &= ~RCC_CFGR_SW;

		if( !UnCheckRegister( &RCC->CFGR, RCC_CFGR_SWS))
		{
			return false;
		}

		RCC->CR &= ~RCC_CR_PLLON;

		if( !UnCheckRegister( &RCC->CR, RCC_CR_PLLRDY))
		{
			return false;
		}
		return true;
	}

	bool RccHelper::InitPLL()
	{
		static const uint8_t ZERO = 0x00;

		RCC->CFGR |= RCC_CFGR_PLLMULL_0 | RCC_CFGR_PLLMULL_1 | RCC_CFGR_PLLMULL_2;
		RCC->CFGR |= RCC_CFGR_PLLSRC;
		RCC->CR |= RCC_CR_PLLON;

		if( !CheckRegister( &RCC->CR, RCC_CR_PLLRDY))
		{
			return false;
		}
		return true;
	}

	void RccHelper::InitSW()
	{
		static const uint8_t ZERO = 0x00;

		RCC->CFGR = ZERO;
		RCC->CFGR |= RCC_CFGR_PPRE1;
		//RCC->CFGR |= RCC_CFGR_PPRE2;
		RCC->CFGR |= RCC_CFGR_SW_1;
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_1 | RCC_CFGR_PPRE1_0);
		//RCC->CFGR &= ~( RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_1 );

		RCC->CR &= ~RCC_CR_HSION;
	}

	bool RccHelper::CheckRegister( const volatile uint32_t* base_reg, uint32_t check_reg )
	{
		static const uint16_t TIMER_FULL = 0xFFFF;
		volatile uint16_t timer = 0;

		while(((*base_reg & check_reg) != check_reg) && timer != TIMER_FULL )
		{
			timer++;
		}
		if( timer == TIMER_FULL )
		{
			return false;
			//TODO ERROR
		}
		return true;
	}

	bool RccHelper::UnCheckRegister( const volatile uint32_t* base_reg, unsigned long check_reg )
	{
		static const uint8_t TIMER_FULL = 0xFF;
		uint8_t timer = 0;

		while(((*base_reg & check_reg) == check_reg) && timer != TIMER_FULL )
		{
			timer++;
		}
		if( timer == TIMER_FULL )
		{
			return false;
			//TODO ERROR
		}
		return true;
	}
}