/*
 * Login.h
 *
 *  Created on: Apr 18, 2014
 *      Author: Robert
 */

#ifndef LOGIN_H_
#define LOGIN_H_

#include "ServerModule/Module.h"
#include "PlayerManager.h"

class Login : public Module
{
private:
	PlayerManager _player_manager;

public:
	Login();
	virtual ~Login();

public:

};

#endif /* LOGIN_H_ */
