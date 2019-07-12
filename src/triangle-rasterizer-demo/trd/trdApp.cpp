#include "trdApp.hpp"
#include "trdExternalLibraryException.hpp"
#include "trdInstructions.hpp"
#include "trdFrameRateCounter.hpp"

trd::App::App() :
	m_reinitWindow(false),
	m_running(false),
	m_sdlWindow(nullptr),
	m_sdlRenderer(nullptr),
	m_sdlTexture(nullptr)
{
	initSdl();
	initWindow();

	m_running = true;
}

trd::App::~App()
{
	deinitWindow();
	SDL_Quit();
}

void trd::App::initSdl()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		throw ExternalLibraryException("trd::App::initSdl(): Failed to initialise SDL");
	}
}

void trd::App::initWindow()
{
	deinitWindow();

	m_sdlWindow = SDL_CreateWindow("Triangle rasterizer demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(m_settings.getScreenSize().width), int(m_settings.getScreenSize().height), SDL_WINDOW_SHOWN | (m_settings.getFullscreen() ? SDL_WINDOW_FULLSCREEN : 0));

	if (!m_sdlWindow)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialize SDL window");
	}

	m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!m_sdlRenderer)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialise SDL renderer");
	}

	m_sdlTexture = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, int(m_settings.getScreenSize().width), int(m_settings.getScreenSize().height));

	if (!m_sdlTexture)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialize SDL teuxtre");
	}

	m_colorBuffer = tr::ColorBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
}

void trd::App::deinitWindow()
{
	SDL_DestroyTexture(m_sdlTexture);
	SDL_DestroyRenderer(m_sdlRenderer);
	SDL_DestroyWindow(m_sdlWindow);
}

void trd::App::updateInputs()
{
	SDL_Event event;

 	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_running = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			constexpr float translationIncrement = 0.1f;
			constexpr float rotationIncrement    = 2.0f;

 			if      (event.key.keysym.sym == SDLK_ESCAPE) { m_running = false;                                    }
			else if (event.key.keysym.sym == SDLK_1)      { m_settings.cycleScreenSize();  m_reinitWindow = true; }
			else if (event.key.keysym.sym == SDLK_2)      { m_settings.toggleFullscreen(); m_reinitWindow = true; }
			//else if (event.key.keysym.sym == SDLK_w)      { position.z -= translationIncrement; }
			//else if (event.key.keysym.sym == SDLK_a)      { position.x -= translationIncrement; }
			//else if (event.key.keysym.sym == SDLK_s)      { position.z += translationIncrement; }
			//else if (event.key.keysym.sym == SDLK_d)      { position.x += translationIncrement; }
			//else if (event.key.keysym.sym == SDLK_SPACE)  { position.y += translationIncrement; }
			//else if (event.key.keysym.sym == SDLK_LCTRL)  { position.y -= translationIncrement; }
			//else if (event.key.keysym.sym == SDLK_LEFT)   { rotation.y += rotationIncrement;    }
			//else if (event.key.keysym.sym == SDLK_RIGHT)  { rotation.y -= rotationIncrement;    }
			//else if (event.key.keysym.sym == SDLK_UP)     { rotation.x += rotationIncrement;    }
			//else if (event.key.keysym.sym == SDLK_DOWN)   { rotation.x -= rotationIncrement;    }
		}
	}
}

void trd::App::renderColorBufferToWindow()
{
	tr::Color* pixels;
	int        pitch;

 	SDL_SetRenderTarget(m_sdlRenderer, m_sdlTexture);
	SDL_LockTexture(m_sdlTexture, NULL, (void**)&pixels, &pitch);

 	memcpy(pixels, m_colorBuffer.getData(), m_colorBuffer.getWidth() * m_colorBuffer.getHeight() * 4);

 	SDL_UnlockTexture(m_sdlTexture);
	SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, NULL, NULL);
	SDL_RenderPresent(m_sdlRenderer);
}

void trd::App::mainLoop()
{
	//const std::vector<tr::Vertex>     vertices         = defineVertices();
	//const float                       aspectRatio      = float(screenWidth) / float(screenHeight);
	//const Matrix4                     projectionMatrix = createPerspectiveProjectionMatrix(-aspectRatio, aspectRatio, -1.0f, 1.0f, 1.0f, 100.0f);

	//tr::Texture                       texture("data/udon.png");
	//tr::DepthBuffer                   depthBuffer(screenWidth, screenHeight);
	//tr::DefaultShader                 shader;

	//Vector4                           cameraRotation(0.0f, 0.0f, 0.0f, 1.0f);
	//Vector4                           cameraPosition(0.0f, 0.0f, 10.0f, 1.0f);
	//
	//tr::Rasterizer<tr::DefaultShader> rasterizer;

	//texture.generateMipmaps();

	//rasterizer.setPrimitive(tr::Primitive::Triangles);
	//rasterizer.setDepthTest(true);
	//rasterizer.setTextureMode(tr::TextureMode::Perspective);
	//rasterizer.setCullFaceMode(tr::CullFaceMode::None);
	//rasterizer.setInterlace(0, 1);
	//
	//shader.setTexture(&texture);
	//shader.setTextureWrappingMode(tr::TextureWrappingMode::Repeat);
	//shader.setTextureFiltering(false);
	//shader.setBlendMode(tr::BlendMode::None);

	trd::Instructions     instructions;
	trd::FrameRateCounter frameRateCounter;

	while (m_running)
	{
		//Matrix4   viewMatrix;

		updateInputs();

		if (m_reinitWindow)
		{
			initWindow();
			m_reinitWindow = false;
		}

		m_colorBuffer.fill(tr::Color(0, 0, 0, 255));
		//m_colorBuffer.at(5, 5) = tr::Color(255, 255, 255, 255);
		//viewMatrix.identity();
		//viewMatrix.translate(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z);
		//viewMatrix.rotateY(-cameraRotation.y);
		//viewMatrix.rotateX(-cameraRotation.x);

		//colorBuffer.fill(tr::Color(0, 0, 0, 255));
		//depthBuffer.fill(1.0f);

		//rasterizer.setMatrix(projectionMatrix * viewMatrix);
		//rasterizer.draw(vertices, shader, colorBuffer, depthBuffer);

		instructions.draw(m_settings, m_colorBuffer);
		frameRateCounter.draw(m_settings.getScreenSize(), m_colorBuffer);

		renderColorBufferToWindow();

		frameRateCounter.update();
	}
}
