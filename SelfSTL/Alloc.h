#pragma once

#include<cstdlib>

/*
	空间配置器
*/
namespace SelfSTL
{
	class Alloc
	{
	public:
		static void *allocate(size_t bytes);
		static void deallocate(void* ptr, size_t bytes);
		static void *reallocate(void* ptr, size_t old_sz, size_t new_sz);

	private:
		enum Align { ALIGN = 8 }; //小型区块的上调边界
		enum MaxBytes{MAXTYPES = 128}; //小型区块的上限，超过的区块由malloc分配
		enum FreeLists{FREELISTS = (MaxBytes::MAXTYPES / Align::ALIGN) }; //free-lists的个数
		enum Objs{OBJS = 20}; //每次增加的节点数

		//free-lists的节点构造
		union obj
		{
			union obj* next;
			char client[1];
		};

		static obj* free_list[FreeLists::FREELISTS];
		static char* start_free; //内存池起始位置
		static char* end_free; //内存池结束位置
		static size_t heap_size;

		//将bytes上调至8的倍数
		static size_t round_up(size_t bytes)
		{
			return ((bytes + Align::ALIGN - 1) & ~(Align::ALIGN - 1));
		}

		//根据区块大小，决定使用第n号free-list，n从0开始计算
		static size_t free_list_index(size_t bytes)
		{
			return (((bytes + Align::ALIGN - 1) / Align::ALIGN - 1));
		}

		//返回一个大小为n的对象，并可能键入大小为n的其他区块到free-list
		static void* return_fill(size_t n);

		//配置一大块空间，可容纳objs个大小为size的区块，如果配置objs个区块有所不便，objs可能会降低
		static char* chunk_alloc(size_t size, size_t& objs);
	};
}