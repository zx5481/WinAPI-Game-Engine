#pragma once

#include <array>

#include "struct.h"

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	RELEASE,
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	ALT,
	CTRL,
	LSHIFT,
	RSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct KeyInfo
{
	KEY_STATE	state;
	bool		isPrevPressed;
};

class KeyMgr
{
	SINGLE(KeyMgr);

private:
	std::array<KeyInfo, (size_t)KEY::LAST>	m_arrKey;
	Vec2 m_MousePos;

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY key) const { return m_arrKey[(size_t)key].state; }
	Vec2 GetMousePos() const { return m_MousePos; }
	
	
};