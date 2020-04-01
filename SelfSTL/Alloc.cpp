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
		//�ж������С������128bytes�͵��õ�һ��������
		if (bytes > MaxBytes::MAXTYPES)
		{
			return malloc(bytes);
		}

		//����Ӧ��free list�����free list���п��õ����飬��ֱ�������ã�
		//û�еĻ����ͽ������С�ϵ���8�ı����߽�,Ȼ�����return_fill()
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
		//����128bytes�͵��õ�һ���������ͷ�
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

		//���ڴ��ȡ
		char* chunk = chunk_alloc(bytes, objs);

		//ȡ���Ŀռ�ֻ��һ������ʹ��
		if (objs == 1)
		{
			return chunk;
		}

		obj* cur_obj = 0;
		obj* next_obj = 0;
		obj** tmp_free_list = free_list + free_list_index(bytes);
		
		//��һ��׼�����ظ��ͻ���
		obj* ret = (obj*)(chunk);
		
		//free listָ�������õĿռ䣬ȡ���ڴ��
		*tmp_free_list = next_obj = (obj*)(chunk + bytes);

		//��ȡ���Ķ���Ŀռ���뵽��Ӧ��freelist����ȥ
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

		//�ڴ��ʣ��ռ���ȫ������Ҫ
		if (bytes_left >= total_bytes)
		{
			ret = start_free;
			start_free = start_free + total_bytes;
			return ret;
		}

		//�ڴ��ʣ��ռ䲻����ȫ������Ҫ�����㹻��Ӧһ�������ϵ�����
		if (bytes_left >= bytes)
		{
			objs = bytes_left / bytes;
			total_bytes = objs * bytes;
			ret = start_free;
			start_free += total_bytes;
			return ret;
		}

		//�ڴ��ʣ��ռ���һ������Ĵ�С���޷��ṩ
		size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);
		//�����������ڴ���еĲ�����ͷ�������ü�ֵ
		if (bytes_left > 0)
		{
			//�ڴ���ڻ���һЩ��ͷ�������ø��ʵ���free list
			//����Ѱ���ʵ��� free list
			obj** tmp_free_list = free_list + free_list_index(bytes_left);
			//����free list, ���ڴ���еĲ���ռ����
			((obj*)start_free)->next = *tmp_free_list;
			*tmp_free_list = (obj*)start_free;
		}

		//����heap�ռ䣬���������ڴ��
		start_free = (char*)malloc(bytes_to_get);
		
		//�ѿռ䲻�㣬malloc()ʧ��
		if (!start_free)
		{	
			obj** tmp_free_list = 0;
			obj* ptr = 0;
			//��Ѱ����δ�õ����飬�����鹻��� free list
			for (int i = 0; i <= MaxBytes::MAXTYPES; i += Align::ALIGN)
			{
				tmp_free_list = free_list + free_list_index(i);
				ptr = *tmp_free_list;
				//free list����δ�õ�����
				if (ptr != 0)
				{
					//����free list �ͷų�δ������
					*tmp_free_list = ptr->next;
					start_free = (char*)ptr;
					end_free = start_free + i;
					//�ݹ�����Լ���Ϊ������objs
					return chunk_alloc(bytes, objs);
				}
			}
			
			//�������⣬������û���ڴ������
			end_free = 0;
		}

		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;
		//�ݹ�����Լ���Ϊ������objs
		return chunk_alloc(bytes, objs);

	}
}