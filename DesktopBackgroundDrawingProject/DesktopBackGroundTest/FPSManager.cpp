#include "FPSManager.h"
#include <chrono>
#include <thread>
#include "Timer.h"
#include "Counter.h"
#include <Windows.h>
#include <utility>
#include <stdexcept>

FPSManager::FPSManager(int fps, int fpsCtrlTiming) :
	m_currentFrame(0),
	m_fps_limit(fps),
	m_fps_real(-1),
	m_sum_dt_millisecond(0),
	m_pTimer(nullptr),
	m_pFrameCounter(nullptr)
{
	m_pTimer = new Timer();
	m_pFrameCounter = new Counter(fpsCtrlTiming);

	if (fpsCtrlTiming > fps) {
		throw std::invalid_argument("FPSManager constractor argument error.");
	}

	init();
}

FPSManager::~FPSManager()
{
	delete m_pTimer;
	delete m_pFrameCounter;
}

void FPSManager::init()
{
	InitCurrentFrame();
	m_pTimer->start();
}

void FPSManager::update()
{
	m_currentFrame++;
	m_pFrameCounter->countUp();

	long long oneFrame_dt_millisecond = m_pTimer->update();

	m_sum_dt_millisecond += oneFrame_dt_millisecond;

	if (m_pFrameCounter->isCountMax()) {
		CallSleepMillisecond(m_sum_dt_millisecond);
	}
	else {
		if (IsLimitFrameOver()) {
			CallSleepMillisecond(m_sum_dt_millisecond);
		}
	}

	if (m_pTimer->isTimeOverSecond(1)) {
		//1•bŒo‰ß‚µ‚Ä‚¢‚½ê‡

		UpdateRealFPS();

		InitCurrentFrame();

		m_pTimer->reset();
		m_pTimer->start();
	}

}

int FPSManager::getRealFPS() const
{
	return m_fps_real;
}

void FPSManager::InitCurrentFrame()
{
	m_currentFrame = 0;
	m_pFrameCounter->reset();
	m_sum_dt_millisecond = 0;
}

void FPSManager::UpdateRealFPS()
{
	m_fps_real = m_currentFrame;
}

long long FPSManager::GetMillisecondPerFrame(int frame) const
{
	double result = 1000.0 / (double)m_fps_limit * frame;
	return (long long)result;
}

void FPSManager::SleepMillisecond(long long xFrame_dt_millisecond)
{
	long long need_xFrameMillisecond = GetMillisecondPerFrame(m_pFrameCounter->getCount());

	if (xFrame_dt_millisecond < need_xFrameMillisecond) {

		long long dt_sleep_millisecond = need_xFrameMillisecond - xFrame_dt_millisecond;
		long long min_interrupt_millisecond = dt_sleep_millisecond;

		if (min_interrupt_millisecond >= 10) {

			min_interrupt_millisecond = (std::min)(min_interrupt_millisecond - 1, (long long)15);
		}

		timeBeginPeriod(min_interrupt_millisecond);
		std::this_thread::sleep_for(std::chrono::milliseconds(dt_sleep_millisecond));
		timeEndPeriod(min_interrupt_millisecond);
	}
}

void FPSManager::CallSleepMillisecond(long long dt_millisecond)
{
	SleepMillisecond(dt_millisecond);
	
	m_pTimer->update();
	m_pFrameCounter->reset();
	m_sum_dt_millisecond = 0;
}

bool FPSManager::IsLimitFrameOver() const
{
	return m_currentFrame >= m_fps_limit;
}
