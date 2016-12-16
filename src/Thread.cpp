/* 
 * File:   Thread.cpp
 * Author: sergeylapin
 * 
 * Created on 24 Сентябрь 2015 г., 16:23
 */

#include <Thread.h>
#include <errno.h>
#include <iostream>

Thread::Thread() {
}

Thread::~Thread() {
}

/** Returns true if the thread was successfully started, false if there was an error starting the thread */
bool Thread::StartInternalThread() {
        return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
}

/** Will not return until the internal thread has exited. */
int Thread::WaitForInternalThreadToExit() {
    return pthread_join(_thread, NULL);
}

void* Thread::InternalThreadEntryFunc(void * This){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    (( Thread* )This)->InternalThreadEntry(); return NULL;
}

int Thread::CancelInternalThread(){
    int err = pthread_cancel(_thread);
    if (err != ESRCH) {
        void *res;
        err = pthread_join(_thread, &res);
//        if (res == PTHREAD_CANCELED) {
//            printf("Thread was canceled\n");
//        }
    }
    return err;
}