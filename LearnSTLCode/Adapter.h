#pragma  once

#include "Functor.h"

namespace SelfSTL
{

	template<class Predicate>
	class unary_negate : public unary_function<typename Predicate::argument_type, bool>
	{
	public:
		explicit unary_negate(const Predicate& x) : pred(x){}
		bool operator()(const typename Predicate::argument_type& x)const
		{
			return !pred(x);
		}

	protected:
		Predicate pred;
	};

	template<class Predicate>
	class binary_negate : public binary_function<typename Predicate::first_argument_type,
		typename Predicate::second_argument_type, bool>
	{
	public:
		explicit binary_negate(const Predicate& x) : pred(x){}
		bool operator()(const typename Predicate::first_argument_type& x, 
			const typename Predicate::second_argument_type& y)const
		{
			return !pred(x, y);
		}
	protected:
		Predicate pred;
	};

	template<class Predicate>
	binary_negate<Predicate> not2(const Predicate& pred)
	{
		return binary_negate<Predicate>(pred);
	}

	template<class Operation>
	class binder1st : public unary_function<typename Operation::second_argument_type,
		typename Operation::result_type>
	{
	public:
		binder1st(const Operation& x, 
			const typename Operation::first_argument_type& y) : op(x), value(y)
		{}

		typename Operation::result_type operator()(const typename Operation::second_argument_type& x)const
		{
			return op(value, x);
		}

	protected:
		Operation op;
		typename Operation::first_argument_type value;
	};

	template<class Operation, class T>
	binder1st<Operation>bind1st(const Operation& op, const T& x)
	{
		typedef typename Operation::first_argument_type arg1_type;
		return binder1st<Operation>(op, arg1_type(x));
	}

	template<class Operation>
	class binder2nd : public unary_function<typename Operation::first_argument_type,
		typename Operation::result_type>
	{
	public:
		binder2nd(const Operation& x, 
			const typename Operation::second_argument_type& y) : op(x), value(y){}

		typename Operation::result_type operator()(const typename Operation::first_argument_type& x)const
		{
			return op(x, value);
		}

	protected:
		Operation op;
		typename Operation::second_argument_type value;
	};

	template<class Operation, class T>
	binder2nd<Operation> bind2nd(const Operation& op, const T& x)
	{
		typedef typename Operation::second_argument_type arg2_type;
		return binder2nd<Operation>(op, arg2_type(x));
	}

	template<class Operation1, class Operation2>
	class unary_compose : public unary_function<typename Operation2::argument_type, typename Operation1::result_type>
	{
	public:
		unary_compose(const Operation1& x, const Operation2& y) : op1(x), op2(y){}

		typename Operation1::result_type operator()(const typename Operation2::argument_type& x)const
		{
			return op1(op2(x));
		}

	protected:
		Operation1 op1;
		Operation2 op2;
	};

	template<class Operation1, class Operation2>
	unary_compose<Operation1, Operation2> compose1(const Operation1& op1, const Operation2& op2)
	{
		return unary_compose<Operation1, Operation2>(op1, op2);
	}

	template<class Operation1, class Operation2, class Operation3>
	class binary_compose : public unary_function<typename Operation2::argument_type,
		typename Operation1::result_type>
	{
	public:
		binary_compose(const Operation1& x, const Operation2& y, const Operation3& z) : op1(x), op2(y), op3(z)
		{}

		typename Operation1::result_type operator()(const typename Operation2::argument_type& x)const
		{
			return op1(op2(x), op3(x));
		}

	protected:
		Operation1 op1;
		Operation2 op2;
		Operation3 op3;
	};

	template<class Operation1, class Operation2, class Operation3>
	binary_compose<Operation1, Operation2, Operation3> compose2(const Operation1& op1, const Operation2& op2, const Operation3& op3)
	{
		return binary_compose<Operation1, Operation2, Operation3>(op1, op2, op3);
	}

	template<class Arg, class Result>
	class pointer_to_unary_function : public unary_function<Arg, Result>
	{
	public:
		pointer_to_unary_function(){}
		explicit pointer_to_unary_function(Result(*x)(Arg)) : ptr(x){}

		Result operator()(Arg x)const{ return ptr(x); }
	protected:
		Result(*ptr) (Arg);
	};

	template<class Arg, class Result>
	pointer_to_unary_function<Arg, Result> ptr_fun(Result(*x) (Arg))
	{
		return pointer_to_unary_function<Arg, Result>(x);
	}

	template<class Arg1, class Arg2, class Result>
	class pointer_to_binary_function : public binary_function<Arg1, Arg2, Result>
	{
	public:
		pointer_to_binary_function(){}

		explicit pointer_to_binary_function(Result(*x)(Arg1, Arg2)) : ptr(x){}

		Result operator()(Arg1 x, Arg2 y)const { return ptr(x, y); }

	protected:
		Result(*ptr)(Arg1, Arg2);
	};

	template<class Arg1, class Arg2, class Result>
	pointer_to_binary_function<Arg1, Arg2, Result> ptr_fun(Result(*x) (Arg1, Arg2))
	{
		return pointer_to_binary_function<Arg1, Arg2, Result>(x);
	}
}