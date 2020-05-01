#pragma once

#include "deque.h"

namespace SelfSTL
{
	template<class T, class Sequence = deque<T>>
	class stack
	{
		friend bool operator==(const stack& s1, const stack& s2);
		friend bool operator<(const stack& s1, const stack & s2);

	public:
		typedef typename Sequence::value_type        value_type;
		typedef typename Sequence::size_type         size_type;
		typedef typename Sequence::reference         reference;
		typedef typename Sequence::const_reference   const_reference;

	protected:
		Sequence c_;

	public:
		bool empty()const{ return c_.empty(); }
		size_type size()const{ return c_.size(); }
		reference top(){ return c_.back(); }
		const_reference top()const{ return c_.back(); }
		void push(const value_type& val){ c_.push_back(val); }
		void pop(){ c_.pop_back(); }
	};

	template<class T, class Sequence>
	bool operator==(const stack<T, Sequence>& s1, const stack<T, Sequence>& s2)
	{
		return s1.c_ == s2.c_;
	}

	template<class T, class Sequence>
	bool operator<(const stack<T, Sequence>& s1, const stack<T, Sequence>& s2)
	{
		return s1.c_ < s2.c_;
	}
}