/*
 * Module.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: Robert
 */


#include "Module.h"
#include <cstdio>
#include <boost/bind.hpp>
#include "common/DebugProxy.h"

static const int64_t TIMER_100MS_DELAY = 500;
static const int64_t TIMER_1000MS_DELAY = 2000;

Module::Module()
{
	_module_name = "";
	_module_id = 0;

	_basic_logic = NULL;
	_io_server = NULL;
	_script_manager = NULL;
	_recv_msg = NULL;
}

Module::Module(const std::string &name, u_int32_t id)
{
	_module_name = name;
	_module_id = id;

	_script_manager = ScriptManagerInst();

	_recv_msg = new MessageRecvList();

	_basic_logic = new BasicLogic(_recv_msg);
//	_basic_logic->set_message_handle(boost::bind(&Module::msg_handler, this, _1));

	_io_server = new IOServer(_recv_msg);
	_io_server->set_push_msg_handle(boost::bind(&BasicLogic::add_one_msg, _basic_logic, _1));
}

Module::~Module()
{
	if(_basic_logic)
	{
		delete _basic_logic;
	}
	if(_io_server)
	{
		delete _io_server;
	}

	if(_script_manager)
	{
//		delete _script_manager;
	}

	if(_recv_msg)
	{
		delete _recv_msg;
	}
}

bool Module::on_start()
{
	if(_basic_logic->on_start() == false)
	{
		printf("module start error: basic logic start error");
		return false;
	}

	if(_io_server->on_start("127.0.0.1", 1002) == false)
	{
		printf("moduele start error: io_server start error");
		return false;
	}

	if(_script_manager->init() == false)
	{
		printf("script manager init error");
		return false;
	}

	if(_recv_msg->init() == false)
	{
		printf("recv_msg init error");
		return false;
	}

	return true;
}

bool Module::start()
{
	add_timer(TIMER_100MS_DELAY,boost::bind(&Module::timer_100ms,this));
	add_timer(TIMER_1000MS_DELAY,boost::bind(&Module::timer_1000ms,this));

	_io_server->start();
	_basic_logic->start();

	return true;
}

void Module::stop()
{
	_basic_logic->stop();

	_io_server->stop();
}

void Module::add_timer(const int64_t interval, const BasicTimerCallback & cb)
{
	_basic_logic->add_timer(interval, cb);
}


void Module::timer_100ms()
{
//	debug_info("module:%s, timer_100ms.", _module_name.c_str());
}

void Module::timer_1000ms()
{
//	debug_info("module:%s, timer_1000ms. \n", _module_name.c_str());
	debug_info("total:%d. left:%d", _recv_msg->_total_num, _basic_logic->get_msg_size());
}

void Module::msg_handler(const MessagePtr& msg)
{

}
