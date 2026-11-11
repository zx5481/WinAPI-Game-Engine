#pragma once

#include <vector>
#include <map>

template<typename T>
void Safe_Delete_Vec(std::vector<T>& vector)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		if (nullptr != vector[i])
		{
			delete vector[i];
		}
	}

	vector.clear();
}

template<typename T1, typename T2>
void Safe_Delete_Map(std::map<T1, T2>& map)
{
	typename std::map<T1, T2>::iterator iter = map.begin();

	for (; iter != map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
		}
	}
}