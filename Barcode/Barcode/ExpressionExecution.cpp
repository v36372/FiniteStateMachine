#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "ExpressionExecution.h"
#include <math.h>
#include <functional>

JFSM::ExpressionExecution::ExpressionExecution()
{
	m_pRunTimeMemory = new double[100];
}

void JFSM::ExpressionExecution::LoadExpression(std::vector<Command*> data)
{
	m_pCommandList = data;
}

void JFSM::ExpressionExecution::LoadExpression(std::string data)
{
	data += ":";
	if (s_pCommandCache.find(hash(data.c_str())) != s_pCommandCache.end())
	{
		m_pCommandList = s_pCommandCache[hash(data.c_str())];
		return;
	}

	//char* cdata = _strdup(data.c_str());
	//cdata = strtok(cdata,":");
	std::vector<Command*> res;
	int searchIndex = 0;
	while (data.find(":",searchIndex) != std::string::npos)
	{
		int index = data.find(':',searchIndex);
		Command* cmd = new Command();
		cmd->LoadString(data.substr(searchIndex,index-searchIndex));
		res.push_back(cmd);
		searchIndex = index+1;
	}
	s_pCommandCache[std::tr1::hash<std::string>()(data)] = res;
	m_pCommandList = res;
}

std::vector<param> JFSM::ExpressionExecution::_ParseFunctionParam(Command* cmd)
{
		//object[] param = null;
		std::vector<param> paramList;
		if (cmd->Args.size() > 0)
		{
			//param = new object[cmd.Args.Count / 2];
			param newParam;
			for (int j = 0; j < cmd->Args.size(); j += 2)
			{
				OpCode code = (OpCode)cmd->Args[j];
				int value = cmd->Args[j + 1];
				//if (code == OpCode::OpConstant)
				//{
				//	newParam.type = paramType::Int;
				//	newParam.iParam = value;
				//}
				//else if(code == OpCode::OpEnum)
				//{
				//	
				//}
				///*else if (code == OpCode.OpVariable)
				//{
				//	param[j / 2] = m_pRunTimeMemory[value];
				//}*/
				
				newParam.type = paramType::Float;
				newParam.fParam = value;

				paramList.push_back(newParam);
			}
		}
		return paramList;
}

double JFSM::ExpressionExecution::_GetOperatorData(int index, Command* cmd)
{
	OpCode code = (OpCode)cmd->Args[index * 2 + 0];
	int value = cmd->Args[index * 2 + 1];

	if (code == OpConstant)
	{
		return value;
	}
	else if (code == OpVariable)
	{
		return m_pRunTimeMemory[value];
	}

	return 0.0;
}

