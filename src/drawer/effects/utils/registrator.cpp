//
// Created by claiff on 30.01.2022.
//

#include "registrator.hpp"

static constexpr uint8_t EMPTY_POSITION = 0;

namespace drawer::effects::utils
{
	Registrator::Registrator()
			: mPosition( EMPTY_POSITION )
	{

	}

	Registrator::~Registrator()
	{
		for(auto effect : mEffects)
		{
			delete effect;
		}
	}

	void Registrator::Add( types::IEffectPtr const& effect )
	{
		mEffects.push_back( effect );
	}

	types::IEffectPtr Registrator::Get()
	{
		if( mEffects.empty())
		{
			return nullptr;
		}
		if( mPosition >= mEffects.size())
		{
			mPosition = 0;
		}
		return mEffects[mPosition++];
	}




}