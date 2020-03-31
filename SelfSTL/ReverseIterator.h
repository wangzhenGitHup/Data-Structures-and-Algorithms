#pragma once

#include "Iterator.h"

namespace SelfSTL
{
	template<class Iterator>
	class reverse_iterator_t
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef const pointer											const_pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef const reference											const_reference;

	public:
		reverse_iterator_t() : base__(nullptr), cur__(nullptr){}
		explicit reverse_iterator_t(const iterator_type& it) : base__(it)
		{
			auto temp = it;
			cur__ = --temp;
		}

		template<class Iter>
		reverse_iterator_t(const reverse_iterator_t<Iter>& rev_it)
		{
			base__ = (iterator_type)rev_it.base();
			auto temp = base__;
			cur__ = --temp;
		}

		iterator_type base()
		{
			return base__;
		}

		reference operator*()
		{
			return (*cur__);
		}

		const_reference operator*()const
		{
			return (*cur__);
		}

		pointer oprator->()
		{
			return &(operator*());
		}

		const_pointer operator->()const
		{
			return &(operator*());
		}

		reverse_iterator_t& operator++()
		{
			--base__;
			--cur__;
			return *this;
		}

		reverse_iterator_t& operator++(int)
		{
			reverse_iterator_t temp = *this;
			++(*this);
			return temp;
		}

		reverse_iterator_t& operator--()
		{
			++base__;
			++cur__;
			return *this;
		}

		reverse_iterator_t operator--(int)
		{
			reverse_iterator_t temp = *this;
			--(*this);
			return temp;
		}

		reference operator[](difference_type n)
		{
			return base()[-n - 1];
		}

		reverse_iterator_t operator+(difference_type n)const;
		reverse_iterator_t& operator+=(difference_type n);
		reverse_iterator_t operator-(difference_type n)const;
		reverse_iterator_t& operator-=(difference_type n);


	private:
		Iterator base__;
		Iterator cur__;
	};
}