/*
 * Message.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: Robert
 */

#include "Message.h"

Message::Message()
{
	_socket_id = 0;
	_msg = "";
}

Message::~Message()
{

}

void Message::set_socket_id(int id)
{
	_socket_id = id;
}

void Message::append(const void *data, int size)
{
	_msg.append((const char*)data, size);
}

