#pragma once
#include "IContext.h"
#include "INotification.h"
#include "CFSMSystem.h"
#include "ExpressionExecution.h"
#include "InterfaceFSM.h"
#include <Windows.h>
#include <iostream>

class TestFSM : public InterfaceFSM
{
public:
	TestFSM(std::string path);

	//-----------------------------------Basic behavior--------------------------------------------//

	virtual void DoEnter(CStateInfo* stateInfo, CStateInfo* previousStateInfo) override;
	virtual void DoUpdate(CStateInfo* stateInfo, float dt) override;
	virtual void DoExecuteFunction(CStateInfo* stateInfo, float dt) override;
	virtual void DoExit(CStateInfo* stateInfo) override;
	virtual void DoBeginEvent() override;
	virtual void DoEndEvent() override;

	//-----------------------------------Evaluate expression--------------------------------------------//

	virtual double EvaluateFunction(std::string name) override;
	virtual double EvaluateVariable(std::string name) override;
	virtual bool Eval(CTransitionInfo*) override;

	~TestFSM();
protected:
	//-----------------------------------Function Mapping--------------------------------------------//
	typedef bool (TestFSM::*condition)();
	std::map<std::string, condition> m_pFunctionMap;

	//-----------------------------------Logic condition for state transition--------------------------------------------//

	inline bool IsRedState()
	{
		return this->m_pFSMSystem->GetCurrentState()->GetStateName() == "Red";
	}

	inline bool KeyUpPress()
	{
		return ((unsigned short)GetKeyState(VK_UP) >> 15) == 1;
	}

	inline bool KeyDownPress()
	{
		return ((unsigned short)GetKeyState(VK_DOWN) >> 15) == 1;
	}

	inline bool KeyLeftPress()
	{
		return ((unsigned short)GetKeyState(VK_LEFT) >> 15) == 1;
	}

	inline bool KeyRightPress()
	{
		return ((unsigned short)GetKeyState(VK_RIGHT) >> 15) == 1;
	}

	//----------------------------------Mapping Functoin---------------------------------------------//

	virtual void RegisterFunction() override;
private:
	//----------------------------------Event Function---------------------------------------------//

	bool FuncExecuteEvent();
};
