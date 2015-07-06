#pragma once
#include <string>
#include "CTransitionInfo.h"
#include "ExpressionExecution.h"

class IContext
{
public:
	IContext();

	virtual bool Eval(CTransitionInfo*& trans) = 0;
	virtual double EvaluateFunction(std::string name,std::vector<param> ParamList) = 0;
	virtual double EvaluateVariable(std::string name,std::vector<param> ParamList) = 0;

	~IContext();
};