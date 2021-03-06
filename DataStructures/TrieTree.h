#pragma once

#include"BSTMap.h"
#include<string>

class TrieTree
{
public:
	TrieTree();
	~TrieTree();
	int GetSize() { return _size; }
	void Add(std::string& word);
	bool Contains(std::string& word);
	bool IsPrefix(std::string& prefix);

private:
	struct TrieNode
	{
		bool m_isWord;
		BSTMap<char, TrieNode*>* m_next;

		TrieNode(bool isWord)
		{
			m_isWord = isWord;
			m_next = new BSTMap<char, TrieNode*>();
		}

		TrieNode()
		{
			m_isWord = false;
			m_next = new BSTMap<char, TrieNode*>();
		}
	};

	void add(std::string& word)
	{
		TrieNode* pCur = _root;
		for (int i = 0; i < word.size(); i++)
		{
			char ch = word[i];
			if (pCur->m_next->GetValue(ch) == nullptr)
			{
				pCur->m_next->Add(ch, new TrieNode());
			}

			pCur = pCur->m_next->GetValue(ch);
		}

		if (!pCur->m_isWord)
		{
			pCur->m_isWord = true;
			_size++;
		}
	}

	bool contains(std::string& word)
	{
		TrieNode* pNode = _root;
		for (int i = 0; i < word.size(); i++)
		{
			char ch = word[i];
			if (pNode->m_next->GetValue(ch) == nullptr)
			{
				return false;
			}

			pNode = pNode->m_next->GetValue(ch);
		}

		return pNode->m_isWord;
	}
	
	bool isPrefix(std::string& prefix)
	{
		TrieNode* pNode = _root;
		for (int i = 0; i < prefix.size(); i++)
		{
			char ch = prefix[i];
			if (pNode->m_next->GetValue(ch) == nullptr)
			{
				return false;
			}

			pNode = pNode->m_next->GetValue(ch);
		}

		return true;
	}

private:
	TrieNode* _root = nullptr;
	int _size = 0;
};


TrieTree::TrieTree()
{
	_root = new TrieNode();
	_size = 0;
}

TrieTree::~TrieTree()
{
}

void TrieTree::Add(std::string& word)
{
	add(word);
}

bool TrieTree::Contains(std::string & word)
{
	return contains(word);
}
