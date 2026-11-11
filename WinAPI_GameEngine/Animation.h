#pragma once

class Animator;
class Texture;

struct AnimationFrame
{
	Vec2 leftTop;
	Vec2 slice;
	Vec2 offset;
	float duration;
};

class Animation
{
private:
	ANIMATION_TYPE				m_animationType;
	Animator* m_pAnimator;
	Texture* m_pTexture;
	std::vector<AnimationFrame> m_animationFrames;
	int							m_curFrame;
	float						m_elapsedTime;
	bool						m_isFinish;
	bool						m_isLoop;

private:
	void SetType(ANIMATION_TYPE animationType) { m_animationType = animationType; }

public:
	ANIMATION_TYPE GetType() const { return m_animationType; }
	bool IsFinish() const { return m_isFinish; }

	void Reset()
	{
		m_curFrame = 0;
		m_elapsedTime = 0.f;
		m_isFinish = false;
	}

	void SetFrame(int frameIndex)
	{
		if (frameIndex < 0 || frameIndex >= (int)m_animationFrames.size())
		{
			return;
		}

		m_isFinish = false;
		m_curFrame = frameIndex;
		m_elapsedTime = 0.f;
	}

	AnimationFrame& GetFrame(int index) { return m_animationFrames[index]; }
	UINT GetMaxFrame() const { return (UINT)m_animationFrames.size(); }

public:
	void Update();
	void Render(HDC dc);
	void Create(Texture* pTexture,
		Vec2 leftTop, Vec2 sliceSize, Vec2 step, float duration, UINT frameCount, bool isLoop);

public:
	Animation();
	~Animation();

	friend class Animator;
};