# if defined _WIN32
#   include <time.h>
#   include <WinSock.h>
 
    struct timezone 
    {
        int     tz_minuteswest; /* minutes W of Greenwich */
        int     tz_dsttime;     /* type of dst correction */
    };
 
    int gettimeofday(struct timeval *tv, struct timezone *tz);
#elif __APPLE__
#   include <sys/time.h>
# else // Linux
#   include <sys.time.h>
# endif