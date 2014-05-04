/*
 * CThread.h
 *
 *  Created on: Apr 30, 2014
 *      Author: Robert
 */

#include "Message.h"
#include <pthread.h>

#ifndef CTHREAD_H_
#define CTHREAD_H_

class CThread
{
private:
	pthread_t _thread_id;
	MessageRecvList *_msg_queue;  // weak pointer

private:
	CThread();
public:
	CThread(MessageRecvList *msg_queue);
	virtual ~CThread();

public:
	bool start();

	void stop();

	void run();

};

#endif /* CTHREAD_H_ */
