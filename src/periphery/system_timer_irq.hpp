//
// Created by claiff on 31.01.2022.
//

#pragma once

#include <cstdint>

namespace periphery
{
	class SystemTimerIrq
	{
	public:

		~SystemTimerIrq();

		static SystemTimerIrq* GetInstance();

		static void SetTime( uint32_t time );
		static void IncrementTime();
		static uint32_t GetTime();

		static SystemTimerIrq* mInstance;
	private:
		SystemTimerIrq();

		static uint32_t mTime;
	};
}

