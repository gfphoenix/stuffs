#ifndef _PHOENIX_MUTEX_HPP
#define _PHOENIX_MUTEX_HPP

#include <pthread.h>
#include <boost/noncopyable.hpp>

class Mutex : boost::noncopyable 
{
    public :
        Mutex()
        {
            pthread_mutex_init(&mutex, nullptr);
        }
        ~Mutex()
        {
            pthread_mutex_destroy(&mutex);
        }
        void lock()
        {
            pthread_mutex_lock(&mutex);
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }
        bool tryLock()
        {
            return pthread_mutex_trylock(&mutex);
        }
        friend class Condition;
    private:
        pthread_mutex_t mutex;
};
class MutexGuard : boost::noncopyable 
{
    public:
        explicit MutexGuard(Mutex &mutex)
            :lock(mutex)
        {
            lock.lock();
        }
        ~MutexGuard()
        {
            lock.unlock();
        }
    private:
        Mutex &lock;
};


#endif /* _PHOENIX_MUTEX_HPP */
