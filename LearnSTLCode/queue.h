#pragma once

#include "deque.h"

namespace SelfSTL
{
	template<class T, class Sequence = deque<T>>
	class queue
	{
		friend bool operator==(const queue& q1, const queue& q2);
		friend bool operator<(const queue& q1, const queue& q2);

	public:
		typedef typename Sequence::value_type       value_type;
		typedef typename Sequence::size_type        size_type;
		typedef typename Sequence::reference        reference;
		typedef typename Sequence::const_reference  const_reference;

	protected:
		Sequence container_;

	public:
		bool empty()const{ return container_.empty(); }
		size_type size()const{ return container_.size(); }
		reference front(){ return container_.front(); }
		const_reference front()const{ return container_.front(); }
		reference back(){ return container_.back(); }
		const_reference back()const{ return container_.back(); }
		void push(const value_type& val){ container_.push_back(val); }
		void pop(){ container_.pop_front(); }
	};

	template<class T, class Sequence>
	bool operator==(const queue<T, Sequence>& q1, const queue<T, Sequence>& q2)
	{
		return q1.container_ == q2.container_;
	}

	template<class T, class Sequence>
	bool operator<(const queue<T, Sequence>& q1, const queue<T, Sequence>& q2)
	{
		return q1.container_ < q2.container_;
	}
}