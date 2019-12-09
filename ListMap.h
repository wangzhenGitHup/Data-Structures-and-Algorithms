#pragma once
#include <iostream>

template<class K, class V>
class ListMap
{
public:
	ListMap();
	virtual ~ListMap();
	void Add(K key, V value);
	void Remove(K key);
	bool Contains(K key);
	V GetValue(K key);
	void Set(K key, V value);
	int GetSize();
	bool IsEmpty();

private:
	struct MapNode
	{
		MapNode()
		{
			_key = K();
			_value = V();
			_next = nullptr;
		}
		MapNode(K key, V value, MapNode* next)
		{
			_key = key;
			_value = value;
			_next = next;
		}
		K _key;
		V _value;
		MapNode* _next;
	};
	MapNode* getNode(K key)
	{
		MapNode* pNode = _mapNode->_next;
		while (pNode != nullptr)
		{
			if (pNode->_key == key)
			{
				return pNode;
			}
			pNode = pNode->_next;
		}

		return nullptr;
	}

public:
	template<class K, class V> friend std::ostream& operator<<(std::ostream& out, 
		const ListMap<K, V>& map)
	{
		out << "ListMap:[ ";
		MapNode* pNode = map._mapNode->_next;
		while (pNode != nullptr)
		{
			out << pNode->_value << " ";
			pNode = pNode->_next;
		}
		out << "]" << std::endl;
		out << "------------------------\n";
		return out;
	}

private:

	MapNode* _mapNode = nullptr;
	int _size;
};

template<class K, class V>
ListMap<K, V>::ListMap()
{
	_mapNode = new MapNode();
	_size = 0;
}

template<class K, class V>
ListMap<K, V>::~ListMap()
{
	MapNode* pNode = _mapNode;
	MapNode* pDelNode = nullptr;

	while (pNode->_next != nullptr)
	{
		pDelNode = pNode->_next;
		pNode->_next = pDelNode->_next;
		delete pDelNode;
		pDelNode = nullptr;
	}

	delete _mapNode;
	_mapNode = nullptr;
}

template<class K, class V>
void ListMap<K, V>::Add(K key, V value)
{
	MapNode* pNode = getNode(key);
	if (pNode != nullptr)
	{
		pNode->_value = value;
		return;
	}

	_mapNode->_next = new MapNode(key, value, _mapNode->_next);
	_size++;

}

template<class K, class V>
void ListMap<K, V>::Remove(K key)
{
	if (_mapNode == nullptr)
	{
		return;
	}

	MapNode* pNode = nullptr;
	MapNode* pDelNode = _mapNode->_next;

	while (pDelNode != nullptr)
	{
		if (pDelNode->_key == key)
		{
			pNode->_next = pDelNode->_next;
			delete pDelNode;
			pDelNode = nullptr;
			_size--;
			return;
		}

		pNode = pDelNode;
		pDelNode = pDelNode->_next;
	}
}

template<class K, class V>
bool ListMap<K, V>::Contains(K key)
{
	MapNode* pNode = _mapNode->_next;
	while (pNode != nullptr)
	{
		if (pNode->_key == key)
		{
			return true;
		}
		pNode = pNode->_next;
	}
	return false;
}

template<class K, class V>
V ListMap<K, V>::GetValue(K key)
{
	MapNode* pNode = _mapNode->_next;
	while (pNode != nullptr)
	{
		if (pNode->_key == key)
		{
			return pNode->_value;
		}

		pNode = pNode->_next;
	}

	return V();
}

template<class K, class V>
void ListMap<K, V>::Set(K key, V value)
{
	MapNode* pNode = getNode(key);
	if (pNode != nullptr)
	{
		pNode->_value = value;
		return;
	}

	throw "Without this Key!";
}

template<class K, class V>
int ListMap<K, V>::GetSize()
{
	return _size;
}

template<class K, class V>
bool ListMap<K, V>::IsEmpty()
{
	return _size == 0;
}