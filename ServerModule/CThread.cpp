/*
 * CThread.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: Robert
 */

#include "CThread.h"

#include <iostream>
#include <cstdio>


static void *thread_run(void *p)
{
	CThread* thread = (CThread*)p;

	thread->run();

	return NULL;
}

CThread::CThread()
{
	_thread_id = 0;
	_msg_queue = NULL;
}

CThread::CThread(MessageRecvList *msg_queue)
{
	_thread_id = 0;
	_msg_queue = msg_queue;
}

CThread::~CThread()
{

}


bool CThread::start()
{
	int ret = pthread_create(&_thread_id, NULL, thread_run, (void*)this);
	if(ret != 0)
	{
		std::cout << "CThread pthread_create() error" << std::endl;
		return false;
	}
	return true;
}

void CThread::stop()
{
//	pthread_exit(NULL);
}

void CThread::run()
{
	std::cout << "CThread thread_id:" << _thread_id << std::endl;

	while(true)
	{
		pthread_mutex_lock(&_msg_queue->_mutex);

		if(_msg_queue->is_empty() == false)
		{
			CMessage* one_msg = _msg_queue->get_msg();
			delete one_msg;
//			printf("handle msg. thread_id:%d \n", _thread_id);
		}

		pthread_mutex_unlock(&_msg_queue->_mutex);
	}
}

