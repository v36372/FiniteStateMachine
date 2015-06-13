#include "InterfaceFSM.h"

InterfaceFSM::InterfaceFSM()
{
	
}

void InterfaceFSM::Start()
{
	typedef Delegate<double, std::string> TestDelegate;
	m_Exe->FunctionEvalHandler = TestDelegate::from_function<InterfaceFSM, &InterfaceFSM::EvaluateFunction>(this);
	m_Exe->VariableEvalHandler = TestDelegate::from_function<InterfaceFSM, &InterfaceFSM::EvaluateVariable>(this);

	//Create and load FSM
	//  For any logic change please modify Resource/colorchange.graphml
	//  Resource/colorchange.grapml will be compile to colorchange.txt by Unity Editor
	//  Noted: Sometime UnityEditor don't auto recompile please import it manualy
	//m_pFSMSystem = new CFSMSystem(this, this);
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