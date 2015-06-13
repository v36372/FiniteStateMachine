#pragma once
#include <vector>
#include <string>

namespace JFSM
{
	enum OpCode
	{
		OpVariableEval,
		OpFunctionEval,
		OpLT,
		OpGT,
		OpAdd,
		OpSub,
		OpMul,
		OpDiv,
		OpPow,
		OpEqual,
		OpAnd,
		OpOr,
		OpNot,
		OpConstant,
		OpVariable,
		opResult
	};

	class Command
	{
	public:
		Command();

		OpCode opCode;
		std::vector<int> Args;
		int OutputVariableIndex;
		std::string DataName;

		std::string GetString();
		void LoadString(std::string);

		~Command();
	};
}