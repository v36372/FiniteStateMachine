#pragma once
#include "CStateInfo.h"

class INotification
{
public:
	INotification();

	virtual void DoEnter(CStateInfo*&,CStateInfo*&)=0;
	virtual void DoExit(CStateInfo*&)=0;
	virtual void DoBeginEvent()=0;
	virtual void DoEndEvent()=0;
	virtual void DoUpdate(CStateInfo*&, float)=0;
	virtual void DoExecuteFunction(CStateInfo*&, float)=0;

	~INotification();
};