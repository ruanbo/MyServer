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

class ThreadLib;

class ThreadImpl
{
private:
	ThreadImpl();
	ThreadImpl(const ThreadImpl &)throw();
	void operator = (const ThreadImpl &);

public:
	static const int INVALID_THREAD_ID = 0;
	static const size_t DEFAULT_STACK_SIZE = 0;

public:
	typedef int (*THREAD_FUNCTION)(ThreadLib *thread);
	typedef void *(*THREAD_ROUTINE)(void *params);

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

	static bool wati_for_thead_end(const ThreadStruct &ts, int32_t time_out);

	static void temanite_thread(ThreadStruct &ts);

	static bool is_alive(const ThreadStruct &ts);

	static int get_thread_id(const ThreadStruct &ts);

	static void imp_sleep(int32_t time_ms);
};


class ThreadLib {
public:
	ThreadLib();
	virtual ~ThreadLib();
};



#endif /* THREADLIB_H_ */
