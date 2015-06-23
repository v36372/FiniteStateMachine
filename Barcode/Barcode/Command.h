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
		opResult,
		OpEnum
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
		std::string to_string(int);
		void LoadString(std::string);

		~Command();
	};
}