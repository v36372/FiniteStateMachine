#include "InterfaceFSM.h"

InterfaceFSM::InterfaceFSM()
{
	
}

void InterfaceFSM::Start()
{
	typedef Delegate<double, std::string,std::vector<param>> TestDelegate;
	m_Exe->FunctionEvalHandler = TestDelegate::from_function<InterfaceFSM, &InterfaceFSM::EvaluateFunction>(this);
	m_Exe->VariableEvalHandler = TestDelegate::from_function<InterfaceFSM, &InterfaceFSM::EvaluateVariable>(this);

	m_pFSMSystem->Load(m_pPath);
}

void InterfaceFSM::Update(float dt)
{
	m_pFSMSystem->Update(dt);
}

void InterfaceFSM::RaiseEvent(std::string name)
{
	m_pFSMSystem->RaiseEvent(name);
}


InterfaceFSM::~InterfaceFSM()
{

}