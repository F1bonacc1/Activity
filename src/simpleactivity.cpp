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

template <class A1, class E>
SimpleActivity<A1, E>::SimpleActivity(const std::string& aName,
                                       std::vector< A1* >& aVars,
                                       E* aExecutor,
                                       pfcn aFunc,
                                       recfcn aRecFunc,
                                       BaseActivity* aParent):
                                       BaseActivity(aName, aParent)
{
    mVar = NULL;
    onPrepare(aVars, aExecutor, aFunc, aRecFunc);
}

template <class A1, class E>
SimpleActivity<A1, E>::SimpleActivity(const std::string& aName,
                                      A1* aVar,
                                      E* aExecutor,
                                      pfcn aFunc,
                                      recfcn aRecFunc,
                                      BaseActivity* aParent):
                                      BaseActivity(aName, aParent)
{
    mVar      = aVar;
    mFctn     = aFunc;
    mRecFunc  = aRecFunc;
    mExecutor = aExecutor;
}


template <class A1, class E>
SimpleActivity<A1, E>::~SimpleActivity()
{

}

template <class A1, class E>
void SimpleActivity<A1, E>::onPrepare(std::vector<A1 *> &aVars, E *aExecutor, pfcn aFunc, recfcn aRecFunc)
{
    if(aVars.size() > 1)
    {
        for(size_t i = 0; i < aVars.size(); ++i)
        {
            std::ostringstream ost;
            ost << getName() << "_" << i;

            mChildren.push_back(new SimpleActivity(ost.str(), aVars[i], aExecutor, aFunc, aRecFunc, this));
        }
    }
}

template <class A1, class E>
void SimpleActivity<A1, E>::onStart()
{
    if(mChildren.size() > 1)
    {
        BaseActivity::onStart();
    }
    else if(mVar)
    {
        //printf("time %s\n", mName.c_str());

        //boost::this_thread::sleep(boost::posix_time::milliseconds(500));
        //Log::DEBUG(LOC, "Test %s - %d", mName.c_str(), 500);
        (mExecutor->*mFctn)(mVar);
    }
}

template <class A1, class E>
bool SimpleActivity<A1, E>::onRecovery()
{
    if(mVar)
    {
        //printf("time %s\n", mName.c_str());

        //boost::this_thread::sleep(boost::posix_time::milliseconds(500));
        //Log::DEBUG(LOC, "Test %s - %d", mName.c_str(), 500);
        return (mExecutor->*mRecFunc)();
    }
    return false;
}
