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

    std::vector<int> lVars;
    int lNumThreads = THREADS_NUM;
    if(argc > 1)
    {
        lNumThreads = atoi(argv[1]);
    }
    for(int i = 0; i < lNumThreads; ++i)
    {
        lVars.push_back(i);
    }

    Executor exec(42);
    BaseActivity* lActivity = new SimpleActivity<int, Executor>("SimpleActivity", lVars, &exec, &Executor::PrintVar, NULL);
    lActivity->start();
    
    
    
    lActivity->wait();
    
    delete lActivity;
    return 0;
}
