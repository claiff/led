//
// Created by claiff on 30.01.2022.
//

#include "cyclic.hpp"

namespace drawer
{
	Cyclic::Cyclic( device::LedMatrix const& led_matrix, effects::utils::Registrator const& effects,
					effects::utils::TimerPolicy const& timer )
			: mLedMatrix( led_matrix )
			, mEffects( effects )
			, mTimer( timer )
	{

	}

	void Cyclic::Draw()
	{
		while(1)
		{
			auto effect = mEffects.Get();
			effect->Draw(mLedMatrix);
			mTimer.SetTime();
			while(!mTimer.IsSwitch());
		}
	}
}