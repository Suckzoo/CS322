#ifndef __FUNC_HPP__
#define __FUNC_HPP__

#include <functional>
using namespace std;
#define DO_NOTHING [](wstring*, wchar_t){}
#define NOT(x) [](wstring* result, wchar_t param){return !((x)(result, param));}
#define AND(x,y) [](wstring* result, wchar_t param){return ((x)(result, param)) && ((y)(result, param));}
#define OR(x,y) [](wstring* result, wchar_t param){return ((x)(result, param)) || ((y)(result, param));}
#define EQUAL(x) [](wstring* result, wchar_t param){return param==(x);}

#define __CHOSUNG__
//#define __BATCHIM__

typedef function<void(wstring*, wchar_t)> transit_func;

void PushToStack(wstring* str, wchar_t x);
void FlushBuffer(wstring* str, wchar_t x);
void onDeleteKey(wstring* str, wchar_t x);
//namespace predicate
//{
//	bool isConsonant(wstring* result, wchar_t x);
//	bool isVowel(wstring* result, wchar_t x);
//	bool isDelCharacter(wstring* result, wchar_t x);
//	bool isVowelDefault(wstring* result, wchar_t x);
//	bool isVowelO(wstring* result, wchar_t x);
//	bool isVowelOA(wstring* result, wchar_t x);
//	bool isVowelUE(wstring* result, wchar_t x);
//	bool isConsonantKB(wstring* result, wchar_t x);
//	bool isConsonantForN(wstring* result, wchar_t x);
//	bool isConsonantForR(wstring* result, wchar_t x);
//	bool isNotConsonantKB(wstring* result, wchar_t x);
//	bool isNotConsonantForN(wstring* result, wchar_t x);
//	bool isNotConsonantForR(wstring* result, wchar_t x);
//	bool isConsonantDefault(wstring* result, wchar_t x);
//	bool isConsonantDoubler(wstring* result, wchar_t x);
//	bool isDelWithSingleVowel(wstring* result, wchar_t x);
//	bool isDelWithODouble(wstring* result, wchar_t x);
//	bool isDelWithUDouble(wstring* result, wchar_t x);
//	bool isDelWithEuDouble(wstring* result, wchar_t x);
//	bool isDelWithDefaultVowel(wstring* result, wchar_t x);
//	bool isDelWithOVowel(wstring* result, wchar_t x);
//	bool isDelWithUVowel(wstring* result, wchar_t x);
//	bool isDelWithEuVowel(wstring* result, wchar_t x);
//	bool isDelWithDefaultVowelSingleTerminal(wstring* result, wchar_t x);
//	bool isDelWithOVowelSingleTerminal(wstring* result, wchar_t x);
//	bool isDelWithUVowelSingleTerminal(wstring* result, wchar_t x);
//	bool isDelWithEuVowelSingleTerminal(wstring* result, wchar_t x);
//	bool isDelWithDefaultVowelSingleTerminalChosungFirst(wstring* result, wchar_t x);
//	bool isDelWithOVowelSingleTerminalChosungFirst(wstring* result, wchar_t x);
//	bool isDelWithUVowelSingleTerminalChosungFirst(wstring* result, wchar_t x);
//	bool isDelWithEuVowelSingleTerminalChosungFirst(wstring* result, wchar_t x);
//	bool isDelWithKTerminal(wstring* result, wchar_t x);
//	bool isDelWithNTerminal(wstring* result, wchar_t x);
//	bool isDelWithRTerminal(wstring* result, wchar_t x);
//	bool isDelWithKTerminalChosungFirst(wstring* result, wchar_t x);
//	bool isDelWithNTerminalChosungFirst(wstring* result, wchar_t x);
//	bool isDelWithRTerminalChosungFirst(wstring* result, wchar_t x);
//	
//};
//namespace functional
//{
//	void addToMachine(wstring* result, wchar_t x);
//	void addToMachineWithResolve(wstring* result, wchar_t x);
//	void removeFromMachine(wstring* result, wchar_t x);
//	void delFromMachine(wstring* result, wchar_t x);
//	void combineLetter(wstring* result, wchar_t x);
//	void resolveAndCombineLetter(wstring* result, wchar_t x);
//	void resolveAndCombineLetterChosungFirst(wstring* result, wchar_t x);
//	void combineLetterChosungFirst(wstring* result, wchar_t x);
//};

#endif