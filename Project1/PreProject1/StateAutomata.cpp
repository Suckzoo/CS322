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
	wstring lang = L"�����õ����丶��Ÿ��Ʈ"; //You can define your own language set ��
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
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"Ÿ");
	m_pLabelToState[L"Ÿ"].get()->setFinal();

	//Connection goes here
	//test case: (��+)�丶Ÿ
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"��"].get(), [](wchar_t x) {return x == L'��'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(), [](wchar_t x) {return x == L'��'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(), [](wchar_t x) {return x == L'��'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(), [](wchar_t x) {return x == L'��'; }, DO_NOTHING);
	ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"Ÿ"].get(), [](wchar_t x) {return x == L'Ÿ'; }, DO_NOTHING);
}
#endif