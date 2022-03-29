#pragma once
#ifndef _MESSAGEQUEUE_
#define _MESSAGEQUEUE_
#include<queue>
#include<mutex>
#include<condition_variable>


template<typename T>
class MessageQueue
{
private:
    std::queue <T> que;
    mutable std::mutex mut;
    std::condition_variable condit;

public:
    MessageQueue& operator=(const MessageQueue&) = delete;
    MessageQueue(const MessageQueue& other) = delete;
    MessageQueue() :que(), mut(), condit() {};
    virtual ~MessageQueue() {};
    void Push(T mes)
    {
        std::lock_guard<std::mutex> lock(mut);
        que.push(mes);
        condit.notify_one();
    };
    T Pop(bool isBlocked = true)
    {

        if (isBlocked)
        {
            xtime abs_time = 5;
            std::unique_lock<std::mutex> lock(mut);
            if (condit.wait_until(lock, abs_time) == cv_status::no_timeout)
            {
                return nullptr;
            }
        }
        T result;
        result = que.front();
        que.pop();
        return result;
    }

    int32_t Size() 
    {
        std::lock_guard <std::mutex> lock(mut);
        return que.size();
    }

    bool Empty() 
    {
        std::lock_guard <std::mutex> lock(mut);
        return que.empty(); 
    }
};

#endif //_MESSAGEQUEUE_

