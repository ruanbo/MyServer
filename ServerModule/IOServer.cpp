/*
 * IOServer.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: Robert
 */

#include "IOServer.h"

#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#include <iostream>

#include "common/DebugProxy.h"

using namespace std;


IOServer::IOServer(MessageRecvList* msg_list)
{
	_ip_addr = "";
	_host_port = 0;

	_server_sock = 0;
	_epoll_fd = 0;

	_is_runing = false;

	_msg_list = msg_list;

	_local_msgs = new MessageRecvList();
}

IOServer::~IOServer()
{
	if(_local_msgs)
	{
		delete _local_msgs;
	}
}


void IOServer::set_push_msg_handle(const MessageHandler& handle)
{
	_push_message = handle;
}

void IOServer::push_message(CMessage* msg)
{
	_push_message(msg);
}

bool IOServer::on_start(const std::string &ip, int port)
{
	_ip_addr = ip;
	_host_port = port;

	_server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(_server_sock < 0)
	{
		printf("socket() error");
		return false;
	}

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	if(bind(_server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("bind() error");
		return false;
	}

	bool ret = set_nonblocking(_server_sock);
	if(ret == false)
	{
		printf("set_non_blocking error");
		return false;
	}

	if(listen(_server_sock, MAX_EPOLL_EVENT) < 0)
	{
		printf("listen() error");
		return false;
	}

	_epoll_fd = epoll_create(MAX_EPOLL_EVENT);
	if(_epoll_fd < 0)
	{
		printf("epoll_create() error \n");
		close(_server_sock);
		return false;
	}

	struct epoll_event ep_event;
	ep_event.data.fd = _server_sock;
	ep_event.events = EPOLLIN | EPOLLET;

	if(epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _server_sock, &ep_event) < 0)
	{
		printf("cpoll_ctl() error");
		close(_epoll_fd);
		close(_server_sock);
		return false;
	}

	if(_local_msgs->init() == false)
	{
		printf("io server local msg init error");
		return false;
	}
	return true;
}

bool IOServer::start()
{
	bool ret = ThreadLib::start();

	return ret;
}

void IOServer::run()
{
	_is_runing = true;

	struct epoll_event events[MAX_EPOLL_EVENT];
	int events_num;

	while(_is_runing == true)
	{
		events_num = epoll_wait(_epoll_fd, events, MAX_EPOLL_EVENT, 10);
		if(events_num < 0)
		{
			printf("epoll_wait() error \n");
			continue;
		}
//		boost::asio::detail::mutex::scoped_lock lock(_mutex);
//		lock.lock();

		for(int i=0; i<events_num; ++i)
		{
			int socket_id = events[i].data.fd;
			if(socket_id <= 0)
			{
				continue;
			}

			if(socket_id == _server_sock)
			{
				new_connect();
				continue;
			}
			else if(events[i].events & (EPOLLIN))
			{
				read_op(socket_id);
			}
			else if(events[i].events & (EPOLLOUT))
			{

			}
			else if(events[i].events & (EPOLLRDHUP))
			{
				close_connect(socket_id);
			}
		}

//		lock.unlock();

		sleep(10);
	}
}

void IOServer::stop()
{
	_is_runing = false;

	std::map<int32_t, std::string>::const_iterator iter = _conn_buff.begin();
	for(; iter!=_conn_buff.end(); ++iter)
	{
		cout << "sock id:" << iter->first << ". recv_bytes:" << iter->second.length() << endl;
	}

	printf("local msg length:%d \n", _local_msgs->_total_num);

	close(_epoll_fd);
	close(_server_sock);
}

bool IOServer::set_nonblocking(int socket_id)
{
	int flags = fcntl(socket_id, F_GETFL);
	if(flags < 0)
	{
		printf("fcntl(F_GETFL) error \n");
		return false;
	}

	flags = flags | O_NONBLOCK;

	int ret = fcntl(socket_id, F_SETFL, flags);
	if(ret < 0)
	{
		printf("fcntl(F_SETFL) error \n");
		return false;
	}

	return true;
}

bool IOServer::epoll_ctl_add(int socket_id)
{
	epoll_event ep_event;
	ep_event.data.fd = socket_id;
	ep_event.events = EPOLLIN | EPOLLOUT;

	if(epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, socket_id, &ep_event) < 0)
	{
		return false;
	}
	return true;
}

void IOServer::close_connect(int socket_id)
{
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, socket_id, NULL);

	close(socket_id);

	debug_info("connected socket closed by peer");
}

void IOServer::new_connect()
{
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));

	socklen_t addr_size = sizeof(client_addr);
	int new_fd = accept(_server_sock, (struct sockaddr*)&client_addr, &addr_size);
	if(new_fd < 0)
	{
		printf("accept() error \n");
		return;
	}

	set_nonblocking(new_fd);

	debug_info("new connect:%s", inet_ntoa(client_addr.sin_addr));

	epoll_ctl_add(new_fd);
}

std::string IOServer::get_conn_buf(int32_t sock_id)
{
	std::map<int32_t, std::string>::iterator iter = _conn_buff.find(sock_id);
	if(iter != _conn_buff.end())
	{
		return iter->second;
	}
	return std::string();
}

void IOServer::set_conn_buf(int32_t sock_id, const std::string& str)
{
	_conn_buff[sock_id] = str;
}

void IOServer::read_op(int socket_id)
{
	char read_buf[1024];
	bzero(&read_buf, sizeof(read_buf));

	int read_bytes = read(socket_id, read_buf, sizeof(read_buf));
	if(read_bytes <= 0)
	{
		cout << "read() error" << endl;
		epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, socket_id, NULL);
		close_connect(socket_id);

		return;
	}

	string conn_buf = get_conn_buf(socket_id);

	conn_buf.append(read_buf, read_bytes);

	while(conn_buf.length() > 4)
	{
		int16_t packet_size = 0;
		int16_t packet_type = 0;
		uint32_t msg_id = 0;

		conn_buf.copy((char*)&packet_size, sizeof(packet_size), 0);

		if(packet_size < 1 || packet_size > 1024)
		{
			cout << "packet size error" << endl;
			break;
		}

		if(conn_buf.length() < (u_int32_t)packet_size)
		{
			cout << "conn_buf < packet_size" << endl;
			break;
		}

		conn_buf.copy((char*)&packet_type, sizeof(packet_type), sizeof(packet_size));
		conn_buf.copy((char*)&msg_id, sizeof(msg_id), (sizeof(packet_size) + sizeof(packet_type)) );

		conn_buf.erase(0, packet_size);

		{
			CMessage* new_msg = new CMessage(socket_id, packet_type);
			new_msg->set_socket_id(socket_id);
			_local_msgs->add_msg(new_msg);
		}
	}

	set_conn_buf(socket_id, conn_buf);

//	new_msg->append(read_buf, sizeof(read_buf));

//	{
//		pthread_mutex_lock(&_msg_list->_mutex);
//		_msg_list->add_msg(new_msg);
//		pthread_mutex_unlock(&_msg_list->_mutex);
//	}

	{
//		pthread_mutex_lock(&_local_msgs->_mutex);
//		_local_msgs->add_msg(new_msg);
//		pthread_mutex_unlock(&_local_msgs->_mutex);
	}


//	push_message(new_msg);
}

void IOServer::write_op(int socket_id, const MessagePtr &msg)
{

}
