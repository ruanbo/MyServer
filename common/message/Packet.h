/*
 * Packet.h
 *
 *  Created on: Apr 29, 2014
 *      Author: Robert
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "MessageStream.h"


class Packet
{
protected:
	int32_t _sock_id;
	MessageStream _body;

private:
	Packet();

public:
	Packet(int32_t sock_id, const char *data, const int32_t size)
	{
		_sock_id = sock_id;
		_body.append(data, size);
	}

public:
	MessageStream *body()
	{
		return &_body;
	}
};









#endif /* PACKET_H_ */
