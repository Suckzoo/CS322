#include "Machine.hpp"
#define MAX_LANGUAGE 200

State::State()
{
	m_isFinalState = false;
}

void State::setFinal()
{
	m_isFinalState = true;
}

void State::setLabel(wstring label)
{
	m_Label = label;
}

bool State::isFinal()
{
	return m_isFinalState;
}

State::operator std::wstring() const
{
	return m_Label;
}

Machine::Machine()
{
	GenerateLanguageSet();
	CreateStateEdge();
}

void Machine::StateTransition(wchar_t x)
{
	for (auto edge = m_pCurrentState.get()->m_Edge.begin();
		edge != m_pCurrentState.get()->m_Edge.end();
		edge++)
	{
		if ((*edge)->m_CheckFunction(x))
		{
			m_pCurrentState = (*edge)->m_NextState;
			//m_pCurrentState->m_StateFunction();
			return;
		}
	}
	m_pCurrentState = m_pDeadState;
}

bool Machine::isFinalState()
{
	return m_pCurrentState.get()->isFinal();
}

bool Machine::isDeadState()
{
	return m_pCurrentState.get() == m_pDeadState.get();
}

shared_ptr<State> Machine::getStateByLabel(wstring label)
{
	return m_pLabelToState[label];
}

bool Machine::isValidPattern(wstring pattern)
{
	int i;
	for (i = 0; i < pattern.length(); i++)
	{
		if (m_pLanguageSet.find(pattern[i]) == m_pLanguageSet.end())
		{
			return false;
		}
	}
	return true;
}
