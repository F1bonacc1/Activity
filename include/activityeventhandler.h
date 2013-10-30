#ifndef ACTIVITYEVENTHANDLER_H
#define ACTIVITYEVENTHANDLER_H

class ActivityEventHandler
{
public:
    enum ActivityStatus{
        NOT_STARTED,
        RUNNING,
        DONE_OK,
        DONE_FAIL,
        RECOVERING,
        DESTROYED
    };
    ActivityEventHandler();

    static void SetStatus(const char *aName, ActivityStatus aStatus);
};

#endif // ACTIVITYEVENTHANDLER_H
