#pragma once

#include <glew.h>
#include <glfw3.h>

#include "Time.h"

#include <iostream>

namespace TMT {

	class Timer
	{
	public:
		Timer(float timer_duration);
		~Timer();

		bool get_end_status();

		float get_time();

		float get_normalized_time();

		void stop();

		void resume();

		void restart();

		void update();

	private:
		float m_time;
		float m_timer_duration;
		bool m_stop;
	};
}