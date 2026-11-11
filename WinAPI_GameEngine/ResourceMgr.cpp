#include "pch.h"

#include "ResourceMgr.h"

#include "PathMgr.h"
#include "Texture.h"

ResourceMgr::ResourceMgr()
{

}

ResourceMgr::~ResourceMgr()
{
	Safe_Delete_Map(m_mapTexture);
}

Texture* ResourceMgr::LoadTexture(const std::wstring& key, const std::wstring& relativePath)
{
	Texture* pTexture = FindTexture(key);

	if (nullptr != pTexture)
	{
		return pTexture;
	}

	std::wstring filePath = PathMgr::GetInst()->GetContentPath();

	filePath += relativePath;

	pTexture = new Texture;
	pTexture->Load(filePath);
	pTexture->SetKey(key);
	pTexture->SetRelativePath(relativePath);

	m_mapTexture.insert(make_pair(key, pTexture));

	return pTexture;
}

Texture* ResourceMgr::CreateTexture(const std::wstring& key, UINT width, UINT height)
{
	Texture* pTexture = FindTexture(key);
	
	if (nullptr != pTexture)
	{
		return pTexture;
	}

	pTexture = new Texture;
	pTexture->Create(width, height);
	pTexture->SetKey(key);

	m_mapTexture.insert(make_pair(key, pTexture));

	return pTexture;
}

Texture* ResourceMgr::FindTexture(const std::wstring& key)
{
	std::map<std::wstring, GameResource*>::iterator iter = m_mapTexture.find(key);

	if (iter == m_mapTexture.end())
	{
		return nullptr;
	}

	return (Texture*)iter->second;
}