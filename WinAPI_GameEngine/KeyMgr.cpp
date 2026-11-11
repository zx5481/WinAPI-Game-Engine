#include "pch.h"

#include "KeyMgr.h"

#include "Core.h"

const int g_arrVK[(size_t)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_RSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,

	// LAST
};

KeyMgr::KeyMgr()
{

}

KeyMgr::~KeyMgr()
{

}

void KeyMgr::Init()
{
	for (size_t i = 0; i < (size_t)KEY::LAST; ++i)
	{
		m_arrKey[i] = KeyInfo{ KEY_STATE::NONE, false };
	}
}

void KeyMgr::Update()
{
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (size_t i = 0; i < (size_t)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_arrKey[i].isPrevPressed)
				{
					m_arrKey[i].state = KEY_STATE::HOLD;
				}
				else
				{
					m_arrKey[i].state = KEY_STATE::TAP;
				}

				m_arrKey[i].isPrevPressed = true;
			}
			else
			{
				if (m_arrKey[i].isPrevPressed)
				{
					m_arrKey[i].state = KEY_STATE::RELEASE;
				}
				else
				{
					m_arrKey[i].state = KEY_STATE::NONE;
				}

				m_arrKey[i].isPrevPressed = false;
			}
		}

		POINT ptPos = {};
		GetCursorPos(&ptPos);

		ScreenToClient(Core::GetInst()->GetMainHwnd(), &ptPos);

		m_MousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}
	else
	{
		for (size_t i = 0; i < (size_t)KEY::LAST; ++i)
		{
			if (KEY_STATE::TAP == m_arrKey[i].state || KEY_STATE::HOLD == m_arrKey[i].state)
			{
				m_arrKey[i].state = KEY_STATE::RELEASE;
			}
			else if (KEY_STATE::RELEASE == m_arrKey[i].state)
			{
				m_arrKey[i].state = KEY_STATE::NONE;
			}

			m_arrKey[i].isPrevPressed = false;
		}
	}
}