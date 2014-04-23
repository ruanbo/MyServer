/*
 * Player.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#include "Player.h"

Player::Player(u_int32_t pid, int conn_fd)
{
	_pid = pid;
	_conn_fd = conn_fd;
}

Player::~Player()
{

}

uint32 Player::get_pid()const
{
	return _pid;
}


int Player::get_conn_fd()const
{
	return _conn_fd;
}
