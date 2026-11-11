#pragma once


class Texture;

class Tile : public Object
{
private:
	Texture*	m_pTileTexture;
	int			m_imageIdx;

public:
	void SetTexture(Texture* pTexture) { m_pTileTexture = pTexture; }

	void AddImageIdx() { ++m_imageIdx; }

private:
	virtual void Update();
	virtual void Render(HDC hDC);

public:
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

	CLONE(Tile);

public:
	Tile();
	~Tile();
};