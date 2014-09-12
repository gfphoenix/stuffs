#ifndef _PHOENIX_THREAD_HPP
#define _PHOENIX_THREAD_HPP
#include <assert.h>
#include <pthread.h>
#include <functional>
#include <boost/noncopyable.hpp>

class Thread : boost::noncopyable
{
    typedef pthread_t tid_t;
    typedef std::function<void()> func_t;
    public:
    Thread(const func_t &fn)
        :fn(fn)
         , tid(0)
         , running(false)
         , joined(false)
    {}
    Thread(func_t &&fn)
        :fn(fn)
         , tid(0)
         , running(false)
         , joined(false)
    {}
    ~Thread()
    {
        if(running && !joined)
            pthread_detach(this->tid);
    }
    bool start()
    {
        int e;
        e = pthread_create(&this->tid, nullptr, Thread::startFn, this);
        this->running   = true;
        if(e==0)
            this->running = false;
        return this->running;
    }
    bool join()
    {
        assert(this->running);
        if(this->joined)
            return true;
        this->joined = true;
        return pthread_join(this->tid, nullptr);
    }
    bool cancel()
    {
        return pthread_cancel(this->tid)==0;
    }
    tid_t getTid()const
    {
        return this->tid;
    }
    bool equals(const tid_t id)const
    {
        return this->tid == id;
    }
    private:
    static void *startFn(void *arg)
    {
        Thread *self = reinterpret_cast<Thread*>(arg);
        self->fn();
        return nullptr;
    }
    private:
        func_t fn;
        pthread_t tid;
        bool running;
        bool joined;
};
#endif /* _PHOENIX_THREAD_HPP */
