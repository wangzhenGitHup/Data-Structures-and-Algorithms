#pragma once

#include "Vector.h"
#include "heap.h"


namespace SelfSTL
{
	template<class T, class Sequence = Vector<T>, class Compare = less<typename Sequence::value_type>>
	class priority_queue
	{
	public:
		typedef typename Sequence::value_type        value_type;
		typedef typename Sequence::size_type         size_type;
		typedef typename Sequence::reference         reference;
		typedef typename Sequence::const_reference   const_reference;

	protected:
		Sequence container_;
		Compare comp_;

	public:
		priority_queue() : container_(){}
		explicit priority_queue(const Compare& comp) : container_(), comp_(comp){}

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& comp) : 
			container_(first, last), comp_(comp)
		{
			make_heap(container_.begin(), container_.end(), comp_);
		}

		bool empty()const{ return container_.empty(); }
		size_type size() const{ return container_.size(); }
		const_reference top()const{ return container_.front(); }
		
		void push(const value_type& val)
		{
			container_.push_back(val);
			push_heap(container_.begin(), container_.end(), comp_);
		}

		void pop()
		{
			pop_heap(container_.begin(), container_.end(), comp_);
			container_.pop_back();
		}
	};
}