/*
 * SimpleServer.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Robert
 */


#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <string.h>
#include <iostream>
using namespace std;


const int SERV_PORT = 1002;
const int MAX_EVENT = 512;
const string SERV_ADDR = "127.0.0.1";

static void set_nonblocking(int sock)
{
	int ret;
	ret = fcntl(sock, F_GETFL);
	if(ret < 0)
	{
		cout << "fcntl(F_GETFL) error" << endl;
		exit(0);
	}

	ret = ret | O_NONBLOCK;

	if(fcntl(sock, F_SETFL, ret) < 0)
	{
		cout << "fcntl(F_SETFL) error" << endl;
		exit(0);
	}
	return;
}

void simple_server_test()
{
	int ret;
	int server_sock;
	int epoll_fd;

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock < 0)
	{
		cout << "socket() error" << endl;
		exit(0);
	}

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = SERV_PORT;
	server_addr.sin_addr.s_addr = inet_addr(SERV_ADDR.c_str());

	ret = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(ret < 0)
	{
		cout << "bind() error" << endl;
		exit(0);
	}

	set_nonblocking(server_sock);

	ret = listen(server_sock, MAX_EVENT);
	if(ret < 0)
	{
		cout << "listen() error" << endl;
		exit(0);
	}

	epoll_fd = epoll_create(MAX_EVENT);
	if(epoll_fd < 0)
	{
		cout << "epoll_create() error" << endl;
		exit(0);
	}

	struct epoll_event ep_event;
	ep_event.data.fd = server_sock;
	ep_event.events = EPOLLIN | EPOLLET;

	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_sock, &ep_event) < 0)
	{
		cout << "epoll_ctl() error" << endl;
		exit(0);
	}

	int ep_num;
	struct epoll_event events[MAX_EVENT];
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	socklen_t addr_size = sizeof(struct sockaddr_in);

	while(true)
	{
		ep_num = epoll_wait(epoll_fd, events, MAX_EVENT, 100);
		if(ep_num < 0)
		{
			cout << "epoll_wait error" << endl;
			exit(0);
		}

		for(int n=0; n<ep_num; ++n)
		{
			if(events[n].data.fd == server_sock)
			{
				int fd_new = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
				if(fd_new < 0)
				{
					cout << "accept error" << endl;
					continue;
				}
				set_nonblocking(fd_new);
				string client_addr_str = inet_ntoa(client_addr.sin_addr);
				cout << "new connect:" << client_addr_str << "port:" << client_addr.sin_port << endl;

				ep_event.data.fd = fd_new;
				ep_event.events = EPOLLIN | EPOLLOUT;
				epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd_new, &ep_event);
			}
			else if(events[n].events & EPOLLIN)
			{
				int sockfd = events[n].data.fd;
				if(sockfd < 0)
				{
					continue;
				}
				char read_str[1024];
				bzero(&read_str, sizeof(read_str));
				int read_size = read(sockfd, read_str, 1024);
				if(read_size == 0)
				{
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sockfd, NULL);
					close(sockfd);
					events[n].data.fd = -1;
					continue;
				}

				cout << "read data:" << read_str << endl;
			}

		}
	}



}






















