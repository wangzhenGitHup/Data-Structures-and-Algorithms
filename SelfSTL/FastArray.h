#pragma once

#include <cstddef>

template<class T, std::size_t arraySize>
class FastArray
{
public:
	typedef T               value_type;
	typedef T*              iterator;
	typedef const T*        const_iterator;
	typedef T&              reference;
	typedef const T&        const_reference;
	typedef std::size_t     size_type;
	typedef std::ptrdiff_t  difference_type;

	iterator begin() { return data; }
	const_iterator begin()const { return data; }
	iterator end() { return data + arraySize; }
	const_iterator end() const { return data + arraySize; }
	reference operator[](std::size_t idx){ return data[idx]; }
	const_reference operator[](std::size_t idx) const { return data[idx]; }

	size_type size() const { return arraySize; }
	size_type max_size() const{ return arraySize; }

	T* as_array() { return data; }

private:
	T data[arraySize];
};