#include "Machine.hpp"
#include <functional>
using namespace std;

void Machine::ConnectState(State* s1, State* s2, function<bool(wchar_t)> checker)
{
	Edge* edge = new Edge();
	edge->m_NextState = shared_ptr<State>(s2);
	edge->m_CheckFunction = checker;
	s1->m_Edge.push_back(edge);
}
void Machine::CreateState(wstring label, bool isFinal = false)
{
	State* state = new State();
	state->setLabel(label);
	if (isFinal) state->setFinal();
	m_pLabelToState[label] = shared_ptr<State>(state);
}

/* Your langset goes here
 * Usage: Just save your langset to variable 'lang'.
 */

//You can choose test case set
//APPLE DFA test-case
//#define __APPLE__
//AUTOMATA DFA test-case
#define __AUTOMATA__

void Machine::GenerateLanguageSet()
{
#ifdef __APPLE__
	wstring lang = L"abcdefpl"; //You can define your own language set 
#endif
#ifdef __AUTOMATA__
	wstring lang = L"오리궁뎅이토마토타르트"; //You can define your own language set Σ
#endif
	int i;
	for (i = 0; i < lang.length(); i++)
	{
		m_pLanguageSet.insert(lang[i]);
	}
}
/* Your grammar goes here
 * Usage:
 * Make state with label
 * Connect them with ConnectState function
 * Each edge needs checker function: callable object(function, lambda, ...)
 * Each state can hold StateFunction: callable object(function, lambda, ...)
 * You can
 */
void Machine::CreateStateEdge()
{
	//Create essential state
	CreateState(L"initial");
	CreateState(L"dead");
	m_pCurrentState = getStateByLabel(L"initial");
	m_pInitialState = getStateByLabel(L"initial");
	m_pDeadState = getStateByLabel(L"dead");

#ifdef __APPLE__
	/* Example: Apple Grammar
	 * This example shows simple DFA which allow L"apple" only.
	 * init->a->ap->app->appl->apple / otherwise: dead
	 */

	//States goes here
	CreateState(L"a");
	CreateState(L"ap");
	CreateState(L"app");
	CreateState(L"appl");
	CreateState(L"apple");
	m_pLabelToState[L"apple"].get()->setFinal();
	
	//Connection goes here
	//with lambda
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"a"].get(), [](wchar_t x) {return x == L'a'; });
	ConnectState(m_pLabelToState[L"a"].get(), m_pLabelToState[L"ap"].get(), [](wchar_t x) {return x == L'p'; });
	ConnectState(m_pLabelToState[L"ap"].get(), m_pLabelToState[L"app"].get(), [](wchar_t x) {return x == L'p'; });
	ConnectState(m_pLabelToState[L"app"].get(), m_pLabelToState[L"appl"].get(), [](wchar_t x) {return x == L'l'; });
	ConnectState(m_pLabelToState[L"appl"].get(), m_pLabelToState[L"apple"].get(), [](wchar_t x) {return x == L'e'; });
#endif

#ifdef __AUTOMATA__
	//State goes here
	CreateState(L"오");
	CreateState(L"토");
	CreateState(L"마");
	CreateState(L"타");
	m_pLabelToState[L"타"].get()->setFinal();

	//Connection goes here
	//test case: (오+)토마타
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"오"].get(), [](wchar_t x) {return x == L'오'; });
	ConnectState(m_pLabelToState[L"오"].get(), m_pLabelToState[L"오"].get(), [](wchar_t x) {return x == L'오'; });
	ConnectState(m_pLabelToState[L"오"].get(), m_pLabelToState[L"토"].get(), [](wchar_t x) {return x == L'토'; });
	ConnectState(m_pLabelToState[L"토"].get(), m_pLabelToState[L"마"].get(), [](wchar_t x) {return x == L'마'; });
	ConnectState(m_pLabelToState[L"마"].get(), m_pLabelToState[L"타"].get(), [](wchar_t x) {return x == L'타'; });
#endif
}
