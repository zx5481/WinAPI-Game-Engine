#pragma once

#include <string>

class GameResource
{
private:
	std::wstring m_key;
	std::wstring m_relativePath;

public:
	void SetKey(const std::wstring& key) { m_key = key; }
	void SetRelativePath(const std::wstring& relativePath) { m_relativePath = relativePath; }

	const std::wstring& GetKey() const { return m_key; }
	const std::wstring& GetRelativePath() const { return m_relativePath; }

public:
	GameResource() = default;
	virtual ~GameResource() = default;
};