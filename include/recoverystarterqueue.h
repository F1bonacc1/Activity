#ifndef RECOVERYSTARTERQUEUE_H
#define RECOVERYSTARTERQUEUE_H

#include <queue>
#include "activity.h"

class RecoveryStarterQueue
{
public:
    RecoveryStarterQueue();
    virtual ~RecoveryStarterQueue();

    void push(Activity* aRecoveree);
    void stop();

private:
    Activity *pop();
    virtual void waitForEventThread();
    std::queue< Activity* > mRecoveryQ;

    boost::condition_variable mCondVar;
    boost::mutex mMutex;
    boost::thread* pThread;
    bool mStopped;
};

#endif // RECOVERYSTARTERQUEUE_H
