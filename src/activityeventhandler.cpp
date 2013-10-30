#include "activityeventhandler.h"
#include "log.h"

ActivityEventHandler::ActivityEventHandler()
{
}

void ActivityEventHandler::SetStatus(const char* aName, ActivityEventHandler::ActivityStatus aStatus)
{
    const static char* states_literals[] = {"NOT_STARTED", "RUNNING", "DONE_OK", "DONE_FAIL", "RECOVERING","DESTROYED"};
    Log::DEBUG(LOC, "%s - %s", aName, states_literals[aStatus]);
}

