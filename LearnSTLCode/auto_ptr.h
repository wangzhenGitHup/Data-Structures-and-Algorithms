#pragma once

namespace SelfSTL
{
	template<class Y>
	struct auto_ptr_ref
	{
		Y* m_yptr;
		auto_ptr_ref(Y* rhs) : m_yptr(rhs) {}
	};

	template<class T>
	class auto_ptr
	{
	public:
		typedef T element_type;

		explicit auto_ptr(T* ptr = nullptr) throw() : m_val_ptr(ptr){}

		auto_ptr(auto_ptr& rhs) throw() : m_val_ptr(rhs.release()){}

		template<class U>
		auto_ptr(auto_ptr<U>& rhs) throw() : m_val_ptr(rhs.release()){}

		auto_ptr& operator=(auto_ptr& rhs) throw() 
		{
			reset(rhs.release());
			return *this;
		}

		template<class U>
		auto_ptr& operator=(auto_ptr<U>& rhs) throw()
		{
			reset(rhs.release());
			return *this;
		}

		~auto_ptr() throw()
		{
			delete m_val_ptr;
		}

		T* get() const throw()
		{
			return m_val_ptr;
		}

		T& operator*()const throw()
		{
			return *m_val_ptr;
		}

		T* operator->()const throw()
		{
			return m_val_ptr;
		}

		T* release() throw()
		{
			T* tmp(m_val_ptr);
			m_val_ptr = nullptr;
			return tmp;
		}

		void reset(T* ptr = nullptr) throw()
		{
			if (m_val_ptr != ptr)
			{
				delete m_val_ptr;
				m_val_ptr = ptr;
			}
		}

	public:
		auto_ptr(auto_ptr_ref<T> rhs) throw() : m_val_ptr(rhs.m_yptr) {}

		auto_ptr& operator=(auto_ptr_ref<T> rhs) throw()
		{
			reset(rhs.m_yptr);
			return *this;
		}

		template<class U> operator auto_ptr_ref<U>() throw()
		{
			return auto_ptr_ref<U>(release());
		}

		template<class U> operator auto_ptr<U>() throw()
		{
			return auto_ptr<U>(release());
		}

	private:
		T* m_val_ptr;
	};
}