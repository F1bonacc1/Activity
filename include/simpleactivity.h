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


#ifndef SIMPLEACTIVITY_H
#define SIMPLEACTIVITY_H
#include "baseactivity.h"
#include "executor.h"
#include <vector>
#include "boost/function.hpp"
#include "boost/bind.hpp"


class SimpleActivity:public BaseActivity
{
public:

    SimpleActivity(const std::string& aName, std::vector< boost::function<bool(void)> >& aFuncs,
                   std::vector< boost::function<bool(void)> >& aRecFuncs, BaseActivity* aParent);
    SimpleActivity(const std::string& aName, boost::function<bool(void)> &aFunc, boost::function<bool(void)> &aRecFunc, BaseActivity* aParent);

    virtual ~SimpleActivity();
    
    virtual void onPrepare(std::vector<boost::function<bool(void)> >& aFuncs, std::vector<boost::function<bool(void)> >& aRecFuncs);
    virtual void onStart();
    virtual bool onRecovery();
    
private:

    boost::function<bool(void)> mFunction;
    boost::function<bool(void)> mRecoveryFunction;
};

#endif // SIMPLEACTIVITY_H
