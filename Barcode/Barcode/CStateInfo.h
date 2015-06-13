#pragma once
#include <string>
#include <vector>
#include "CStateField.h"

//void replaceAll(std::string& str, const std::string& from, const std::string& to);

class  CStateInfo
{
public:
	CStateInfo();

	~CStateInfo();
private:
	std::string m_bStateDefault;
	std::string m_bStateTrigger;
	std::string m_bStateFunction;
	std::string m_bStateName;
	std::string m_bStateID;
	float m_X;
	float m_Y;

	std::vector<CStateField*> m_pFields;	//
public:

	std::string GetStateDefault()
	{
		return m_bStateDefault;
	}

	void SetStateDefault(std::string StateDefault)
	{
		m_bStateDefault = StateDefault;
	}

	std::string GetStateTrigger()
	{
		return m_bStateTrigger;
	}

	void SetStateTrigger(std::string StateTrigger)
	{
		m_bStateTrigger = StateTrigger;
	}

	std::string GetStateFunction()
	{
		return m_bStateFunction;
	}

	void SetStateFunction(std::string StateFunction)
	{
		m_bStateFunction = StateFunction;
	}

	std::string GetStateName()
	{
		return m_bStateName;
	}

	void SetStateName(std::string StateName)
	{
		m_bStateName = StateName;
	}

	std::string GetStateID()
	{
		return m_bStateID;
	}

	void SetStateID(std::string StateID)
	{
		m_bStateID = StateID;
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

	void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}

	void GetFunctionParam(std::map<std::string, std::string> param, std::map<std::string, std::string> macro)
	{
		param.clear();
		CStateField* tmp;
		for (int i = 0; i < m_pFields.size(); i++)
		{
			tmp = m_pFields[i];
			std::string key = tmp->GetName();
			std::string value = tmp->GetValue();

			//Expand Macro
			if (macro.size() > 0 && tmp->Getmacro().size() > 0)
			{
				for (int j = 0; j < tmp->Getmacro().size(); j++)
				{
					std::string macroKey = tmp->Getmacro()[j];
					if (macro.find(macroKey)._Ptr)
					{
						//value = value.Replace(macroKey, macro[macroKey]);
						replaceAll(value, macroKey, macro[macroKey]);
					}
				}
			}
			param[key] = value;
		}
	}
};