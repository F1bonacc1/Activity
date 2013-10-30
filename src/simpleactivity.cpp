/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

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


#include "simpleactivity.h"
#include <stdio.h>
#include "log.h"
#include "sstream"


SimpleActivity::SimpleActivity(const std::string& aName,
                                       std::vector< boost::function<bool(void)> >& aFuncs,
                                       std::vector< boost::function<bool(void)> >& aRecFuncs,
                                       Activity* aParent):
                                       Activity(aName, aParent)
{
    onPrepare(aFuncs, aRecFuncs);
}

SimpleActivity::SimpleActivity(const std::string& aName,
                                       std::vector< boost::function<bool(void)> >& aFuncs,
                                       Activity* aParent):
                                       Activity(aName, aParent)
{
    onPrepare(aFuncs);
}


SimpleActivity::SimpleActivity(const std::string& aName,
                                      boost::function<bool(void)>& aFunc,
                                      boost::function<bool(void)>& aRecFunc,
                                      Activity* aParent):
                                      Activity(aName, aParent)
{
    mIsRecoverable     = true;
    mFunction          = aFunc;
    mRecoveryFunction  = aRecFunc;
}

SimpleActivity::SimpleActivity(const std::string& aName,
                                      boost::function<bool(void)>& aFunc,
                                      Activity* aParent):
                                      Activity(aName, aParent)
{
    mFunction      = aFunc;
}

SimpleActivity::~SimpleActivity()
{

}


void SimpleActivity::onPrepare(std::vector<boost::function<bool(void)> >& aFuncs, std::vector<boost::function<bool(void)> >& aRecFuncs)
{
    if(aFuncs.size() > 1)
    {
        for(size_t i = 0; i < aFuncs.size(); ++i)
        {
            std::ostringstream ost;
            ost << getName() << "_" << i;

            mChildren.push_back(new SimpleActivity(ost.str(), aFuncs[i], aRecFuncs[i], this));
        }
    }
    else if(aFuncs.size() == 1)
    {
        mFunction          = aFuncs[0];
        mRecoveryFunction  = aRecFuncs[0];
        mIsRecoverable     = true;
    }
}

void SimpleActivity::onPrepare(std::vector<boost::function<bool(void)> >& aFuncs)
{
    if(aFuncs.size() > 1)
    {
        for(size_t i = 0; i < aFuncs.size(); ++i)
        {
            std::ostringstream ost;
            ost << getName() << "_" << i;

            mChildren.push_back(new SimpleActivity(ost.str(), aFuncs[i], this));
        }
    }
    else if(aFuncs.size() == 1)
    {
        mFunction = aFuncs[0];
    }
}


bool SimpleActivity::onStart()
{
    bool rc = false;
    if(mChildren.size() > 1)
    {
        rc = Activity::onStart();
    }
    else
    {
        if(mFunction && !mFunction.empty())
        {
            rc = mFunction();
        }
        else
        {
            Log::ERROR(LOC, "Unable to execute %s! Function undefined!", mName.c_str());
        }

    }
    return rc;
}


bool SimpleActivity::onRecovery()
{

    //printf("time %s\n", mName.c_str());

    //boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    //Log::DEBUG(LOC, "Test %s - %d", mName.c_str(), 500);
    return mRecoveryFunction();
}
