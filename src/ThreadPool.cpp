#include "..\include\mylib\ThreadPool.h"
#include "ThreadPool.h"
#include<iostream>

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool* pool, int id):owner_pool(pool),id(id)
{
}

void ThreadPool::ThreadWorker::operator()()
{
	std::function<void()> func;
	bool bis_deque = false;

	while (owner_pool->bis_running)
	{
		{
			std::unique_lock<std::mutex> lock(owner_pool->mutex);

			//任务队列为空，则阻塞当前线程
			if (owner_pool->message_queue.Size()==0)
			{
				owner_pool->condition.wait(lock);
			}
			
			func = owner_pool->message_queue.Pop(bis_deque);
		}
		if (bis_deque)
			func();
	}
}


ThreadPool::ThreadPool():bis_running(true)
{
	//Init(thread_num);
}

ThreadPool::~ThreadPool()
{
	CloseTheadPool();
}

void ThreadPool::Init(int thread_num)
{
	thread_list = std::vector<std::thread>(thread_num);
	for (size_t i = 0; i < thread_num; i++)
	{
		thread_list.at(i) = std::thread( ThreadWorker(this, i));
	}
}

void ThreadPool::CloseTheadPool()
{
	bis_running = false;
	//唤醒所有线程，并等待他们执行完毕；
	Join();
}

void ThreadPool::Join()
{
	condition.notify_all();
	for (size_t i = 0; i < thread_list.size(); i++)
	{
		if (thread_list.at(i).joinable())
		{
			thread_list.at(i).join();
		}
	}
}
