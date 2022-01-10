#include "FPSManager.h"
#include <chrono>
#include <thread>
#include <iostream>
FPSManager::FPSManager(int fps):
	m_currentFrame(0),
	m_fps_limit(fps),
	m_fps_real(-1),
	m_startTime()
{
	start();
}

FPSManager::~FPSManager()
{}

void FPSManager::start()
{
	m_startTime = GetCurrentTimeMillisecond();
	InitCurrentFrame();
}

void FPSManager::update()
{
	m_currentFrame++;

	if (m_currentFrame >= m_fps_limit) {
		//既定のフレーム数処理が完了した場合

		WaitMillisecond();

		UpdateRealFPS();

		InitCurrentFrame();
	}
	
	if (IsOverOneSecond()) {
		//既定のフレーム数に達する前に、1秒経過した場合

		UpdateRealFPS();

		start();
	}
}

int FPSManager::getRealFPS() const
{
	return m_fps_real;
}

void FPSManager::InitCurrentFrame()
{
	m_currentFrame = 0;
}

long long FPSManager::GetCurrentTimeMillisecond() const
{
	auto currentTime = std::chrono::system_clock::now();
	long long result = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();

	return result;
}

bool FPSManager::IsOverOneSecond() const
{
	//経過時間を計算
	long long dt = GetCurrentTimeMillisecond() - m_startTime;

	//1秒経過していたらtrue
	return dt >= 1000;
}

void FPSManager::UpdateRealFPS()
{
	m_fps_real = m_currentFrame;

	__raise updateRealFPS(getRealFPS());
}

void FPSManager::WaitMillisecond()
{
	long long update_startTime = m_startTime;

	long long endTime_calcResult = m_startTime + 1000;

	long long endTime_real = GetCurrentTimeMillisecond();

	if (endTime_real < endTime_calcResult) {

		long long dt_millisecond = endTime_calcResult - endTime_real;
		std::this_thread::sleep_for(std::chrono::microseconds(dt_millisecond * 1000));

		update_startTime = GetCurrentTimeMillisecond();
	}
	else {
		update_startTime = endTime_real;
	}

	m_startTime = update_startTime;
}
