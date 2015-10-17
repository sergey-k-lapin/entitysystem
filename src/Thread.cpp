/* 
 * File:   Thread.cpp
 * Author: sergeylapin
 * 
 * Created on 24 Сентябрь 2015 г., 16:23
 */

#include "Thread.h"

Thread::Thread() {
}

Thread::~Thread() {
}

/** Returns true if the thread was successfully started, false if there was an error starting the thread */
bool Thread::StartInternalThread() {
        return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
}

/** Will not return until the internal thread has exited. */
void Thread::WaitForInternalThreadToExit() {
    (void) pthread_join(_thread, NULL);
}

void* Thread::InternalThreadEntryFunc(void * This){
    (( Thread* )This)->InternalThreadEntry(); return NULL;
}
