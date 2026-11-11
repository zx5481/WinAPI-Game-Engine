#pragma once

class Object;
class Animation;
class Texture;

struct AnimationKey
{
	ANIMATION_TYPE animationType;
	DIR dir;

	bool operator<(const AnimationKey& other) const
	{
		if ((int)animationType != (int)other.animationType)
		{
			return (int)animationType < (int)other.animationType;
		}

		return (int)dir < (int)other.dir;
	}
};

class Animator
{
private:
	std::map<AnimationKey, Animation*>		m_animations;
	Animation*								m_pCurAnimation;
	Object*									m_pOwner;

public:
	Object* GetOwner() const { return m_pOwner; }

public:
	void CreateAnimation(ANIMATION_TYPE animationType, DIR dir, Texture* pTexture
		, Vec2 leftTop, Vec2 sliceSize, Vec2 step, float duration, UINT frameCount, bool isLoop);
	Animation* FindAnimation(ANIMATION_TYPE animationType, DIR dir);

	void Update();
	void FinalUpdate();
	void Render(HDC dc);

private:
	ANIMATION_TYPE GetAnimationType() const;
	void ChangeAnimation(ANIMATION_TYPE animationType, DIR dir);

public:
	Animator();
	~Animator();

	friend class Object;
};