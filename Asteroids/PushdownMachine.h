#pragma once
#include <stack>

class PushdownState;

class PushdownMachine
{
public:
	PushdownMachine(PushdownState* initialState);
	~PushdownMachine();

	bool Update(float dt);
	void Draw();

protected:
	PushdownState* m_ActiveState;
	PushdownState* m_InitialState;

	std::stack<PushdownState*> m_StateStack;
};

