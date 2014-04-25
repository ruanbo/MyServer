/*
 * ScriptDefine.h
 *
 *  Created on: Apr 24, 2014
 *      Author: Robert
 */

#ifndef SCRIPTDEFINE_H_
#define SCRIPTDEFINE_H_


#include <string>
#include <map>
#include "common/SmartPtr.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

enum LuaScriptID
{
	LSID_NONE = 0,

	LSID_TEST_1 = 100000,
	LSID_TEST_2 = 100000,
	LSID_TEST_3 = 100000,
	LSID_TEST_4 = 100000,

	LSID_END
};

struct ScriptPath
{
	LuaScriptID _id;
	std::string _path;
};

enum LuaRetCorrectness
{
	LRC_NONE = 0,

	LRC_OK = 1,
	LRC_ERR = 2,

	LRC_END
};

struct LuaCallResult
{
	LuaRetCorrectness _corrness;
	double _val;

	LuaCallResult()
	{
		_corrness = LRC_NONE;
		_val = 0;
	}

	LuaCallResult(LuaRetCorrectness corr, double val)
	{
		_corrness = corr;
		_val = val;
	}

	bool is_ok()const
	{
		return _corrness == LRC_OK;
	}
};

#define LUA_CALL_ERR  (LuaCallResult(LRC_ERR, 0))
#define LUA_CALL_OK  (LuaCallResult(LRC_OK, 0))


struct LuaScriptItem : public smart_count
{
	LuaScriptID _id;
	std::string _path;

	lua_State *_L;

	LuaScriptItem()
	{
		_id = LSID_NONE;
		_path = "";
		_L = NULL;
	}
};
typedef smart_ptr<LuaScriptItem> LuaScriptItemPtr;



#endif /* SCRIPTDEFINE_H_ */
