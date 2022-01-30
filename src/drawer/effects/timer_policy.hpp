//
// Created by claiff on 31.01.2022.
//

#pragma once

#include <cstdint>

namespace drawer::effects
{
	class TimerPolicy
	{
	public:
		explicit TimerPolicy( uint16_t time_ms );
		~TimerPolicy() = default;

		void SetTime();
		bool IsSwitch() const;

	private:
		uint16_t mTimerMs;
		uint32_t mBeginTime;
	};
}