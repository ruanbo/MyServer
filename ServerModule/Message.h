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
#include "common/SmartPtr.h"

class Message : public smart_count
{
private:
	int _socket_id;
	std::string _msg;

public:
	Message();
	virtual ~Message();

public:
	void set_socket_id(int id);
	void append(const void *data, int size);
};

typedef smart_ptr<Message> MessagePtr;

typedef boost::function<void (const MessagePtr & msg)> MessageHandler;

#endif /* MESSAGE_H_ */
