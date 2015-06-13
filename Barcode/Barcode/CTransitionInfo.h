#pragma once
#include <string>
#include <vector>
#include "Command.h"

class CTransitionInfo
{
public:
	CTransitionInfo();

	~CTransitionInfo();
private:
	std::string m_sStateIDFrom;
	std::string m_sStateIDTo;
	std::string m_sCondition;
	std::string m_sUniqueKey;
	std::string m_sByteCode;

	std::vector<JFSM::Command*> m_pCompiledByteCode;
public:
	std::string GetStateIDFrom()
	{
		return m_sStateIDFrom;
	}

	void SetStateIDFrom(std::string StateIDFrom)
	{
		m_sStateIDFrom = StateIDFrom;
	}

	std::string GetStateIDTo()
	{
		return m_sStateIDTo;
	}

	void SetStateIDTo(std::string StateIDTo)
	{
		m_sStateIDTo = StateIDTo;
	}

	std::string GetCondition()
	{
		return m_sCondition;
	}

	void SetCondition(std::string Condition)
	{
		m_sCondition = Condition;
	}

	std::string GetUniqueKey()
	{
		return m_sUniqueKey;
	}

	void SetUniqueKey(std::string UniqueKey)
	{
		m_sUniqueKey = UniqueKey;
	}

	std::string GetByteCode()
	{
		return m_sByteCode;
	}

	void SetByteCode(std::string ByteCode)
	{
		m_sByteCode = ByteCode;
	}

	std::vector<JFSM::Command*> GetCompiledByteCode()
	{
		return m_pCompiledByteCode;
	}

	void SetCompiledByteCode(std::vector<JFSM::Command*> CompiledByteCode)
	{
		m_pCompiledByteCode.clear();
		m_pCompiledByteCode = CompiledByteCode;
	}
};