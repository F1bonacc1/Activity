#include "recoverystarterqueue.h"

RecoveryStarterQueue::RecoveryStarterQueue()
{
    mStopped = false;
    pThread  = new boost::thread(&RecoveryStarterQueue::waitForEventThread, this);
}

RecoveryStarterQueue::~RecoveryStarterQueue()
{
    pThread->join();
    delete pThread;
}

void RecoveryStarterQueue::push(Activity *aRecoveree)
{
    boost::lock_guard<boost::mutex> lock(mMutex);

    mRecoveryQ.push(aRecoveree);
    mCondVar.notify_one();
}

void RecoveryStarterQueue::stop()
{
    mStopped = true;
    mCondVar.notify_one();
}

Activity *RecoveryStarterQueue::pop()
{
    boost::unique_lock<boost::mutex> lock(mMutex);
    while(mRecoveryQ.empty())
    {
        mCondVar.wait(lock);
    }
    Activity *lActFront = mRecoveryQ.front();
    mRecoveryQ.pop();
    return lActFront;
}


void RecoveryStarterQueue::waitForEventThread()
{
    while (!mStopped) {
        Activity *lRecoveree = pop();
    }
}
