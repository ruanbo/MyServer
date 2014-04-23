/*
 * PlayerManager.cpp
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#include "PlayerManager.h"
#include "common/util.h"


PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager()
{

}

void PlayerManager::add_player(const PlayerPtr & player)
{
	_pid_players.insert(std::make_pair(player->get_pid(), player));
	_conn_players.insert(std::make_pair(player->get_conn_fd(), player));
}

PlayerPtr PlayerManager::get_conn_player(int conn_id)
{
	return find_container(_conn_players, conn_id, PlayerPtr());
}

PlayerPtr PlayerManager::get_pid_player(uint32 pid)
{
	return find_container(_pid_players, pid, PlayerPtr());
}
