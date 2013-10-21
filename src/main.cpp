#include <iostream>
#include "baseactivity.h"
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

    int ll = 90;

    for(int i = 0; i < lNumThreads; ++i)
    {
        lFuncs.push_back( boost::bind(&Executor::PrintVar, &exec, i, boost::ref(ll)) );
        lRecFuncs.push_back( boost::bind(&Executor::Recovery, &exec) );
    }





    BaseActivity* lActivity = new SimpleActivity("SimpleActivity", lFuncs, lRecFuncs, NULL);
    lActivity->start();
    
    
    
    lActivity->wait();
    Log::DEBUG(LOC, "Test - %d", ll);
    
    delete lActivity;
    return 0;
}
