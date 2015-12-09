#include "MachineConverter.hpp"
#include <set>
#include <queue>
using namespace std;
typedef NFAMachine::NFAInstance Instance;
typedef map<wchar_t, vector<int>>* Adj;
int GetClosureNumber(set<int> s, vector<set<int>>& cV)
{
	int i;
	int N = cV.size();
	for (i = 1; i < N; i++)
	{
		if (s.size() != cV[i].size()) continue;
		auto j1 = s.begin();
		auto j2 = cV[i].begin();
		for (; j1 != s.end() && j2 != cV[i].end(); j1++, j2++)
		{
			if ((*j1) != (*j2))
			{
				break;
			}
		}
		if (j1 == s.end())
		{
			return i;
		}
	}
	return -1;
}
void GetEpsilonClosure(int v, Adj e, wstring l, set<int>& s)
{
	s.insert(v);
	for(int i=0;i<e[v][L'*'].size();i++)
	{
		if (s.find(e[v][L'*'][i]) == s.end())
		{
			GetEpsilonClosure(e[v][L'*'][i], e, l, s);
		}
	}
}
NFAMachine::NFAInstance* GetDFAFromNFA(NFAMachine::NFAInstance instance)
{
	vector<set<int>> closureVertex;
	closureVertex.clear();
	Adj e = instance.edge;
	int &n = instance.n;
	int &m = instance.m;
	wstring &language = instance.language;
	int l = language.length();
	int vCnt = 2, eCnt = 0;
	set<int> closure;
	closure.clear();
	GetEpsilonClosure(1, e, language, closure);
	closureVertex.push_back(set<int>());
	closureVertex.push_back(closure);
	queue<int> que;
	que.push(1);
	int head;
	int finale;
	NFAMachine::NFAInstance* result = new NFAMachine::NFAInstance();
	while (!que.empty())
	{
		head = que.front();
		que.pop();
		for (unsigned int L = 0; L < language.length(); L++){
			closure.clear();
			finale = 0;
			for (auto it = closureVertex[head].begin(); it != closureVertex[head].end(); it++)
			{
				for (int j = 0; j < e[(*it)][language[L]].size(); j++)
				{
					GetEpsilonClosure(e[(*it)][language[L]][j], e, language, closure);
				}
			}
			int vv = GetClosureNumber(closure, closureVertex);
			if (closure.size() == 0) continue;
			if (vv == -1)
			{
				result->edge[head][language[L]].push_back(vCnt);
				closureVertex.push_back(closure);
				que.push(vCnt);
				vCnt++;
				eCnt++;
			}
			else
			{
				result->edge[head][language[L]].push_back(vv);
				eCnt++;
			}
		}
	}
	result->accept.clear();
	for (int i = 1; i < vCnt; i++)
	{
		for (auto j = instance.accept.begin(); j != instance.accept.end(); j++)
		{
			if (closureVertex[i].find(*j) != closureVertex[i].end())
			{
				result->accept.insert(i);
			}
		}
	}
	result->q0 = 0;
	result->n = vCnt-1;
	result->m = eCnt;
	result->language = language;
	return result;
}
struct DisjointSet
{
	int group[110][2];
	int check[110];
	int gr[110];
	int N;
	DisjointSet(int n)
	{
		int i;
		N = n;
		for (i = 1; i <= n; i++)
		{
			gr[i] = 0;
			group[i][0] = i;
			group[i][1] = 1;
			check[i] = 0;
		}
	}
	int Find(int x)
	{
		if (x == group[x][0]) return x;
		return group[x][0] = Find(group[x][0]);
	}
	void Union(int x, int y)
	{
		int px = Find(x);
		int py = Find(y);
		if (px == py) return;
		if (group[px][1] > group[py][1])
		{
			group[py][0] = px;
		}
		else if (group[py][1] > group[px][1])
		{
			group[px][0] = py;
		}
		else
		{
			group[py][0] = px;
			group[px][1]++;
		}
	}
	void MakeGroup()
	{
		int i;
		int cnt = 1;
		for (i = 1; i <= N; i++)
		{
			int pr = Find(i);
			if (gr[pr] == 0)
			{
				gr[pr] = cnt++;
				gr[i] = gr[pr];
			}
			else
			{
				gr[i] = gr[pr];
			}
		}
	}
	int isChecked(int x)
	{
		return check[x];
	}
	int GetGroupNumber(int x)
	{
		return gr[x];
	}
	void Check(int x)
	{
		check[x] = 1;
	}
};
NFAMachine::NFAInstance* MinimizeDFA(NFAMachine::NFAInstance instance)
{
	int i,j,L; 
	int n = instance.n;
	wstring& lang = instance.language;
	DisjointSet ds(n);
	bool unionRocks = true;
	while (unionRocks)
	{
		unionRocks = false;
		for (i = 1; i <= n; i++)
		{
			for (j = i + 1; j <= n; j++)
			{
				int pi = ds.Find(i);
				int pj = ds.Find(j);
				if (pi == pj) continue;
				if ((instance.accept.find(pi) == instance.accept.end() &&
					instance.accept.find(pj) == instance.accept.end()) ||
					(instance.accept.find(pi) != instance.accept.end() &&
					instance.accept.find(pj) != instance.accept.end()))
				{
					for (L = 0; L < lang.length(); L++)
					{
						if (!instance.edge[pi][lang[L]].size() && instance.edge[pj][lang[L]].size()) break;
						if (instance.edge[pi][lang[L]].size() && !instance.edge[pj][lang[L]].size()) break;
						if (!instance.edge[pi][lang[L]].size() && !instance.edge[pj][lang[L]].size()) continue;
						if (ds.Find(instance.edge[pi][lang[L]][0]) != ds.Find(instance.edge[pj][lang[L]][0]))
						{
							break;
						}
					}
					if (L == lang.length())
					{
						ds.Union(i, j);
						unionRocks = true;
					}
				}
			}
		}
	}
	ds.MakeGroup();
	NFAMachine::NFAInstance* result = new NFAMachine::NFAInstance();
	int vCnt = 1;
	int eCnt = 0;
	int vv;
	for (i = 1; i <= n; i++)
	{
		if (!ds.isChecked(ds.Find(i)))
		{
			ds.Check(ds.Find(i));
			vCnt++;
			vv = ds.GetGroupNumber(i);
			if (instance.accept.find(i) != instance.accept.end())
			{
				result->accept.insert(vv);
			}
			for (L = 0; L < lang.length(); L++)
			{
				if (instance.edge[i][lang[L]].empty())
				{
					continue;
				}
				else
				{
					int gv = ds.GetGroupNumber(instance.edge[i][lang[L]][0]);
					result->edge[vv][lang[L]].push_back(gv);
					eCnt++;
				}
			}
		}
	}
	result->n = vCnt-1;
	result->m = eCnt;
	result->language = lang;
	result->q0 = 1;
	return result;
}