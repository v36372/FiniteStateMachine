#pragma once
#include <string>
#include "CTransitionInfo.h"

class IContext
{
public:
	IContext();

	virtual bool Eval(CTransitionInfo* trans);
	virtual double EvaluateFunction(std::string name);
	virtual double EvaluateVariable(std::string name);

	~IContext();
};