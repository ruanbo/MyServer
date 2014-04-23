/*
 * Player.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "common/SmartPtr.h"
#include "common/TypeDef.h"

class Player : public smart_count
{
private:
	uint32 _pid;
	int _conn_fd;


public:
	Player(u_int32_t pid, int conn_fd);
	virtual ~Player();

public:
	uint32 get_pid()const;
	int get_conn_fd()const;


};

typedef smart_ptr<Player> PlayerPtr;



#endif /* PLAYER_H_ */
