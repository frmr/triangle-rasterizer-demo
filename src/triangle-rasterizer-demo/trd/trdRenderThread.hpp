#pragma once

#include "trdSettings.hpp"
#include "trdCamera.hpp"
#include "trdModel.hpp"
#include "trdShader.hpp"
#include "tr.hpp"
#include <condition_variable>

namespace trd
{
	class RenderThread
	{
	public:
		                         RenderThread(const size_t threadIndex, const Settings& settings, const tf::Vector<Model>& models);
		                         ~RenderThread();

		void                     draw(const Camera& camera, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer);
		void                     wait();
		void                     kill();

	private:
		void                     threadFunction();
		void                     setTextureMode(tr::Rasterizer<Shader>& rasterizer, Shader& shader);

	private:
		const size_t             m_threadIndex;
		const Settings&          m_settings;
		const tf::Vector<Model>& m_models;
		std::thread              m_thread;
		std::condition_variable  m_conditionVariable;
		std::mutex               m_mutex;
		bool                     m_quit;
		bool                     m_draw;
		const Camera*            m_camera;
		tr::ColorBuffer*         m_colorBuffer;
		tr::DepthBuffer*         m_depthBuffer;
	};
}