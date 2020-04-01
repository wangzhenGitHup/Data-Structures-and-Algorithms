#include "Alloc.h"

namespace SelfSTL
{
	char* Alloc::start_free = nullptr;
	char*Alloc::end_free = nullptr;
	size_t Alloc::heap_size = 0;

	Alloc::obj* Alloc::free_list[Alloc::FreeLists::FREELISTS] =
	{
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	void* Alloc::allocate(size_t bytes)
	{
		//判断区块大小，大于128bytes就调用第一级配置器
		if (bytes > MaxBytes::MAXTYPES)
		{
			return malloc(bytes);
		}

		//检查对应的free list，如果free list内有可用的区块，就直接拿来用；
		//没有的话，就将区块大小上调至8的倍数边界,然后调用return_fill()
		size_t idx = free_list_index(bytes);
		obj* list = free_list[idx];
		if (list != 0)
		{
			free_list[idx] = list->next;
			return list;
		}

		return return_fill(round_up(bytes));
	}

	void Alloc::deallocate(void* ptr, size_t bytes)
	{
		//大于128bytes就调用第一级配置器释放
		if (bytes > MaxBytes::MAXTYPES)
		{
			free(ptr);
			return;
		}
		
		size_t idx = free_list_index(bytes);
		obj* pNode = static_cast<obj*>(ptr);
		pNode->next = free_list[idx];
		free_list[idx] = pNode;
	}

	void* Alloc::reallocate(void* ptr, size_t old_sz, size_t new_sz)
	{
		deallocate(ptr, old_sz);
		ptr = allocate(new_sz);
		return ptr;
	}

	void* Alloc::return_fill(size_t bytes)
	{
		size_t objs = Objs::OBJS;

		//从内存池取
		char* chunk = chunk_alloc(bytes, objs);

		//取出的空间只够一个对象使用
		if (objs == 1)
		{
			return chunk;
		}

		obj* cur_obj = 0;
		obj* next_obj = 0;
		obj** tmp_free_list = free_list + free_list_index(bytes);
		
		//这一块准备返回给客户端
		obj* ret = (obj*)(chunk);
		
		//free list指向新配置的空间，取自内存池
		*tmp_free_list = next_obj = (obj*)(chunk + bytes);

		//将取出的多余的空间加入到相应的freelist里面去
		for (int i = 1; ; i++)
		{
			cur_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + bytes);
			if (objs - 1 == i)
			{
				cur_obj->next = 0;
				break;
			}
			else
			{
				cur_obj->next = next_obj;
			}
		}

		return ret;
	}

	char* Alloc::chunk_alloc(size_t bytes, size_t& objs)
	{
		char* ret = 0;
		size_t total_bytes = bytes * objs;
		size_t bytes_left = end_free - start_free;

		//内存池剩余空间完全满足需要
		if (bytes_left >= total_bytes)
		{
			ret = start_free;
			start_free = start_free + total_bytes;
			return ret;
		}

		//内存池剩余空间不能完全满足需要，但足够供应一个或以上的区块
		if (bytes_left >= bytes)
		{
			objs = bytes_left / bytes;
			total_bytes = objs * bytes;
			ret = start_free;
			start_free += total_bytes;
			return ret;
		}

		//内存池剩余空间连一个区块的大小都无法提供
		size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
		//以下试着让内存池中的残余零头还有利用价值
		if (bytes_left > 0)
		{
			//内存池内还有一些零头，先配置给适当的free list
			//首先寻找适当的 free list
			obj** tmp_free_list = free_list + free_list_index(bytes_left);
			//调整free list, 将内存池中的残余空间编入
			((obj*)start_free)->next = *tmp_free_list;
			*tmp_free_list = (obj*)start_free;
		}

		//配置heap空间，用来补充内存池
		start_free = (char*)malloc(bytes_to_get);
		
		//堆空间不足，malloc()失败
		if (!start_free)
		{	
			obj** tmp_free_list = 0;
			obj* ptr = 0;
			//搜寻尚有未用的区块，且区块够大的 free list
			for (int i = 0; i <= MaxBytes::MAXTYPES; i += Align::ALIGN)
			{
				tmp_free_list = free_list + free_list_index(i);
				ptr = *tmp_free_list;
				//free list尚有未用的区块
				if (ptr != 0)
				{
					//调整free list 释放出未用区块
					*tmp_free_list = ptr->next;
					start_free = (char*)ptr;
					end_free = start_free + i;
					//递归调用自己，为了修正objs
					return chunk_alloc(bytes, objs);
				}
			}
			
			//出现意外，到处都没有内存可用了
			end_free = 0;
		}

		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;
		//递归调用自己，为了修正objs
		return chunk_alloc(bytes, objs);

	}
}