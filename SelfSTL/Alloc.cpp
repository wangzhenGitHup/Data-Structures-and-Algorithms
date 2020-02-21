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
		if (bytes > MaxBytes::MAXTYPES)
		{
			return malloc(bytes);
		}

		size_t idx = free_list_index(bytes);
		obj* list = free_list[idx];
		if (list != nullptr)
		{
			free_list[idx] = list->next;
			return list;
		}

		return return_fill(round_up(bytes));
	}

	void Alloc::deallocate(void* ptr, size_t bytes)
	{
		if (bytes > MaxBytes::MAXTYPES)
		{
			free(ptr);
		}
		else
		{
			size_t idx = free_list_index(bytes);
			obj* pNode = static_cast<obj*>(ptr);
			pNode->next = free_list[idx];
			free_list[idx] = pNode;
		}
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

		obj* cur_obj = nullptr;
		obj* next_obj = nullptr;
		obj** tmp_free_list = free_list + free_list_index(bytes);
		obj* ret = (obj*)(chunk);
		*tmp_free_list = next_obj = (obj*)(chunk + bytes);

		//将取出的多余的空间加入到相应的freelist里面去
		for (int i = 1; ; i++)
		{
			cur_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + bytes);
			if (objs - 1 == i)
			{
				cur_obj->next = nullptr;
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
		char* ret = nullptr;
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
		if (bytes_left > 0)
		{
			obj** tmp_free_list = free_list + free_list_index(bytes_left);
			((obj*)start_free)->next = *tmp_free_list;
			*tmp_free_list = (obj*)start_free;
		}

		start_free = (char*)malloc(bytes_to_get);
		if (!start_free)
		{
			obj** tmp_free_list = nullptr;
			obj* ptr = nullptr;
			for (int i = 0; i <= MaxBytes::MAXTYPES; i += Align::ALIGN)
			{
				tmp_free_list = free_list + free_list_index(i);
				ptr = *tmp_free_list;
				if (ptr != nullptr)
				{
					*tmp_free_list = ptr->next;
					start_free = (char*)ptr;
					end_free = start_free + i;
					return chunk_alloc(bytes, objs);
				}
			}
			end_free = nullptr;
		}

		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;
		return chunk_alloc(bytes, objs);

	}
}