#ifndef __MACHINE__
#define __MACHINE__
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <utility>
#include <functional>

using namespace std;

class Edge;
class State
{
private:
	bool m_isFinalState;
	wstring m_Label;
public:
	State();
	vector<Edge*> m_Edge;
	bool isFinal();
	void setFinal();
	void setLabel(wstring label);
	operator wstring() const;
};

class Edge
{
public:
	function<bool(wstring*, wchar_t)> m_CheckFunction;
	function<void(wstring*, wchar_t)> m_TransitFunction;
	shared_ptr<State> m_NextState;
};

class Machine
{
protected:
	shared_ptr<State> m_pInitialState;
	shared_ptr<State> m_pCurrentState;
	shared_ptr<State> m_pDeadState;
	set<wchar_t> m_pLanguageSet;
	map<wstring, shared_ptr<State>> m_pLabelToState;
	wstring m_pMachineResult;
	void GenerateLanguageSet();
	void CreateStateEdge();
	void ConnectState(State* s1, State* s2, 
		function<bool(wstring*, wchar_t)> checker, 
		function<void(wstring*, wchar_t)> transit);
	void CreateState(wstring label, bool isFinal = false);
public:
	Machine();
	void StateTransition(wchar_t x);
	bool isValidPattern(wstring);
	bool isFinalState();
	bool isDeadState();
	void PrintMachineResult();
	void Reset();
	shared_ptr<State> getStateByLabel(wstring label);
};
#endif