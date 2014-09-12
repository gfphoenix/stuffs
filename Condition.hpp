#ifndef _PHOENIX_CONDITION_HPP
#define _PHOENIX_CONDITION_HPP

#include <errno.h>
#include <pthread.h>
#include <boost/noncopyable.hpp>
#include "Mutex.hpp"

class Condition : boost::noncopyable 
{
    public:
        Condition(Mutex &mutex)
            : mutex(mutex)
        {
            pthread_cond_init(&cond, nullptr);
        }
        ~Condition()
        {
            pthread_cond_destroy(&cond);
        }
        void wait()
        {
            pthread_cond_wait(&this->cond, &this->mutex.mutex);
        }
        bool waitTimeout(long miliSeconds)
        {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += miliSeconds*1000;
            return pthread_cond_timedwait(&this->cond, &this->mutex.mutex, &ts)==ETIMEDOUT;
        }
        void notify()
        {
            pthread_cond_signal(&this->cond);
        }
        void notifyAll()
        {
            pthread_cond_broadcast(&this->cond);
        }
    private:
        Mutex &mutex;
        pthread_cond_t cond;
};

#endif /* _PHOENIX_CONDITION_HPP */
