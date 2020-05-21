#pragma once

#include "Allocator.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "tools.h"

namespace SelfSTL
{
	template<class T, class Alloc = Allocator<T>>
	class deque;
	namespace DequeIterator
	{
		template<class T>
		class deque_iterator : public iterator<bidirectional_iterator_tag, T>
		{
		private:
			template<class T, class Alloc>
			friend class ::SelfSTL::deque;

		private:
			typedef const ::SelfSTL::deque<T>* contPtr_;
			size_t mapIdx_;
			T* cur_;
			contPtr_ container_;


		public:
			deque_iterator() : mapIdx_(-1), cur_(0), container_(0)
			{}

			deque_iterator(size_t idx, T* ptr, contPtr_ c) : 
				mapIdx_(idx), cur_(ptr), container_(c)
			{}

			deque_iterator& operator=(const deque_iterator& it);
			void swap(deque_iterator& it);
			reference operator*(){ return *cur_; }
			const reference operator*()const{ return *cur_; }
			pointer operator->(){ return &(operator*()); }
			const pointer operator->()const{ return&(operator*()); }
			deque_iterator& operator++();
			deque_iterator operator++(int);
			deque_iterator& operator--();
			deque_iterator operator--(int);
			bool operator==(const deque_iterator& it)const;
			bool operator!=(const deque_iterator& it)const;

		private:
			T* getBuckTail(size_t mapIdx)const;
			T* getBuckHead(size_T mapIdx)const;
			size_t getBuckSize()const;

		public:
			template<class T>
			friend deque_iterator<T>operator+(const deque_iterator<T>& it, typename deque_iterator<T>::difference_type n);

			template<class T>
			friend deque_iterator<T>operator+(typename deque_iterator<T>::difference_type n, const deque_iterator<T>& it);

			template<class T>
			friend deque_iterator<T>operator-(const deque_iterator<T>& it, typename deque_iterator<T>::difference_type n);

			template<class T>
			friend deque_iterator<T>operator-(typename deque_iterator<T>::difference_type n, const deque_iterator<T>& it);

			template<class T>
			friend typename deque_iterator<T>::difference_type operator-(const deque_iterator<T>& it, const deque_iterator<T>& it2);

			template<class T>
			friend void swap(deque_iterator<T>& lhs, deque_iterator<T>& rhs);
		};
	}//end namespace DequeIterator

	template<class T, class Alloc>
	class deque
	{
	private:
		template<class T>
		friend class ::SelfSTL::DequeIterator::deque_iterator;

	public:
		typedef T value_type;
		typedef DequeIterator::deque_iterator<T> iterator;
		typedef DequeIterator::deque_iterator<const T> const_iterator;
		typedef T& reference;
		typedef const reference const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Alloc allocator_type;

	private:
		typedef Alloc dataAllocator;
		enum class EBucksSize{BUCKSIZE = 64};

	private:
		iterator begin_, end_;
		size_t mapSize_;
		T** map_;

	public:
		deque();
		explicit deque(size_type n, const value_type& val = value_type());
		
		template<class InputIterator>
		deque(InputIterator first, InputIterator last);

		deque(const deque& dq);
		~deque();

		deque& operator=(const deque& dq);
		deque& operator=(deque&& dq);

		iterator begin();
		iterator end();
		iterator begin()const;
		iterator end()const;

	public:
		size_type size() const{ return end() - begin(); }
		bool empty()const{ return begin() == end(); }

		reference operator[](size_type n);
		reference front();
		reference back();
		const_reference operator[](size_type n)const;
		const_reference front()const;
		const_reference back()const;

		void push_back(const value_type& val);
		void push_front(const value_type& val);
		void pop_back();
		void pop_front();
		void swap(deque& dq);
		void clear();

	private:
		T* getNewBuck();
		T** getNewMap(const size_t size);
		size_t getNewMapSize(const size_t size);
		size_t getBuckSize()const;
		void init();
		bool back_full()const;
		bool front_full()const;
		void deque_aux(size_t n, const value_type& val, std::true_type);

		template<class Iterator>
		void deque_aux(Iterator first, Iterator last, std::false_type);

		void reallocateAndCopy();

	public:
		template<class T, class Alloc>
		friend bool operator==(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);

		template<class T, class Alloc>
		friend bool operator!=(const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);

		template<class T, class Alloc>
		friend void swap(deque<T, Alloc>& dq1, deque<T, Alloc>& dq2);
	};
}

#include "deque.impl.h"