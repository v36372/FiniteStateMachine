#include "stdafx.h"
#include "InterfaceFSM.h"
#include "IView.h"
#include <sstream>

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
	if(!m_pFSMSystem->IsEventInQueue(name))
		m_pFSMSystem->RaiseEvent(name);
}

void InterfaceFSM::SetPath(std::string newPath)
{
//-------------------Code that only runs on windows-----------------------//
//#ifdef Win32
	m_pPath = newPath;
	std::stringstream stream;
	stream << "FSMGraphParser.exe " << m_pPath.substr(0,m_pPath.length()-3) + "graphml";
	system(stream.str().c_str());
//#endif
//-------------------Code that only runs on windows-----------------------//
}

InterfaceFSM::~InterfaceFSM()
{
	delete m_Exe;
	delete m_pFSMSystem;
}
