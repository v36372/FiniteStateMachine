#include "CJsonStateTransitionInfo.h"
#include "json\json.h"
#include <fstream>

std::map<std::string, CJsonStateTransitionInfo*> CJsonStateTransitionInfo::m_pInstanceDatabase = std::map<std::string, CJsonStateTransitionInfo*>();

CJsonStateTransitionInfo::CJsonStateTransitionInfo()
{
	m_pJsonStateList.clear();
	m_pJsonTransitionList.clear();
}

CJsonStateTransitionInfo::CJsonStateTransitionInfo(std::string content)
{
	Parse(content);
}

void CJsonStateTransitionInfo::Load(std::string data)
{
	Parse(data);
}

void CJsonStateTransitionInfo::Parse(std::string path)
{
	// Todo : parse JSON string
	std::string currentKey = "";
	Json::Value root;
	Json::Reader reader;
	try 
	{
		m_pJsonStateList.clear();
		m_pJsonTransitionList.clear();
		std::ifstream File;
		File.open(path);
		if (!File)
			return;
		reader.parse(File, root, false);

		const Json::Value state = root["FiniteStateMachine"]["State"];

		for (int index = 0; index < state.size(); ++index)  // Iterates over the sequence elements.
		{
			CStateInfo* StateInfo = new CStateInfo();
			StateInfo->SetStateDefault(state[index].get("StateDefault", "DefaultStateDefault").asString());
			StateInfo->SetStateName(state[index].get("StateName", "DefaultStateName").asString());
			StateInfo->SetStateTrigger(state[index].get("StateTrigger", "DefaultStateTrigger").asString());
			StateInfo->SetStateFunction(state[index].get("StateFunction", "DefaultStateFunction").asString());

			StateInfo->SetX(atof(state[index].get("X", "0.0").asString().c_str()));

			StateInfo->SetY(atof(state[index].get("Y", "0.0").asString().c_str()));
			const Json::Value fields = state[index]["Fields"];

			for (int index = 0; index < fields.size(); ++index)  // Iterates over the sequence elements.
			{
				if (fields[index].get("FieldName", "DefaultFieldName").asString() == "ID")
				{
					StateInfo->SetStateID(fields[index].get("Value","DefaultStateID").asString());
				}
				else
				{
					CStateField* field = new CStateField(fields[index]);
					StateInfo->GetStateFields().push_back(field);
				}
			}

			m_pJsonStateList.push_back(StateInfo);
		}

		const Json::Value condition = root["FiniteStateMachine"]["Condition"];
		for (int index = 0; index < condition.size(); ++index)  // Iterates over the sequence elements.
		{
			CTransitionInfo* TransitionInfo = new CTransitionInfo();
			TransitionInfo->SetStateIDFrom(condition[index].get("StateIDFrom", "DefaultStateIDFrom").asString());
			TransitionInfo->SetStateIDTo(condition[index].get("StateIDTo", "DefaultStateIDTo").asString());
			TransitionInfo->SetCondition(condition[index].get("ConditionValue", "DefaultConditionValue").asString());

			TransitionInfo->SetByteCode(condition[index].get("ByteCode","DefaultByteCode").asString());
			m_pJsonTransitionList.push_back(TransitionInfo);
		}

	}
	catch (std::string msg)
	{
		m_pJsonStateList.clear();
		m_pJsonTransitionList.clear();
		throw msg;
	}
}

CJsonStateTransitionInfo* CJsonStateTransitionInfo::LoadFromResource(std::string resourcePath)
{
	if (resourcePath != "")
	{
		CJsonStateTransitionInfo* ins = new CJsonStateTransitionInfo();
		ins->Load(resourcePath);
		m_pInstanceDatabase[resourcePath] = ins;
		return ins;
	}
	return nullptr;
}

CJsonStateTransitionInfo::~CJsonStateTransitionInfo()
{

}