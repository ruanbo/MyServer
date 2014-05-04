/*
 * Message.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: Robert
 */

#include "Message.h"

CMessage::CMessage()
{
	_socket_id = 0;
	_type = 0;
	_msg = "";
}

CMessage::CMessage(int sock_id, int16_t type)
{
	_socket_id = sock_id;
	_type = type;
}

CMessage::~CMessage()
{

}

void CMessage::set_socket_id(int id)
{
	_socket_id = id;
}

void CMessage::append(const void *data, int size)
{
	_msg.append((const char*)data, size);
}

