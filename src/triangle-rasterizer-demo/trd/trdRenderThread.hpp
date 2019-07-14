#pragma once

#include "tr.hpp"
#include "trdShader.hpp"
#include "trdCamera.hpp"
#include "trdModel.hpp"
#include "trdSettings.hpp"
#include <thread>

namespace trd
{
	class RenderThread
	{
	public:
		                                        RenderThread(const Settings& settings, const tf::Vector<Model>& models, const size_t interlaceOffset, const size_t interlaceStep);
		                                        ~RenderThread();

		void                                    drawFrame(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);
		bool                                    isFinished() const;

	private:
		void                                    threadLoop();

	private:
		const Settings&                         m_settings;
		const tf::Vector<Model>&                m_models;
		bool                                    m_running;
		bool                                    m_drawFrame;
		bool                                    m_finished;
		std::thread                             m_thread;
		tr::Rasterizer<Shader>                  m_rasterizer;
		trd::Shader                             m_shader;
		const Camera*                           m_camera;
		tr::ColorBuffer*                        m_colorBuffer;
		tr::DepthBuffer*                        m_depthBuffer;
	};
}