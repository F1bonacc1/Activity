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


#include "baseactivity.h"
#include "log.h"
#include <boost/bind.hpp>


BaseActivity::BaseActivity(const std::string& aName, BaseActivity* aParent)
{
    mName           = aName;
    pThread         = NULL;
    mParent         = aParent;
    mAbortFlag      = false;
    mActiveChildren = 0;
    mIsStarted      = false;
}

BaseActivity::~BaseActivity()
{
    std::list<BaseActivity*>::iterator iter = mChildren.begin();
    for(; iter != mChildren.end(); ++iter)
    {
        (*iter)->wait();
        delete *iter;
    }
}

const char* BaseActivity::getName()
{
    return mName.c_str();
}

void BaseActivity::onStart()
{
    mActiveChildren = mChildren.size();
    std::list<BaseActivity*>::iterator iter = mChildren.begin();
    for(; iter != mChildren.end(); ++iter)
    {
        (*iter)->start();
    }
}

bool BaseActivity::isStarted()
{
    return mIsStarted;
}

void BaseActivity::start()
{
    mIsStarted = true;
    pThread = new boost::thread(&BaseActivity::execute, this);
}

void BaseActivity::wait()
{
    if(pThread)
    {
        pThread->join();
        delete pThread;
    }
}

void BaseActivity::execute()
{
    if(!mAbortFlag)
    {
        //TODO Observer Start
        Log::DEBUG(LOC, "Activity %s START", getName());

        onPrepare();
        onStart();
    }
    onWaitEnd();
    Log::DEBUG(LOC, "Activity %s END", getName());
    //TODO Observer End
}

void BaseActivity::onWaitEnd()
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

        /*for (std::list<BaseActivity*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
        {
            if((*it)->isStarted())
            {
                Log::DEBUG(LOC,"Waiting for %s to end", (*it)->getName());
                (*it)->wait();
                Log::DEBUG(LOC,"%s ended", (*it)->getName());
            }
        }*/
    }
    if(mParent)
    {
        mParent->onChildActivityEnd(this);
    }
}


void BaseActivity::onChildActivityEnd(BaseActivity* aCaller)
{
    {
        boost::lock_guard<boost::mutex> lock(mMutex);
        Log::DEBUG(LOC,"On Activity %s End", aCaller->getName());
        mActiveChildren--;
        
        Log::DEBUG(LOC,"Remaining Children: %d", mActiveChildren);
    }
    mCondVar.notify_one();
}


