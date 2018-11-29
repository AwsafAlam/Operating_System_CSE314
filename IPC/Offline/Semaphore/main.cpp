#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semutil.h"
#include <iostream>

using namespace std;

int main()
{
    int i;
    Semaphore *sem;

    sem = new Semaphore(1);

    for(i = 0; i < 1000; i++)
    {  
        sem->getLock();
        cout<<"I have the lock:%d"<<getpid()<<endl;
        sem->ReleaseLock();
    }

    return 0;
}