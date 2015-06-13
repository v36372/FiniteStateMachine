#pragma once
#include "CStateInfo.h"

class INotification
{
public:
	INotification();

	virtual void DoEnter(CStateInfo*,CStateInfo*);
	virtual void DoExit(CStateInfo*);
	virtual void DoBeginEvent();
	virtual void DoEndEvent();
	virtual void DoUpdate(CStateInfo*, float);
	virtual void DoExecuteFunction(CStateInfo*, float);

	~INotification();
};