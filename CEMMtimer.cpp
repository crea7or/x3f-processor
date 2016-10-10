// Document modified at : Monday, November 27, 2006 04:48:15 PM , by user : Pavel Sokolov , from computer : CREA7OR
// CEMMtimer.cpp: implementation of the CEMMtimer class.
#include "stdafx.h"
#include "CEMMtimer.h"


#pragma message( "Linking Winmm.lib" )
#pragma comment( lib, "Winmm.lib" )


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEMMtimer::CEMMtimer()
{

//	DWORD start, finish, duration, i;
	
	if (timeGetDevCaps (&l_stResolution, sizeof (TIMECAPS)) == TIMERR_NOERROR)
    {
		//printf ("Minimum supported resolution = %d\n", resolution.wPeriodMin);
		//printf ("Maximum supported resolution = %d\n", resolution.wPeriodMax);
    }
	
//	if (resolution.wPeriodMin <= 1)
   // {
	//	if (timeBeginPeriod (1) == TIMERR_NOERROR)
	//	{
	//		for (i = 100; i <= 120; i++)
	//		{
	//			start = timeGetTime ();
				//while (timeGetTime () < (start + i));
				//finish = timeGetTime ();
				//duration = finish - start;
				//printf ("expected:%d  actual:%ld\n", i, duration);
			//}
			//timeEndPeriod (1);
		//}
    //}

	timeBeginPeriod (1);
}

CEMMtimer::~CEMMtimer()
{
	timeEndPeriod (1);
}
