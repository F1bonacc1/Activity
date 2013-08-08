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

template<class A1, class E>
//template<class A1, class A2, class A3, class A4, class A5, class E>
class SimpleActivity:public BaseActivity
{
public:
    
    typedef bool (E::*pfcn)(A1);
    //typedef bool (E::*pfcn2)(A1, A2);
    SimpleActivity(const std::string& aName, std::vector< A1 >& aVars, E* aExecutor, pfcn aFunc, BaseActivity* aParent);
    /*SimpleActivity(const std::string& aName, std::vector< A1 >& aVars, E* aExecutor, pfcn aFunc, BaseActivity* aParent);
    SimpleActivity(const std::string& aName, std::vector< A1 >& aVars, E* aExecutor, pfcn aFunc, BaseActivity* aParent);
    SimpleActivity(const std::string& aName, std::vector< A1 >& aVars, E* aExecutor, pfcn aFunc, BaseActivity* aParent);*/
    virtual ~SimpleActivity();

    virtual void onPrepare();
    virtual void onStart();
    
private:
    std::vector<A1> mVars;
    pfcn mFctn;
    E* mExecutor;
};

#endif // SIMPLEACTIVITY_H
