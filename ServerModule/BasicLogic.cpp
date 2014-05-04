/*
 * BasicLogic.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: root
 */

#include "BasicLogic.h"
#include <time.h>
#include <sys/time.h>

using namespace std;

#define MICROSECS_PER_SECOND 1000000
#define MICROSECS_PER_MIILLISEC 1000


BasicLogic::BasicLogic(MessageRecvList* msg_list)
{
	_is_working = false;

//	_msg_queue = new RecvMsgQueue();
	_msg_list = msg_list;
}

BasicLogic::~BasicLogic()
{
	_timers.clear();

//	if(_msg_queue != NULL)
//	{
//		delete _msg_queue;
//	}
	if(_msg_list)
	{
//		delete _msg_list;
	}

	while(_thread_pool.empty() == false)
	{
		CThread* one_thread = _thread_pool.front();
		_thread_pool.pop_front();

		delete one_thread;
	}
}

bool BasicLogic::on_start()
{
	bool ret = true;

	for(int i=0; i<THREAD_POOL_SIZE; ++i)
	{
		CThread *one_thread = new CThread(_msg_list);

		_thread_pool.push_back(one_thread);
	}

	return ret;
}

bool BasicLogic::start()
{
	list<CThread*>::const_iterator iter = _thread_pool.begin();
	for(; iter!=_thread_pool.end(); ++iter)
	{
		(*iter)->start();
	}

	bool ret = ThreadLib::start();

	_is_working = true;

	return ret;
}

void BasicLogic::add_timer(int64_t interval_ms, const BasicTimerCallback &cb)
{
	int64_t now_ms = get_now_ms();

	SimpleTimerPtr timer = new SimpleTimer(interval_ms, now_ms+interval_ms, cb);

	_timers.push_back(timer);
}

int64_t BasicLogic::get_now_ms()const
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	int64_t now_us = tv.tv_sec * MICROSECS_PER_SECOND + tv.tv_usec;
	return now_us / MICROSECS_PER_MIILLISEC;
}

void BasicLogic::run()
{
	while(_is_working == true)
	{
		int64_t now_ms = get_now_ms();

		for(std::list<SimpleTimerPtr>::const_iterator iter = _timers.begin(); iter!=_timers.end(); ++iter)
		{
			SimpleTimerPtr timer = *iter;
			int64_t old_when = timer->get_when();

			if(old_when > now_ms)
			{
				continue;
			}
			timer->run();
			timer->set_when(old_when + timer->get_interval());
		}
		sleep(10);
	}
}

bool BasicLogic::stop()
{
	_is_working = false;

	list<CThread*>::iterator iter = _thread_pool.begin();
	for(; iter!=_thread_pool.end(); ++iter)
	{
		CThread *thread = *iter;
		thread->stop();
//		(*iter)->stop();
	}

	return true;
}


void BasicLogic::add_one_msg(CMessage* msg)
{
//	_msg_queue->add_msg(msg);
	_msg_list->add_msg(msg);
}

void BasicLogic::set_message_handle(const MessageHandler & handle)
{
	_msg_handle = handle;
}

void BasicLogic::handle_one_msg(const MessagePtr& msg)
{
//	_msg_handle(msg);
}

int32_t BasicLogic::get_msg_size()const
{
//	return _msg_queue->get_size();
	return _msg_list->get_size();
}
