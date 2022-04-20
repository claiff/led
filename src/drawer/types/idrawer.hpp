//
// Created by claiff on 19.04.22.
//

#pragma once

namespace drawer::types
{
	class IDrawer
	{
	public:
		virtual ~IDrawer() = default;

		virtual void ReDraw() = 0;
	};
}