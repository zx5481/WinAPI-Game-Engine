#pragma once

#include <string>

class PathMgr
{
	SINGLE(PathMgr);

private:
	std::wstring	m_contentPath;

public:
	void Init();
	
	const std::wstring GetContentPath() const { return m_contentPath; }

	std::wstring GetRelativePath(const wchar_t* filepath);
};