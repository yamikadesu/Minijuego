#ifndef _TIMER_H_
#define _TIMER_H_

class cTimer
{
private:
	const float	m_fFixedTick;	// Time between every tick process. Seconds.
	float	m_fMaxElapsedTime;	// Max. elapsed time to process. Seconds.
	LARGE_INTEGER	m_Frequency;	// Freq. of the performance counter.
	LARGE_INTEGER	m_PreviousTime, m_CurrentTime;	// Iteration times.
	float	m_fElapsedTime;	// Time between iterations. Storing time remaining from previous process.
	float	m_fTotalTime;	// Total time for every g_fFixedTick since it started. Secs.
	float	m_fTimeBetwSlots;	// Time elpased between 2 Slot calls.

public:
	cTimer(float fFixedTick);
	inline void SetMaxElapsedTime(float fElapsedTime) { m_fMaxElapsedTime = fElapsedTime; }
	inline float GetFixedTick() const { return m_fFixedTick; }
	inline float GetTimeBetwSlots() const { return m_fTimeBetwSlots; }
	inline float GetElapsedTime() const { return m_fElapsedTime; }
	inline float GetTotalTime() const { return m_fTotalTime; }
	void InitSlotsToProcess();	// To call before ProcessSlots.
	bool ProcessSlots();	// Process timer. True if there are ticks to process next.
};

#endif // !_TIMER_H_

