#include <iostream>
#include "baseactivity.h"
#include "printeractivity.h"


int main(int argc, char **argv) {

    PrinterActivity* lActivity = new PrinterActivity("try");
    lActivity->start();
    lActivity->wait();
    delete lActivity;
    return 0;
}
