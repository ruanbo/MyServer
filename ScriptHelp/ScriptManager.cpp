/*
 * ScriptManaget.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: Robert
 */



extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <iostream>

#include "ScriptManager.h"
#include "common/DebugProxy.h"

using namespace std;

struct ScriptPath lua_script_def[] =
{
	{ LSID_TEST_1, "script/test.lua" },
	{ LSID_TEST_2, "script/test.lua" },
	{ LSID_TEST_3, "script/test.lua" },
	{ LSID_TEST_4, "script/test.lua" },
};

extern "C"{

static bool init_load_script(LuaScriptItemPtr& item, LuaScriptID id, const string& path)
{
	item->_id = id;
	item->_path = path;
	item->_L = lua_open();

	luaL_openlibs(item->_L);

//	if( luaL_loadfile(item->_L, item->_path.c_str()) != 0)
	if(luaL_dofile(item->_L, path.c_str()) != 0)
	{
		cout << "luaL_loadfile() error:" << lua_tostring(item->_L, -1) << endl;

		lua_close(item->_L);
		return false;
	}
	return true;
}

/*
 *调用lua函数的命名规则 lua_func_N_D()
 * N_i : 表示函数有 N 个 double 参数
 */
static LuaCallResult lua_func_1_D(lua_State* L, const string& fn_name, double para)
{
	lua_getfield(L, LUA_GLOBALSINDEX, fn_name.c_str());
	if(!lua_isfunction(L, -1))
	{
		cout << "not a function" << endl;
		lua_pop(L, 1);
		return LUA_CALL_ERR;
	}
	lua_pushnumber(L, para);
	lua_call(L, 1, 1);

	LuaCallResult ret = LUA_CALL_OK;

	ret._val = lua_tonumber(L, -1);

	lua_pop(L, 1);

	return ret;
}

static LuaCallResult lua_func_2_D(lua_State* L, const string& fn_name, double para1, double para2)
{
	lua_getfield(L, LUA_GLOBALSINDEX, fn_name.c_str());
	if(!lua_isfunction(L, -1))
	{
		lua_pop(L, 1);
		return LUA_CALL_ERR;
	}

	lua_pushnumber(L, para1);
	lua_pushnumber(L, para2);
	lua_call(L, 2, 1);

	LuaCallResult ret = LUA_CALL_OK;

	ret._val = lua_tonumber(L, -1);

	lua_pop(L, 1);

	return ret;
}

}  // end of extern "C"

ScriptManager::ScriptManager()
{

}

ScriptManager::~ScriptManager()
{

}

ScriptManager* ScriptManager::get_instance()
{
	static ScriptManager instance;

	return &instance;
}

bool ScriptManager::init()
{
	int script_len = sizeof(lua_script_def) / sizeof(ScriptPath);

	bool ret = true;

	for(int i=0; i<script_len; ++i)
	{
		ret = add_script_path(lua_script_def[i]._id, lua_script_def[i]._path);
		if(ret == false)
		{
			return false;
		}
	}

	return true;
}

void ScriptManager::uninit()
{
	map<LuaScriptID, LuaScriptItemPtr>::const_iterator iter = _scripts_path.begin();

	for(; iter!=_scripts_path.end(); ++iter)
	{
		lua_close(iter->second->_L);
	}
}

bool ScriptManager::add_script_path(LuaScriptID id, const std::string& path)
{
	LuaScriptItemPtr script_item = new LuaScriptItem();

	bool ret = init_load_script(script_item, id, path);

	if(ret == false)
	{
		uninit();
		return false;
	}

	_scripts_path[script_item->_id] = script_item;
	return true;
}

std::string ScriptManager::get_path(LuaScriptID id)const
{
	map<LuaScriptID, LuaScriptItemPtr>::const_iterator iter = _scripts_path.find(id);
	if(iter != _scripts_path.end())
	{
		return iter->second->_path;
	}
	return "";
}

LuaScriptItemPtr ScriptManager::get_script_item(LuaScriptID id)const
{
	map<LuaScriptID, LuaScriptItemPtr>::const_iterator iter = _scripts_path.find(id);
	if(iter != _scripts_path.end())
	{
		return iter->second;
	}
	return NULL;
}

LuaCallResult ScriptManager::ran_script_1_D(LuaScriptID id, const std::string& fn_name, double para)
{
	LuaScriptItemPtr script = get_script_item(id);
	if(script == NULL)
	{
		return LUA_CALL_ERR;
	}

	if(script->_L == NULL)
	{
		return LUA_CALL_ERR;
	}

	return lua_func_1_D(script->_L, fn_name, para);
}

LuaCallResult ScriptManager::ran_script_2_D(LuaScriptID id, const std::string& fn_name, double para1, double para2)
{
	LuaScriptItemPtr script = get_script_item(id);
	if(script == NULL)
	{
		return LUA_CALL_ERR;
	}

	if(script->_L == NULL)
	{
		return LUA_CALL_ERR;
	}

	return lua_func_2_D(script->_L, fn_name, para1, para2);
}

