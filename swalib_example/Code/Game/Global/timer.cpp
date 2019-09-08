#include "../../../../common/stdafx.h"
#include "../Global/timer.h"

cTimer::cTimer(float fFixedTick) : m_fFixedTick(fFixedTick)
	, m_fElapsedTime(0.0f)
	, m_fMaxElapsedTime(1.0f / 10.0f)
	, m_fTimeBetwSlots(0.0f)
	, m_fTotalTime(0.0f)
{
	QueryPerformanceFrequency(&m_Frequency);	// Freq. cached.
	QueryPerformanceCounter(&m_PreviousTime);	// Init. prev. time.
	QueryPerformanceCounter(&m_CurrentTime);
}

void cTimer::InitSlotsToProcess()
{
	QueryPerformanceCounter(&m_CurrentTime);
	LARGE_INTEGER elapsed;
	elapsed.QuadPart = m_CurrentTime.QuadPart - m_PreviousTime.QuadPart;
	m_PreviousTime = m_CurrentTime;
	// Adding time elapsed from previous process to remaining time.
	m_fTimeBetwSlots = static_cast<float>(elapsed.QuadPart) / static_cast<float>(m_Frequency.QuadPart);
	m_fElapsedTime += m_fTimeBetwSlots;

	// To fix number of iterations.
	if (m_fElapsedTime > m_fMaxElapsedTime) {
		m_fElapsedTime = m_fMaxElapsedTime;
	}
}

bool cTimer::ProcessSlots()
{
	if (m_fElapsedTime >= m_fFixedTick) {
		m_fTotalTime += m_fFixedTick;	// Secs.
		m_fElapsedTime -= m_fFixedTick;	// g_fElapsedTime can remain time after process.
		return true;
	}
	return false;
}
