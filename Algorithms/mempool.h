#pragma once

#include<iostream>

/*
	需保证应用本来的类的sizeof 不少于4个字节
*/
class MemPool
{
public:
	void* allocate(size_t size)
	{
		obj* tmpLink;
		if (m_freeMemPos == nullptr)
		{
			//申请一块大内存
			size_t realSize = m_onceAllocateCnt * size;
			m_freeMemPos = (obj *)malloc(realSize);
			tmpLink = m_freeMemPos;

			//把分配出来的这块内存彼此链接起来，供后续使用
			for (int i = 0; i < m_onceAllocateCnt - 1; i++)
			{
				tmpLink->m_next = (obj *)((char *)tmpLink + size);
				tmpLink = tmpLink->m_next;
			}
			tmpLink->m_next = nullptr;
		}

		tmpLink = m_freeMemPos;
		m_freeMemPos = m_freeMemPos->m_next;
		return tmpLink;
	}

	void deallocate(void* pHead)
	{
		((obj *)pHead)->m_next = m_freeMemPos;
		m_freeMemPos = (obj *)pHead;
	}
private:
	struct obj
	{
		struct obj *m_next;
	};

	int m_onceAllocateCnt = 50;
	obj* m_freeMemPos = nullptr;
};


#define DECLARE_POOL_ALLOC() \
public: \
	static MemPool memPool; \
	static void* operator new(size_t size) \
	{\
		return memPool.allocate(size); \
	}\
	static void operator delete(void* pHead) \
	{ \
		return memPool.deallocate(pHead); \
	} \

//-----------------------------------------------------
#define IMPLEMENT_POOL_ALLOC(className) \
MemPool className::memPool;


//=============example===============================
class TestMemPool
{
	DECLARE_POOL_ALLOC()
public:
	int m_i;
	int m_j;
};

IMPLEMENT_POOL_ALLOC(TestMemPool);

void Test()
{
	TestMemPool* test[100];
	for (int i = 0; i < 15; i++)
	{
		test[i] = new TestMemPool();
		printf("%p\n", test[i]);
	}

	for (int i = 0; i < 15; i++)
	{
		delete test[i];
	}
}
