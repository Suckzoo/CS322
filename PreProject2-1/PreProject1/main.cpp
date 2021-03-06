#define MAX_LENGTH 200
#include <cstdio>
#include <string>
#include <locale>
#include "NFAMachine.hpp"
using namespace std;
wchar_t temp[MAX_LENGTH];
wstring input;
int main()
{
	locale::global(locale("Korean"));
	NFAMachine* m = new NFAMachine("input.txt");
	wscanf(L"%ls", temp);
	input = temp;
	if (!m->isValidPattern(input))
	{
		printf("Invalid pattern\n");
	}
	else
	{
		for (int i = 0; i < input.length(); i++)
		{
			m->StateTransition(input[i]);
		}
		if (m->isFinalState())
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}