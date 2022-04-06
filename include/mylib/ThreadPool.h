#pragma once
#ifndef _THREADPOOL_
#define _THREADPOOL_
#include <mutex>
#include<thread>
#include <functional>
#include <future>
#include <utility>
#include"MessageQueue.h"

template<typename T>
class MessageQueue;

class ThreadPool
{
private:
	//内置的线程工作类
	class ThreadWorker
	{	
	private:
		int id;
		ThreadPool* owner_pool;
	public:
		ThreadWorker(ThreadPool* pool, int id);
		~ThreadWorker()=default;

		void operator()();


	};

	//任务队列
	MessageQueue<std::function<void()>> message_queue;
	std::vector<std::thread> thread_list;
	bool bis_running;
	std::mutex mutex;
	std::condition_variable condition;
public:
	ThreadPool();
	virtual ~ThreadPool();
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	ThreadPool& operator=(ThreadPool&&) = delete;

	//初始化线程池
	void Init(int thread_num = 8);

	//等待所有任务完成，并关闭线程池
	void CloseTheadPool();

	//等待所有任务完成
	void Join();

	//提交任务到消息队列
	template <typename F, typename... Args>
	auto SubmitMessage(F&& f, Args &&...args)->std::future<decltype(f(args...))>
	{
		// 连接函数和参数定义，特殊函数类型，避免左右值错误
		std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...); 
		
		//将其封装到一个共享指针中以便能够复制构造
		auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
		
		//使用lambda进行再次封装
		std::function<void()> warpper_func = [task_ptr]()
		{
			(*task_ptr)();
		};

		//将封装之后的函数压入队列
		message_queue.Push(warpper_func);

		//唤醒一个线程
		condition.notify_one();

		return task_ptr->get_future();
	};
};

#endif //_THREADPOOL_

