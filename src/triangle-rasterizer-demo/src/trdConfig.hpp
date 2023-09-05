#pragma once

#include "tfIniFile.hpp"
#include "trdScreenSize.hpp"

namespace trd
{
	class Config : public tf::IniFile
	{
	public:
		           Config();

		ScreenSize getCustomScreenSize() const;
		ScreenSize getCustomTileSize() const;
		float      getMouseSensitivity() const;

	private:
		uint32_t   getU32(const tf::String& keyName) const;
		float      getFloat(const tf::String& keyName) const;
		tf::String getString(const tf::String& keyName) const;

	private:
		ScreenSize m_customScreenSize;
		ScreenSize m_customTileSize;
		float      m_mouseSensitivity;
	};
}