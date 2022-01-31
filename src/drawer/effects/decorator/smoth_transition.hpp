//
// Created by claiff on 31.01.2022.
//

#pragma once

#include "drawer/effects/simple_color.hpp"
#include "drawer/effects/utils/timer_policy.hpp"

namespace drawer::effects::decorator
{
	class SmoothTransition
			: public SimpleColor
	{
	public:
		explicit SmoothTransition( Pixel_t const& color, utils::TimerPolicy const& timer );
		~SmoothTransition() override = default;

		void Draw( device::LedMatrix& led_matrix ) const override;
	private:
		mutable utils::TimerPolicy mTimer;
		void IncreaseBrightness( device::LedMatrix& led_matrix ) const;
		void DecreaseBrightness( device::LedMatrix& led_matrix ) const;
		void
		ProcessBrightness( device::LedMatrix& led_matrix, uint8_t brightness, uint8_t step, bool is_increase ) const;
	};

}
