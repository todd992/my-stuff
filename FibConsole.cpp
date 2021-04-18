// FibConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <unistd.h>
//#include <io.h>
#include <sys/types.h>
//#include <pthread.h>
//#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <mutex>

#include "thread.h"
#include <thread>
using namespace std;

//#include "unistd.h"
#define THREAD_COUNT 10

static char block[] = "--block";
int test = 0;

std::mutex mutx;           // mutex for critical section

int main(int argc, char** argv)
{
    srand(time(NULL));
    
    static char pidText[] = "PID: ";
    string helpText = "Attach a debugger and execute 'set foo=0' to continue";
    char helloText[] = "Hello World!";

    cout << helloText << std::endl;

    //pthread_t threads[THREAD_COUNT];
    HANDLE  hThreadArray[THREAD_COUNT]{};

    std::thread threads[THREAD_COUNT];
     
    if (argc == 2 && !strcmp(block, argv[1]))
    {
        std::cout << helpText << std::endl;
        volatile int foo = 1;
        while (foo)
            ;
    }

    if (argc == 2 && !strcmp("--crash", argv[1]))
    {
        int foo = 0;
        int bar = 1 / foo;
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
       /* mutx.lock();
        std::cout << "Test " << i << std::endl;
        mutx.unlock();*/
       // pthread_create(&threads[i], NULL, &thread_proc, NULL);
        
        hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            (LPTHREAD_START_ROUTINE)&thread_proc,       // thread function name
            NULL,          // argument to thread function 
            0,                      // use default creation flags 
            (LPDWORD)&threads[i]     // returns the thread identifier
        );    
        //int threadID = threads[i].get_id();

        //std::cout << (LPDWORD)&threads[i] << std::endl;
         
        //std::thread thread(&thread_proc, &threads[i]); 

    }

    WaitForMultipleObjects(THREAD_COUNT, hThreadArray, TRUE, INFINITE);

    //for (auto& th : threads) th.join();
   
    /*for (int i = 0; i < THREAD_COUNT; i++)
    {*/
        //CloseHandle(hThreadArray[i]);

        //if (&threads[i] != NULL)
        //{
        //    HeapFree(GetProcessHeap(), 0, &threads[i]);
        //    threads[i] = NULL;    // Ensure address is not reused.
        //}

        //if (thread_proc != NULL)
        //{
        //    HeapFree(GetProcessHeap(), 0, &threads[i]);
        //    //thread_proc = NULL;    // Ensure address is not reused.
        //}
        //pthread_join(threads[i], NULL);
        //threads[i].join();
        //test++;
    //}

    std::cout << "All threads exited!" << std::endl;

    return 1;
}


//#include <iostream>
//
//int main()
//{
//    std::cout << "Hello World!\n";
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
