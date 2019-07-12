#pragma once

#include "trdTextRenderer.hpp"
#include "trdSettings.hpp"
#include "tfVector.hpp"

namespace trd
{
	class Instructions : public TextRenderer
	{
	public:
		static void draw(const Settings& settings, tr::ColorBuffer& buffer);
	};
}