#include <iostream>
#include "activity.h"
#include "simpleactivity.h"
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include "executor.h"
#include "boost/bind.hpp"
#include <boost/function.hpp>
#include "log.h"

#define THREADS_NUM 10

int main(int argc, char **argv) {

    std::vector< boost::function<bool(void)> > lFuncs;
    std::vector< boost::function<bool(void)> > lRecFuncs;
    int lNumThreads = THREADS_NUM;
    if(argc > 1)
    {
        lNumThreads = atoi(argv[1]);
    }


    Executor exec(42);

    std::vector<int> ll(lNumThreads, 0);

    for(int i = 0; i < lNumThreads; ++i)
    {
        lFuncs.push_back(    boost::bind(&Executor::PrintVar, &exec, i, 5, boost::ref(ll[i])) );
        //lRecFuncs.push_back( boost::bind(&Executor::Recovery, &exec, boost::ref(ll[i])) );
    }





    Activity* lActivity = new SimpleActivity("SimpleActivity", lFuncs, /*lRecFuncs,*/ NULL);
    lActivity->setRetryCount(2);
    lActivity->start();
    
    
    lActivity->wait();
    for(int i = 0; i < lNumThreads; ++i)
    {
        Log::DEBUG(LOC, "%d Test - %d", i, ll[i]);
    }
    
    delete lActivity;
    return 0;
}
