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

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <vector>
#include <ostream>

struct SimpActParams{
    int mResourceId;
    std::vector<int> *mIncomingInt;
    std::vector<int> *mOutgoingInt;

    std::ostream& operator<<(std::ostream& os)
    {
      os << mResourceId;
      return os;
    }
};

class Executor
{
public:
    
    Executor(int a);
    ~Executor();
    

    bool PrintVar(SimpActParams *var);
    
    bool Recovery();

private:
    int m;
};
    
#endif // EXECUTOR_H
