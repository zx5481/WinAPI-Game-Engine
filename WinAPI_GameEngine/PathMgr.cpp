#include "pch.h"

#include "PathMgr.h"

#include "Core.h"

PathMgr::PathMgr()
	: m_contentPath{}
{

}

PathMgr::~PathMgr()
{

}

void PathMgr::Init()
{
	wchar_t buffer[256];

	GetCurrentDirectory(256, buffer);

	m_contentPath = buffer;

	size_t endPos = m_contentPath.find_last_of(L"\\");

	if (endPos != std::wstring::npos)
	{
		m_contentPath.erase(endPos);
	}

	m_contentPath += L"\\bin\\content\\";
}

std::wstring PathMgr::GetRelativePath(const wchar_t* filepath)
{
	std::wstring strFilePath = filepath;

	size_t absLength = m_contentPath.length();
	size_t fullLength = strFilePath.length();

	std::wstring strRelativePath = strFilePath.substr(absLength, fullLength - absLength);

	return strRelativePath;
}