/*
 * main.cpp
 *
 *  Created on: Apr 9, 2014
 *      Author: Robert
 */

#include "common/Define.h"
#include "ServerRun.hpp"

#include <iostream>


int main(int argc, char ** argv)
{
	ServerRun server_run;

	server_run.run();

	string input_str;

	while(true)
	{
		std::cin >> input_str;

		if (input_str == "quit")
		{
			break;
		}
		sleep(1);
	}

	server_run.stop();
	sleep(1);

//	simple_server_test();

	return 0;
}


