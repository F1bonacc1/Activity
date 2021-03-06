/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  Eugene <email>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "executor.h"
#include "log.h"

Executor::Executor(int a)
{
    m = a;
}

Executor::~Executor()
{

}

bool Executor::PrintVar(int a, int b, int &aToChange)
{
    Log::DEBUG(LOC, "PrintVar - %d, %d", a, m);
    int ans = 0;

    for(int i = 1; i < 10000000; i++)
    {
        ans += i / b + a;

        if(ans % 2 == 0) ans--;
        else ans /= 2;
    }

    aToChange = ans;
    if(a % 3)
        return true;
    else
        return false;
}


bool Executor::Recovery(int &aToChange)
{
    Log::DEBUG(LOC, "Recovery - %d", m);
    aToChange = m;
    return true;
}

