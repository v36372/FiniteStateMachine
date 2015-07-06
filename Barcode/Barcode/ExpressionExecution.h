#pragma once
#include <string>
#include <vector>
#include <map>	
#include "Command.h"
#include "Delegate.h"

enum paramType
	{
		Int,
		Float,
		String,
	};

	struct param
	{
		paramType type;
		int iParam;
		float fParam;
		std::string sParam;

		param()
		{
			type = paramType::Int;
			iParam = 0;
			fParam = 0.0;
			sParam = "";
		}
	};

namespace JFSM
{
	class ExpressionExecution
	{
	public:
		ExpressionExecution();

		double Result;
		std::string ErrorCode;
		bool HasError;
		
		Delegate<double,std::string,std::vector<param>> FunctionEvalHandler;
		Delegate<double,std::string,std::vector<param>> VariableEvalHandler;

		void LoadExpression(std::vector<Command*> data);

		void LoadExpression(std::string data);

		std::vector<Command*> GetCompileData()
		{
			return m_pCommandList;
		}

		void Eval();
		std::vector<param> _ParseFunctionParam(Command* cmd);
		double _GetOperatorData(int index, Command* cmd);
	
		unsigned long hash(const char *str)
		{
			unsigned long hash = 5381;
			int c;
			
			while (c = *str++)
				hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
			
			return hash;
		}	

		~ExpressionExecution();
	private:
		std::vector<Command*> m_pCommandList;
		double* m_pRunTimeMemory;

		std::map<int, std::vector<Command*>> s_pCommandCache;
	};
}