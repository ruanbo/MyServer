/*
 * BasicLogic.h
 *
 *  Created on: Apr 10, 2014
 *      Author: Robert
 */

#ifndef BASICLOGIC_H_
#define BASICLOGIC_H_


#include <string.h>
#include <sys/types.h>
#include <boost/function.hpp>
#include <list>

#include "ThreadLib.h"
#include "common/SmartPtr.h"

typedef boost::function<void ()> BasicTimerCallback;

class SimpleTimer : public smart_count
{
private:
	int64_t _interval;
	int64_t _when;
	BasicTimerCallback _cb;

private:
	SimpleTimer()
	{
		_interval = 0;
		_when = 0;
	}

public:
	SimpleTimer(int64_t interval, int64_t when, const BasicTimerCallback &cb) : _interval(interval), _when(when), _cb(cb)
	{

	}
	virtual ~SimpleTimer()
	{


	}

	void run()
	{
		_cb();
	}

	int64_t get_when()const
	{
		return _when;
	}
	void set_when(int64_t when)
	{
		_when = when;
	}
	int64_t get_interval()const
	{
		return _interval;
	}
};
typedef smart_ptr<SimpleTimer> SimpleTimerPtr;


class BasicLogic : protected ThreadLib
{
private:
	std::list<SimpleTimerPtr> _timers;
	bool _is_working;

public:
	BasicLogic();
	virtual ~BasicLogic();

public:
	bool start();

	void add_timer(int64_t interval_ms, const BasicTimerCallback &cb);

	int64_t get_now_ms()const;

	virtual void run();

	bool stop();
};



#endif /* BASICLOGIC_H_ */
