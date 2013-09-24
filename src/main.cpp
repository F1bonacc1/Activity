#include <iostream>
#include "baseactivity.h"
#include "simpleactivity.h"
#include "simpleactivity.cpp"
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include "executor.h"

#define THREADS_NUM 10

int main(int argc, char **argv) {

    std::vector<int> lVars0, lVars1;
    std::vector<struct SimpActParams> lVecParams;
    int lNumThreads = THREADS_NUM;
    if(argc > 1)
    {
        lNumThreads = atoi(argv[1]);
    }
    for(int i = 0; i < lNumThreads; ++i)
    {
        lVars0.push_back(i);
    }

    for(int i = lNumThreads; i < 2*lNumThreads; ++i)
    {
        lVars1.push_back(i);
    }

    struct SimpActParams lParams0;
    lParams0.mIncomingInt = &lVars0;
    lParams0.mResourceId = 1;

    struct SimpActParams lParams1;
    lParams1.mIncomingInt = &lVars1;
    lParams1.mResourceId = 2;

    lVecParams.push_back(lParams0);
    lVecParams.push_back(lParams1);

    Executor exec(42);
    BaseActivity* lActivity = new SimpleActivity<SimpActParams, Executor>("SimpleActivity", lVecParams, &exec, &Executor::PrintVar, &Executor::Recovery, NULL);
    lActivity->start();
    
    
    
    lActivity->wait();
    
    delete lActivity;
    return 0;
}
