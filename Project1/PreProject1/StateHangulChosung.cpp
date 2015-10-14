#include "State.hpp"
#ifdef __HANGUL2__
#include "Machine.hpp"
#include "Hangul.hpp"
#include "func.hpp"
#include <functional>
using namespace std;


/* Your langset goes here
* Usage: Just save your langset to variable 'lang'.
*/
void Machine::GenerateLanguageSet()
{
	// You can define your own language set 
	wstring lang = L"abcdefghijklmnopqrstuvwxyzQWERTOP\\";
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
	// Create essential state
	CreateState(L"initial");
	CreateState(L"dead");
	m_pCurrentState = getStateByLabel(L"initial");
	m_pInitialState = getStateByLabel(L"initial");
	m_pDeadState = getStateByLabel(L"dead");

	/* Example: Apple Grammar
	* This example shows simple DFA which allow L"apple" only.
	* init->a->ap->app->appl->apple / otherwise: dead
	*/

	// States goes here
	// example
	// CreateState(L"q1");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	CreateState(L"��");
	// set final
	// m_pLabelToState[L"q2"].get()->setFinal();

	// Connection goes here
	// with lambda
	// example
	// ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"q1"].get(), [](wchar_t x) {return x == L'a'; }, DO_NOTHING);

	//Normal Transition
	[this]() {
		ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"initial"].get(),
			predicate::isVowel, functional::addToMachine);
		ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonant, functional::addToMachine);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelDefault, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'h'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelOA, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'n'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelUE, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'm'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'l'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantKB, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L's'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'f'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDefault, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantKB, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L's'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'f'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDefault, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantKB, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L's'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'f'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDefault, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantKB, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L's'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'f'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDefault, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDoubler, functional::addToMachine);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDoubler, functional::addToMachine);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDoubler, functional::addToMachine);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantDoubler, functional::addToMachine);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L't'), functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantForN, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonantForR, functional::combineLetterChosungFirst);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelDefault, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelDefault, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelDefault, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isVowelDefault, functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'h'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'h'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'h'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'h'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'n'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'n'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'n'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'n'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'm'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'm'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'm'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			EQUAL(L'm'), functional::combineLetter);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			AND(NOT(EQUAL(L't')), predicate::isConsonant),
			functional::addToMachineWithResolve);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isNotConsonantForN, functional::addToMachineWithResolve);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isNotConsonantForR, functional::addToMachineWithResolve);
		ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
			predicate::isConsonant, functional::addToMachineWithResolve); }();
	//Delete Transition
	[this]()
		{
			ConnectState(m_pLabelToState[L"initial"].get(), m_pLabelToState[L"initial"].get(),
				predicate::isDelCharacter, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"initial"].get(),
				predicate::isDelCharacter, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelCharacter, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelCharacter, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelCharacter, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithSingleVowel, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithODouble, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithUDouble, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithEuDouble, functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithDefaultVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithOVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithUVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithEuVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithDefaultVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithOVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithUVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithEuVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithDefaultVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithOVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithUVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithEuVowel, functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithDefaultVowelSingleTerminalChosungFirst,
				functional::delFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithOVowelSingleTerminalChosungFirst,
				functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithUVowelSingleTerminalChosungFirst,
				functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithEuVowelSingleTerminalChosungFirst,
				functional::removeFromMachine);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithKTerminalChosungFirst,
				functional::resolveAndCombineLetterChosungFirst);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithNTerminalChosungFirst,
				functional::resolveAndCombineLetterChosungFirst);
			ConnectState(m_pLabelToState[L"��"].get(), m_pLabelToState[L"��"].get(),
				predicate::isDelWithRTerminalChosungFirst,
				functional::resolveAndCombineLetterChosungFirst);
		}();
}
#endif