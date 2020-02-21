#pragma once

#include<cstdlib>

/*
	�ռ�������
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
		enum Align { ALIGN = 8 }; //С��������ϵ��߽�
		enum MaxBytes{MAXTYPES = 128}; //С����������ޣ�������������malloc����
		enum FreeLists{FREELISTS = (MaxBytes::MAXTYPES / Align::ALIGN) }; //free-lists�ĸ���
		enum Objs{OBJS = 20}; //ÿ�����ӵĽڵ���

		//free-lists�Ľڵ㹹��
		union obj
		{
			union obj* next;
			char client[1];
		};

		static obj* free_list[FreeLists::FREELISTS];
		static char* start_free; //�ڴ����ʼλ��
		static char* end_free; //�ڴ�ؽ���λ��
		static size_t heap_size;

		//��bytes�ϵ���8�ı���
		static size_t round_up(size_t bytes)
		{
			return ((bytes + Align::ALIGN - 1) & ~(Align::ALIGN - 1));
		}

		//���������С������ʹ�õ�n��free-list��n��0��ʼ����
		static size_t free_list_index(size_t bytes)
		{
			return (((bytes + Align::ALIGN - 1) / Align::ALIGN - 1));
		}

		//����һ����СΪn�Ķ��󣬲����ܼ����СΪn���������鵽free-list
		static void* return_fill(size_t n);

		//����һ���ռ䣬������objs����СΪsize�����飬�������objs�������������㣬objs���ܻή��
		static char* chunk_alloc(size_t size, size_t& objs);
	};
}