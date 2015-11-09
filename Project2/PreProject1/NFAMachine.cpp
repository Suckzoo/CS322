#include "NFAMachine.hpp"
#include "MachineConverter.hpp"

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
	fscanf(fi, "%d%d", &instance->n, &instance->m);
	int i;
	NFAInstance::edge tmp;
	wchar_t buf_raw[50];
	wstring buf;
	int x, y;
	for (i = 0; i < m; i++)
	{
		fwscanf(fi, L"%d%d%ls", &x, &y, buf);
		buf = buf_raw;
		tmp.v = y;
		for (i = 0; i < buf.length(); i++)
		{
			tmp.w = buf[i];
			instance->e[x].push_back(tmp);
		}
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

}

void NFAMachine::NFAInstance::PrintInformation()
{
	//TODO: print what machine have
	wprintf(L"# of states: %d\n", n);
	wprintf(L"Vocabulary Set: %ls\n", language.c_str());
	wprintf(L"State Transition Function\n");
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < e[i].size(); j++)
		{
			wprintf(L"%d --%c--> %d\n", i, e[i][j].w, e[i][j].v);
		}
	}
}