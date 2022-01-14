#include "Timer.h"
#include <chrono>
#include <utility>

Timer::Timer() :
    m_prevTimeMillisecond(0),
    m_sumTimeMillisecond(0)
{
    start();
    reset();
}

Timer::~Timer()
{}

long long Timer::GetCurrentTimeMillisecond()
{
	auto currentTime = std::chrono::system_clock::now();
	long long result = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();

	return result;
}

long long Timer::GetTimeMillisecond() const
{
    return m_sumTimeMillisecond;
}

long long Timer::GetTimeSecond() const
{
    double result = GetTimeMillisecond() / 1000.0;
    return (long long)result;
}

bool Timer::isTimeOverMillisecond(long long millisecond) const
{
    return GetTimeMillisecond() >= millisecond;
}

bool Timer::isTimeOverSecond(long long second) const
{
    return isTimeOverMillisecond(second * 1000);
}

void Timer::start()
{
    m_prevTimeMillisecond = Timer::GetCurrentTimeMillisecond();
}

void Timer::reset()
{
    m_sumTimeMillisecond = 0;
}

long long Timer::update()
{
    long long currentTime = Timer::GetCurrentTimeMillisecond();
    long long dt_millisecond = currentTime - m_prevTimeMillisecond;

    addTimeMillisecond(dt_millisecond);

    m_prevTimeMillisecond = currentTime;

    return dt_millisecond;
}

void Timer::addTimeMillisecond(long long millisecond)
{
    m_sumTimeMillisecond += millisecond;

    m_sumTimeMillisecond = std::max(m_sumTimeMillisecond, (long long)0);
}

void Timer::addTimeSecond(long long second)
{
    addTimeMillisecond(second * 1000);
}
