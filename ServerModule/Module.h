/*
 * Module.h
 *
 *  Created on: Apr 9, 2014
 *      Author: Robert
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "common/Define.h"
#include "BasicLogic.h"


class Module {
private:
	string _module_name;
	uint32 _module_id;

	BasicLogic* _basic_logic;

public:
	Module(const string &name, uint32 id);
	virtual ~Module();

public:
	bool on_start();

	bool start();

	void stop();

	void add_timer(const int64 interval, const BasicTimerCallback & cb);

	void timer_100ms();

	void timer_1000ms();
};




#endif /* MODULE_H_ */
