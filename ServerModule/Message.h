/*
 * Message.h
 *
 *  Created on: Apr 16, 2014
 *      Author: Robert
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <boost/function.hpp>
#include <pthread.h>
#include <list>

#include "common/SmartPtr.h"


class CMessage : public smart_count
{
private:
	int _socket_id;
	std::string _msg;

public:
	CMessage();
	virtual ~CMessage();

public:
	void set_socket_id(int id);
	void append(const void *data, int size);
};

typedef smart_ptr<CMessage> MessagePtr;

typedef boost::function<void (const MessagePtr & msg)> MessageHandler;


class MessageRecvList
{
public:
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	std::list<MessagePtr> _msges;

public:
	MessageRecvList()
	{
	}
	virtual ~MessageRecvList()
	{
		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_cond);
	}

public:
	bool init()
	{
		if(pthread_mutex_init(&_mutex, NULL) != 0)
		{
			return false;
		}
		if(pthread_cond_init(&_cond, NULL) != 0)
		{
			return false;
		}
		return true;
	}

public:
	void add_msg(const MessagePtr& msg)
	{
		_msges.push_back(msg);
	}
	MessagePtr get_msg()
	{
		MessagePtr msg = _msges.front();
		_msges.pop_front();
		return msg;
	}
	bool is_empty()const
	{
		return _msges.empty();
	}
};

#endif /* MESSAGE_H_ */
