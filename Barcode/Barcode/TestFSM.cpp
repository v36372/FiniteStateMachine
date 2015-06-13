#include "TestFSM.h"

TestFSM::TestFSM(std::string path)
{
	RegisterFunction();

	m_Exe = new JFSM::ExpressionExecution();

	m_pFSMSystem = new CFSMSystem(this, this);

	m_pPath = path;
}

double TestFSM::EvaluateFunction(std::string name)
{
	if ((this->*m_pFunctionMap[name])())
		return 1.0;
	else
		return 0.0;
}

double TestFSM::EvaluateVariable(std::string name)
{
	if (name == "True")
		return 1.0;
	else
		return 0.0;
}

bool TestFSM::Eval(CTransitionInfo* trans)
{
	//Compile Expression if needed. compiled expression will be cached in order to fast access next time
	if (trans->GetCompiledByteCode().size() == 0)
	{
		m_Exe->LoadExpression(trans->GetByteCode());
		trans->SetCompiledByteCode(m_Exe->GetCompileData());
	}
	else
	{
		m_Exe->LoadExpression(trans->GetCompiledByteCode());
	}

	m_Exe->Eval();

	return m_Exe->Result == 1.0;
}

void TestFSM::DoEnter(CStateInfo* stateInfo, CStateInfo* previousStateInfo)
{
	if (stateInfo->GetStateName() == "Idle")
	{
		std::cout << "Dang o state idle ne`" << std::endl;
	}
	else if (stateInfo->GetStateName() == "Green")
	{
		std::cout << "Dang o state green ne`" << std::endl;
	}
	else if (stateInfo->GetStateName() == "Red")
	{
		std::cout << "Dang o state red ne` hihi" << std::endl;
	}
}

void TestFSM::RegisterFunction()
{
	m_pFunctionMap["KeyUpPress"] = &TestFSM::KeyUpPress;
	m_pFunctionMap["KeyDownPress"] = &TestFSM::KeyDownPress;
	m_pFunctionMap["KeyLeftPress"] = &TestFSM::KeyLeftPress;
	m_pFunctionMap["KeyRightPress"] = &TestFSM::KeyRightPress;
	m_pFunctionMap["IsRedState"] = &TestFSM::IsRedState;
	m_pFunctionMap["FuncExecuteEvent"] = &TestFSM::FuncExecuteEvent;
}

void TestFSM::DoUpdate(CStateInfo* stateInfo, float dt)
{
	
}

void TestFSM::DoExit(CStateInfo* stateInfo)
{
	
}

void TestFSM::DoExecuteFunction(CStateInfo* stateInfo,float dt)
{
	stateInfo->GetFunctionParam(m_pParam, m_pMacro);
	if (m_pFunctionMap[stateInfo->GetStateName()] != nullptr)
		(this->*m_pFunctionMap[stateInfo->GetStateName()])();
}

void TestFSM::DoBeginEvent()
{
	std::cout << "Bat dau` EVENT ne` cac ban oi !!" << std::endl;
}

void TestFSM::DoEndEvent()
{
	std::cout << "Ket' thuc' EVENT ne` cac ban oi !!" << std::endl;
}

bool TestFSM::FuncExecuteEvent()
{
	std::cout << "FuncExecuteEvent ne`" << std::endl;
	return true;
}

TestFSM::~TestFSM()
{
	delete m_Exe;
	delete m_pFSMSystem;
}