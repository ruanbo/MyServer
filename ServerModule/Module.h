/*
 * Module.h
 *
 *  Created on: Apr 9, 2014
 *      Author: Robert
 */

#ifndef MODULE_H_
#define MODULE_H_


#include <list>
#include "BasicLogic.h"
#include "Message.h"
#include "IOServer.h"

#include "ScriptHelp/ScriptManager.h"

#include "common/message/MessageStream.h"

class Module
{
private:
	std::string _module_name;
	u_int32_t _module_id;

	BasicLogic* _basic_logic;
	IOServer* _io_server;
	ScriptManager *_script_manager;

	MessageRecvList *_recv_msg;


public:
	Module();
	Module(const std::string &name, u_int32_t id);
	virtual ~Module();

public:
	bool on_start();

	bool start();

	void stop();

	void add_timer(const int64_t interval, const BasicTimerCallback & cb);

	void timer_100ms();

	void timer_1000ms();

public:
	void msg_handler(const MessagePtr& msg);

};




#endif /* MODULE_H_ */
