#include "IContext.h"

IContext::IContext()
{

}

bool IContext::Eval(CTransitionInfo* TransitionInfo)
{
	return true;
}

double IContext::EvaluateFunction(std::string)
{
	return 0;
}

double IContext::EvaluateVariable(std::string)
{
	return 0;
}


IContext::~IContext()
{

}