#ifndef WORKERCALLBACKINTERFACE_H
#define WORKERCALLBACKINTERFACE_H

#include <vector>
using namespace std;

class WorkerCallbackInterface
{
public:

    WorkerCallbackInterface() {}
//    ~WorkerCallbackInterface() {}
    // pure virutal method
    virtual void wcbiCallbackFunction(int l_startValue, vector<uint64_t> *l_pSharedData, void *CallerWorker )=0;
};

#endif // WORKERCALLBACKINTERFACE_H
