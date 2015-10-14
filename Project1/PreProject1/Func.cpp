#include "State.hpp"
#include "Hangul.hpp"
#include "func.hpp"
#include <string>
using namespace std;

wstring J = L"qwertasdfgzxcvQWERT";
wstring Jkor = L"ぁあいぇえぉけげこさざしじすずせぜそぞ";
wstring M = L"yuiophjklbnmOP";
wstring doubleM = L"とどなねのはひ";

#ifdef __HANGUL1__
bool predicate::isConsonant(wstring* result, wchar_t x)
{
	return J.find(x) != wstring::npos;
}
bool predicate::isVowel(wstring* result, wchar_t x)
{
	return M.find(x) != wstring::npos;
}
bool predicate::isDelCharacter(wstring* result, wchar_t x)
{
	return x == DEL;
}
bool predicate::isVowelDefault(wstring* result, wchar_t x)
{
	return x != L'h' && x != L'n' && x != L'm' && isVowel(result, x);
}
bool predicate::isVowelOA(wstring* result, wchar_t x)
{
	return x == L'k' || x == L'o' || x == L'l';
}
bool predicate::isVowelUE(wstring* result, wchar_t x)
{
	return x == L'j' || x == L'p' || x == 'l';
}
bool predicate::isConsonantKB(wstring* result, wchar_t x)
{
	return x == L'r' || x == L'q';
}
bool predicate::isConsonantForN(wstring* result, wchar_t x)
{
	return x == L'w' || x == L'g';
}
bool predicate::isConsonantForR(wstring* result, wchar_t x)
{
	return x == L'r' || x == L'a' || x == L'q' || x == L't' ||
		x == L'x' || x == L'v' || x == L'g';
}
bool predicate::isNotConsonantKB(wstring* result, wchar_t x)
{
	return x != L'r' && x != L'q' && isConsonant(result, x);
}
bool predicate::isNotConsonantForN(wstring* result, wchar_t x)
{
	return x != L'w' && x != L'g' && isConsonant(result, x);
}
bool predicate::isNotConsonantForR(wstring* result, wchar_t x)
{
	return x != L'r' && x != L'a' && x != L'q' && x != L't' &&
		x != L'x' && x != L'v' && x != L'g' && 
		isConsonant(result, x);
}
bool predicate::isConsonantDefault(wstring* result, wchar_t x)
{
	return isConsonant(result, x) && x != L'r' && x != L'q' &&
		x != L'f' && x != L's' && x != L'E' && x != L'W' && x != L'Q';
}
bool predicate::isConsonantDoubler(wstring* result, wchar_t x)
{
	return x == L'E' || x == L'W' || x == L'Q';
}
bool predicate::isDelWithSingleVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return doubleM.find(moeum) == wstring::npos && x == DEL;
}
bool predicate::isDelWithODouble(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return (moeum == L'と' || moeum == L'ど' || moeum == L'な') && x == DEL;
}
bool predicate::isDelWithUDouble(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return (moeum == L'ね' || moeum == L'の' || moeum == L'は') && x == DEL;
}
bool predicate::isDelWithEuDouble(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'ひ' && x == DEL;
}
bool predicate::isDelWithDefaultVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum != L'で' && moeum != L'ぬ' && moeum != L'ぱ' && x == DEL;
}
bool predicate::isDelWithOVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum = L'で' && x == DEL;
}
bool predicate::isDelWithUVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum = L'ぬ' && x == DEL;
}
bool predicate::isDelWithEuVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum = L'ぱ' && x == DEL;
}
bool predicate::isDelWithDefaultVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum != L'で' && moeum != L'ぬ' && moeum != L'ぱ'
		&& term == 0 && x == DEL;
}
bool predicate::isDelWithOVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'で' && term == 0 && x == DEL;
}
bool predicate::isDelWithUVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'ぬ' && term == 0 && x == DEL;
}
bool predicate::isDelWithEuVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'ぱ' && term == 0 && x == DEL;
}
bool predicate::isDelWithKTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'ぁ' && x == DEL;
}
bool predicate::isDelWithNTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'い' && x == DEL;
}
bool predicate::isDelWithRTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'ぉ' && x == DEL;
}
void functional::addToMachine(wstring* result, wchar_t x)
{
	result->push_back(AndromedaToKorean(x));
}
void functional::removeFromMachine(wstring* result, wchar_t x)
{
	if (result->size() == 0) return;
	result->pop_back();
}
void functional::delFromMachine(wstring* result, wchar_t x)
{
	wchar_t D = JamoCombiner::combine((*result)[result->size() - 1], DEL);
	(*result)[result->size() - 1] = D;
}
void functional::combineLetter(wstring* result, wchar_t x)
{
	wchar_t D = JamoCombiner::combine((*result)[result->size() - 1],
									AndromedaToKorean(x));
	(*result)[result->size() - 1] = D;
}
void functional::resolveAndCombineLetter(wstring* result, wchar_t x)
{
	wchar_t newInit = JamoCombiner::resolveFinalSingle((*result)[result->size() - 1]);
	wchar_t D = JamoCombiner::combine((*result)[result->size() - 1], DEL);
	(*result)[result->size() - 1] = D;
	result->push_back(JamoCombiner::combine(newInit, AndromedaToKorean(x)));
}

