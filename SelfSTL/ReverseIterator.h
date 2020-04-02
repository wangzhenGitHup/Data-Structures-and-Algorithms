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

		reverse_iterator_t operator+(difference_type n)const
		{
			reverse_iterator_t res = *this;
			res += n;
			return res;
		}

		reverse_iterator_t& operator+=(difference_type n)
		{
			base__ == advanceNStep(base__, n, false, iterator_category());
			cur__ = advanceNStep(cur__, n, false, iterator_category());
			return *this;
		}

		reverse_iterator_t operator-(difference_type n)const
		{
			reverse_iterator_t res = *this;
			res += n;
			return res;
		}

		reverse_iterator_t& operator-=(difference_type n)
		{
			base__ = advanceNStep(base__, n, false, iterator_category());
			cur__ = advanceNStep(cur__, n, false, iterator_category());
			return *this;
		}

		friend bool operator==(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
		{
			return lhs.cur__ == rhs.cur__;
		}

		friend bool operator!=(const reverse_iterator_t<Iterator>& lhs, reverse_iterator_t<Iterator>& rhs)
		{
			return !(lhs == rhs);
		}

		friend bool operator<(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
		{
			return lhs.cur__ < rhs.cur__;
		}

		friend bool operator<=(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
		{
			return !(lhs > rhs);
		}

		friend bool operator>(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
		{
			return lhs.cur__ > rhs.cur__;
		}

		friend bool operator>=(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
		{
			return !(lhs < rhs);
		}

		friend reverse_iterator_t operator+(typename reverse_iterator_t<Iterator>::difference_type n, const reverse_iterator_t<Iterator>& rev_it)
		{
			return rev_it + n;
		}

		friend typename reverse_iterator_t<Iterator>::difference_type operator-(const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs)
		{
			return lhs.cur__ - rhs.cur__;
		}

	private:
		Iterator advanceNStep(Iterator it, difference_type n, bool bRight, random_access_iterator_tag)
		{
			if (bRight)
			{
				it += n;
			}
			else
			{
				it -= n;
			}

			return it;
		}

		Iterator advanceNStep(Iterator it, difference_type n, bool bRight, bidirectional_iterator_tag)
		{
			difference_type i;
			difference_type absN = n >= 0 ? n : -n;
			if ((bRight && n > 0) || (!bRight && n < 0))
			{
				for (i = 0; i != absN; i++)
				{
					it = it + 1;
				}
			}
			else if ((!bRight && n > 0) || (bRight && n < 0))
			{
				for (i = 0; i != absN; i++)
				{
					it = it - 1;
				}
			}

			return it;
		}

	private:
		Iterator base__;
		Iterator cur__;
	};
}