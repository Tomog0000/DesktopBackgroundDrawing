#pragma once

class Timer;
class Counter;

class FPSManager {
public:
	FPSManager(int fps = 60, int fpsCtrlTiming = 10);
	~FPSManager();

	void init();
	void update();

	int getRealFPS()const;

private:
	void InitCurrentFrame();
	void UpdateRealFPS();
	long long GetMillisecondPerFrame(int frame)const;
	void SleepMillisecond(long long dt_millisecond);
	void CallSleepMillisecond(long long dt_millisecond);
	bool IsLimitFrameOver()const;

private:
	int m_currentFrame;
	int m_fps_limit;
	int m_fps_real;
	long long m_sum_dt_millisecond;
	Timer* m_pTimer;
	Counter* m_pFrameCounter;
};