#include "trdInputState.hpp"
#include "SDL.h"
#include <stdexcept>

const std::map<int, trd::Key> trd::InputState::m_keyMapping = {
	{ SDLK_ESCAPE, Key::Quit           },
	{ SDLK_w,      Key::MoveForward    },
	{ SDLK_a,      Key::MoveLeft       },
	{ SDLK_s,      Key::MoveBackward   },
	{ SDLK_d,      Key::MoveRight      },
	{ SDLK_SPACE,  Key::MoveUp         },
	{ SDLK_LCTRL,  Key::MoveDown       },
	{ SDLK_1,      Key::ChangeSetting1 },
	{ SDLK_2,      Key::ChangeSetting2 },
	{ SDLK_3,      Key::ChangeSetting3 },
	{ SDLK_4,      Key::ChangeSetting4 },
	{ SDLK_5,      Key::ChangeSetting5 },
	{ SDLK_6,      Key::ChangeSetting6 },
	{ SDLK_7,      Key::ChangeSetting7 },
	{ SDLK_8,      Key::ChangeSetting8 },
	{ SDLK_9,      Key::ChangeSetting9 }
};

trd::InputState::InputState() :
	m_keys(),
	m_mouseChangeX(0.0f),
	m_mouseChangeY(0.0f),
	m_quit(false)
{
	for (const auto& keyPair : m_keyMapping)
	{
		m_keys.insert({ keyPair.second, DigitalInput() });
	}
}

void trd::InputState::update()
{
	SDL_Event event;

	resetPressedKeys();

	m_quit         = false;
	m_mouseChangeX = 0.0f;
	m_mouseChangeY = 0.0f;

 	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_quit = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			const auto element = m_keyMapping.find(event.key.keysym.sym);

			if (element != m_keyMapping.end())
			{
				m_keys[element->second].held    = true;
				m_keys[element->second].pressed = true;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			const auto element = m_keyMapping.find(event.key.keysym.sym);

			if (element != m_keyMapping.end())
			{
				m_keys[element->second].held = false;
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			m_mouseChangeX = event.motion.xrel;
			m_mouseChangeY = event.motion.yrel;
		}
	}
}

bool trd::InputState::getQuit() const
{
	return m_quit;
}

trd::DigitalInput trd::InputState::getKeyState(const Key key) const
{
	try
	{
		return m_keys.at(key);
	}
	catch (const std::out_of_range&)
	{
		return trd::DigitalInput();
	}
}

float trd::InputState::getMouseChangeX() const
{
	return m_mouseChangeX;
}

float trd::InputState::getMouseChangeY() const
{
	return m_mouseChangeY;
}

void trd::InputState::resetPressedKeys()
{
	for (auto& keyPair : m_keys)
	{
		keyPair.second.pressed = false;
	}
}
