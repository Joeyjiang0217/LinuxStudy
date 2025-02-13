#pragma once
#include <iostream>
#include <vector>
#include <semaphore.h>
#include <pthread.h>

const static int defaultcap = 5;

template <class T>
class RingQueue
{
private:
    void P(sem_t& sem)
    {
        sem_wait(&sem);
    }

    void V(sem_t& sem)
    {
        sem_post(&sem);
    }

    void Lock(pthread_mutex_t& mutex)
    {
        pthread_mutex_lock(&mutex);
    }

    void Unlock(pthread_mutex_t& mutex)
    {
        pthread_mutex_unlock(&mutex);
    }
public:
    RingQueue(int cap = defaultcap)
        : ringqueue_(cap),
          cap_(cap),
          c_step_(0),
          p_step_(0)
    {
        sem_init(&cdata_sem_, 0, 0);
        sem_init(&pspace_sem_, 0, cap_);

        pthread_mutex_init(&c_mutex_, nullptr);
        pthread_mutex_init(&p_mutex_, nullptr);
    }

    void Push(const T& in)
    {
        P(pspace_sem_);
        Lock(p_mutex_);
        ringqueue_[p_step_] = in;
        p_step_++;
        p_step_ = p_step_ % cap_;
        Unlock(p_mutex_);
        V(cdata_sem_);
    }

    void Pop(T* out)
    {
        P(cdata_sem_);
        Lock(c_mutex_);
        *out = ringqueue_[c_step_];
        c_step_++;
        c_step_ %= cap_;
        Unlock(c_mutex_);
        V(pspace_sem_);
    }

    ~RingQueue()
    {
        sem_destroy(&cdata_sem_);
        sem_destroy(&pspace_sem_);
        pthread_mutex_destroy(&c_mutex_);
        pthread_mutex_destroy(&p_mutex_);
    }

private:
    std::vector<T> ringqueue_;
    int cap_;
    int c_step_;
    int p_step_;
    sem_t cdata_sem_;
    sem_t pspace_sem_;
    pthread_mutex_t c_mutex_;
    pthread_mutex_t p_mutex_;
};