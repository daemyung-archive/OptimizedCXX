# include <unistd.h>
# include <sys/resource.h>

# include "priority_thread.h"

//  class PriorityThread implementation for unix
PriorityThread::PriorityThread()
{
    setpriority(PRIO_PROCESS, getpid(), -20);
}

PriorityThread::~PriorityThread()
{
    setpriority(PRIO_PROCESS, getpid(), 0);
}