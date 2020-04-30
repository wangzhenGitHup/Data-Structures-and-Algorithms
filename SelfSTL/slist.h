#pragma once

#include "Iterator.h"
#include "Allocator.h"
#include "Construct.h"
#include <utility>

namespace SelfSTL
{
	struct slist_node_base
	{
		slist_node_base* next;
	};

	template<class T>
	struct slist_node : public slist_node_base
	{
		T data;
	};

	slist_node_base* slist_make_link(slist_node_base* prev_node, slist_node_base* new_node)
	{
		new_node->next = prev_node->next;
		prev_node->next = new_node;
		return new_node;
	}

	size_t slist_size(slist_node_base* pnode)
	{
		size_t ret = 0;
		for (; pnode != nullptr; pnode = pnode->next)
		{
			++ret;
		}
		return ret;
	}

	struct slist_iterator_base
	{
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef forward_iterator_tag iterator_category;

		slist_node_base* node;
		slist_iterator_base(slist_node_base* pnode) : node(pnode){}
		void incr(){ node = node->next; }
		bool operator==(const slist_iterator_base& it) const
		{
			return node == it.node;
		}

		bool operator!=(const slist_iterator_base& it)const
		{
			return node != it.node;
		}
	};

	template<class T, class Ref, class Ptr>
	struct slist_iterator : public slist_iterator_base
	{
		typedef slist_iterator<T, T&, T*> iterator;
		typedef slist_iterator<T, const T&, const T*> const_iterator;
		typedef slist_iterator<T, Ref, PTR> self;

		typedef T value_type;
		typedef PTR pointer;
		typedef Ref reference;
		typedef slist_node<T> list_node;

		slist_iterator(list_node* it) : slist_iterator_base(it){}
		slist_iterator() : slist_iterator_base(nullptr){}
		slist_iterator(const iterator& it) : slist_iterator_base(it.node){}

		reference operator*()const{ return ((list_node*)node)->data; }
		pointer operator->()const{ return &(operator*()); }

		self& operator++()
		{
			incr();
			return *this;
		}

		self operator++(int)
		{
			self tmp = *this;
			incr();
			return tmp;
		}
	};


	template<class T, class Alloc = Allocator>
	class slist
	{
	public:
		typedef T										value_type;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef slist_iterator<T, T&, T*> iterator;
		typedef slist_iterator<T, const T&, const T*>	const_iterator;

	private:
		typedef slist_node<T> list_node;
		typedef slist_node_base list_node_base;
		typedef slist_iterator_base iterator_base;
		typedef Alloc list_node_allocator;

		static list_node* create_node(const value_type& val)
		{
			list_node* pNode = list_node_allocator::allocates();
			construct(&pNode->data, val);
			pNode->next = nullptr;

			return pNode;
		}

		static void destroy_node(list_node* pnode)
		{
			destroy(&pnode->data);
			list_node_allocator::deallocate(pnode);
		}

		slist(){ head_.next = nullptr; }
		~slist(){ clear(); }

		iterator begin(){ return iterator((list_node*)head_.next); }
		iterator end(){ return iterator(nullptr); }
		size_type size()const{ return slist_size(head_.next); }
		bool empty()const{ return head_.next == nullptr; }
		void swap(slist& list)
		{
			list_node_base* tmp = head_.next;
			head_.next = list.head_.next;
			list.head_.next = tmp;
		}

		reference front(){ return ((list_node*)head_.next)->data; }

		void push_front(const value_type& val)
		{
			slist_make_link(&head_, create_node(val));
		}

		void pop_front()
		{
			list_node* pnode = (list_node*)head_.next;
			head_.next = pnode->next;
			destroy_node(pnode);
		}

	private:
		list_node_base head_;
	};
}