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
		int32_t                         getMouseChangeX() const;
		int32_t                         getMouseChangeY() const;

	private:
		void                            resetPressedKeys();

	private:
		static const std::map<int, Key> m_keyMapping;
		std::map<Key, DigitalInput>     m_keys;
		int32_t                         m_mouseChangeX;
		int32_t                         m_mouseChangeY;
		bool                            m_quit;
	};
}