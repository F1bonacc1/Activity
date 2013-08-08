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


#ifndef BASEACTIVITY_H
#define BASEACTIVITY_H

#include <string>
#include <list>
#include <boost/thread/thread.hpp>

class BaseActivity
{

public:
    BaseActivity(const std::string& aName, BaseActivity* aParent);
    virtual ~BaseActivity();

    virtual void start();
    virtual void wait();
    
    virtual const char* getName();



protected:
    std::string mName;
    bool mAbortFlag;
    int mActiveChildren;
    virtual bool isStarted();
    virtual void execute();
    virtual void onPrepare() = 0;
    virtual void onStart();
    virtual void onWaitEnd();
    virtual void onChildActivityEnd(BaseActivity* aCaller);
    boost::thread* pThread;
    BaseActivity* mParent;
    std::list<BaseActivity*> mChildren;
    boost::condition_variable mCondVar;
    boost::mutex mMutex;
    
private:
    bool mIsStarted;
    BaseActivity* mLastFinishedChild;
    
};

#endif // BASEACTIVITY_H
