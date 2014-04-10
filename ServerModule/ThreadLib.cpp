/*
 * ThreadLib.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: Robert
 */



#include "ThreadLib.h"
#include <unistd.h>

bool ThreadImpl::create_thread(ThreadStruct &ts, THREAD_FUNCTION thread_func,
					  size_t stack_size, ThreadLib *thread)
{
	pthread_attr_t *p_attr = NULL;
//	pthread_attr_t attr;

	if(stack_size != DEFAULT_STACK_SIZE)
	{
		if(pthread_attr_init(p_attr) != 0)
		{
			return false;
		}
		if(pthread_attr_setstacksize(p_attr, stack_size) != 0)
		{
			pthread_attr_destroy(p_attr);
			return false;
		}
	}

	int ret = pthread_create(&(ts._thread_id), p_attr, (THREAD_ROUTINE)thread_func, (void*)thread);
	if(p_attr != NULL)
	{
		pthread_attr_destroy(p_attr);
	}
	if(ret != 0)
	{
		return false;
	}

	pthread_detach(ts._thread_id);

	return true;
}

void ThreadImpl::destory_thread(ThreadStruct &ts)
{
	pthread_exit(NULL);
}

bool ThreadImpl::wati_for_thead_end(const ThreadStruct &ts, int32_t time_out)
{
	if(is_alive(ts) == false)
	{
		return true;
	}

	imp_sleep(time_out);

	return false;
}

void ThreadImpl::temanite_thread(ThreadStruct &ts)
{
	pthread_cancel(ts._thread_id);
}

bool ThreadImpl::is_alive(const ThreadStruct &ts)
{
	int policy;
	struct sched_param sp;

	int ret = pthread_getschedparam(ts._thread_id, &policy, &sp);

	if(ret == 0)
	{
		return true;
	}

	return false;
}

int ThreadImpl::get_thread_id(const ThreadStruct &ts)
{
	return (int)(ts._thread_id);
}

void ThreadImpl::imp_sleep(int32_t time_ms)
{
	int32_t sleep_s = time_ms / 1000;
	int32_t sleep_us = (time_ms % 1000) * 1000;

	if(sleep_s > 0)
	{
		sleep(sleep_s);
	}
	if(sleep_us > 0)
	{
		usleep(sleep_us);
	}
}

ThreadLib::ThreadLib()
{

}

ThreadLib::~ThreadLib()
{

}

