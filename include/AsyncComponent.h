/*
 * File:   Component.h
 * Author: sergeylapin
 *
 * Created on 27 Сентябрь 2014 г., 12:08
 */
#ifndef AsyncComponent_h
#define	AsyncComponent_h

#include <pthread.h>
#include <Component.h>

class AsyncComponent:public Component {
public:
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
};
#endif