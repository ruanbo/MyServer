/*
 * IOServer.h
 *
 *  Created on: Apr 12, 2014
 *      Author: Robert
 */

#ifndef IOSERVER_H_
#define IOSERVER_H_


#include "ThreadLib.h"
#include "Message.h"
#include <boost/asio/detail/mutex.hpp>


class IOServer : protected ThreadLib
{
private:
	std::string _ip_addr;
	int _host_port;
	int _server_sock;
	int _epoll_fd;
	bool _is_runing;
	boost::asio::detail::mutex _mutex;

	MessageHandler _push_message;

#define MAX_EPOLL_EVENT  512

public:
	IOServer();
	virtual ~IOServer();

public:
	void set_push_msg_handle(const MessageHandler& handle);

	void push_message(const MessagePtr & msg);

	bool on_start(const std::string &ip, int port);

	bool start();

	virtual void run();

	void stop();

public:
	bool set_nonblocking(int socket_id);

	bool epoll_ctl_add(int socket_id);

	void close_connect(int socket_id);

	void new_connect();

	void read_op(int socket_id);

	void write_op(int socket_id, const MessagePtr &msg);

};





#endif /* IOSERVER_H_ */
