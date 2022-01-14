#pragma once

class Timer
{
public:
	Timer();
	~Timer();

	static long long GetCurrentTimeMillisecond();

	long long GetTimeMillisecond()const;
	long long GetTimeSecond()const;

	bool isTimeOverMillisecond(long long millisecond)const;
	bool isTimeOverSecond(long long second)const;

	void start();
	void reset();
	long long update();

	void addTimeMillisecond(long long millisecond);
	void addTimeSecond(long long second);

private:
	long long m_prevTimeMillisecond;
	long long m_sumTimeMillisecond;
};