#endif
#ifdef __HANGUL2__
bool predicate::isConsonant(wstring* result, wchar_t x)
{
	return J.find(x) != wstring::npos;
}
bool predicate::isVowel(wstring* result, wchar_t x)
{
	return M.find(x) != wstring::npos;
}
bool predicate::isDelCharacter(wstring* result, wchar_t x)
{
	return x == DEL;
}
bool predicate::isVowelDefault(wstring* result, wchar_t x)
{
	return x != L'h' && x != L'n' && x != L'm' && isVowel(result, x);
}
bool predicate::isVowelOA(wstring* result, wchar_t x)
{
	return x == L'k' || x == L'o' || x == L'l';
}
bool predicate::isVowelUE(wstring* result, wchar_t x)
{
	return x == L'j' || x == L'p' || x == 'l';
}
bool predicate::isConsonantKB(wstring* result, wchar_t x)
{
	return x == L'r' || x == L'q';
}
bool predicate::isConsonantForN(wstring* result, wchar_t x)
{
	return x == L'w' || x == L'g';
}
bool predicate::isConsonantForR(wstring* result, wchar_t x)
{
	return x == L'r' || x == L'a' || x == L'q' || x == L't' ||
		x == L'x' || x == L'v' || x == L'g';
}
bool predicate::isNotConsonantKB(wstring* result, wchar_t x)
{
	return x != L'r' && x != L'q' && isConsonant(result, x);
}
bool predicate::isNotConsonantForN(wstring* result, wchar_t x)
{
	return x != L'w' && x != L'g' && isConsonant(result, x);
}
bool predicate::isNotConsonantForR(wstring* result, wchar_t x)
{
	return x != L'r' && x != L'a' && x != L'q' && x != L't' &&
		x != L'x' && x != L'v' && x != L'g' &&
		isConsonant(result, x);
}
bool predicate::isConsonantDefault(wstring* result, wchar_t x)
{
	return isConsonant(result, x) && x != L'r' && x != L'q' &&
		x != L'f' && x != L's' && x != L'E' && x != L'W' && x != L'Q';
}
bool predicate::isConsonantDoubler(wstring* result, wchar_t x)
{
	return x == L'E' || x == L'W' || x == L'Q';
}
bool predicate::isDelWithSingleVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return doubleM.find(moeum) == wstring::npos && x == DEL;
}
bool predicate::isDelWithODouble(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return (moeum == L'と' || moeum == L'ど' || moeum == L'な') && x == DEL;
}
bool predicate::isDelWithUDouble(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return (moeum == L'ね' || moeum == L'の' || moeum == L'は') && x == DEL;
}
bool predicate::isDelWithEuDouble(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'ひ' && x == DEL;
}
bool predicate::isDelWithDefaultVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum != L'で' && moeum != L'ぬ' && moeum != L'ぱ' && x == DEL;
}
bool predicate::isDelWithOVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum = L'で' && x == DEL;
}
bool predicate::isDelWithUVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum = L'ぬ' && x == DEL;
}
bool predicate::isDelWithEuVowel(wstring* result, wchar_t x)
{
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum = L'ぱ' && x == DEL;
}
bool predicate::isDelWithDefaultVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum != L'で' && moeum != L'ぬ' && moeum != L'ぱ'
		&& term == 0 && x == DEL;
}
bool predicate::isDelWithOVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'で' && term == 0 && x == DEL;
}
bool predicate::isDelWithUVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'ぬ' && term == 0 && x == DEL;
}
bool predicate::isDelWithEuVowelSingleTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 1]);
	return moeum == L'ぱ' && term == 0 && x == DEL;
}
bool predicate::isDelWithDefaultVowelSingleTerminalChosungFirst
	(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 2]);
	return moeum != L'で' && moeum != L'ぬ' && moeum != L'ぱ'
		&& term == 0 && x == DEL;
}
bool predicate::isDelWithOVowelSingleTerminalChosungFirst
	(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 2]);
	return moeum == L'で' && term == 0 && x == DEL;
}
bool predicate::isDelWithUVowelSingleTerminalChosungFirst
	(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 2]);
	return moeum == L'ぬ' && term == 0 && x == DEL;
}
bool predicate::isDelWithEuVowelSingleTerminalChosungFirst
	(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	wchar_t moeum = JamoCombiner::resolveMiddle((*result)[result->size() - 2]);
	return moeum == L'ぱ' && term == 0 && x == DEL;
}
bool predicate::isDelWithKTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'ぁ' && x == DEL;
}
bool predicate::isDelWithNTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'い' && x == DEL;
}
bool predicate::isDelWithRTerminal(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 1];
	term = JamoCombiner::combine(term, DEL);
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'ぉ' && x == DEL;
}
bool predicate::isDelWithKTerminalChosungFirst(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'ぁ' && x == DEL;
}
bool predicate::isDelWithNTerminalChosungFirst(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'い' && x == DEL;
}
bool predicate::isDelWithRTerminalChosungFirst(wstring* result, wchar_t x)
{
	wchar_t term = (*result)[result->size() - 2];
	term = JamoCombiner::resolveFinalSingle(term);
	return term == L'ぉ' && x == DEL;
}
void functional::addToMachine(wstring* result, wchar_t x)
{
	result->push_back(AndromedaToKorean(x));
}
void functional::removeFromMachine(wstring* result, wchar_t x)
{
	if (result->size() == 0) return;
	result->pop_back();
}
void functional::delFromMachine(wstring* result, wchar_t x)
{
	wchar_t D = JamoCombiner::combine((*result)[result->size() - 1], DEL);
	(*result)[result->size() - 1] = D;
}
void functional::combineLetter(wstring* result, wchar_t x)
{
	wchar_t D = JamoCombiner::combine((*result)[result->size() - 1],
		AndromedaToKorean(x));
	(*result)[result->size() - 1] = D;
}
void functional::combineLetterChosungFirst(wstring* result, wchar_t x)
{
	wchar_t D = (*result)[result->size() - 1];
	if (Jkor.find(D) != wstring::npos)
	{
		(*result)[result->size() - 2]
			= JamoCombiner::combine((*result)[result->size() - 2], D);
		(*result)[result->size() - 1] = AndromedaToKorean(x);
	}
	else
	{
		result->push_back(AndromedaToKorean(x));
	}
}
void functional::resolveAndCombineLetter(wstring* result, wchar_t x)
{
	wchar_t newInit = JamoCombiner::resolveFinalSingle((*result)[result->size() - 1]);
	wchar_t D = JamoCombiner::combine((*result)[result->size() - 1], DEL);
	(*result)[result->size() - 1] = D;
	result->push_back(JamoCombiner::combine(newInit, AndromedaToKorean(x)));
}
void functional::addToMachineWithResolve(wstring* result, wchar_t x)
{
	wchar_t D = JamoCombiner::combine(result->at(result->size() - 2),
									result->at(result->size() - 1));
	(*result)[result->size() - 2] = D;
	(*result)[result->size() - 1] = AndromedaToKorean(x);
}
void functional::resolveAndCombineLetterChosungFirst(wstring* result, wchar_t x)
{
	wchar_t endSound = JamoCombiner::resolveFinal(result->at(result->size() - 2));
	wchar_t D = JamoCombiner::combine(result->at(result->size() - 2), DEL);
	(*result)[result->size() - 2] = D;
	(*result)[result->size() - 1] = endSound;
}
#endif