//
// Created by claiff on 01.02.2022.
//

#include "adc.hpp"
#include "specific/stm32f103xb.h"

namespace periphery
{

	Adc::Adc()
	{
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		RCC->AHBENR |= RCC_AHBENR_CRCEN;

		GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);

		ADC1->CR2 |= ADC_CR2_ADON;
		ADC1->CR2 |= ADC_CR2_EXTSEL_0 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2;
	}

	uint32_t Adc::GetValue()const
	{
		CRC->CR |=  CRC_CR_RESET;

		ADC1->CR2 |= ADC_CR2_EXTTRIG;
		ADC1->CR2 |= ADC_CR2_SWSTART;
		while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC);
		auto data = ADC1->DR;
		CRC->DR = data;
		auto result = CRC->DR;
		return result;
	}
}