/*
    Copyright 2013 Eugene <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#define LOC __FILE__, __LINE__, __FUNCTION__

class Log
{
public:
    static void DEBUG(const char * file, int line, const char * func, const char * format, ... )
    {
        //handle time up to secs
        time_t rawtime;
        struct tm * timeinfo;
        char timebuf [10];
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (timebuf, 10, "%X", timeinfo);
            
        //handle msecs
        struct timeval lTv;
        gettimeofday(&lTv, NULL);

        char buffer[256];
        va_list args;
        va_start (args, format);
        vsprintf (buffer,format, args);
        printf ("%s.%04ld | DEBUG | %s : %d \t\t| %s \t| %s\n",timebuf, lTv.tv_usec / 100 ,file, line , func, buffer);
        
        va_end (args);
    }
};

#endif // LOG_H
