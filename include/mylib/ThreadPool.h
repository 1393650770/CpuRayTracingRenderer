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
	//���õ��̹߳�����
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

	//ѭ�����������ж��ύ��������е��������������ж��̵߳�������ȫ�Ƿ����
	int message_num = 0;
	int cpu_logicoperator_num = 0;
	void AddMessage();

	//�������
	MessageQueue<std::function<void()>> message_queue;
	std::vector<std::thread> thread_list;
	bool bis_running;
	std::mutex mutex;
	std::mutex messagenum_mutex;
	std::mutex mainthread_mutex;
	std::condition_variable mainthread_condition;
	std::condition_variable condition;

public:

	ThreadPool();
	virtual ~ThreadPool();
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
	ThreadPool& operator=(ThreadPool&&) = delete;

	//��ʼ���̳߳�
	void Init(int thread_num = 8,int cpu_logic_operator_num =7);

	//�ȴ�����������ɣ����ر��̳߳�
	void CloseTheadPool();

	//�ȴ������������
	void Join();

	//�ύ������Ϣ����
	template <typename F, typename... Args>
	auto SubmitMessage(F&& f, Args &&...args)->std::future<decltype(f(args...))>
	{
		// ���Ӻ����Ͳ������壬���⺯�����ͣ���������ֵ����
		std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...); 
		
		//�����װ��һ������ָ�����Ա��ܹ����ƹ���
		auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
		
		//ʹ��lambda�����ٴη�װ
		std::function<void()> warpper_func = [task_ptr]()
		{
			(*task_ptr)();
		};

		//����װ֮��ĺ���ѹ�����
		message_queue.Push(warpper_func);
		AddMessage();

		if (thread_list.size() < cpu_logicoperator_num && message_queue.Size() > thread_list.size())
		{
			thread_list.push_back(std::thread(ThreadWorker(this, thread_list.size())));
		}
		//����һ���߳�
		condition.notify_one();

		return task_ptr->get_future();
	};
};

#endif //_THREADPOOL_

