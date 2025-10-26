#include "Timer.h"

TMT::Timer::Timer(float timer_duration) : m_timer_duration(timer_duration), m_time(0), m_stop(false)
{

}

TMT::Timer::~Timer()
{
}


bool TMT::Timer::get_end_status()
{
	return m_time >= m_timer_duration && !m_stop;
}

float TMT::Timer::get_time()
{
	return m_time;
}

float TMT::Timer::get_normalized_time()
{
	return m_time / m_timer_duration;
}

void TMT::Timer::stop()
{
	m_stop = true;
}

void TMT::Timer::resume()
{
	m_stop = false;
}

void TMT::Timer::restart()
{
	m_stop = false;
	m_time = 0;
}

void TMT::Timer::update() {
	if (m_time < m_timer_duration && !m_stop) {
		m_time += delta_time;
	}
}