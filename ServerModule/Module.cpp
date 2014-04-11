/*
 * Module.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: Robert
 */


#include "Module.h"
#include <cstdio>
#include <boost/bind.hpp>

static const int64 TIMER_100MS_DELAY = 500;
static const int64 TIMER_1000MS_DELAY = 2000;

Module::Module(const string &name, uint32 id)
{
	_module_name = name;
	_module_id = id;

	_basic_logic = new BasicLogic();
}

Module::~Module()
{
	delete _basic_logic;
}

bool Module::on_start()
{
	if(_basic_logic->start() == false)
	{
		printf("module start error: basic logic start error");
		return false;
	}
	return true;
}

bool Module::start()
{
	add_timer(TIMER_100MS_DELAY,boost::bind(&Module::timer_100ms,this));
	add_timer(TIMER_1000MS_DELAY,boost::bind(&Module::timer_1000ms,this));

	return true;
}

void Module::stop()
{
	_basic_logic->stop();
}

void Module::add_timer(const int64 interval, const BasicTimerCallback & cb)
{
	_basic_logic->add_timer(interval, cb);
}


void Module::timer_100ms()
{
	printf("module:%s, timer_100ms. \n", _module_name.c_str());
}

void Module::timer_1000ms()
{
	printf("module:%s, timer_1000ms. \n", _module_name.c_str());
}
