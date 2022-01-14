#include "Counter.h"
#include <utility>

Counter::Counter(int countMax):
	m_currentCnt(0),
	m_cntMax(countMax),
	m_isMinZero(true)
{
	reset();
}

Counter::~Counter()
{}

void Counter::reset()
{
	m_currentCnt = 0;
}

bool Counter::isCountMax() const
{
	return m_currentCnt >= m_cntMax;
}

void Counter::addCount(int add)
{
	m_currentCnt += add;
	
	if (m_isMinZero)
	{
		m_currentCnt = std::max(m_currentCnt, 0);
	}
}

void Counter::countUp()
{
	addCount(1);
}

void Counter::countDown()
{
	addCount(-1);
}

void Counter::setMinZeroFlag(bool flag)
{
	m_isMinZero = flag;
}

int Counter::getCount() const
{
	return m_currentCnt;
}
