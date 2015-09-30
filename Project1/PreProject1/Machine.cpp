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
			(*edge)->m_TransitFunction(&this->m_pMachineResult, x); //필요하다면 두 번째 argument를 적극 활용할 것.
			m_pCurrentState = (*edge)->m_NextState;
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

void Machine::ConnectState(State* s1, State* s2, function<bool(wchar_t)> checker, function<void(wstring*, wchar_t)> transit)
{
	Edge* edge = new Edge();
	edge->m_NextState = shared_ptr<State>(s2);
	edge->m_CheckFunction = checker;
	edge->m_TransitFunction = transit;
	s1->m_Edge.push_back(edge);
}

void Machine::CreateState(wstring label, bool isFinal)
{
	State* state = new State();
	state->setLabel(label);
	if (isFinal) state->setFinal();
	m_pLabelToState[label] = shared_ptr<State>(state);
}

void Machine::PrintMachineResult()
{
	wprintf(L"%ls\n", m_pMachineResult.c_str());
}