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
	_msg = "";
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

