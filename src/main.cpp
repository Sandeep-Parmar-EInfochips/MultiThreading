#include <iostream>
#include <primary.h>
#include <signal.h>

#include "UnitTest++/UnitTest++.h"

using namespace std;

bool exitFlag = false;

void sigHandler(int)
{
    exitFlag = true;
}

int main()
{
    Primary p;
    signal(SIGTSTP,sigHandler);
    signal(SIGABRT,sigHandler);
    signal(SIGTERM,sigHandler);
    signal(SIGINT, sigHandler);
    while (1)
    {
        if(true == exitFlag)
        {
            break;
        }
    }
    return UnitTest::RunAllTests();
}
