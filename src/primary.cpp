#include "primary.h"

#include "UnitTest++/UnitTest++.h"

Primary::Primary()
{    
    thread l_thread = thread(&Primary::createPrimary,this);
    l_thread.join();
}

Primary::~Primary()
{
    cout << "" << endl;
    cout << "Worker-1 Success Count is : " << m_pWorker1->getSuccessCount() << endl;
    cout << "Worker-1 Fail Count is : " << m_pWorker1->getFailCount() << endl;

    cout << "Worker-2 Success Count is : " << m_pWorker2->getSuccessCount() << endl;
    cout << "Worker-2 Fail Count is : " << m_pWorker2->getFailCount() << endl;

    cout << "Worker-3 Success Count is : " << m_pWorker3->getSuccessCount() << endl;
    cout << "Worker-3 Fail Count is : " << m_pWorker3->getFailCount() << endl;

    cout << "Worker-4 Success Count is : " << m_pWorker4->getSuccessCount() << endl;
    cout << "Worker-4 Fail Count is : " << m_pWorker4->getFailCount() << endl;

    delete m_pSharedData1;
    delete m_pSharedData2;
    delete m_pSharedData3;
    delete m_pSharedData4;

    delete m_pWorker1;
    delete m_pWorker2;
    delete m_pWorker3;
    delete m_pWorker4;
}


void Primary::createPrimary()
{
    m_pSharedData1 = new vector<DWORD64>;
    m_pSharedData2 = new vector<DWORD64>;
    m_pSharedData3 = new vector<DWORD64>;
    m_pSharedData4 = new vector<DWORD64>;

    m_pWorker1 = new Worker(1,"W1",100,m_pSharedData1);
    m_pWorker2 = new Worker(2,"W2",300,m_pSharedData2);
    m_pWorker3 = new Worker(3,"W3",600,m_pSharedData3);
    m_pWorker4 = new Worker(4,"W4",900,m_pSharedData4);

    m_pWorker1->connectCallback(m_pWorker2);
    m_pWorker2->connectCallback(m_pWorker3);
    m_pWorker3->connectCallback(m_pWorker4);
    m_pWorker4->connectCallback(m_pWorker1);

    m_pWorker1->start();
    m_pWorker2->start();
    m_pWorker3->start();
    m_pWorker4->start();
}

TEST(Sanity)
{
    vector<DWORD64> SharedData1;
    vector<DWORD64> SharedData2;
    vector<DWORD64> SharedData3;
    vector<DWORD64> SharedData4;

    Worker Worker1(1,"W1",100,&SharedData1);
    Worker Worker2(2,"W2",300,&SharedData2);
    Worker Worker3(3,"W3",600,&SharedData3);
    Worker Worker4(4,"W4",900,&SharedData4);

    Worker1.connectCallback(&Worker2);
    Worker2.connectCallback(&Worker3);
    Worker3.connectCallback(&Worker4);
    Worker4.connectCallback(&Worker1);

    Worker1.start();
    Worker2.start();
    Worker3.start();
    Worker4.start();

    this_thread::sleep_for(chrono::seconds(1));

   CHECK_EQUAL(115, Worker1.getSuccessCount());
   CHECK_EQUAL(0, Worker1.getFailCount());

   CHECK_EQUAL(115, Worker2.getSuccessCount());
   CHECK_EQUAL(0, Worker2.getFailCount());

   CHECK_EQUAL(115, Worker3.getSuccessCount());
   CHECK_EQUAL(0, Worker3.getFailCount());

   CHECK_EQUAL(115, Worker4.getSuccessCount());
   CHECK_EQUAL(0, Worker4.getFailCount());
}


