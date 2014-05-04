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
	int16_t _type;

	std::string _msg;

public:
	CMessage();
	CMessage(int sock_id, int16_t type);
	virtual ~CMessage();

public:
	void set_socket_id(int id);
	void append(const void *data, int size);
};

typedef smart_ptr<CMessage> MessagePtr;

typedef boost::function<void (CMessage* msg)> MessageHandler;


class MessageRecvList
{
public:
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	std::list<CMessage*> _msges;
	u_int64_t _total_num;

public:
	MessageRecvList()
	{
		_total_num = 0;
	}
	virtual ~MessageRecvList()
	{
		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_cond);

		while(_msges.empty() == false)
		{
			CMessage* msg = _msges.front();
			_msges.pop_front();
			delete msg;
		}
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
	void add_msg(CMessage* msg)
	{
		_msges.push_back(msg);
		_total_num++;
	}
	CMessage* get_msg()
	{
		CMessage* msg = _msges.front();
		_msges.pop_front();
		return msg;
	}
	int get_size()
	{
		return _msges.size();
	}
	bool is_empty()const
	{
		return _msges.empty();
	}
};

#endif /* MESSAGE_H_ */
