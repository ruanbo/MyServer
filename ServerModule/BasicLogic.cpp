/*
 * BasicLogic.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: root
 */

#include "BasicLogic.h"
#include <time.h>
#include <sys/time.h>

#define MICROSECS_PER_SECOND 1000000
#define MICROSECS_PER_MIILLISEC 1000


BasicLogic::BasicLogic()
{
	_is_working = false;
}

BasicLogic::~BasicLogic()
{
	_timers.clear();
}

bool BasicLogic::start()
{
	bool ret = ThreadLib::start();

	_is_working = true;

	return ret;
}

void BasicLogic::add_timer(int64_t interval_ms, const BasicTimerCallback &cb)
{
	int64_t now_ms = get_now_ms();

	SimpleTimerPtr timer = new SimpleTimer(interval_ms, now_ms+interval_ms, cb);

	_timers.push_back(timer);
}

int64_t BasicLogic::get_now_ms()const
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	int64_t now_us = tv.tv_sec * MICROSECS_PER_SECOND + tv.tv_usec;
	return now_us / MICROSECS_PER_MIILLISEC;
}

void BasicLogic::run()
{
	while(_is_working == true)
	{
		int64_t now_ms = get_now_ms();

		for(std::list<SimpleTimerPtr>::const_iterator iter = _timers.begin(); iter!=_timers.end(); ++iter)
		{
			SimpleTimerPtr timer = *iter;
			int64_t old_when = timer->get_when();

			if(old_when > now_ms)
			{
				continue;
			}
			timer->run();
			timer->set_when(old_when + timer->get_interval());
		}
		sleep(10);
	}
}

bool BasicLogic::stop()
{
	_is_working = false;

	return true;
}
