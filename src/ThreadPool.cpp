#include "..\include\mylib\ThreadPool.h"
#include "ThreadPool.h"
#include<iostream>

//�ж��ύ��������е��������������ж��̵߳�������ȫ�Ƿ����
static int message_num = 0;

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

			//�������Ϊ�գ���������ǰ�߳�
			if (owner_pool->message_queue.Size()==0)
			{
				owner_pool->condition.wait(lock);
			}
			
			func = owner_pool->message_queue.Pop(bis_deque);
		}
		if (bis_deque)
		{
			func();
			{
				std::unique_lock<std::mutex> lock(owner_pool->messagenum_mutex);
				if (owner_pool->message_num > 0)
				{
					owner_pool->message_num--;
					if (owner_pool->message_num == 0)
					{
						owner_pool->mainthread_condition.notify_one();
					}
				}
			}
		}
	}
}


void ThreadPool::AddMessage()
{
	{
		std::unique_lock<std::mutex> lock(messagenum_mutex);
		message_num++;
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

void ThreadPool::Init(int thread_num, int cpu_logic_operator_num)
{
	thread_list = std::vector<std::thread>(thread_num);
	for (size_t i = 0; i < thread_num; i++)
	{
		thread_list.at(i) = std::thread( ThreadWorker(this, i));
	}

	cpu_logicoperator_num = cpu_logic_operator_num;
}

void ThreadPool::CloseTheadPool()
{
	bis_running = false;
	//���������̣߳����ȴ�����ִ����ϣ�
	condition.notify_all();
	for (size_t i = 0; i < thread_list.size(); i++)
	{
		if (thread_list.at(i).joinable())
		{
			thread_list.at(i).join();
		}
	}
}

void ThreadPool::Join()
{
	std::unique_lock<std::mutex> lock(mainthread_mutex);
	mainthread_condition.wait(lock);
}
