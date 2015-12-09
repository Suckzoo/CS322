#include "RegexConverter.hpp"
#include <cstdio>
#include <string>
#include <stack>
#include <utility>
#include <map>
#include <vector>
using namespace std;
struct Edge
{
	int v;
	wchar_t s;
};
struct Parseblock
{
	pair<int, int> p;
	int isClosure;
};
vector<Edge> edge[100000];
wchar_t stream[300];
map<int, int> paren;
wstring reg;
int vn = 1, mcnt = 0;;
void Parenthesize()
{
	stack<int> s;
	int i;
	for (i = 0; i < reg.length(); i++)
	{
		if (reg[i] == '(')
		{
			s.push(i);
		}
		else if (reg[i] == ')')
		{
			paren[s.top()]=i;
			paren[i] = s.top();
			s.pop();
		}
	}
}
pair<int, int> Parse(int s, int e)
{
	vector<int> parse_block;
	vector<Parseblock> res;
	int level = 0;
	int i;
	int sp;
	if (s == e)
	{
		int S = vn++;
		int E = vn++;
		Edge tmp;
		tmp.s = reg[s];
		tmp.v = E;
		edge[S].push_back(tmp);
		mcnt++;
		return pair<int, int>(S, E);
	}
	for (i = s; i <= e; i++)
	{
		if (reg[i] == L'(')
		{
			level++;
		}
		else if (reg[i] == L')')
		{
			level--;
		}
		else if (reg[i] == L'+' && level == 0)
		{
			parse_block.push_back(i);
		}
	}
	sp = s;
	Parseblock tmpBlock;
	if (parse_block.size() != 0)
	{
		for (i = 0; i < parse_block.size(); i++)
		{
			tmpBlock.p = Parse(sp, parse_block[i] - 1);
			tmpBlock.isClosure = 0;
			res.push_back(tmpBlock);
			sp = parse_block[i] + 1;
		}
		tmpBlock.p = Parse(sp, e);
		tmpBlock.isClosure = 0;
		res.push_back(tmpBlock);
		int S = vn++;
		int E = vn++;
		Edge tmp;
		for (i = 0; i < res.size(); i++)
		{
			tmp.v = res[i].p.first;
			tmp.s = L'*';
			edge[S].push_back(tmp);
			mcnt++;
			tmp.v = E;
			edge[res[i].p.second].push_back(tmp);
			mcnt++;
		}
		return pair<int, int>(S, E);
	}
	for (i = s; i <= e; i++)
	{
		if (reg[i] == L'(')
		{
			tmpBlock.p = Parse(i + 1, paren[i] - 1);
			if (paren[i] + 1 <= e)
			{
				if (reg[paren[i] + 1] == L'*')
				{
					tmpBlock.isClosure = 1;
					i = paren[i] + 1;
				}
				else
				{
					tmpBlock.isClosure = 0;
					i = paren[i];
				}
			}
			else
			{
				tmpBlock.isClosure = 0;
				i = paren[i];
			}
			res.push_back(tmpBlock);
		}
		else
		{
			tmpBlock.p = Parse(i, i);
			if (i + 1 <= e) {
				if (reg[i + 1] == L'*')
				{
					tmpBlock.isClosure = 1;
					i = i + 1;
				}
				else
				{
					tmpBlock.isClosure = 0;
				}
			}
			else
			{
				tmpBlock.isClosure = 0;
			}
			res.push_back(tmpBlock);
		}
	}
	int conS,conV;
	for (i = 0; i < res.size(); i++)
	{
		Edge tmp;
		if (res[i].isClosure)
		{
			tmp.v = res[i].p.first;
			tmp.s = L'*';
			edge[res[i].p.second].push_back(tmp);
			mcnt++;
			int S = vn++;
			int E = vn++;
			edge[S].push_back(tmp);
			mcnt++;
			tmp.v = E;
			edge[S].push_back(tmp);
			mcnt++;
			edge[res[i].p.second].push_back(tmp);
			mcnt++;
			if (i == 0)
			{
				conS = S;
				conV = E;
			}
			else
			{
				tmp.s = L'*';
				tmp.v = S;
				edge[conV].push_back(tmp);
				mcnt++;
				conV = E;
			}
		}
		else
		{
			if (i == 0)
			{
				conS = res[i].p.first;
				conV = res[i].p.second;
			}
			else
			{
				tmp.s = L'*';
				tmp.v = res[i].p.first;
				edge[conV].push_back(tmp);
				mcnt++;
				conV = res[i].p.second;
			}
		}
	}
	return pair<int, int>(conS, conV);
}
void ParseRegex(string input)
{
	FILE *in = fopen(input.c_str(), "rt");
	FILE *out = fopen("input.txt", "wt");
	//wprintf(L"Input vocabulary (except *):\n");
	fwscanf(in, L"%s", stream);
	fwprintf(out, L"%s\n", stream);
	//wprintf(L"Input regular expression:\n");
	fwscanf(in, L"%s", stream);
	reg = stream;
	Parenthesize();
	pair<int, int> pv = Parse(0, reg.length()-1);
	fwprintf(out, L"%d %d 1\n", vn - 1, mcnt);
	int i, j;
	for (i = 1; i < vn; i++)
	{
		for (j = 0; j < edge[i].size(); j++)
		{
			int S = i;
			int E = edge[i][j].v;
			if (S == pv.first)
			{
				S = 1;
			}
			else if (S == 1)
			{
				S = pv.first;
			}
			if (E == pv.first)
			{
				E = 1;
			}
			else if (E == 1)
			{
				E = pv.first;
			}
			if(edge[i][j].s==L'\\')
				fwprintf(out, L"%d %d %lc\n", S, E, L'*');
			else
				fwprintf(out, L"%d %d %lc\n", S, E, edge[i][j].s);
		}
	}
	fwprintf(out, L"%d\n%d\n", 1, pv.second);
	fclose(out);
}