#include "../../../../common/stdafx.h"
#include <sstream>
#include <vector>
#include <time.h>
#include <string.h>

#include <fstream>     
#include <iterator>

#include <iostream>
#include "../../../../common/core.h"
#include "../Graphics/Sprite.h"
#include "../Entities/Entity.h"
#include "../Entities/Player.h"
#include "../Entities/Boss.h"
#include "../Graphics/Background.h"
#include "GameController.h"
#include "graphics_engine.h"
#include "InterfaceController.h"
#include "../Entities/Components/render_comp.h"
#include "../Entities/Components/life_comp.h"
#include "../Entities/Components/linear_vel_comp.h"
#include "../Entities/Messages/collision_msg.h"
#include "InputController.h"
#include "../../../../common/sys.h"
#include "../Entities/Components/collision_comp.h"
#include "../Entities/Components/level_comp.h"
#include "../Entities/Messages/new_pos_msg.h"
#include "Level.h"
#include "../Entities/Bullet.h"
#include "../Entities/Enemy.h"
#include <stdio.h>
#include "../Entities/Components/bullet_comp.h"
#include "../Entities/Components/component.h"
#include "../Entities/Components/dialog_comp.h"
#include "../Entities/Components/sound_comp.h"
#include "../Entities/Components/menu_comp.h"
#include "../Entities/Components/click_comp.h"
#include "../Entities/Button.h"
#include "../Entities/CheckBox.h"
#include <functional>

using namespace std;

struct Lua_Bullet {
	string BLL_SPRITE;
	vec2 BLL_SIZE;
	float BLL_SPEED;
	int BLL_DAMAGE;
	float BLL_COOLDOWN;
};

struct Lua_Player {
	string PLY_SPRITE;
	int PLY_FRAMES;
	float PLY_FRAMES_TIME;
	vec2 PLY_SIZE;
	int PLY_LIFES;
	float PLY_INV_TIME;
	float PLY_INV_TICKS;
	float PLY_BLANK_TIME;
	float PLY_COLL_RADIUS;
	Lua_Bullet PLY_BULLET;
};

struct Lua_Enemy {
	string ENE_SPRITE;
	vec2 ENE_SIZE;
	float ENE_MAXSPEED;
	float ENE_MINSPEED;
};

struct Lua_EnemyBoss : public Lua_Enemy {
	bool ENE_ROTATE;
	float ENE_ERROR;
};

struct Lua_Background {
	string BCK_SPRITE;
	vec2 BCK_SIZE;
	vec2 BCK_RESIZE;
	vec2 BCK_RESIZEPOS;
	vec2 BCK_OFFSET;
	string BCK_MUSIC;
};

struct Lua_Upgrade {
	string UPG_SPRITE;
	vec2 UPG_SIZE;
	int UPG_TYPE;
	float UPG_AMOUNT;
	float UPG_DELAY;
};

struct Lua_Boss {
	vector<vec3> BSS_POSS;
	vector<vector<vector<string>>> BSS_BEHAVIOUR;
	int BSS_FRAMES;
	float BSS_FRAMES_TIME;
	bool BSS_RANDOM;
	string BSS_SPRITE;
	vec2 BSS_SIZE;
	float BSS_ROUNDWAIT;
	float BSS_INITWAIT;
	int BSS_LIFES;
	float BSS_RADIUS;
	Lua_EnemyBoss BSS_ENEMY;
};

struct Lua_Level {
	vector<string> LVL_INIT_TEXT;
	vector<string> LVL_BOSS_TEXT;
	vector<string> LVL_END_TEXT;
	float LVL_INITWAIT;
	float LVL_WAITTIME;
	bool LVL_HORIZONTAL;
	int LVL_ENEMYAMOUNT;
	float LVL_WIDTH;
	float LVL_HEIGHT;
	Lua_Enemy LVL_ENEMY;
	vector<Lua_Background> LVL_BACKGROUND;
	vector<Lua_Boss> LVL_BOSSES;
	vector<Lua_Upgrade> LVL_UPGRADES;
};

struct Lua_Button {
	string BUTTON_SPRITE;
	vec2 BUTTON_SIZE;
	vec2 BUTTON_POS;
	int BUTTON_FRAMES;
	float BUTTON_FRAMES_TIME;
	vec2 BUTTON_SPEED;
};

