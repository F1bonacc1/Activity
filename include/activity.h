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


#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <list>
#include <boost/thread/thread.hpp>
#include "activityeventhandler.h"

class Activity
{

public:
    Activity(const std::string& aName, Activity* aParent);
    virtual ~Activity();

    virtual void start();

    virtual void wait();
    
    virtual const char* getName();

    virtual bool IsRecoverable();
    void SetStatus(ActivityEventHandler::ActivityStatus aStatus);

    ActivityEventHandler::ActivityStatus GetStatus() const;


    virtual void setRetryCount(int aCount);

protected:
    std::string mName;
    bool mAbortFlag;
    int mActiveChildren;
    virtual bool isStarted();
    virtual void execute();
    virtual bool onStart();
    virtual void onEnd();
    virtual void onChildActivityEnd(Activity* aCaller);

    virtual bool onRecovery() = 0;

    boost::thread* pThread;
    Activity* mParent;
    std::list<Activity*> mChildren;
    boost::condition_variable mCondVar;
    boost::mutex mMutex;
    bool mIsRecoverable;

private:
    bool mIsStarted;
    int mRetryCount;
    ActivityEventHandler::ActivityStatus mStatus;
};

#endif // ACTIVITY_H
