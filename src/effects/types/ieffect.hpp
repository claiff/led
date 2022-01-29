//
// Created by claiff on 29.01.2022.
//

#pragma once

namespace effect::types
{
	class IEffect
	{
	public:
		~IEffect() = default;

		virtual void Draw() const = 0;
	};
}
