/*
 * ScriptManaget.h
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */

#ifndef SCRIPTMANAGET_H_
#define SCRIPTMANAGET_H_

#include "ScriptDefine.h"

class ScriptManager
{
private:
	std::map<LuaScriptID, LuaScriptItemPtr> _scripts_path;

	ScriptManager(const ScriptManager&);
	ScriptManager operator = (const ScriptManager&);

public:
	ScriptManager();
	virtual ~ScriptManager();

	ScriptManager* get_instance();

public:
	bool init();

	void uninit();

	bool add_script_path(LuaScriptID id, const std::string& path);

	std::string get_path(LuaScriptID id)const;

	LuaScriptItemPtr get_script_item(LuaScriptID id)const;

	LuaCallResult ran_script_1_D(LuaScriptID id, const std::string& fn_name, double para);

};

#endif /* SCRIPTMANAGET_H_ */
