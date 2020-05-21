#pragma once

namespace SelfSTL
{
	template<class T, class Alloc>
	Vector<T, Alloc>::~Vector()
	{
		destroyAndDeallocateAll();
	}

	template<class T, class Alloc>
	Vector<T, Alloc>::Vector(const size_type n)
	{
		allocateAndFillN(n, value_type());
	}

	template<class T, class Alloc>
	Vector<T, Alloc>::Vector(const size_type n, const value_type& value)
	{
		allocateAndFillN(n, value);
	}

	template<class T, class Alloc>
	template<class InputIterator>
	Vector<T, Alloc>::Vector(InputIterator first, InputIterator last)
	{
		vector_aux(first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	Vector<T, Alloc>::Vector(const Vector& v)
	{
		allocateAndCopy(v.start_, v.finish_);
	}

	template<class T, class Alloc>
	Vector<T, Alloc>::Vector(Vector&& v)
	{
		start_ = v.start_;
		finish_ = v.finish_;
		endOfStorage_ = v.endOfStorage_;
		v.start_ = v.finish_ = v.endOfStorage_ = 0;
	}

	template<class T, class Alloc>
	Vector<T, Alloc>& Vector<T, Alloc>::opeartor = (const Vector& v)
	{
		if (this != &v)
		{
			allocateAndCopy(v.start_, v.finish_);
		}

		return *this;
	}

	template<class T, class Alloc>
	Vector<T, Alloc>& Vector<T, Alloc>::opeartor = (Vector&& v)
	{
		if (this != &v)
		{
			destroyAndDeallocateAll();
			start_ = v.start_;
			finish_ = v.finish_;
			endOfStorage_ = v.endOfStorage_;
			v.start_ = v.finish_ = v.endOfStorage_ = 0;
		}

		return *this;
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::resize(size_type n, value_type val /* = value_type() */)
	{
		if (n < size())
		{
			dataAllocator::destroy(start_ + n, finish_);
			finish_ = start_ + n;
		}
		else if (n > size() && n <= capacity())
		{
			auto lengthOfInsert = n - size();
			finish_ = SelfSTL::uninitialized_fill_n(finish_, lengthOfInsert, val);
		}
		else if (n > capacity())
		{
			auto lengthOfInsert = n - size();
			T* newStart = dataAllocator::allocates(getNewCapacity(lengthOfInsert));
			T* newFinish = SelfSTL::uninitialized_copy(begin(), end(), newStart);
			newFinish = SelfSTL::uninitialized_fill_n(newFinish, lengthOfInsert, val);

			destroyAndDeallocateAll();
			start_ = newStart;
			finish_ = newFinish;
			endOfStorage_ = start_ + n;
		}
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::reserve(size_type n)
	{
		if (n <= capacity())
		{
			return;
		}

		T* newStart = dataAllocator::allocates(n);
		T* newFinish = SelfSTL::uninitialized_copy(begin(), end(), newStart);
		destroyAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + n;
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator position)
	{
		return erase(position, position + 1);
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator first, iterator last)
	{
		difference_type lenOfTail = end() - last;
		difference_type lenOfRemoved = last - first;
		finish_ = finish_ - lenOfRemoved;
		for (; lenOfTail != 0; --lenOfTail)
		{
			auto temp = (last - lenOfRemoved);
			*temp = *(last++);
		}

		return first;
	}


	template<class T, class Alloc>
	template<class InputIterator>
	void Vector<T, Alloc>::reallocateAndCopy(iterator position, InputIterator first, InputIterator last)
	{
		difference_type newCapacity = getNewCapacity(last - first);

		T* newStart = dataAllocator::allocates(newCapacity);
		T* newEndOfStorage = newStart + newCapacity;
		T* newFinish = SelfSTL::uninitialized_copy(begin(), position, newStart);
		newFinish = SelfSTL::uninitialized_copy(first, last, newFinish);
		newFinish = SelfSTL::uninitialized_copy(position, end(), newFinish);

		destroyAndDeallocateAll();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = newEndOfStorage;
	}


	template<class T, class Alloc>
	void Vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type& n, const value_type& val)
	{
		difference_type newCapacity = getNewCapacity(n);

		T* newStart = dataAllocator::allocates(newCapacity);
		T* newEndOfStorage = newStart + newCapacity;
		T* newFinish = SelfSTL::uninitialized_copy(begin(), position, newStart);
		newFinish = SelfSTL::uninitialized_fill(newFinish, n, val);
		newFinish = SelfSTL::uninitialized_copy(position, end(), newFinish);

		destroyAndDeallocateAll();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = newEndOfStorage;
	}

	template<class T, class Alloc>
	template<class InputIterator>
	void Vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
	{
		difference_type locationLeft = endOfStorage_ - finish_;
		difference_type locationNeed = distance(first, last);

		if (locationLeft >= locationNeed)
		{
			if (finish_ - position > locationNeed)
			{
				SelfSTL::uninitialized_copy(finish_ - locationNeed, finish_, finish_);
				std::copy_backward(position, finish_ - locationNeed, finish_);
				std::copy(first, last, position);
			}
			else
			{
				iterator tmp = SelfSTL::uninitialized_copy(first + (finish_ - position), last, finish_);
				SelfSTL::uninitialized_copy(position, finish_, tmp);
				std::copy(first, first + (finish_ - position), position);
			}

			finish_ += locationNeed;
		}
		else
		{
			reallocateAndCopy(position, first, last);
		}
	}


	template<class T, class Alloc>
	template<class Integer>
	void Vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type)
	{
		assert(n != 0);
		difference_type locationLeft = endOfStorage_ - finish_;
		difference_type locationNeed = n;

		if (locationLeft >= locationNeed)
		{
			auto tmpPtr = end() - 1;
			for (; tmpPtr - position >= 0; --tmpPtr)
			{
				construct(tmpPtr + locationNeed, *tmpPtr);
			}

			SelfSTL::uninitialized_fill_n(position, n, value);
			finish_ += locationNeed;
		}
		else
		{
			reallocateAndFillN(position, n, value);
		}
	}


	template<class T, class Alloc>
	template<class InputIterator>
	void Vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
	{
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val)
	{
		insert_aux(position, n, val, typename std::is_integral<size_type>::type());
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val)
	{
		const auto idx = position - begin();
		insert(position, 1, val);
		return begin() + idx;
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::push_back(const value_type& value)
	{
		insert(end(), value);
	}

	template<class T, class Alloc>
	bool Vector<T, Alloc>::opeartor == (const Vector& v)const
	{
		if (size() != v.size())
		{
			return false;
		}

		auto ptr1 = start_;
		auto ptr2 = v.start_;
		for (; ptr1 != finish_ && ptr2 != v.finish_; ++ptr1, ++ptr2)
		{
			if (*ptr1 != *ptr2)
			{
				return false;
			}
		}

		return true;
	}


	template<class T, class Alloc>
	bool Vector<T, Alloc>::opeartor != (const Vector& v)const
	{
		return !(*this == v);
	}

	template<class T, class Alloc>
	bool operator == (const Vector<T, Alloc>& v1, const Vector<T, Alloc>& v2)
	{
		return v1.operator ==(v2);
	}

	template<class T, class Alloc>
	bool operator != (const Vector<T, Alloc>& v1, const Vector<T, Alloc>& v2)
	{
		return !(v1 == v2);
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::shrink_to_fit()
	{
		T* tmp = (T*)dataAllocator::allocates(size());
		finish_ = SelfSTL::uninitialized_copy(start_, finish_, tmp);
		dataAllocator::deallocate(start_, capacity());
		start_ = t;
		endOfStorage_ = finish_;
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::clear()
	{
		dataAllocator::destroy(start_, finish_);
		finish_ = start_;
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::swap(Vector& v)
	{
		if (this != &v)
		{
			SelfSTL::swap(start_, v.start_);
			SelfSTL::swap(finish_, v.finish_);
			SelfSTL::swap(endOfStorage_, v.endOfStorage_);
		}
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::pop_back()
	{
		--finish_;
		dataAllocator::destroy(finish_);
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::destroyAndDeallocateAll()
	{
		if (capacity() != 0)
		{
			dataAllocator::destroy(start_, finish_);
			dataAllocator::deallocate(start_, capacity());
		}
	}

	template<class T, class Alloc>
	void Vector<T, Alloc>::allocateAndFillN(const size_type n, const value_type& value)
	{
		start_ = dataAllocator::allocates(n);
		SelfSTL::uninitialized_fill_n(start_, n, value);
		finish_ = endOfStorage_ = start_ + n;
	}

	template<class T, class Alloc>
	template<class InputIterator>
	void Vector<T, Alloc>::allocateAndCopy(InputIterator first, InputIterator last)
	{
		start_ = dataAllocator::allocates(last - first);
		finish_ = SelfSTL::uninitialized_copy(first, last, start_);
		endOfStorage_ = finish_;
	}

	template<class T, class Alloc>
	template<class InputIterator>
	void Vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type)
	{
		allocateAndCopy(first, last);
	}

	template<class T, class Alloc>
	template<class InputIterator>
	void Vector<T, Alloc>::vector_aux(Integer n, const value_type& value, std::true_type)
	{
		allocateAndFillN(n, value);
	}

	template<class T, class Alloc>
	typename Vector<T, Alloc>::size_type Vector<T, Alloc>::getNewCapacity(size_type len)const
	{
		size_type oldCapacity = endOfStorage_ - start_;
		auto res = SelfSTL::max(oldCapacity, len);
		size_type newCapacity = (oldCapacity != 0) ? (oldCapacity + res) : len;
		return newCapacity;
	}

}