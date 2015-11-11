#include "NFAMachine.hpp"
#include "MachineConverter.hpp"
#include "func.hpp"

NFAMachine::NFAMachine() : instance(nullptr)
{
}

NFAMachine::NFAMachine(string filename) : instance(nullptr)
{
	ImportFromFile(filename);
}

void NFAMachine::ImportFromFile(string filename)
{
	this->Reset();
	instance = new NFAInstance();
	wchar_t lang[50];
	int n, m;
	FILE *fi = fopen(filename.c_str(), "rt");
	fwscanf(fi, L"%ls", lang);
	instance->language = lang;
	this->GenerateLanguageSet();
	int k;
	fwscanf(fi, L"%d%d%d", &instance->n, &instance->m, &k);
	int i,j;
	wchar_t buf_raw[50];
	wstring buf;
	int x, y;
	for (i = 0; i < instance->m; i++)
	{
		fwscanf(fi, L"%d%d%ls", &x, &y, buf_raw);
		buf = buf_raw;
		for (j = 0; j < buf.length(); j++)
		{
			instance->edge[x][buf[j]].push_back(y);
		}
	}
	fwscanf(fi, L"%d", &instance->q0);
	int xx;
	for (i = 0; i < k; i++)
	{
		fwscanf(fi, L"%d", &xx);
		instance->accept.insert(xx);
	}
	NFAInstance* DFA = GetDFAFromNFA(*instance);
	wprintf(L"Report: DFA Conversion:\n");
	DFA->PrintInformation();
	NFAInstance* mDFA = MinimizeDFA(*DFA);
	wprintf(L"Report: DFA Minimization:\n");
	mDFA->PrintInformation();
	delete instance;
	delete DFA;
	instance = mDFA;
	this->CreateStateEdge();
}

void NFAMachine::GenerateLanguageSet()
{
	int i;
	for (i = 0; i < instance->language.length(); i++)
	{
		m_pLanguageSet.insert(instance->language[i]);
	}
}

void NFAMachine::CreateStateEdge()
{
	//TODO: from instance, create states and edges.
	int i, j, L;
	for (i = 1; i <= instance->n; i++)
	{
		wchar_t vertName[50];
		swprintf(vertName, L"q%d", i);
		CreateState(vertName);
		if (i == instance->q0)
		{
			m_pInitialState = getStateByLabel(vertName);
		}
		if (instance->accept.find(i) != instance->accept.end())
		{
			getStateByLabel(vertName)->setFinal();
		}
	}
	CreateState(L"Dead");
	m_pDeadState = getStateByLabel(L"Dead");
	m_pCurrentState = m_pInitialState;
	for (i = 1; i <= instance->n; i++)
	{
		for (L = 0; L < instance->language.length(); L++)
		{
			if (!instance->edge[i][instance->language[L]].empty())
			{
				wchar_t v1[50],v2[50];
				swprintf(v1, L"q%d", i);
				swprintf(v2, L"q%d", instance->edge[i][instance->language[L]][0]);
				ConnectState(m_pLabelToState[wstring(v1)].get(), m_pLabelToState[wstring(v2)].get(),
					[this, L](wstring *str, wchar_t x){return x==instance->language[L]; }, DO_NOTHING);
			}
		}
	}
}

void NFAMachine::NFAInstance::PrintInformation()
{
	//TODO: print what machine have
	wprintf(L"# of states: %d\n", n);
	wprintf(L"Vocabulary Set: %ls\n", language.c_str());
	wprintf(L"State Transition Function\n");
	int i, j, k;
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < language.length(); j++)
		{
			if (edge[i][language[j]].size() != 0)
			{
				for (k = 0; k < edge[i][language[j]].size(); k++)
				{
					wprintf(L"%d --%c--> %d\n", i, language[j], edge[i][language[j]][k]);
				}
			}
		}
	}
	wprintf(L"Starts at: 1\n");
	wprintf(L"Accept at:\n");
	for (auto it = accept.begin(); it != accept.end(); it++)
	{
		wprintf(L"%d ", *it);
	}
	wprintf(L"\n");
}