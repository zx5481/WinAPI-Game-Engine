#pragma once

class Texture;

class Player : public Object
{
private:


public:
	virtual void Update();
	virtual void Render(HDC dc);

public:
	CLONE(Player);

public:
	Player();
	~Player();
};