#ifndef PRIMARY_H
#define PRIMARY_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <list>
#include <stdint.h>
#include <vector>

#include "common.h"
#include "worker.h"

using namespace std;


class Primary
{
public:
    Primary();
    ~Primary();

private:

    void createPrimary();
    vector<DWORD64> *m_pSharedData1 ;
    vector<DWORD64> *m_pSharedData2 ;
    vector<DWORD64> *m_pSharedData3 ;
    vector<DWORD64> *m_pSharedData4 ;

    Worker *m_pWorker1;
    Worker *m_pWorker2;
    Worker *m_pWorker3;
    Worker *m_pWorker4;

};

#endif // PRIMARY_H
