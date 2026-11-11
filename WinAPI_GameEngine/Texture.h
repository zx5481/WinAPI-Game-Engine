#pragma once

#include <windows.h>

#include "GameResource.h"

class Texture : public GameResource
{
	HDC		m_hdc;
	HBITMAP	m_hBitmap;
	BITMAP	m_bitInfo;

public:
	void Load(const std::wstring& filePath);
	void Create(UINT width, UINT height);

	UINT GetWidth() const { return m_bitInfo.bmWidth; }
	UINT GetHeight() const { return m_bitInfo.bmHeight; }

	HDC GetDC() const { return m_hdc; }

private:
	Texture();
	virtual ~Texture();

	friend class ResourceMgr;
};