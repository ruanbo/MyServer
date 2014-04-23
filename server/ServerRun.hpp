/*
 * ServerRun.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Robert
 */


#include "ServerModule/Module.h"
#include <boost/foreach.hpp>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "common/DebugProxy.h"


//#include "server/login/"

void simple_server_test();

//void io_server_test()
//{
//	IOServer my_server;
//
//	my_server.on_start("127.0.0.1", 1002);
//
//	my_server.start();
//
//	my_server.stop();
//}


class ServerRun
{
private:
	std::vector<Module*> _all_modules;

public:
	ServerRun()
	{
	}

	~ServerRun()
	{
	}

public:
	void test()
	{
		Module* module_one = new Module("module_1", 1);
		add_module(module_one);

//		Module* module_two = new Module("module_two", 2);
//		add_module(module_two);
	}

	void add_module(Module* module)
	{
		_all_modules.push_back(module);
	}

	bool run()
	{
		test();

		debug_info("===server run ===");

		BOOST_FOREACH(Module* module, _all_modules)
		{
			if(module->on_start() == false)
			{
				stop();

				return false;
			}
		}

		BOOST_FOREACH(Module* module, _all_modules)
		{
			if(module->start() == false)
			{
				stop();

				return false;
			}
		}

//		Module* module_one = new Module("module_1", 1);
//
//
//		bool ret = module_one->on_start();
//
//		if(ret == true)
//		{
//			module_one->start();
//		}
//
//		module_one->stop();
//
//		delete module_one;

		return true;
	}

	void stop()
	{
		debug_info("----- stop the server ----");

		BOOST_FOREACH(Module* module, _all_modules)
		{
			module->stop();
		}

		while(_all_modules.empty() == false)
		{
			Module *p = *_all_modules.end();

			_all_modules.pop_back();

			delete p;
		}
	}



};
