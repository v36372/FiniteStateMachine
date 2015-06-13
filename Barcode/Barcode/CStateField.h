#pragma once
#include <string>
#include <vector>
#include "json/json.h"

class CStateField
{
public:
	CStateField(Json::Value Field);

	std::string GetName()
	{
		return Name;
	}

	std::string GetValue()
	{
		return Value;
	}
	
	std::vector<std::string> Getmacro()
	{
		return Macro;
	}

	void SetName(std::string name)
	{
		Name = name;
	}

	void SetValue(std::string value)
	{
		Value = value;
	}

	void Setmacro(std::vector<std::string> macro)
	{
		Macro = macro;
	}

	~CStateField();
private:
	std::string Name;
	std::string Value;
	std::vector<std::string> Macro;
};