#pragma once

#define SINGLE(type)	public:\
							static type* GetInst()\
							{\
								static type mgr;\
								return &mgr;\
							}\
						private:\
							type();\
							~type();

#define fDT TimeMgr::GetInst()->GetfDT()
#define DT TimeMgr::GetInst()->GetDT()

#define CLONE(type) type* Clone() { return new type(*this); }

#define KEY_CHECK(key, state) KeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_RELEASE(key) KEY_CHECK(key, KEY_STATE::RELEASE)
#define MOUSE_POS KeyMgr::GetInst()->GetMousePos()

#define TILE_SIZE 64

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class GROUP_TYPE
{
	DEFAULT,
	TILE,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	UI,
	END,
};

enum class SCENE_TYPE
{
	TOOL,

	START,

	STAGE_01,
	STAGE_02,

	END,
};

enum class ANIMATION_TYPE
{
	IDLE,
	WALK,
	ROLL,
	FALL,
	
	ATTACK,
	HIT,

	DIE,

	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};

enum class STATE_BASE
{
	IDLE,
	WALK,
	ROLL,
	FALL,

	END,
};

enum class STATE_ACTION
{
	NONE,
	ATTACK,
	HIT,
	DIE,

	END,
};

enum class DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};