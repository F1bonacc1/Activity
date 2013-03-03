#include <iostream>
#include "baseactivity.h"
#include "printeractivity.h"
#include <stdio.h>
#include <vector>

#define THREADS_NUM 1000

int main(int argc, char **argv) {

    char name[16];
    std::vector<BaseActivity*> lActivities;
    for(int i = 0; i < THREADS_NUM; ++i)
    {
        sprintf(name, "%s_%d", "Thread", i);
        
        BaseActivity* lActivity = new PrinterActivity(name);
        lActivity->start();
        lActivities.push_back(lActivity);
    }
    for(int i = 0; i < THREADS_NUM; ++i)
    {

        lActivities[i]->wait();
        delete lActivities[i];
    }
    //lActivity.wait();
    return 0;
}
