#include <iostream>
//#include <unistd.h>
#include <sys/types.h>
//#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <Windows.h>

#include "thread.h"
#include <mutex>

static int g_tid = 0;
//std::atomic_flag locked = ATOMIC_FLAG_INIT;
std::mutex mtx;           // mutex for critical section


static int fib(int n){
    
    try
    {
        //mtx.lock();

        switch (n) {
        case 0: 
            //mtx.unlock();
            return 1;
        case 1: 
            //mtx.unlock();
            return 1;
        default: 
            //mtx.unlock();
            return (fib(n - 2) + fib(n - 1));
        }
    }
    catch (const std::exception& ex)
    {
        const char * pWhat = ex.what();
        std::cout << pWhat << std::endl;
    }
      
    
}

//void lock() {
//    while (locked.test_and_set(std::memory_order_acquire)) { ; }
//}
//void unlock() {
//    locked.clear(std::memory_order_release);
//}

void * thread_proc(void* ctx)
{

    //lock();
    //mtx.lock();
    int tid = g_tid++;
    
    char thread_name[16]{};
    //thread_name = itoa(tid);
   // sprintf_s(thread_name, "Thread %d", tid);
//#ifdef __APPLE__
//    pthread_setname_np(thread_name);
//#else
//   // pthread_setname_np(pthread_self(), thread_name);
//#endif
    
    // Random delay, 0 - 0.5 sec
    timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 500000000 + ((float)rand() / (float)RAND_MAX) * 500000000;
    //nanosleep(&ts, NULL);
    //Sleep(ts.tv_nsec);
    //Sleep(0);
    volatile int i = 0;

    
    while (i <= 30) {
        mtx.lock();
        std::cout << "Thread " << tid << ": fib(" << i << ") = " << fib(i) << std::endl;
        mtx.unlock();
        i++;
        
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        //Sleep(0);
        //nanosleep(&ts, NULL);
       // Sleep(ts.tv_nsec);
    }
    //mtx.lock();
    //std::string threadName = (std::string)tid; //thread_name;
    //size_t sz = 16;
    //std::string threadName = _itoa_s(tid, thread_name, sz, 10);
    std::cout << "Thread " << std::to_string(tid) << " exited!" << std::endl;
    //mtx.unlock();
    return 0;
}