struct Lua_CheckBox {
	string CHECKED_SPRITE;
	string UNCHECKED_SPRITE;
	bool CHECKED_STATE;
	vec2 BUTTON_SIZE;
	vec2 CHECKED_POS;
	int BUTTON_FRAMES;
	float BUTTON_FRAMES_TIME;
	vec2 BUTTON_SPEED;
};

struct Lua_World {
	int WRL_WIDTH;
	int WRL_HEIGHT;
	int WRL_FULLSCREEN;
	float WRL_TEXTTIME;
	vector<Lua_Level> WRL_LEVELS;
	Lua_Player WRL_PLAYER;
	vector<Lua_Button> WRL_BUTTONS;
	vector<Lua_CheckBox> WRL_CHECKBOXES;
	Lua_Background WRL_VICTORY;
	Lua_Background WRL_DEFEAT;
	Lua_Background WRL_MENU;
};

void lua_Vec2(lua_State *L, int idx, vec2& vec) {
	// universal helper function to get Vec3 function argument from Lua to C++ function
	luaL_checktype(L, idx, LUA_TTABLE);
	lua_rawgeti(L, idx, 1); vec.x = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_rawgeti(L, idx, 2); vec.y = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
}

void lua_Vec3(lua_State *L, int idx, vec3& vec) {
	// universal helper function to get Vec3 function argument from Lua to C++ function
	luaL_checktype(L, idx, LUA_TTABLE);
	lua_rawgeti(L, idx, 1); vec.x = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_rawgeti(L, idx, 2); vec.y = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_rawgeti(L, idx, 3); vec.z = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
}

vec2 lua_getVector2(lua_State *L, string name) {
	vec2 res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	lua_Vec2(L, -1, res);
	lua_pop(L, 1);
	return res;
}

int lua_getInteger(lua_State *L, string name) {
	int res = 0;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	res = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return res;
}

float lua_getFloat(lua_State *L, string name) {
	float res = 0.f;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	res = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return res;
}

bool lua_getBool(lua_State *L, string name) {
	bool res = false;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	res = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return res;
}

string lua_getString(lua_State *L, string name) {
	string res = "";
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	res = lua_tostring(L, -1);
	lua_pop(L, 1);
	return res;
}

vector<string> lua_getStringArray(lua_State *L, string name) {
	vector<string> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i); res.push_back(lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

vector<vec2> lua_getVector2Array(lua_State *L, string name) {
	vector<vec2> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			vec2 vect;
			lua_rawgeti(L, -1, i); 
			lua_Vec2(L, -1, vect);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

vector<vec3> lua_getVector3Array(lua_State *L, string name) {
	vector<vec3> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			vec3 vect;
			lua_rawgeti(L, -1, i);
			lua_Vec3(L, -1, vect);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_Bullet lua_getBullet(lua_State * L, string name) {
	Lua_Bullet res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res.BLL_SPRITE = lua_getString(L, "BLL_SPRITE");
		res.BLL_SIZE = lua_getVector2(L, "BLL_SIZE");
		res.BLL_SPEED = lua_getFloat(L, "BLL_SPEED");
		res.BLL_DAMAGE = lua_getInteger(L, "BLL_DAMAGE");
		res.BLL_COOLDOWN = lua_getFloat(L, "BLL_COOLDOWN");
	}
	lua_pop(L, 1);
	return res;
}

Lua_Player lua_getPlayer(lua_State * L, string name) {
	Lua_Player res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res.PLY_SPRITE = lua_getString(L, "PLY_SPRITE");
		res.PLY_FRAMES = lua_getInteger(L, "PLY_FRAMES");
		res.PLY_FRAMES_TIME = lua_getFloat(L, "PLY_FRAMES_TIME");
		res.PLY_SIZE = lua_getVector2(L, "PLY_SIZE");
		res.PLY_LIFES = lua_getInteger(L, "PLY_LIFES");
		res.PLY_INV_TIME = lua_getFloat(L, "PLY_INV_TIME");
		res.PLY_INV_TICKS = lua_getFloat(L, "PLY_INV_TICKS");
		res.PLY_BLANK_TIME = lua_getFloat(L, "PLY_BLANK_TIME");
		res.PLY_COLL_RADIUS = lua_getFloat(L, "PLY_COLL_RADIUS");
		res.PLY_BULLET = lua_getBullet(L, "PLY_BULLET");
	}
	lua_pop(L, 1);
	return res;
}

Lua_Enemy lua_getEnemy(lua_State * L, string name) {
	Lua_Enemy res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res.ENE_SPRITE = lua_getString(L, "ENE_SPRITE");
		res.ENE_SIZE = lua_getVector2(L, "ENE_SIZE");
		res.ENE_MAXSPEED = lua_getFloat(L, "ENE_MAXSPEED");
		res.ENE_MINSPEED = lua_getFloat(L, "ENE_MINSPEED");
	}
	lua_pop(L, 1);
	return res;
}


