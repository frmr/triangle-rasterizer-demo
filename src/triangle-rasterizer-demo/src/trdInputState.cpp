#include "trdInputState.hpp"
#include "SDL.h"
#include <stdexcept>

const std::map<int, trd::Key> trd::InputState::m_keyMapping = {
	{ SDLK_ESCAPE, Key::Quit                            },
	{ SDLK_w,      Key::MoveForward                     },
	{ SDLK_a,      Key::MoveLeft                        },
	{ SDLK_s,      Key::MoveBackward                    },
	{ SDLK_d,      Key::MoveRight                       },
	{ SDLK_SPACE,  Key::MoveUp                          },
	{ SDLK_LCTRL,  Key::MoveDown                        },
	{ SDLK_p,      Key::ChangeSettingPauseAnimation     },
	{ SDLK_r,      Key::ChangeSettingResolution         },
	{ SDLK_l,      Key::ChangeSettingTileSize           },
	{ SDLK_t,      Key::ChangeSettingThreads            },
	{ SDLK_h,      Key::ChangeSettingHorizontalFov      },
	{ SDLK_f,      Key::ChangeSettingFragmentShaderMode },
	{ SDLK_m,      Key::ChangeSettingTextureMapping     },
	{ SDLK_b,      Key::ChangeSettingBilinearFiltering  },
	{ SDLK_i,      Key::ChangeSettingInstructions       },
	{ SDLK_c,      Key::ChangeSettingFrameRateCounter   },
	{ SDLK_F11,    Key::ChangeSettingFullscreen         },
	{ SDLK_F12,    Key::TakeScreenshot                  }
};

trd::InputState::InputState() :
	m_keys(),
	m_mouseChangeX(0),
	m_mouseChangeY(0),
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
	m_mouseChangeX = 0;
	m_mouseChangeY = 0;

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

int32_t trd::InputState::getMouseChangeX() const
{
	return m_mouseChangeX;
}

int32_t trd::InputState::getMouseChangeY() const
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
