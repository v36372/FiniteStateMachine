#pragma once
#include "IContext.h"
#include "INotification.h"
#include "CFSMSystem.h"
#include "ExpressionExecution.h"
#include <Windows.h>
#include <iostream>

class InterfaceFSM : public INotification, public IContext
{
public:
	InterfaceFSM();

	//------------------------------------Flow methods-------------------------------------------//

	virtual void Start();
	virtual void Update(float dt);
	
	//--------------------------------Basic Behavior------------------------------ Needed to be Overrided-----------------//

	virtual void DoEnter(CStateInfo* stateInfo, CStateInfo* previousStateInfo)=0;
	virtual void DoUpdate(CStateInfo* stateInfo, float dt)=0;
	virtual void DoExecuteFunction(CStateInfo* stateInfo, float dt)=0;
	virtual void DoExit(CStateInfo* stateInfo)=0;
	virtual void DoBeginEvent()=0;
	virtual void DoEndEvent()=0;
	virtual void RaiseEvent(std::string name);

	//---------------------------------Evaluate Expression ------------------------- Needed to be Overrided---------------------//

	virtual double EvaluateFunction(std::string name,std::vector<param> paramList)=0;
	virtual double EvaluateVariable(std::string name,std::vector<param> paramList)=0;
	virtual bool Eval(CTransitionInfo*)=0;

	~InterfaceFSM();

protected:
	//-------------------------------------Main Properties------------------------------------------//

	std::string m_pPath;
	CFSMSystem* m_pFSMSystem;
	JFSM::ExpressionExecution* m_Exe;

	//----------------------------------Store Event Function Parameters---------------------------------------------//

	std::map<std::string, std::string> m_pParam;
	std::map<std::string, std::string> m_pMacro;

	//-----------------------------------Function Mapping--------------------------------------------//

	virtual void RegisterFunction() = 0;
};
