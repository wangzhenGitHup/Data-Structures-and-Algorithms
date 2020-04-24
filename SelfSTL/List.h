#pragma once

#include "Alloc.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"
#include "TypeTraits.h"


namespace SelfSTL
{
	template<class T>
	class List;

	namespace ListNode
	{
		template<class T>
		struct Node
		{
			T data;
			Node* prev;
			Node* next;
			List<T>* container;

			Node(const T& d, Node* p, Node* n, List<T>* c) : data(d), 
				prev(p), next(n), container(c)
			{

			}

			bool operator==(const Node& node)
			{
				return  data == node.data && 
						prev == node.prev && 
						next = node.next  && 
						container == node.container;
			}
		};

		template<class T>
		struct ListIterator : public iterator<bidirectional_iterator_tag, T>
		{
			template<class T>
			friend class List;

		public:
			typedef Node<T>* NodePtr;
			NodePtr ptr_;

		public:
			explicit ListIterator(NodePtr ptr = nullptr) : ptr_(ptr)
			{

			}

			ListIterator& operator++();
			ListIterator operator++(int);
			ListIterator& operator--();
			ListIterator operator--(int);
			T& operator*(){ return ptr_->data; }
			T* operator->(){ return &(operator*()); }

			template<class T>
			friend bool operator==(const ListIterator<T>& lhs, const ListIterator<T>& rhs);

			template<class T>
			friend bool operator!=(const ListIterator<T>& lhs, const ListIterator<T>& rhs);
		};
	}//end namespace ListNode

	

	template<class T>
	class List
	{
	private:
		template<class T>
		friend struct ListIterator;

	private:
		typedef Allocator<ListNode::Node<T>> NodeAllocator;
		typedef ListNode::Node<T>* NodePtr;

	public:
		typedef T									value_type;
		typedef ListNode::ListIterator<T>			iterator;
		typedef ListNode::ListIterator<const T>		const_iterator;
		typedef reverse_iterator_t<iterator>		reverse_iterator;
		typedef T&									reference;
		typedef size_t								size_type;

	private:
		iterator head_;
		iterator tail_;

	public:
		List();
		explicit List(size_type n, const value_type& val = value_type());

		template<class InputIterator>
		List(InputIterator first, InputIterator last);
		List(const List& list);
		List& operator=(const List& list);
		~List();

		bool empty()const{ return head_ == tail_; }
		size_type size()const;
		reference front(){ return head_->ptr_->data; }
		reference back(){ return tail_->ptr_->data; }

		void push_front(const value_type& val);
		void pop_front();
		void push_back(const value_type& val);
		void pop_back();

		iterator begin();
		iterator end();
		const_iterator begin()const;
		const_iterator end()const;
		reverse_iterator rbegin();
		reverse_iterator rend();

		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(List& list);
		void clear();
		void splice(iterator position, List& list);
		void splice(iterator position, List& list, iterator it);
		void splice(iterator position, List& list, iterator first, iterator last);
		void remove(const value_type& val);
		
		template<class Predicate>
		void remove_if(Predicate pred);
		void unique();

		template<class BinaryPredicate>
		void unique(BinaryPredicate pred);
		void merge(List& list);

		template<class Compare>
		void merge(List& list, Compare comp);
		
		void sort();

		template<class Compare>
		void sort(Compare comp);

		void reverse();

	private:
		void ctorAux(size_type n, const value_type& val, std::true_type);

		template<class InputIterator>
		void ctorAux(InputIterator first, InputIterator last, std::false_type);

		nodePtr newNode(const T& val = T());

		void deleteNode(NodePtr p);

		void insert_aux(iterator position, size_type n, const T& val, std::true_type);

		template<class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		const_iterator changeIteratorToConstIterator(iterator& it)const;

		template<class T>
		friend void swap(List<T>& list1, List<T>& list2);

		template<class T>
		friend bool operator==(const List<T>& lhs, const List<T>& rhs);

		template<class T>
		friend bool operator!=(const List<T>& lhs, const List<T>& rhs);
	};
}