#include "thread.hpp" /* Thread header  */
#include "semaphore.hpp" /* Semaphore header */
#include <stdio.h>
#include <iostream>


/* global variables */
Semaphore g_sem(0, 5);

int g_y = 0;

void* SemaphoreTestAction(void* a_arg);
void TestSemaphore();

int main() {

    TestSemaphore();

    return 0;
}


void TestSemaphore() {

    int thr1Arg = 1;
    int thr2Arg = 2;
    int thr3Arg = 3;
    int thr4Arg = 4;

    
        Thread thr1(SemaphoreTestAction, &thr1Arg);
        Thread thr2(SemaphoreTestAction, &thr2Arg);
        Thread thr3(SemaphoreTestAction, &thr3Arg);
        Thread thr4(SemaphoreTestAction, &thr4Arg);

        thr1.Join(NULL);
        thr2.Join(NULL);
        thr3.Join(NULL);
        thr4.Join(NULL);
    
}


void* SemaphoreTestAction(void* a_arg)
{
    g_sem.Wait();
    int value;
    g_sem.GetValue(&value);
    std::cout << value << std::endl;

    g_y += *(int*)a_arg;

    g_sem.Post();
    g_sem.GetValue(&value);
    std::cout << value << std::endl;
}
