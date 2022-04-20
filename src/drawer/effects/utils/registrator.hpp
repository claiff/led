//
// Created by claiff on 30.01.2022.
//

#pragma once

#include <vector>

#include "drawer/effects/types/ieffect.hpp"

namespace drawer::effects::utils
{
	static constexpr uint8_t EMPTY_POSITION = 0;

	template<typename T>
	class Registrator
	{
	public:
		Registrator()
				: mPosition( EMPTY_POSITION )
		{
		};
		~Registrator()
		{
			mEffects.clear();
		}

		void Add( T const& effect )
		{
			mEffects.push_back( effect );
		}

		T& Get()
		{
			if( mEffects.empty())
			{
				//return {};
			}
			if( mPosition >= mEffects.size())
			{
				mPosition = 0;
			}
			return mEffects[mPosition++];
		}

		[[nodiscard]] size_t Size() const
		{
			return mEffects.size();
		}

	private:
		std::vector < T > mEffects;
		uint8_t mPosition;
	};

}
