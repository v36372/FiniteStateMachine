#include "CFSMSystem.h"

CFSMSystem::CFSMSystem(INotification* Notify, IContext* Context)
{
	SetContext(Notify, Context);
	EnableTransitionCheck = true;
	EnableEvent = true;

	m_CurrentStateIndex = 0;
	m_LastStateIndex = 0;
	m_pCurrentStateInfo = NULL;
	m_pPreviousStateInfo = NULL;
	m_pAnyState = NULL;
}

void CFSMSystem::SetContext(INotification* notify, IContext* context)
{
	m_pCurrentNotification = notify;
	m_pContext = context;
}

void CFSMSystem::SetDefaultStateInfo()
{
	CStateInfo* StateInfo;
	for (int i = 0; i < m_zpStateList.size(); i++)
	{
		StateInfo = m_zpStateList[i];
		if (StateInfo->GetStateName() == "AnyState")
		{
			m_pAnyState = StateInfo;
			m_zpAnyStateTransition.clear();
		}
		else
		if (StateInfo->GetStateDefault() == "True")
		{
			m_pCurrentStateInfo = StateInfo;
			m_CurrentStateIndex = i;
			m_LastStateIndex = i;
		}
	}

	if (!m_pCurrentStateInfo)
	{
		return;
	}

	for each (CTransitionInfo* TransitionInfo in m_zpTransitionList)
	{
		if (TransitionInfo->GetStateIDFrom() ==  m_pCurrentStateInfo->GetStateID())
		{
			m_zpCurrentTransitionInfo.push_back(TransitionInfo);
		}

		if (m_pAnyState && TransitionInfo->GetStateIDFrom() == m_pAnyState->GetStateID())
		{
			m_zpAnyStateTransition.push_back(TransitionInfo);
		}
	}
}

void CFSMSystem::SetNextStateInfo(CTransitionInfo* CurrentTransitionInfo)
{
	CStateInfo* StateInfo;
	for (int i = 0; i < m_zpStateList.size(); i++)
	{
		StateInfo = m_zpStateList[i];
		if (StateInfo->GetStateID() == CurrentTransitionInfo->GetStateIDTo())
		{
			m_pCurrentStateInfo = StateInfo;
			m_CurrentStateIndex = i;

			break;
		}
	}

	m_zpCurrentTransitionInfo.clear();
	CTransitionInfo* TransitionInfo;
	for (int i = 0; i < m_zpTransitionList.size(); i++)
	{
		TransitionInfo = m_zpTransitionList[i];
		if (TransitionInfo->GetStateIDFrom() ==  m_pCurrentStateInfo->GetStateID())
			m_zpCurrentTransitionInfo.push_back(TransitionInfo);
	}
}

void CFSMSystem::SetNextStateInfo(std::string ID)
{
	CStateInfo* StateInfo;
	for (int i = 0; i < m_zpStateList.size(); i++)
	{
		StateInfo = m_zpStateList[i];
		if (StateInfo->GetStateID() == ID)
		{
			m_pCurrentStateInfo = StateInfo;
			m_CurrentStateIndex = i;

			break;
		}
	}

	m_zpCurrentTransitionInfo.clear();
	CTransitionInfo* TransitionInfo;
	for (int i = 0; i < m_zpTransitionList.size(); i++)
	{
		TransitionInfo = m_zpTransitionList[i];
		if (TransitionInfo->GetStateIDFrom() == m_pCurrentStateInfo->GetStateID())
			m_zpCurrentTransitionInfo.push_back(TransitionInfo);
	}
}

void CFSMSystem::Load(std::string resourcePath)
{
	CJsonStateTransitionInfo* JsonStateTransitionInfo;
	JsonStateTransitionInfo = JsonStateTransitionInfo->LoadFromResource(resourcePath);

	m_zpStateList = JsonStateTransitionInfo->m_pJsonStateList;
	m_zpTransitionList = JsonStateTransitionInfo->m_pJsonTransitionList;

	m_zpCurrentTransitionInfo.clear();

	SetDefaultStateInfo();
	InitializeEvent();

	m_pPreviousStateInfo = NULL;

	if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
	{
		m_pCurrentNotification->DoEnter(m_pCurrentStateInfo, m_pPreviousStateInfo);
	}
}

bool CFSMSystem::HasEvent(std::string name)
{
	for (int i = 0; i < m_zpEventList.size(); i++)
	{
		if (m_zpEventList[i]->GetStateName() == name)
			return true;
	}
	return false;
}

void CFSMSystem::InitializeEvent()
{
	m_zpEventList.clear();
	for (int i = 0; i < m_zpStateList.size(); i++)
	{
		if (m_zpStateList[i]->GetStateTrigger() == "True")
		{
			m_zpEventList.push_back(m_zpStateList[i]);
		}
	}
}

CStateInfo* CFSMSystem::FindEventState(std::string name)
{
	for (int i = 0; i < m_zpStateList.size(); i++)
	{
		if (m_zpStateList[i]->GetStateName() == name)
			return m_zpStateList[i];
	}
	CStateInfo* cs;
	cs = NULL;
	return cs;
}

