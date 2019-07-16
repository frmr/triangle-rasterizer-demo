#pragma once

#include <condition_variable>

namespace trd
{
	struct RenderThread
	{
		std::thread             thread;
		std::condition_variable conditionVariable;
		std::mutex              mutex;
		bool                    quit;
		bool                    draw;
	};
}