void JFSM::ExpressionExecution::Eval()
{
	if (m_pCommandList.size() == 0)
		throw "[ExpressionExecution] Command has not loaded or Function or Variable Handler has null Value. Good Luck!";

	Command* cmd;
	ErrorCode = "";
	HasError = true;
	Result = 0.0;
	try
	{
		for (int i = 0; i < m_pCommandList.size(); i++)
		{
			cmd = m_pCommandList[i];

			switch (cmd->opCode)
			{
			case OpVariableEval:
			{
										  std::vector<param> paramList;
										  m_pRunTimeMemory[cmd->OutputVariableIndex] = VariableEvalHandler(cmd->DataName,paramList);
			}
				break;
			case OpFunctionEval:
			{
										  //object[] param = _ParseFunctionParam(cmd);
										  //object[] param = null;
										  std::vector<param> paramList = _ParseFunctionParam(cmd);
										  m_pRunTimeMemory[cmd->OutputVariableIndex] = FunctionEvalHandler(cmd->DataName,paramList);
			}
				break;
			case OpLT:
			{
								double val1 = _GetOperatorData(0, cmd);
								double val2 = _GetOperatorData(1, cmd);

								bool res = val1 < val2;

								m_pRunTimeMemory[cmd->OutputVariableIndex] = res ? 1.0 : 0.0;
			}
				break;
			case OpGT:
			{
								double val1 = _GetOperatorData(0, cmd);
								double val2 = _GetOperatorData(1, cmd);

								bool res = val1 > val2;

								m_pRunTimeMemory[cmd->OutputVariableIndex] = res ? 1.0 : 0.0;
			}
				break;
			case OpAdd:
			{
								 double val1 = _GetOperatorData(0, cmd);
								 double val2 = _GetOperatorData(1, cmd);

								 double res = val1 + val2;

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res;
			}
				break;
			case OpSub:
			{
								 double val1 = _GetOperatorData(0, cmd);
								 double val2 = _GetOperatorData(1, cmd);

								 double res = val1 - val2;

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res;
			}
				break;
			case OpMul:
			{
								 double val1 = _GetOperatorData(0, cmd);
								 double val2 = _GetOperatorData(1, cmd);

								 double res = val1 * val2;

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res;
			}
				break;
			case OpDiv:
			{
								 double val1 = _GetOperatorData(0, cmd);
								 double val2 = _GetOperatorData(1, cmd);

								 double res = val1 / val2;

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res;
			}
				break;
			case OpPow:
			{
								 double val1 = _GetOperatorData(0, cmd);
								 double val2 = _GetOperatorData(1, cmd);

								 double res = pow(val1, val2);

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res;
			}
				break;
			case OpEqual:
			{
								   double val1 = _GetOperatorData(0, cmd);
								   double val2 = _GetOperatorData(1, cmd);

								   bool res = val1 == val2;

								   m_pRunTimeMemory[cmd->OutputVariableIndex] = res ? 1.0 : 0.0;
			}
				break;
			case OpAnd:
			{
								 // HHoang (optimize)
								 bool res = false;

								 if (_GetOperatorData(0, cmd) != 0.0)
								 if (_GetOperatorData(1, cmd) != 0.0)
									 res = true;

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res ? 1.0 : 0.0;

								 //double val1 = _GetOperatorData(0, cmd);
								 //double val2 = _GetOperatorData(1, cmd);
								 //bool res = (val1 != 0.0) && (val2 != 0.0);
								 //m_pRunTimeMemory[cmd.OutputVariableIndex] = res ? 1.0 : 0.0;
			}
				break;
			case OpOr:
			{
								// HHoang (optimize)
								bool res = false;

								if (_GetOperatorData(0, cmd) != 0.0)
									res = true;
								else if (_GetOperatorData(1, cmd) != 0.0)
									res = true;

								m_pRunTimeMemory[cmd->OutputVariableIndex] = res ? 1.0 : 0.0;

								//double val1 = _GetOperatorData(0, cmd);
								//double val2 = _GetOperatorData(1, cmd);
								//bool res = (val1 != 0.0) || (val2 != 0.0);
								//m_pRunTimeMemory[cmd.OutputVariableIndex] = res ? 1.0 : 0.0;
			}
				break;
			case OpNot:
			{
								 // HHoang (optimize)
								 bool res = _GetOperatorData(1, cmd) == 0.0;

								 m_pRunTimeMemory[cmd->OutputVariableIndex] = res ? 1.0 : 0.0;

								 //double val1 = _GetOperatorData(0, cmd);
								 //double val2 = _GetOperatorData(1, cmd);
								 //bool res = !(val2 != 0.0);
								 //m_pRunTimeMemory[cmd.OutputVariableIndex] = res ? 1.0 : 0.0;
			}
				break;
			case OpConstant:
				break;
			case OpVariable:
				break;
			case opResult:
				Result = m_pRunTimeMemory[cmd->OutputVariableIndex];
				HasError = false;
				break;
			default:
				break;
			}
		}
	}
	catch (std::string e)
	{
		HasError = true;
		ErrorCode = "[ExpressionExecution] Error at \n" + e;
		return;
	}
}

JFSM::ExpressionExecution::~ExpressionExecution()
{
	delete m_pRunTimeMemory;
	for (int i = 0; i < m_pCommandList.size(); i++)
	{
		delete m_pCommandList[i];
	}
}