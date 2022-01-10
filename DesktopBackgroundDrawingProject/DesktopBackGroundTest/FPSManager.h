#pragma once

class FPSManager {
public:
	FPSManager(int fps = 60);
	~FPSManager();

	void start();
	void update();

	int getRealFPS()const;

	__event void updateRealFPS(double);

private:
	void InitCurrentFrame();
	long long GetCurrentTimeMillisecond()const;
	bool IsOverOneSecond()const;
	void UpdateRealFPS();
	void WaitMillisecond();

private:
	int m_currentFrame, m_fps_limit, m_fps_real;
	long long m_startTime;
};