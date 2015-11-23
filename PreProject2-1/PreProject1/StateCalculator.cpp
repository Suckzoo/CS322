#include "State.hpp"
#ifdef __CALC__
#include "func.hpp"
#include "Machine.hpp"
#include <functional>
#define NUM_CHECK [](wchar_t x) {return L'0' <= x && x <= L'9'; }
#define OPER_CHECK(_x,_y) [](wchar_t x){return x == (_x) || x == (_y); }
using namespace std;

//function with state
class closure_calc
{
private:
	static closure_calc* instance;
	closure_calc();
public:
	long long result, val;
	int mode;
	
	transit_func init_num;
	transit_func append_num;
	transit_func operator_input;
	transit_func after_operator;
	transit_func equal;
	static closure_calc* GetInstance();
};
closure_calc* closure_calc::instance = nullptr;
/* Your langset goes here
* Usage: Just save your langset to variable 'lang'.
*/

void Machine::GenerateLanguageSet()
{
	wstring lang = L"0123456789+-="; //You can define your own language set ¥Ò
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
	CreateState(L"Number");
	CreateState(L"Operator");
	CreateState(L"Equal");
	m_pLabelToState[L"Equal"].get()->setFinal();

	//Connection goes here
	ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"Number"].get(), NUM_CHECK, closure_calc::GetInstance()->init_num);
	ConnectState(m_pLabelToState[L"Number"].get(), m_pLabelToState[L"Number"].get(), NUM_CHECK, closure_calc::GetInstance()->append_num);
	ConnectState(m_pLabelToState[L"Number"].get(), m_pLabelToState[L"Operator"].get(), OPER_CHECK(L'+', L'-'), closure_calc::GetInstance()->operator_input);
	ConnectState(m_pLabelToState[L"Operator"].get(), m_pLabelToState[L"Number"].get(), NUM_CHECK, closure_calc::GetInstance()->after_operator);
	ConnectState(m_pLabelToState[L"Number"].get(), m_pLabelToState[L"Equal"].get(), OPER_CHECK(L'=', L'='), closure_calc::GetInstance()->equal);
	
}

closure_calc::closure_calc() {
	result = 0;
	val = 0;
	mode = 0;
	init_num = [this](wstring *wx, wchar_t vp)
	{
		val = (long long)(vp - L'0');
	};

	append_num = [this](wstring* wx, wchar_t vp)
	{
		val *= 10;
		val += (long long)(vp - L'0');
	};

	operator_input = [this](wstring* wx, wchar_t vp)
	{
		if (mode == 1)
		{
			result += val;
		}
		else if (mode == 2)
		{
			result -= val;
		}
		else
		{
			result = val;
		}
		val = 0;
		if (vp == L'+')
		{
			mode = 1;
		}
		else
		{
			mode = 2;
		}
	};

	after_operator = [this](wstring* wx, wchar_t vp)
	{
		val = (long long)(vp - L'0');
	};

	equal = [this](wstring *wx, wchar_t vp)
	{
		if (mode == 1)
		{
			result += val;
		}
		else if (mode == 2)
		{
			result -= val;
		}
		else
		{
			result = val;
		}
		while (result != 0)
		{
			wx->push_back(L'0' + (wchar_t)(result % 10));
			result /= 10;
		}
		reverse(wx->begin(), wx->end());
	};
}
closure_calc* closure_calc::GetInstance()
{
	if (!instance)
	{
		instance = new closure_calc();
	}
	return instance;
}

#endif