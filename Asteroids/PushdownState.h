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

	virtual PushdownResult OnUpdate(float DeltaTime, PushdownState** newState) = 0;
	virtual void OnDraw() {}
	virtual void OnAwake() {}
	virtual void OnSleep() {}
};