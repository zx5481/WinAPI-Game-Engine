#pragma once

class GameResource;
class Texture;

class ResourceMgr
{
	SINGLE(ResourceMgr);

private:
	std::map<std::wstring, GameResource*> m_mapTexture;

public:
	Texture* LoadTexture(const std::wstring& key, const std::wstring& relativePath);
	Texture* CreateTexture(const std::wstring& key, UINT width, UINT height);

	Texture* FindTexture(const std::wstring& key);
};