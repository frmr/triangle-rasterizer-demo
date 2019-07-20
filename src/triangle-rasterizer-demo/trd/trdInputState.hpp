#pragma once

#include "trdDigitalInput.hpp"
#include "trdKey.hpp"
#include <map>

namespace trd
{
	class InputState
	{
	public:
		                                InputState();

		void                            update();
		bool                            getQuit() const;
		DigitalInput                    getKeyState(const Key key) const;
		float                           getMouseChangeX() const;
		float                           getMouseChangeY() const;

	private:
		void                            resetPressedKeys();

	private:
		static const std::map<int, Key> m_keyMapping;
		std::map<Key, DigitalInput>     m_keys;
		float                           m_mouseChangeX;
		float                           m_mouseChangeY;
		bool                            m_quit;
	};
}