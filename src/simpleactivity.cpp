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
                                       BaseActivity* aParent):
                                       BaseActivity(aName, aParent)
{

    onPrepare(aFuncs, aRecFuncs);
}


SimpleActivity::SimpleActivity(const std::string& aName,
                                      boost::function<bool(void)>& aFunc,
                                      boost::function<bool(void)>& aRecFunc,
                                      BaseActivity* aParent):
                                      BaseActivity(aName, aParent)
{
    mFunction     = aFunc;
    mRecoveryFunction  = aRecFunc;
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
}


void SimpleActivity::onStart()
{
    if(mChildren.size() > 1)
    {
        BaseActivity::onStart();
    }
    else
    {
        mFunction();
    }
}


bool SimpleActivity::onRecovery()
{

    //printf("time %s\n", mName.c_str());

    //boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    //Log::DEBUG(LOC, "Test %s - %d", mName.c_str(), 500);
    return mRecoveryFunction();

}
