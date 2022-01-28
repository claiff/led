//
// Created by claiff on 27.01.2022.
//

#pragma once

#include "specific/stm32f103xb.h"

namespace periphery
{
	class  RccHelper
	{
	public:
		RccHelper() = default;
		~RccHelper() = default;

		void SetMaxRcc();
		void SetTimer( TIM_TypeDef* tim );
		void SetGPIO( GPIO_TypeDef* gpio );
		void SetDMA( DMA_TypeDef* dma );

	private:
		bool InitHSE();
		bool InitPLL();
		void InitSW();

		bool CheckRegister( const volatile uint32_t* base_reg, unsigned long check_reg );
		bool UnCheckRegister( const volatile uint32_t* base_reg, unsigned long check_reg );
	};
}
