/* 
 * File:   Thread.h
 * Author: sergeylapin
 *
 * Created on 24 Сентябрь 2015 г., 16:23
 */

#ifndef THREAD_H
#define	THREAD_H
#include <pthread.h>


class Thread {
public:
    Thread();
    virtual ~Thread();
    bool StartInternalThread();
    int WaitForInternalThreadToExit();
    int CancelInternalThread();
private:
    /** Implement this method in your subclass with the code you want your thread to run. */   
    virtual void InternalThreadEntry() = 0;
    static void * InternalThreadEntryFunc(void* This);
    pthread_attr_t _attr;
    pthread_t _thread;
};

#endif	/* THREAD_H */

