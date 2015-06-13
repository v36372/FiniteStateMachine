#include "CStateField.h"

CStateField::CStateField(Json::Value Field)
{
	if (Field.size() == 0)
	{
		Name = "";
		Value = "";
		return;
	}
	Name = Field.get("FieldName","DefaultFieldName").asString();
	Value = Field.get("Value", "DefaultFieldValue").asString();
	for (int i = 0; i < Field["Macro"].size();i++)
	{
		Macro.push_back(Field["Macro"][i].asString());
	}
}

CStateField::~CStateField()
{

}