Lua_EnemyBoss lua_getEnemyBoss(lua_State * L, string name) {
	Lua_EnemyBoss res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res.ENE_SPRITE = lua_getString(L, "ENE_BSS_SPRITE");
		res.ENE_SIZE = lua_getVector2(L, "ENE_BSS_SIZE");
		res.ENE_MAXSPEED = lua_getFloat(L, "ENE_BSS_MAXSPEED");
		res.ENE_MINSPEED = lua_getFloat(L, "ENE_BSS_MINSPEED");
		res.ENE_ROTATE = lua_getBool(L, "ENE_BSS_ROTATE");
		res.ENE_ERROR = lua_getFloat(L, "ENE_BSS_ERROR");
	}
	lua_pop(L, 1);
	return res;
}

Lua_Background lua_getBasicBackground(lua_State * L) {
	Lua_Background res;
	res.BCK_SPRITE = lua_getString(L, "BCK_SPRITE");
	res.BCK_SIZE = lua_getVector2(L, "BCK_SIZE");
	res.BCK_RESIZE = lua_getVector2(L, "BCK_RESIZE");
	res.BCK_RESIZEPOS = lua_getVector2(L, "BCK_RESIZEPOS");
	res.BCK_OFFSET = lua_getVector2(L, "BCK_OFFSET");
	res.BCK_MUSIC = lua_getString(L, "BCK_MUSIC");
	return res;
}

Lua_Background lua_getBackground(lua_State * L, string name) {
	Lua_Background res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res = lua_getBasicBackground(L);
	}
	lua_pop(L, 1);
	return res;
}

vector<Lua_Background> lua_getBackgroundArray(lua_State * L, string name) {
	vector<Lua_Background> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i);
			Lua_Background vect = lua_getBasicBackground(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_Upgrade lua_getBasicUpgrade(lua_State * L) {
	Lua_Upgrade res;
	res.UPG_SPRITE = lua_getString(L, "UPG_SPRITE");
	res.UPG_SIZE = lua_getVector2(L, "UPG_SIZE");
	res.UPG_TYPE = lua_getInteger(L, "UPG_TYPE");
	res.UPG_AMOUNT = lua_getFloat(L, "UPG_AMOUNT");
	res.UPG_DELAY = lua_getFloat(L, "UPG_DELAY");
	return res;
}

Lua_Upgrade lua_getUpgrade(lua_State * L, string name) {
	Lua_Upgrade res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res = lua_getBasicUpgrade(L);
	}
	lua_pop(L, 1);
	return res;
}

vector<Lua_Upgrade> lua_getUpgradeArray(lua_State * L, string name) {
	vector<Lua_Upgrade> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i);
			Lua_Upgrade vect = lua_getBasicUpgrade(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}


vector<string> lua_getBehaviourArray(lua_State *L) {
	vector<string> res;
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i); 
			res.push_back(lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
	return res;
}

