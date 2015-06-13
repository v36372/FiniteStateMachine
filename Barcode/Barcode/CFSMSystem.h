#pragma once
#include "IContext.h"
#include "INotification.h"
#include "CStateInfo.h"
#include "CTransitionInfo.h"
#include "CJsonStateTransitionInfo.h"
#include <list>
#include <stack>
#include <queue>
#include <vector>

class CFSMSystem
{
public:
	CFSMSystem(INotification*, IContext*);

	~CFSMSystem();
private:
	INotification* m_pCurrentNotification;
	IContext* m_pContext;
	std::vector<CStateInfo*> m_zpStateList;
	std::vector<CTransitionInfo*> m_zpTransitionList;
	CStateInfo* m_pCurrentStateInfo, *m_pPreviousStateInfo;
	std::vector<CTransitionInfo*> m_zpCurrentTransitionInfo;
	int m_CurrentStateIndex, m_LastStateIndex;

	//Event
	std::vector<CStateInfo*> m_zpEventList;
	std::stack<CStateInfo*> m_pProcessingStack;                         //
	std::queue<std::string> m_pEventQueue;							//

	//Any State
	CStateInfo* m_pAnyState;
	std::vector<CTransitionInfo*> m_zpAnyStateTransition;
	std::string m_Prefix;

public:
	bool EnableTransitionCheck;
	bool EnableEvent;


	INotification* CurrentState()
	{
		return m_pCurrentNotification;
	}

	IContext* Context()
	{
		return m_pContext;
	}

	std::vector<CStateInfo*> GetStateList()
	{
		return m_zpStateList;
	}

	std::vector<CTransitionInfo*> GetTransitionList()
	{
		return m_zpTransitionList;
	}

	CStateInfo*& GetCurrentState()
	{
		return m_pCurrentStateInfo;
	}

	int GetCurrentStateIndex()
	{
		return m_CurrentStateIndex;
	}

	void SetCurrentStateIndex(int StateIndex)
	{
		m_CurrentStateIndex = StateIndex;
	}

	int GetLastStateIndex()
	{
		return m_LastStateIndex;
	}

	void SetLastStateIndex(int StateIndex)
	{
		m_LastStateIndex = StateIndex;
	}

	void SetContext(INotification*,IContext*);
	void SetDefaultStateInfo();
	void SetNextStateInfo(CTransitionInfo* CurrentTransitionInfo);
	void SetNextStateInfo(std::string ID);
	
	void RaiseEvent(std::string eventName)
	{
		m_pEventQueue.push(eventName);
	}

	bool IsEventProcessing()
	{
		return m_pEventQueue.size() > 0;
	}

	void Load(std::string resourcePath);

	void InitializeEvent();

	bool HasEvent(std::string EventName);

	CStateInfo* FindEventState(std::string name);

	void BeginProcessingEvent(CStateInfo* state);

	void EndEventProcessing();
	void UpdateEvent(float dt);
	void Update(float dt);
};