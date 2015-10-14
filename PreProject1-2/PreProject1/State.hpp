#ifndef __STATE__
#define __STATE__

#include <functional>
using namespace std;
#define DO_NOTHING [](wstring*, wchar_t){}
typedef function<void(wstring*, wchar_t)> transit_func;

//Choose your testcase:

//Phase 1-1: Simple DFA Simulator
//#define __APPLE__
//#define __AUTOMATA__
#define __CLAIM__

//Phase 1-2: Simple Mealy Machine Simulator
//#define __CALC__

#endif