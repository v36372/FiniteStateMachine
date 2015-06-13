#pragma once

template<typename return_type, typename param_type>
class Delegate
{
	typedef return_type(*Type)(void* callee, param_type);
public:
	Delegate()
	{

	}

	Delegate(void* callee, Type function)
		: fpCallee(callee)
		, fpCallbackFunction(function) {}
	template <class T, return_type(T::*TMethod)(param_type)>
	static Delegate from_function(T* callee)
	{
		Delegate d(callee, &methodCaller<T, TMethod>);
		return d;
	}
	return_type operator()(param_type x) const
	{
		return (*fpCallbackFunction)(fpCallee, x);
	}
private:
	void* fpCallee;
	Type fpCallbackFunction;
	template <class T, return_type(T::*TMethod)(param_type)>
	static return_type methodCaller(void* callee, param_type x)
	{
		T* p = static_cast<T*>(callee);
		return (p->*TMethod)(x);
	}
};