vector<vector<string>> lua_getBehaviourStateArray(lua_State *L) {
	vector<vector<string>> res;
	//lua_pushstring(L, name.c_str());
	//lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			vector<string> vect;
			lua_rawgeti(L, -1, i);
			vect = lua_getBehaviourArray(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	//lua_pop(L, 1);
	return res;
}

vector<vector<vector<string>>> lua_getBehaviourTreeArray(lua_State *L, string name) {
	vector<vector<vector<string>>> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			vector<vector<string>> vect;
			lua_rawgeti(L, -1, i);
			vect = lua_getBehaviourStateArray(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_Boss lua_getBasicBoss(lua_State * L) {
	Lua_Boss res;
	res.BSS_POSS = lua_getVector3Array(L, "BSS_POSS");
	res.BSS_BEHAVIOUR = lua_getBehaviourTreeArray(L, "BSS_BEHAVIOUR");
	res.BSS_FRAMES = lua_getInteger(L, "BSS_FRAMES");
	res.BSS_FRAMES_TIME = lua_getFloat(L, "BSS_FRAMES_TIME");
	res.BSS_RANDOM = lua_getBool(L, "BSS_RANDOM");
	res.BSS_SPRITE = lua_getString(L, "BSS_SPRITE");
	res.BSS_SIZE = lua_getVector2(L, "BSS_SIZE");
	res.BSS_ROUNDWAIT = lua_getFloat(L, "BSS_ROUNDWAIT");
	res.BSS_INITWAIT = lua_getFloat(L, "BSS_INITWAIT");
	res.BSS_LIFES = lua_getInteger(L, "BSS_LIFES");
	res.BSS_RADIUS = lua_getFloat(L, "BSS_RADIUS");
	res.BSS_ENEMY = lua_getEnemyBoss(L, "BSS_ENEMY");
	return res;
}

Lua_Boss lua_getBoss(lua_State * L, string name) {
	Lua_Boss res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res = lua_getBasicBoss(L);
	}
	lua_pop(L, 1);
	return res;
}

vector<Lua_Boss> lua_getBossArray(lua_State * L, string name) {
	vector<Lua_Boss> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i);
			Lua_Boss vect = lua_getBasicBoss(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_Level lua_getBasicLevel(lua_State * L) {
	Lua_Level res;
	res.LVL_INIT_TEXT = lua_getStringArray(L, "LVL_INIT_TEXT");
	res.LVL_BOSS_TEXT = lua_getStringArray(L, "LVL_BOSS_TEXT");
	res.LVL_END_TEXT = lua_getStringArray(L, "LVL_END_TEXT");
	res.LVL_INITWAIT = lua_getFloat(L, "LVL_INITWAIT");
	res.LVL_WAITTIME = lua_getFloat(L, "LVL_WAITTIME");
	res.LVL_HORIZONTAL = lua_getBool(L, "LVL_HORIZONTAL");
	res.LVL_ENEMYAMOUNT = lua_getInteger(L, "LVL_ENEMYAMOUNT");
	res.LVL_WIDTH = lua_getFloat(L, "LVL_WIDTH");
	res.LVL_HEIGHT = lua_getFloat(L, "LVL_HEIGHT");
	res.LVL_ENEMY = lua_getEnemy(L, "LVL_ENEMY");
	res.LVL_BACKGROUND = lua_getBackgroundArray(L, "LVL_BACKGROUND");
	res.LVL_BOSSES = lua_getBossArray(L, "LVL_BOSSES");
	res.LVL_UPGRADES = lua_getUpgradeArray(L, "LVL_UPGRADES");
	return res;
}

Lua_Level lua_getLevel(lua_State * L, string name) {
	Lua_Level res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res = lua_getBasicLevel(L);
	}
	lua_pop(L, 1);
	return res;
}

vector<Lua_Level> lua_getLevelArray(lua_State * L, string name) {
	vector<Lua_Level> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i);
			Lua_Level vect = lua_getBasicLevel(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_Button lua_getBasicButton(lua_State * L) {
	Lua_Button res;
	res.BUTTON_SPRITE = lua_getString(L, "BUTTON_SPRITE");
	res.BUTTON_SIZE = lua_getVector2(L, "BUTTON_SIZE");
	res.BUTTON_POS = lua_getVector2(L, "BUTTON_POS");
	res.BUTTON_FRAMES = lua_getInteger(L, "BUTTON_FRAMES");
	res.BUTTON_FRAMES_TIME = lua_getFloat(L, "BUTTON_FRAMES_TIME");
	res.BUTTON_SPEED = lua_getVector2(L, "BUTTON_SPEED");
	return res;
}

Lua_Button lua_getButton(lua_State * L, string name) {
	Lua_Button res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res = lua_getBasicButton(L);
	}
	lua_pop(L, 1);
	return res;
}

vector<Lua_Button> lua_getButtonArray(lua_State * L, string name) {
	vector<Lua_Button> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i);
			Lua_Button vect = lua_getBasicButton(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_CheckBox lua_getBasicCheckBox(lua_State * L) {
	Lua_CheckBox res;
	res.CHECKED_SPRITE = lua_getString(L, "CHECKED_SPRITE");
	res.UNCHECKED_SPRITE = lua_getString(L, "UNCHECKED_SPRITE");
	res.CHECKED_STATE = lua_getBool(L, "CHECKED_STATE");
	res.BUTTON_SIZE = lua_getVector2(L, "BUTTON_SIZE");
	res.CHECKED_POS = lua_getVector2(L, "BUTTON_POS");
	res.BUTTON_FRAMES = lua_getInteger(L, "BUTTON_FRAMES");
	res.BUTTON_FRAMES_TIME = lua_getFloat(L, "BUTTON_FRAMES_TIME");
	res.BUTTON_SPEED = lua_getVector2(L, "BUTTON_SPEED");
	return res;
}

Lua_CheckBox lua_getCheckBox(lua_State * L, string name) {
	Lua_CheckBox res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		res = lua_getBasicCheckBox(L);
	}
	lua_pop(L, 1);
	return res;
}

vector<Lua_CheckBox> lua_getCheckBoxArray(lua_State * L, string name) {
	vector<Lua_CheckBox> res;
	lua_pushstring(L, name.c_str());
	lua_gettable(L, -2);
	if (lua_istable(L, -1)) {
		int size = lua_rawlen(L, -1);
		for (int i = 1; i <= size; i++) {
			lua_rawgeti(L, -1, i);
			Lua_CheckBox vect = lua_getBasicCheckBox(L);
			res.push_back(vect);
			lua_pop(L, 1);
		}
	}
	lua_pop(L, 1);
	return res;
}

Lua_World lua_getBasicWorld(lua_State * L) {
	Lua_World res;
	res.WRL_WIDTH = lua_getInteger(L, "WRL_WIDTH");
	res.WRL_HEIGHT = lua_getInteger(L, "WRL_HEIGHT");
	res.WRL_FULLSCREEN = lua_getInteger(L, "WRL_FULLSCREEN");
	res.WRL_TEXTTIME = lua_getFloat(L, "WRL_TEXTTIME");
	res.WRL_LEVELS = lua_getLevelArray(L, "WRL_LEVELS");
	res.WRL_PLAYER = lua_getPlayer(L, "WRL_PLAYER");
	res.WRL_BUTTONS = lua_getButtonArray(L, "WRL_BUTTONS");
	res.WRL_CHECKBOXES = lua_getCheckBoxArray(L, "WRL_CHECKBOXES");
	res.WRL_VICTORY = lua_getBackground(L, "WRL_VICTORY");
	res.WRL_DEFEAT = lua_getBackground(L, "WRL_DEFEAT");
	res.WRL_MENU = lua_getBackground(L, "WRL_MENU");
	return res;
}

Lua_World lua_getWorld(lua_State * L, string name) {
	Lua_World res;
	//lua_pushstring(L, name.c_str());
	//lua_gettable(L, -2);
	lua_getglobal(L, name.c_str());
	if (lua_istable(L, -1)) {
		res = lua_getBasicWorld(L);
	}
	lua_pop(L, 1);
	return res;
}

GameController* GameController::m_game = nullptr;

lua_State * GameController::luaState;


void onClickPlay(Button* button, void* data) {
	World* world = reinterpret_cast<World*>(data);
	if (world) {
		world->Init();
		world->FindComponent<cMenuComp>()->BeginDestroy();
	}
}

void onClickCheck(Button* checkButton, void* data) {

}

GameController* GameController::lua_getGame() {
	DEL(m_game);
	//Inicialización de los controladores
	cGraphicsEngine::GetInstance().Init();
	cInterfaceController::GetInstance().Init();
	cInputController *pInput_manager = NEW(cInputController, ());

	Lua_World lua_world = lua_getWorld(luaState, "world");

	//Tamaño del mundo
	int width = lua_world.WRL_WIDTH;
	int height = lua_world.WRL_HEIGHT;

	//Creación del jugador (y sus balas)
	Bullet* bullet = NEW(Bullet, ({ lua_world.WRL_PLAYER.PLY_BULLET.BLL_SPRITE,lua_world.WRL_PLAYER.PLY_BULLET.BLL_SIZE }, lua_world.WRL_PLAYER.PLY_BULLET.BLL_SPEED, lua_world.WRL_PLAYER.PLY_BULLET.BLL_DAMAGE, lua_world.WRL_PLAYER.PLY_BULLET.BLL_COOLDOWN));
	Player* player = Player::create();
	cRenderComp* playerRend = NEW(cRenderComp, (lua_world.WRL_PLAYER.PLY_SPRITE, lua_world.WRL_PLAYER.PLY_SIZE, false, lua_world.WRL_PLAYER.PLY_FRAMES, lua_world.WRL_PLAYER.PLY_FRAMES_TIME));
	player->AddComponent(playerRend);
	cLinearVelComp* playerPos = NEW(cLinearVelComp, ({ width / 2.0f, height - 20.0f }, { 0.0f, 0.0f }));
	player->AddComponent(playerPos);
	cLifeComp* playerLife = NEW(cLifeComp, (lua_world.WRL_PLAYER.PLY_LIFES, lua_world.WRL_PLAYER.PLY_INV_TIME, lua_world.WRL_PLAYER.PLY_INV_TICKS, lua_world.WRL_PLAYER.PLY_BLANK_TIME));
	player->AddComponent(playerLife);
	cCollisionComp* playerCollision = NEW(cCollisionComp, (lua_world.WRL_PLAYER.PLY_COLL_RADIUS));
	player->AddComponent(playerCollision);
	cBulletComp* bulletComp = NEW(cBulletComp, (bullet));
	player->AddComponent(bulletComp);

	for (unsigned int i = 0; i < lua_world.WRL_LEVELS.size(); i++) {
		//Diálogos del nivel
		vector<string> initTexts = lua_world.WRL_LEVELS[i].LVL_INIT_TEXT;
		vector<string> bossTexts = lua_world.WRL_LEVELS[i].LVL_BOSS_TEXT;
		vector<string> finalTexts = lua_world.WRL_LEVELS[i].LVL_END_TEXT;

		//Background del nivel
		vector<cBackground*> backgrounds;
		for (unsigned int j = 0; j < lua_world.WRL_LEVELS[i].LVL_BACKGROUND.size(); j++) {
			cBackground* back1 = NEW(cBackground, (lua_world.WRL_LEVELS[i].LVL_BACKGROUND[j].BCK_SPRITE, lua_world.WRL_LEVELS[i].LVL_BACKGROUND[j].BCK_SIZE, lua_world.WRL_LEVELS[i].LVL_BACKGROUND[j].BCK_RESIZE, lua_world.WRL_LEVELS[i].LVL_BACKGROUND[j].BCK_RESIZEPOS, lua_world.WRL_LEVELS[i].LVL_BACKGROUND[j].BCK_OFFSET));
			back1->SetAudio(lua_world.WRL_LEVELS[i].LVL_BACKGROUND[j].BCK_MUSIC);
			backgrounds.push_back(back1);
		}

		vector<Boss*> bosses2;
		for (unsigned int j = 0; j < lua_world.WRL_LEVELS[i].LVL_BOSSES.size(); j++) {
			//Creación del boss del nivel 2 y sus esbirros
			vector<vec3> posboss3 = lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_POSS;
			vector<vector<vector<string>>> behaviourTree = lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_BEHAVIOUR;
			Enemy* enemy3 = NEW(Enemy, ({ lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ENEMY.ENE_SPRITE,lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ENEMY.ENE_SIZE }));
			Boss* boss3 = Boss::create();
			cRenderComp* bossRend3 = NEW(cRenderComp, (lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_SPRITE, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_SIZE, false, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_FRAMES, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_FRAMES_TIME));
			boss3->AddComponent(bossRend3);
			cLinearVelComp* bossPos3 = NEW(cLinearVelComp, ({ posboss3.at(0).x, posboss3.at(0).y }, { 0.0f, 0.0f }));
			boss3->AddComponent(bossPos3);
			cCollisionComp* bossCollision3 = NEW(cCollisionComp, (lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_RADIUS));
			boss3->AddComponent(bossCollision3);
			cNewPosMsg updatePos3({ posboss3.at(0).x, posboss3.at(0).y });
			boss3->ReceiveMessage(updatePos3);
			cEnemyComp* enemyComp3 = NEW(cEnemyComp, (enemy3));
			boss3->AddComponent(enemyComp3);
			bosses2.push_back(boss3);
			cBossLogicComp* bossLogic3 = NEW(cBossLogicComp, (posboss3, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ROUNDWAIT, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_INITWAIT, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_RANDOM, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_LIFES, { lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ENEMY.ENE_MAXSPEED, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ENEMY.ENE_MINSPEED, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ENEMY.ENE_ROTATE, lua_world.WRL_LEVELS[i].LVL_BOSSES[j].BSS_ENEMY.ENE_ERROR }));
			boss3->AddComponent(bossLogic3);
			bossLogic3->SetBehaviourTree(behaviourTree);
		}

		//Mejoras del nivel 2
		vector<Upgrade*> upgrades1;
		for (unsigned int j = 0; j < lua_world.WRL_LEVELS[i].LVL_UPGRADES.size(); j++) {
			Upgrade* upgrade1 = NEW(Upgrade, ({ lua_world.WRL_LEVELS[i].LVL_UPGRADES[j].UPG_SPRITE,lua_world.WRL_LEVELS[i].LVL_UPGRADES[j].UPG_SIZE }, (Upgrade::Type)lua_world.WRL_LEVELS[i].LVL_UPGRADES[j].UPG_TYPE, lua_world.WRL_LEVELS[i].LVL_UPGRADES[j].UPG_AMOUNT, lua_world.WRL_LEVELS[i].LVL_UPGRADES[j].UPG_DELAY));
			upgrades1.push_back(upgrade1);
		}

		//Creación del nivel 2
		cLevelComp* levelComp = NEW(cLevelComp, (initTexts, bossTexts, finalTexts, lua_world.WRL_LEVELS[i].LVL_INITWAIT, lua_world.WRL_LEVELS[i].LVL_WAITTIME, { lua_world.WRL_LEVELS[i].LVL_ENEMY.ENE_SPRITE ,lua_world.WRL_LEVELS[i].LVL_ENEMY.ENE_SIZE }, bosses2, lua_world.WRL_LEVELS[i].LVL_ENEMY.ENE_MAXSPEED, lua_world.WRL_LEVELS[i].LVL_ENEMY.ENE_MINSPEED, backgrounds, lua_world.WRL_LEVELS[i].LVL_HORIZONTAL, lua_world.WRL_LEVELS[i].LVL_ENEMYAMOUNT, { static_cast<float>(lua_world.WRL_LEVELS[i].LVL_WIDTH), static_cast<float>(lua_world.WRL_LEVELS[i].LVL_HEIGHT) }, upgrades1));
		Level* level = Level::create();
		level->AddComponent(levelComp);
	}

	//Creación del Background de victoria
	cBackground* victory = NEW(cBackground, (lua_world.WRL_VICTORY.BCK_SPRITE, lua_world.WRL_VICTORY.BCK_SIZE, lua_world.WRL_VICTORY.BCK_RESIZE, lua_world.WRL_VICTORY.BCK_RESIZEPOS, lua_world.WRL_VICTORY.BCK_OFFSET));
	victory->SetAudio(lua_world.WRL_VICTORY.BCK_MUSIC);
	//Creación del Background de derrota
	cBackground* defeat = NEW(cBackground, (lua_world.WRL_DEFEAT.BCK_SPRITE, lua_world.WRL_DEFEAT.BCK_SIZE, lua_world.WRL_DEFEAT.BCK_RESIZE, lua_world.WRL_DEFEAT.BCK_RESIZEPOS, lua_world.WRL_DEFEAT.BCK_OFFSET));
	defeat->SetAudio(lua_world.WRL_DEFEAT.BCK_MUSIC);
	//Creación del Background de menu
	cBackground* menu = NEW(cBackground, (lua_world.WRL_MENU.BCK_SPRITE, lua_world.WRL_MENU.BCK_SIZE, lua_world.WRL_MENU.BCK_RESIZE, lua_world.WRL_MENU.BCK_RESIZEPOS, lua_world.WRL_MENU.BCK_OFFSET));
	menu->SetAudio(lua_world.WRL_MENU.BCK_MUSIC);

	//Creación del mundo
	World* world = World::create(victory, defeat, menu, { static_cast<float>(width), static_cast<float>(height) });
	cSoundComp* soundContr = NEW(cSoundComp, ());
	world->AddComponent(soundContr);
	cDialogComp* dialogContr = NEW(cDialogComp, (lua_world.WRL_TEXTTIME));
	world->AddComponent(dialogContr);
	cMenuComp* menuContr = NEW(cMenuComp, ());
	pInput_manager->RegisterToEvent(world);

	for (unsigned int i = 0; i < lua_world.WRL_BUTTONS.size(); i++) {
		Button* button = NEW(Button, (lua_world.WRL_BUTTONS[i].BUTTON_SIZE));
		button->SetCallback(onClickPlay);
		cClickComp* buttonClick = NEW(cClickComp, ());
		button->AddComponent(buttonClick);
		cRenderComp* buttonRend = NEW(cRenderComp, (lua_world.WRL_BUTTONS[i].BUTTON_SPRITE, lua_world.WRL_BUTTONS[i].BUTTON_SIZE, true, lua_world.WRL_BUTTONS[i].BUTTON_FRAMES, lua_world.WRL_BUTTONS[i].BUTTON_FRAMES_TIME));
		button->AddComponent(buttonRend);
		cLinearVelComp* buttonPos = NEW(cLinearVelComp, (lua_world.WRL_BUTTONS[i].BUTTON_POS, lua_world.WRL_BUTTONS[i].BUTTON_SPEED));
		button->AddComponent(buttonPos);
		menuContr->AddEntity(button);
	}

	for (unsigned int i = 0; i < lua_world.WRL_CHECKBOXES.size(); i++) {
		bool checkedState = lua_world.WRL_CHECKBOXES[i].CHECKED_STATE;
		CheckBox* checkB = NEW(CheckBox, (lua_world.WRL_CHECKBOXES[i].BUTTON_SIZE, lua_world.WRL_CHECKBOXES[i].CHECKED_SPRITE, lua_world.WRL_CHECKBOXES[i].UNCHECKED_SPRITE, checkedState));
		checkB->SetCallback(onClickCheck);
		cClickComp* checkBClick = NEW(cClickComp, ());
		checkB->AddComponent(checkBClick);
		cRenderComp* checkBRend = nullptr;
		if (checkedState) {
			checkBRend = NEW(cRenderComp, (lua_world.WRL_CHECKBOXES[i].CHECKED_SPRITE, lua_world.WRL_CHECKBOXES[i].BUTTON_SIZE, true, lua_world.WRL_CHECKBOXES[i].BUTTON_FRAMES, lua_world.WRL_CHECKBOXES[i].BUTTON_FRAMES_TIME));
			cGraphicsEngine::GetInstance().InsertImg(lua_world.WRL_CHECKBOXES[i].UNCHECKED_SPRITE);
		}
		else {
			checkBRend = NEW(cRenderComp, (lua_world.WRL_CHECKBOXES[i].UNCHECKED_SPRITE, lua_world.WRL_CHECKBOXES[i].BUTTON_SIZE, true, lua_world.WRL_CHECKBOXES[i].BUTTON_FRAMES, lua_world.WRL_CHECKBOXES[i].BUTTON_FRAMES_TIME));
			cGraphicsEngine::GetInstance().InsertImg(lua_world.WRL_CHECKBOXES[i].CHECKED_SPRITE);
		}
		checkB->AddComponent(checkBRend);
		cLinearVelComp* checkBPos = NEW(cLinearVelComp, (lua_world.WRL_CHECKBOXES[i].CHECKED_POS, lua_world.WRL_CHECKBOXES[i].BUTTON_SPEED));
		checkB->AddComponent(checkBPos);
		menuContr->AddEntity(checkB);
	}

	world->AddComponent(menuContr);
	world->InitMenu();
	//cInputController::GetInstance().
	return m_game = NEW(GameController, (world, pInput_manager));
}

bool lua_checkLua(lua_State * L, int r) {
	if (r != LUA_OK) {
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}


GameController::GameController(World * world, cInputController *pInput_manager)
	: m_timer(1.0f / 60.0f)
	{
	m_world = world;
	m_input = pInput_manager;
	//this->g_fFPS = 0.0f;
}

GameController::~GameController() {
	Player::DeletePlayer();
	DEL(m_world);
	DEL(m_input);
	lua_close(luaState);
	//cInputController::GetInstance().Terminate();
	cInterfaceController::GetInstance().Terminate();
	cGraphicsEngine::GetInstance().Terminate();
}

//Dibuja el mundo
void GameController::Draw() {
	m_world->Draw();
}

//Inicializa el juego con los valores indicados en sys
GameController* GameController::Init() {
	DEL(m_game);
	//Establece una semilla aleatoria
	srand(static_cast<unsigned int>(time(NULL)));

	luaState = luaL_newstate();
	luaL_openlibs(luaState);

	//if (lua_checkLua(luaState, luaL_dofile(luaState, "D:/Proyectos/ProyectoInterfazv3/ProyectoComportamientosv3/common/config.lua"))) {
	if (lua_checkLua(luaState, luaL_dofile(luaState, SYS_VALUES::getLuaFilePath("common/config.lua").c_str()))) {
		return lua_getGame();
	}
	return nullptr;
}

//Actualización lógica del mundo
void GameController::Update() {
	m_timer.InitSlotsToProcess();
	//g_fFPS = 1.0f / timer.GetElapsedTime();
	while (m_timer.ProcessSlots()) {
		m_input->Update(m_timer.GetFixedTick());
		//m_world->Input(m_timer.GetFixedTick());
		m_world->Slot(m_timer.GetFixedTick());
		m_world->Update(m_timer.GetFixedTick());
	}
}

bool GameController::Finished() {
	return SYS_GottaQuit();
}