/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "activity.h"
#include "log.h"



Activity::Activity(const std::string& aName, Activity* aParent)
{
    mName           = aName;
    pThread         = NULL;
    mParent         = aParent;
    mActiveChildren = 0;
    mRetryCount     = 1;
    mIsStarted      = false;
    mIsRecoverable  = false;
}

Activity::~Activity()
{
    std::list<Activity*>::iterator iter = mChildren.begin();
    for(; iter != mChildren.end(); ++iter)
    {
        (*iter)->wait();
        delete *iter;
    }
    SetStatus(ActivityEventHandler::DESTROYED);
}

const char* Activity::getName()
{
    return mName.c_str();
}

bool Activity::onStart()
{
    mActiveChildren = mChildren.size();
    std::list<Activity*>::iterator iter = mChildren.begin();
    for(; iter != mChildren.end(); ++iter)
    {
        (*iter)->start();
    }
    return true;
}

bool Activity::isStarted()
{
    return mIsStarted;
}

void Activity::start()
{
    mIsStarted = true;
    pThread = new boost::thread(&Activity::execute, this);
}

void Activity::wait()
{
    if(pThread)
    {
        Log::DEBUG(LOC,"Waiting for %s finish...", getName());
        pThread->join();
        delete pThread;
        pThread = NULL;
    }
}

void Activity::execute()
{
    //TODO Observer Start
    bool rc = false;

    for (int i = 0; i < mRetryCount; ++i)
    {
        SetStatus(ActivityEventHandler::RUNNING);
        rc = onStart();

        if(!rc && IsRecoverable())
        {
            SetStatus(ActivityEventHandler::RECOVERING);
            rc = onRecovery();
        }
        else
        {
            break;
        }
    }
    SetStatus(rc ? ActivityEventHandler::DONE_OK : ActivityEventHandler::DONE_FAIL);
    onEnd();
    //TODO Observer End
}


void Activity::onEnd()
{
    if(!mChildren.empty())
    {
        Log::DEBUG(LOC, "Waiting for children of %s to finish", getName());
        boost::unique_lock<boost::mutex> lock(mMutex);
        while(mActiveChildren > 0)
        {
            mCondVar.wait(lock);
        }

        Log::DEBUG(LOC,"All the children of %s finished", getName());
    }
    if(mParent)
    {
        mParent->onChildActivityEnd(this);
    }
}


void Activity::onChildActivityEnd(Activity* aCaller)
{
    {
        boost::lock_guard<boost::mutex> lock(mMutex);
        Log::DEBUG(LOC,"On Activity %s End", aCaller->getName());
        mActiveChildren--;
        
        Log::DEBUG(LOC,"Remaining Children: %d", mActiveChildren);
    }
    mCondVar.notify_one();
}


bool Activity::IsRecoverable()
{
    return mIsRecoverable;
}


ActivityEventHandler::ActivityStatus Activity::GetStatus() const
{
    return mStatus;
}


void Activity::SetStatus(ActivityEventHandler::ActivityStatus aStatus)
{
    mStatus = aStatus;
    ActivityEventHandler::SetStatus(getName(), aStatus);
}


void Activity::setRetryCount(int aCount)
{
    mRetryCount = aCount;
    if(mRetryCount < 1) mRetryCount = 1;
    std::list<Activity*>::iterator iter = mChildren.begin();
    for(; iter != mChildren.end(); ++iter)
    {
        (*iter)->setRetryCount(mRetryCount);
    }
}
