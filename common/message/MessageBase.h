/*
 * MessageBase.h
 *
 *  Created on: Apr 29, 2014
 *      Author: Robert
 */

#ifndef MESSAGEBASE_H_
#define MESSAGEBASE_H_

#include "StreamReader.h"
#include "StreamWriter.h"
#include "Packet.h"
#include "common/TypeDef.h"

struct Message
{
	virtual ~Message() {}

	virtual void serial(StreamWriter & w) {}

	virtual void unserial(StreamReader & r) {}
};


inline void msg_from_packet(Message *msg, const Packet* packet)
{
	MessageStream * stream = packet->body();

	StreamReader reader(packet->body());

	msg->unserial(reader);
}

template<typename T>
T msg_from_packet(const Packet* packet)
{
	T msg;

	msg_from_packet(&msg, packet);

	return msg;
}



#endif /* MESSAGEBASE_H_ */
