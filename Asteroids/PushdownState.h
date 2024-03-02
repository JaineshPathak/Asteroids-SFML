#pragma once

class PushdownState
{
public:
	enum PushdownResult 
	{
		PR_Push, 
		PR_Pop, 
		PR_NoChange
	};

	PushdownState() {}
	virtual ~PushdownState() {}

	virtual PushdownResult OnUpdate(float dt, PushdownState** pushFunc) = 0;
	virtual void OnAwake() {}
	virtual void OnSleep() {}
};