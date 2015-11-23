#include "State.hpp"
#ifdef __CLAIM__
#include "func.hpp"
#include "Machine.hpp"
#include <functional>
using namespace std;


/* Your langset goes here
 * Usage: Just save your langset to variable 'lang'.
 */

void Machine::GenerateLanguageSet()
{
	wstring lang = L"ab"; //You can define your own language set 
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

	/* Example: Apple Grammar
	 * This example shows simple DFA which allow L"apple" only.
	 * init->a->ap->app->appl->apple / otherwise: dead
	 */

	//States goes here
	CreateState(L"q1");
	CreateState(L"q2");
	m_pLabelToState[L"q2"].get()->setFinal();
	
	//Connection goes here
	//with lambda
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"q1"].get(), [](wchar_t x) {return x == L'a'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"q2"].get(), [](wchar_t x) {return x == L'b'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"q1"].get(), m_pLabelToState[L"q2"].get(), [](wchar_t x) {return x == L'b'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"q2"].get(), m_pLabelToState[L"q1"].get(), [](wchar_t x) {return x == L'a'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"q2"].get(), m_pLabelToState[L"q2"].get(), [](wchar_t x) {return x == L'b'; }, DO_NOTHING);
}
#endif