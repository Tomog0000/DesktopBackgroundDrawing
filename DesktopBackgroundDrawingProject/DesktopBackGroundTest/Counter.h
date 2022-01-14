#pragma once

class Counter
{
public:
	Counter(int countMax);
	~Counter();

	void reset();
	bool isCountMax()const;
	void addCount(int add);
	void countUp();
	void countDown();
	void setMinZeroFlag(bool flag);
	int getCount()const;

private:
	int m_currentCnt;
	int m_cntMax;
	bool m_isMinZero;
};

