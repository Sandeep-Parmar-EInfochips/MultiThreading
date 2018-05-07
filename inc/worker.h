#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <stdint.h>
#include "common.h"
#include "workercallbackinterface.h"


using namespace std;

class Worker: public WorkerCallbackInterface
{
public:
    Worker();
    ~Worker();
    Worker(int l_ID, string l_name, int startValue, vector<DWORD64> *l_pSharedData);
    int getID();
    string getName();
    int getSuccessCount();
    int getFailCount();
    void start();
    void stop();
    void setSuccessCount(int count);
    void setFailCount(int count);
    void verifyData(int m_startValue,vector<DWORD64> *l_pSharedData, Worker *CallerWorker);
    void wcbiCallbackFunction(int m_startValue, vector<DWORD64> *l_pSharedData, void *CallerWorker);
    void connectCallback(WorkerCallbackInterface *cb);

private:
    int m_ID;
    string m_name;
    int m_successCount;
    int m_failCount;
    bool isRunning;
    thread m_thread;
    int m_startValue;
    vector<DWORD64> *m_pSharedData ;
    WorkerCallbackInterface *m_pCB;
//    mutex m_mutex;

    void writeWord();
};

#endif // WORKER_H
