#pragma once
#include <string>
#include <vector>
#include "CStateField.h"
#include "ExpressionExecution.h"

//void replaceAll(std::string& str, const std::string& from, const std::string& to);

class  CStateInfo
{
public:
	CStateInfo();

	~CStateInfo();
private:
	bool m_bStateDefault;
	bool m_bStateTrigger;
	bool m_bStateFunction;
	std::string m_sStateName;
	int m_iStateID;
	float m_X;
	float m_Y;

	std::vector<CStateField*> m_pFields;	//
public:

	bool GetStateDefault()
	{
		return m_bStateDefault;
	}

	void SetStateDefault(std::string StateDefault)
	{
		if(StateDefault == "True")
			m_bStateDefault = true;
		else
			m_bStateDefault = false;
	}

	bool GetStateTrigger()
	{
		return m_bStateTrigger;
	}

	void SetStateTrigger(std::string StateTrigger)
	{
		if(StateTrigger == "True")
			m_bStateTrigger = true;
		else
			m_bStateTrigger = false;
	}

	bool GetStateFunction()
	{
		return m_bStateFunction;
	}

	void SetStateFunction(std::string StateFunction)
	{
		if(StateFunction == "True")
			m_bStateFunction = true;
		else
			m_bStateFunction = false;
	}

	std::string GetStateName()
	{
		return m_sStateName;
	}

	void SetStateName(std::string StateName)
	{
		m_sStateName = StateName;
	}

	int GetStateID()
	{
		return m_iStateID;
	}

	void SetStateID(std::string StateID)
	{
		m_iStateID = atoi(StateID.c_str());
	}

	float GetX()
	{
		return m_X;
	}

	void SetX(float X)
	{
		m_X = X;
	}

	float GetY()
	{
		return m_Y;
	}

	void SetY(float Y)
	{
		m_Y = Y;
	}

	std::vector<CStateField*> GetStateFields()
	{
		return m_pFields;
	}

	void PushStateField(CStateField*& newField)
	{
		m_pFields.push_back(newField);
	}

	void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}

	std::vector<param> GetFunctionParam()
	{
		std::vector<param> ParamList;
		CStateField* tmp;
		for (int i = 0; i < m_pFields.size(); i++)
		{
			tmp = m_pFields[i];
			param p;
			p.type = paramType::String;
			p.sParam = tmp->GetValue();
			ParamList.push_back(p);
		}
		return ParamList;
	}
};