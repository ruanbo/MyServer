/*
 * ThreadLib.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Robert
 */

#ifndef THREADLIB_H_
#define THREADLIB_H_

#include <pthread.h>
#include <sys/types.h>
#include <boost/function.hpp>

class ThreadLib;

class ThreadImpl
{
private:
	ThreadImpl();
	ThreadImpl(const ThreadImpl &)throw();
	void operator = (const ThreadImpl &);

public:
	static const int WAIT_INFINITE = -1;
	static const int INVALID_THREAD_ID = 0;
	static const size_t DEFAULT_STACK_SIZE = 0;

public:
	typedef int (*THREAD_FUNCTION)(ThreadLib *thread);
	typedef void *(*THREAD_ROUTINE)(void *params);

//	typedef boost::function<void *(void *)> Thread_Routine;
//	typedef boost::function<int (void *)> Thread_Function;

	struct ThreadStruct {
		pthread_t _thread_id;

		ThreadStruct()
		{
			_thread_id = INVALID_THREAD_ID;
		}
		~ThreadStruct()
		{

		}
	};

public:
	static bool create_thread(ThreadStruct &tc, THREAD_FUNCTION thread_func,
							  size_t stack_size, ThreadLib *thread);

	static void destory_thread(ThreadStruct &ts);

	static bool wait_for_thread_end(const ThreadStruct &ts, int32_t time_out);

	static void temanite_thread(ThreadStruct &ts);

	static bool is_alive(const ThreadStruct &ts);

	static int32_t get_thread_id(const ThreadStruct &ts);

	static void imp_sleep(int32_t time_ms);
};


class ThreadLib {
protected:
	ThreadImpl::ThreadStruct _ts;

public:
	static const int WAIT_INFINITE = ThreadImpl::WAIT_INFINITE;
	static const int INVALID_THREAD_ID = ThreadImpl::INVALID_THREAD_ID;
	static const size_t DEFAULT_STACK_SIZE = ThreadImpl::DEFAULT_STACK_SIZE;

public:
	ThreadLib();
	virtual ~ThreadLib();

private:
	ThreadLib(const ThreadLib &)throw();
	void operator = (const ThreadLib &);

public:
	virtual void run() = 0;

	virtual void on_leaking() throw() {}

	static int thread_func(ThreadLib *thread);

	virtual bool start(size_t stack_size=DEFAULT_STACK_SIZE);

	bool wait_for_end(int timeout_ms = WAIT_INFINITE);

	virtual bool is_alive();

	virtual void terminate();

	int32_t get_id();

	static void sleep(int32_t time_ms);
};



#endif /* THREADLIB_H_ */
