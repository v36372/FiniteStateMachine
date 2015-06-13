#pragma once
#include <vector>
#include <map>
#include "CStateInfo.h"
#include "CTransitionInfo.h"

class CJsonStateTransitionInfo
{
public:
	CJsonStateTransitionInfo();
	CJsonStateTransitionInfo(std::string content);

	std::vector<CStateInfo*> m_pJsonStateList;
	std::vector<CTransitionInfo*> m_pJsonTransitionList;
	void Load(std::string data);
	void Parse(std::string content);
	static CJsonStateTransitionInfo* LoadFromResource(std::string resourcePath);

	~CJsonStateTransitionInfo();
private:
	static std::map<std::string, CJsonStateTransitionInfo*> m_pInstanceDatabase;
};