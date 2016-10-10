// Document modified at : Wednesday, November 29, 2006 03:21:10 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEMMtimer.h: interface for the CEMMtimer class.
#pragma once

#include <mmsystem.h>

class CEMMtimer  
{
public:
	CEMMtimer();
	 ~CEMMtimer();

	DWORD GetTime()
	{
		return timeGetTime();
	}

	void StartTimer()
	{
		m_dwordStartTime = GetTime();
	}
	void StopTimer()
	{
		m_dwordEndTime = GetTime();
	}
	void ShowTimer()
	{
		CEHelper::PN( m_dwordEndTime - m_dwordStartTime );
	}

	DWORD GetDifference()
	{
		return ( m_dwordEndTime - m_dwordStartTime );
	}


	DWORD m_dwordStartTime;
	DWORD m_dwordEndTime;

	TIMECAPS l_stResolution;
};

typedef CEMMtimer* LPMMTIMER;
