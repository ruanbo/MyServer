/*
 * MsgStructs.h
 *
 *  Created on: Apr 29, 2014
 *      Author: Robert
 */

#ifndef MSGSTRUCTS_H_
#define MSGSTRUCTS_H_

#include "MessageBase.h"

struct MsgLogin : public Message
{
	uint32 _pid;
	std::string _chat;

	void serial(StreamWriter &w)
	{
		w.write_uint32(_pid);
		w.write_string(_chat);
	}

	void unserial(StreamReader &r)
	{
		_pid = r.read_uint32();
		_chat = r.read_string();
	}
};



#endif /* MSGSTRUCTS_H_ */
