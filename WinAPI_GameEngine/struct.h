#pragma once

#include <windows.h>

#include <math.h>
#include <assert.h>

struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
		{
			return true;
		}
		return false;
	}

	Vec2& Normalize()
	{
		float length = Length();

		assert(length != 0.f);
		x /= length;
		y /= length;

		return *this;
	}

	Vec2& operator = (POINT pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}

	Vec2 operator + (Vec2 other)
	{
		return Vec2(x + other.x, y + other.y);
	}

	void operator += (Vec2 other)
	{
		x += other.x;
		y += other.y;
	}

	Vec2 operator - (Vec2 other)
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator * (Vec2 other)
	{
		return Vec2(x * other.x, y * other.y);
	}

	Vec2 operator * (int i)
	{
		return Vec2(x * (float)i, y * (float)i);
	}

	Vec2 operator * (float f)
	{
		return Vec2(x * f, y * f);
	}

	Vec2 operator / (Vec2 other)
	{
		assert(0.f == other.x || 0.f == other.y);
		return Vec2(x / other.x, y / other.y);
	}

	Vec2 operator / (float f)
	{
		assert(0.f != f);
		return Vec2(x / f, y / f);
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{

	}

	Vec2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vec2(const POINT& pt)
		:x((float)pt.x)
		,y((float)pt.y)
	
	{

	}
};