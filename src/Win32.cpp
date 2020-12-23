# define _CRT_SECURE_NO_WARNINGS
# include <windows.h>
# include <time.h>
# if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#   define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
# else
#   define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
# endif
# include "priority_thread.h"
# include <iostream>
# include "test_driver.h"

//  gettimeofday() implementation for windows
struct timezone 
{
    int     tz_minuteswest; /* minutes W of Greenwich */
    int     tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;
 
  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
 
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
    /*converting file time to unix epoch*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS; 
    tmpres /= 10;  /*convert into microseconds*/
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }
 
  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }
    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }
 
  return 0;
}

int test_gettimeofday(int testno) {
    bool rc = true;
    const long iterations = 1000000;
    timeval t1, t2;
    long dt;
    switch(testno) {
    case 0: return 1;
    default:return -1;
    case 1:
        gettimeofday(&t1, NULL);
        for (int i = 0; i < iterations; ++i)
            gettimeofday(&t2, NULL);
        dt = (t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec);
        std::cout << iterations << " calls to gettimeofday() took " << dt/1000 << " mS" << std::endl;
    }
    return rc ? 1 : 0;
}
//  class PriorityThread implementation for windows
PriorityThread::PriorityThread() 
{ 
    SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST); 
	//TIMECAPS tc;
	//if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
	//	return;
	//timeBeginPeriod(tc.wPeriodMin); 

	//std::cout << "timer period: min " << tc.wPeriodMin
	//			<< ", max " << tc.wPeriodMax << std::endl;
}

PriorityThread::~PriorityThread() 
{ 
    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);  
	//TIMECAPS tc;
	//if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
	//	return;
	//timeEndPeriod(tc.wPeriodMin); 
}
