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
    };
    T Pop(bool& result_bool)
    {
        if (que.empty())
        {
            result_bool = false;
            return nullptr;
        }

        std::unique_lock<std::mutex> lock(mut); 
        
        T result;
        result = std::move(que.front());
        que.pop();
        result_bool = true;
        return std::move(result);
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

