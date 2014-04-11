/*
 * ServerRun.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: Robert
 */


#include "ServerModule/Module.h"
#include <boost/foreach.hpp>

#include <string.h>
#include <vector>

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

		Module* module_two = new Module("module_two", 2);
		add_module(module_two);
	}

	void add_module(Module* module)
	{
		_all_modules.push_back(module);
	}

	bool run()
	{
		test();

		BOOST_FOREACH(Module* module, _all_modules)
		{
			if(module->on_start() == false)
			{
				return false;
			}
		}

		BOOST_FOREACH(Module* module, _all_modules)
		{
			if(module->start() == false)
			{
				return false;
			}
		}

		return true;
	}

	void stop()
	{
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
