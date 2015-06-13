#pragma once
#include <string>
#include <vector>
#include <map>	
#include "Command.h"
#include "Delegate.h"

namespace JFSM
{
	class ExpressionExecution
	{
	public:
		ExpressionExecution();

		double Result;
		std::string ErrorCode;
		bool HasError;

		Delegate<double,std::string> FunctionEvalHandler;
		Delegate<double,std::string> VariableEvalHandler;

		void LoadExpression(std::vector<Command*> data);

		void LoadExpression(std::string data);

		std::vector<Command*> GetCompileData()
		{
			return m_pCommandList;
		}

		void Eval();
		double _GetOperatorData(int index, Command* cmd);

		~ExpressionExecution();
	private:
		std::vector<Command*> m_pCommandList;
		double* m_pRunTimeMemory;

		std::map<int, std::vector<Command*>> s_pCommandCache;
	};
}