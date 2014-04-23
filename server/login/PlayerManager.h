/*
 * PlayerManager.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_

#include <map>
#include "Player.h"


class PlayerManager
{
private:
	std::map<uint32, PlayerPtr> _pid_players;
	std::map<int, PlayerPtr> _conn_players;


public:
	PlayerManager();
	virtual ~PlayerManager();

public:
	void add_player(const PlayerPtr & player);

	PlayerPtr get_conn_player(int conn_id);

	PlayerPtr get_pid_player(uint32 pid);
};

#endif /* PLAYERMANAGER_H_ */
