#include "pch.h"

#include "Texture.h"
#include "Core.h"

Texture::Texture()
	: m_hdc(0)
	, m_hBitmap(0)
	, m_bitInfo{}
{

}

Texture::~Texture()
{
	DeleteDC(m_hdc);
	DeleteObject(m_hBitmap);
}

void Texture::Load(const std::wstring& filePath)
{
	m_hBitmap = (HBITMAP)LoadImage(nullptr, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBitmap);

	m_hdc = CreateCompatibleDC(Core::GetInst()->GetMainDC());

	HBITMAP prevBitmap = (HBITMAP)SelectObject(m_hdc, m_hBitmap);
	DeleteObject(prevBitmap);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitInfo);
}

void Texture::Create(UINT width, UINT height)
{
	HDC mainhdc = Core::GetInst()->GetMainDC();

	m_hBitmap = CreateCompatibleBitmap(mainhdc, width, height);
	m_hdc = CreateCompatibleDC(mainhdc);

	HBITMAP prevBitmap = (HBITMAP)SelectObject(m_hdc, m_hBitmap);
	DeleteObject(prevBitmap);

	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitInfo);
}