#pragma once

template<typename return_type, typename param_type1, typename param_type2>
class Delegate
{
	typedef return_type(*Type)(void* callee, param_type1, param_type2);
public:
	Delegate()
	{

	}

	Delegate(void* callee, Type function)
		: fpCallee(callee)
		, fpCallbackFunction(function) {}
	template <class T, return_type(T::*TMethod)(param_type1, param_type2)>
	static Delegate from_function(T* callee)
	{
		Delegate d(callee, &methodCaller<T, TMethod>);
		return d;
	}
	return_type operator()(param_type1 x, param_type2 y) const
	{
		return (*fpCallbackFunction)(fpCallee, x,y);
	}
private:
	void* fpCallee;
	Type fpCallbackFunction;
	template <class T, return_type(T::*TMethod)(param_type1, param_type2)>
	static return_type methodCaller(void* callee, param_type1 x, param_type2 y)
	{
		T* p = static_cast<T*>(callee);
		return (p->*TMethod)(x,y);
	}
};