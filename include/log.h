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
#include <sstream>
#include <sys/time.h>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#define LOC __FILE__, __LINE__, __FUNCTION__


class Log
{
public:
    static void DEBUG(const char * file, int line, const char * func, const char * format, ...)
    {
        va_list args;
        va_start (args, format);
        PrintLog("DEBUG", file, line, func, format, args);
        va_end (args);
    }
    static void ERROR(const char * file, int line, const char * func, const char * format, ...)
    {
        va_list args;
        va_start (args, format);
        PrintLog("ERROR", file, line, func, format, args);
        va_end (args);
    }
    static void WARN(const char * file, int line, const char * func, const char * format, ...)
    {
        va_list args;
        va_start (args, format);
        PrintLog("WARN", file, line, func, format, args);
        va_end (args);
    }
    static void INFO(const char * file, int line, const char * func, const char * format, ...)
    {
        va_list args;
        va_start (args, format);
        PrintLog("INFO", file, line, func, format, args);
        va_end (args);
    }

private:
    static void PrintLog(const char * mode, const char * file, int line, const char * func, const char * format, va_list args )
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

        char buffer[512];

        vsprintf (buffer,format, args);
        printf ("%s.%04ld | [%s] | %s : %d \t| %ld \t | %s \t| %s\n",timebuf, lTv.tv_usec / 100 , mode, file, line , getThreadId(), func, buffer);
        

    }
    
    static unsigned long getThreadId(){
        std::string threadId = boost::lexical_cast<std::string>(boost::this_thread::get_id());
        unsigned long threadNumber = 0;
        sscanf(threadId.c_str(), "%lx", &threadNumber);
        return threadNumber;
    }
};

#endif // LOG_H
