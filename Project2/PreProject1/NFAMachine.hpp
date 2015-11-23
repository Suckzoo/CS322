#ifndef __NFA__
#define __NFA__
#include "Machine.hpp"
#include "State.hpp"

class NFAMachine: public Machine
{
public:
	struct NFAInstance
	{
		map<wchar_t, vector<int>> edge[110];
		int n, m;
		int q0;
		set<int> accept;
		wstring language;
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