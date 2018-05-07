#include "worker.h"

Worker::Worker()
{
    m_ID = 0;
    m_name = "DefaultName";
    m_successCount = 0;
    m_failCount = 0;
    isRunning = false;
    m_startValue = 0;
    m_pSharedData = NULL;
    m_pCB = NULL;
}

Worker::Worker(int l_ID, string l_name, int startValue, vector<DWORD64> *l_pSharedData)
{
    m_ID = l_ID;
    m_name = l_name;
    m_successCount = 0;
    m_failCount = 0;
    isRunning = false;
    m_startValue = startValue;
    m_pSharedData = l_pSharedData;
    m_pCB = NULL;
}

Worker::~Worker()
{
    if(m_thread.joinable())
    {
        terminate();
    }
}

int Worker::getID()
{
    return m_ID;
}

string Worker::getName()
{
    return m_name;
}

int Worker::getSuccessCount()
{
    return m_successCount;
}

int Worker::getFailCount()
{
    return m_failCount;
}

void Worker::start()
{
    isRunning = true;
    m_thread = thread(&Worker::writeWord,this);
    m_thread.detach();
}

void Worker::stop()
{
    isRunning = false;
    //    m_thread.join();
}

void Worker::setSuccessCount(int count)
{
    m_successCount = count;
}

void Worker::setFailCount(int count)
{
    m_failCount = count;
}

void Worker::writeWord()
{
    if((NULL != m_pSharedData) && (MAX_SIZE > m_pSharedData->size()))
    {
        //printf("Sandeep-1");
        for(int i = 0 ; i < MAX_SIZE; i++)
        {
            printf("Thread Name: %s ,  i = %d , threadID = %d\n",m_name.c_str(),i,m_ID);
            m_pSharedData->push_back(m_startValue + i);
        }
        if(NULL != m_pCB)
        {
            m_pCB->wcbiCallbackFunction(m_startValue,m_pSharedData,this);
        }

    }

}

void Worker::verifyData(int m_startValue, vector<DWORD64> *l_pSharedData, Worker *CallerWorker)
{
    int success = 0, fail = 0;
    if((NULL != l_pSharedData) && (MAX_SIZE <= l_pSharedData->size()))
    {
        for(int i = 0 ; i < MAX_SIZE; i++)
        {
            if(l_pSharedData->at(i) == (unsigned int)m_startValue + i)
            {
                success++;
            }
            else
            {
                fail++;
            }
        }
        cout<< "Success = " << success <<endl;
        cout<< "Fail = " << fail <<endl;
        if(NULL != CallerWorker)
        {
            CallerWorker->setSuccessCount(success);
            CallerWorker->setFailCount(fail);
        }
    }
}

void Worker::wcbiCallbackFunction(int m_startValue, vector<DWORD64> *l_pSharedData, void *CallerWorker)
{
    this->verifyData(m_startValue,l_pSharedData,(Worker *)CallerWorker);
}

void Worker::connectCallback(WorkerCallbackInterface *cb)
{
    m_pCB = cb;
}


