#ifndef __NFA__
#define __NFA__
#include "Machine.hpp"
#include "State.hpp"

class NFAMachine: Machine
{
public:
	struct NFAInstance
	{
		struct edge
		{
			wchar_t w;
			int v;
		};
		int n, m;
		wstring language;
		vector<edge> e[110];
		void PrintInformation();
	};
	NFAMachine();
	NFAMachine(string filename);
	void ImportFromFile(string filename);
protected:
	void GenerateLanguageSet();
	void CreateStateEdge();
private:
	NFAInstance *instance;
};

#endif