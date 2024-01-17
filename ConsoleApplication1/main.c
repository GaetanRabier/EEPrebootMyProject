// MultipleThreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Hints for development:
/*
https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createthread
https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getcurrentthreadid
https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getcurrentthread
https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setthreadaffinitymask
https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority
https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleep
*/

#pragma comment (lib, "kernel32.lib")

#include <stdio.h>
#include <windows.h>
#include <processthreadsapi.h> 

#define PREFERRED_CPU 3
#define DIFFERENT_CPU 4
#define MAXLOOP 4
#define AFFINITY_MASK(n) ((ULONG_PTR)1 << (n))

int periodicSleepThread2 = 0;

int myPrint(char* stringToPrint)
{
    HANDLE hThread = GetCurrentThread();
    int currProcnum = GetCurrentProcessorNumber();
    int currTid = GetCurrentThreadId();
    int currThreadPriority = GetThreadPriority(hThread);

    printf("CPU %d TID %d Priority %d, %s\n", currProcnum, currTid, currThreadPriority, stringToPrint);
    for (int x = 0; x < 100000000; x++) {}  // Busy work to make output more readable so it doesn't scroll by too fast
}

void raiseThreadPriority(HANDLE hThread, int number)
{
    //HANDLE hThread = GetCurrentThread();
    int currThreadPriority = GetThreadPriority(hThread);
    SetThreadPriority(hThread, currThreadPriority + number);
}

void resetThreadPriority(HANDLE hThread)
{
    //HANDLE hThread = GetCurrentThread();
    int currThreadPriority = GetThreadPriority(hThread);
    SetThreadPriority(hThread, 0);
}

int thread1Start()
{
    while (1)    // Thread runs forever
    {
        myPrint("Hello World!");
    }
}

int thread2Start()
{
    while (1)    // Thread runs forever
    {
        if (periodicSleepThread2)
        {
            for (int i = 0; i <= 20; i++)
            {
                myPrint("GoodBye World!");
                if (i == 20)
                {
                    Sleep(10000);
                    i = 0;
                }
            }
        }
        else
        {

            myPrint("GoodBye World!");

        }
    }
}

int main()
{
    HANDLE hThread1 = NULL;
    HANDLE hThread2 = NULL;
    int thread1cpu, thread2cpu;
    ULONG_PTR AffinityMask, CurrentAffinity;

    // Create your threads here
    // Don't forget to do error-handling
  
        hThread1 = CreateThread(
            NULL,
            0,
            thread1Start,
            NULL,
            NULL, NULL
        );
        if (hThread1 == NULL)
        {
            printf("Creation of the thread 1 failed\n");
            ExitProcess;
}


    /*CurrentAffinity = SetThreadAffinityMask(
        hThread1,
        NULL
    );*/

    CurrentAffinity = 0x01;

    SetThreadAffinityMask(
        hThread1,
        CurrentAffinity
    );




    hThread2 = CreateThread(
        NULL,
        0,
        thread2Start,
        NULL,
        NULL, NULL
    );

    if (hThread2 == NULL)
    {
        printf("Creation of the thread 2 failed\n");
        ExitProcess;
    }

    SetThreadAffinityMask(
        hThread2,
        CurrentAffinity
    );

    getch();
    printf("\nSWITCHING THREAD 1 TO HIGHER PRIORITY\n\n");
    raiseThreadPriority(hThread1,1);

    getch();
    printf("\nSWITCHING THREAD 2 TO EVEN HIGHER PRIORITY\n\n");
    raiseThreadPriority(hThread2,2);

    getch();
    printf("\nSWITCHING THREAD 2 TO A DIFFERENT CPU\n\n");
    SetThreadAffinityMask(
        hThread2,
        0x02
    );
    getch();
    printf("\nRESETTING PRIORITIES TO NORMAL\n\n");
    resetThreadPriority(hThread1);
    resetThreadPriority(hThread2);
    periodicSleepThread2 = 1;


    getch();
}