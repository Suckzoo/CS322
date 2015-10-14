#include "State.hpp"
#ifdef __AUTOMATA__
#include "func.hpp"
#include "Machine.hpp"
#include <functional>
using namespace std;


/* Your langset goes here
* Usage: Just save your langset to variable 'lang'.
*/

void Machine::GenerateLanguageSet()
{
	wstring lang = L"오리궁뎅이토마토타르트"; //You can define your own language set Σ
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

	//State goes here
	CreateState(L"오");
	CreateState(L"토");
	CreateState(L"마");
	CreateState(L"타");
	m_pLabelToState[L"타"].get()->setFinal();

	//Connection goes here
	//test case: (오+)토마타
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"오"].get(), [](wchar_t x) {return x == L'오'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"오"].get(), m_pLabelToState[L"오"].get(), [](wchar_t x) {return x == L'오'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"오"].get(), m_pLabelToState[L"토"].get(), [](wchar_t x) {return x == L'토'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"토"].get(), m_pLabelToState[L"마"].get(), [](wchar_t x) {return x == L'마'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"마"].get(), m_pLabelToState[L"타"].get(), [](wchar_t x) {return x == L'타'; }, DO_NOTHING);
}
#endif