#define _CRT_SECURE_NO_WARNINGS
#include "Command.h"

JFSM::Command::Command()
{

}

std::string JFSM::Command::GetString()
{
	std::string res = "";
	res += (int)opCode + "," + DataName + "," + std::to_string(OutputVariableIndex) + ",";

	if (Args.size() > 0)
	{
		res += std::to_string(Args.size());
		for (int i = 0; i < Args.size(); i++)
		{
			res += "," + Args[i];
		}
	}
	else
	{
		res += "0";
	}

	return res;
}

void JFSM::Command::LoadString(std::string data)
{
	data += ",";
	int index = 0;
	std::string tmp;
	int searchIndex = 0;

	index = data.find(",", searchIndex);
	tmp = data.substr(searchIndex, index - searchIndex);
	searchIndex = index + 1;

	opCode = (OpCode)(int)atoi(tmp.c_str());
	
	index = data.find(",", searchIndex);
	tmp = data.substr(searchIndex, index - searchIndex);
	searchIndex = index + 1;

	DataName = tmp;
	
	index = data.find(",", searchIndex);
	tmp = data.substr(searchIndex, index - searchIndex);
	searchIndex = index + 1;

	OutputVariableIndex = (int)atoi(tmp.c_str());

	index = data.find(",", searchIndex);
	tmp = data.substr(searchIndex, index - searchIndex);
	searchIndex = index + 1;

	int count = (int)atoi(tmp.c_str());

	index = data.find(",", searchIndex);
	tmp = data.substr(searchIndex, index - searchIndex);
	searchIndex = index + 1;

	if (count >= 0)
	{
		Args.clear();
		for (int i = 0; i < count; i++)
		{
			if (tmp != "")
			{
				Args.push_back((int)atoi(tmp.c_str()));

				if (index == -1)
					break;
				index = data.find(",", searchIndex);
				tmp = data.substr(searchIndex, index - searchIndex);
				searchIndex = index + 1;
			}
		}
	}
	else
	{
		Args.clear();
	}
}

JFSM::Command::~Command()
{

}