void CFSMSystem::BeginProcessingEvent(CStateInfo* state)
{
	m_pProcessingStack.push(m_pCurrentStateInfo);

	//Switch To Event State
	if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
	{
		m_pCurrentNotification->DoExit(m_pCurrentStateInfo);
		m_pPreviousStateInfo = m_pCurrentStateInfo;
	}
	//Debug.Log (" Processing Event " + state.StateName);
	SetNextStateInfo(state->GetStateID());

	// HHoang (optimize)
	if (m_pCurrentNotification != NULL)
	{
		if (m_pCurrentStateInfo != NULL)
			m_pCurrentNotification->DoEnter(m_pCurrentStateInfo, m_pPreviousStateInfo);
		m_pCurrentNotification->DoBeginEvent();
	}
}

void CFSMSystem::EndEventProcessing()
{
	CStateInfo* state = m_pProcessingStack.top();
	m_pProcessingStack.pop();

	//Switch To LastProcessing State
	if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
	{
		m_pCurrentNotification->DoExit(m_pCurrentStateInfo);
		m_pPreviousStateInfo = m_pCurrentStateInfo;
	}

	if (state == NULL)
	{
		m_pCurrentStateInfo = NULL;
		m_CurrentStateIndex = 0;
		m_zpCurrentTransitionInfo.clear();

		if (m_pCurrentNotification != NULL)
			m_pCurrentNotification->DoEndEvent();

		return;
	}

	SetNextStateInfo(state->GetStateID());

	// HHoang (optimize)
	if (m_pCurrentNotification != NULL)
	{
		if (m_pCurrentStateInfo != NULL)
			m_pCurrentNotification->DoEnter(m_pCurrentStateInfo, m_pPreviousStateInfo);
		m_pCurrentNotification->DoEndEvent();
	}
}

void CFSMSystem::UpdateEvent(float dt)
{
	if (!EnableEvent)
		return;

	//Still processing Event. Waiting
	if (m_pProcessingStack.size() != 0)
		return;

	if (m_pEventQueue.size() > 0)
	{
		std::string strEvent = m_pEventQueue.front();
		m_pEventQueue.pop();
		CStateInfo* state = FindEventState(strEvent);
		if (state != NULL)
		{
			BeginProcessingEvent(state);
		}
	}
}

void CFSMSystem::Update(float dt)
{
	//Update Event
	UpdateEvent(dt);

	//Update Default State

	if (m_pCurrentStateInfo == NULL)
		return;

	// HHoang (optimize)
	if (m_pCurrentNotification != NULL)
	{
		if (m_pCurrentStateInfo->GetStateFunction() == "False")
			m_pCurrentNotification->DoUpdate(m_pCurrentStateInfo, dt);
		else
			m_pCurrentNotification->DoExecuteFunction(m_pCurrentStateInfo, dt);
	}

	if (!EnableTransitionCheck)
		return;

	CTransitionInfo* TransitionInfo;

	//Update AnyState
	if (m_pAnyState != NULL)
	{
		for (int i = 0; i < m_zpAnyStateTransition.size(); i++)
		{
			TransitionInfo = m_zpAnyStateTransition[i];
			if (m_pContext->Eval(TransitionInfo))
			{
				if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
				{
					m_pCurrentNotification->DoExit(m_pCurrentStateInfo);
					m_pPreviousStateInfo = m_pCurrentStateInfo;
				}

				SetNextStateInfo(TransitionInfo);

				if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
				{
					m_pCurrentNotification->DoEnter(m_pCurrentStateInfo, m_pPreviousStateInfo);
				}
				return;
			}
		}
	}

	// Check State has no exit path
	if (m_zpCurrentTransitionInfo.size() == 0)
	{
		if (m_pProcessingStack.size() > 0)
		{
			EndEventProcessing();
		}
	}
	else
	{
		// Update Normal State
		for (int i = 0; i < m_zpCurrentTransitionInfo.size(); i++)
		{
			TransitionInfo = m_zpCurrentTransitionInfo[i];
			if (m_pContext->Eval(TransitionInfo))
			{
				if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
				{
					m_pCurrentNotification->DoExit(m_pCurrentStateInfo);
					m_pPreviousStateInfo = m_pCurrentStateInfo;
				}

				SetNextStateInfo(TransitionInfo);

				if (m_pCurrentNotification != NULL && m_pCurrentStateInfo != NULL)
				{
					m_pCurrentNotification->DoEnter(m_pCurrentStateInfo, m_pPreviousStateInfo);
				}
				break;
			}
		}
	}
}

CFSMSystem::~CFSMSystem()
{
	for (int i = 0; i < m_zpStateList.size(); i++)
	{
		if (m_zpStateList[i])
			delete m_zpStateList[i];
	}

	for (int i = 0; i < m_zpTransitionList.size(); i++)
	{
		if (m_zpTransitionList[i])
			delete m_zpTransitionList[i];
	}
}