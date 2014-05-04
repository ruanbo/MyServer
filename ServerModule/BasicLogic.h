/*
 * BasicLogic.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Robert
 */

#ifndef BASICLOGIC_H_
#define BASICLOGIC_H_


#include <string.h>
#include <sys/types.h>
#include <boost/function.hpp>
#include <list>
#include <vector>

#include "ThreadLib.h"
#include "common/SmartPtr.h"
#include "CThread.h"

#include "Message.h"


typedef boost::function<void ()> BasicTimerCallback;

class SimpleTimer : public smart_count
{
private:
	int64_t _interval;
	int64_t _when;
	BasicTimerCallback _cb;

private:
	SimpleTimer()
	{
		_interval = 0;
		_when = 0;
	}

public:
	SimpleTimer(int64_t interval, int64_t when, const BasicTimerCallback &cb) : _interval(interval), _when(when), _cb(cb)
	{

	}
	virtual ~SimpleTimer()
	{


	}

	void run()
	{
		_cb();
	}

	int64_t get_when()const
	{
		return _when;
	}
	void set_when(int64_t when)
	{
		_when = when;
	}
	int64_t get_interval()const
	{
		return _interval;
	}
};
typedef smart_ptr<SimpleTimer> SimpleTimerPtr;


//struct RecvMsgQueue
//{
//	std::list<MessagePtr> _msges;
//
//	void add_msg(const MessagePtr& one_msg)
//	{
//		_msges.push_back(one_msg);
//	}
//
//	bool is_empty()const
//	{
//		return _msges.empty();
//	}
//
//	MessagePtr get_one_msg()
//	{
//		MessagePtr one_msg = _msges.front();
//		_msges.pop_front();
//
//		return one_msg;
//	}
//
//	int32_t get_size()const
//	{
//		return _msges.size();
//	}
//};
//
//struct SendMsgQueue
//{
//	std::list<MessagePtr> _msges;
//};



class BasicLogic : protected ThreadLib
{
private:
	std::list<SimpleTimerPtr> _timers;
	bool _is_working;

//	RecvMsgQueue *_msg_queue;
	MessageRecvList *_msg_list;

	MessageHandler _msg_handle;

	std::list<CThread*> _thread_pool;

#define THREAD_POOL_SIZE 1

public:
	BasicLogic(MessageRecvList* msg_list);
	virtual ~BasicLogic();

public:
	bool on_start();

	bool start();

	void add_timer(int64_t interval_ms, const BasicTimerCallback &cb);

	int64_t get_now_ms()const;

	virtual void run();

	bool stop();

public:
	void add_one_msg(CMessage* msg);

	void set_message_handle(const MessageHandler & handle);

	void handle_one_msg(const MessagePtr& msg);

	int32_t get_msg_size()const;
};



#endif /* BASICLOGIC_H_ */
