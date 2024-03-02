#include "PushdownMachine.h"
#include "PushdownState.h"

PushdownMachine::PushdownMachine(PushdownState* initialState)
{
	m_ActiveState = nullptr;
	m_InitialState = initialState;
}

PushdownMachine::~PushdownMachine()
{
}

bool PushdownMachine::Update(float dt) 
{
	if (m_ActiveState) 
	{
		PushdownState* newState = nullptr;
		PushdownState::PushdownResult result = m_ActiveState->OnUpdate(dt, &newState);

		switch (result) 
		{
			case PushdownState::PR_Pop: 
			{
				m_ActiveState->OnSleep();
				delete m_ActiveState;

				m_StateStack.pop();
				
				if (m_StateStack.empty())
					return false;
				else 
				{
					m_ActiveState = m_StateStack.top();
					m_ActiveState->OnAwake();
				}					
			}
			break;

			case PushdownState::PR_Push: 
			{
				m_ActiveState->OnSleep();		

				m_StateStack.push(newState);
				m_ActiveState = newState;
				m_ActiveState->OnAwake();
			}
			break;
		}
	}
	else 
	{
		m_StateStack.push(m_InitialState);
		m_ActiveState = m_InitialState;
		m_ActiveState->OnAwake();
	}

	return true;
}